# FUSE (Filesystem in Userspace)

## The problem FUSE solves

Implementing a file system traditionally means writing kernel code. That has a lot of downsides: kernel programming is harder (no easy debugging, restricted libraries, every bug is a system crash), it requires root and module loading, your code must be relicensed under GPL to ship in mainline, and bugs in your file system can corrupt arbitrary kernel memory. Worse, lots of "file systems" you might want to build aren't really file systems in the traditional sense — they're adapters that *present* something as files. Mounting an S3 bucket, exposing a remote SSH host as a directory tree, or making an encrypted view of another directory — none of these benefit from being in the kernel, and all of them suffer from being there.

FUSE inverts the model: the kernel-side file system is a thin generic shim, and the actual logic runs as a normal userspace process.

## How it works

FUSE consists of two pieces. The first is a kernel module (`fuse.ko`) that registers with the VFS as a regular file system type — when you mount something as type `fuse`, the kernel sees it as just another file system and routes all VFS operations on that mount to the FUSE module. The second is a character device, `/dev/fuse`, which acts as the communication channel between the kernel module and userspace.

When you mount a FUSE file system, a userspace daemon opens `/dev/fuse` and passes the resulting file descriptor to the `mount(2)` syscall. From that point on, the dance looks like this: an application (say, `cat`) calls `read()` on a file inside the FUSE mount → kernel routes through VFS → VFS dispatches to the FUSE kernel module's `read` operation → the FUSE module packages up the request as a message and writes it to the `/dev/fuse` channel → the userspace daemon reads the message, does whatever it wants (fetch from S3, decrypt something, generate data on the fly), and writes the response back to `/dev/fuse` → the FUSE kernel module unpacks the response and returns it up through the VFS to `cat`. Two context switches and two copies per operation, in the worst case.

In practice, you don't write all of this protocol handling yourself. You link against **libfuse** (or use bindings in Rust, Go, Python, etc.), implement a set of callbacks — `getattr`, `readdir`, `open`, `read`, `write`, `unlink`, `rename`, and so on, mirroring the VFS operations — and libfuse runs the event loop, parses kernel messages, and calls your callbacks. There are two API flavors: the **high-level API**, which works in terms of paths (similar to how POSIX syscalls look from userspace), and the **low-level API**, which works in terms of inodes and is closer to what the kernel actually sends. The low-level API is harder to use but necessary for performance and for file systems where path-to-inode resolution is expensive.

## Trade-offs

The cost is performance. Every operation that would otherwise be a quick kernel function call now involves crossing the kernel/user boundary twice and copying data through a pipe-like channel. For metadata-heavy workloads (lots of small files, lots of `stat`s), FUSE can be many times slower than a native file system. Modern FUSE has improved this considerably with features like writeback caching, kernel-side attribute and dentry caches with configurable TTLs, splice-based zero-copy data transfer, and (recently) multi-threaded request dispatch and even an experimental in-kernel passthrough mode. But there is still a structural overhead.

The benefits are everything else: you write normal userspace code, you can use any library or language, you can crash without taking the kernel with you, you don't need to be root to develop (mounting still requires privileges or `user_allow_other`), and you can build file systems that would be nearly impossible to put in the kernel — ones that talk to network services, embed Python interpreters, do machine learning on access patterns, whatever.

## Examples of FUSE-based applications

**`sshfs`** is the canonical example. You run `sshfs user@host:/path /mnt/remote` and now `/mnt/remote` shows the remote directory tree as if it were local. Behind the scenes, every `read`/`stat`/`readdir` is translated into the corresponding SFTP request over the SSH connection. Slow over a high-latency link, but extraordinarily convenient.

**`s3fs-fuse`**, **`goofys`**, and **`rclone mount`** expose cloud object stores (S3, GCS, Azure Blob, etc.) as file systems. This lets tools that only understand POSIX paths read and write to cloud storage. The trade-offs are real and worth knowing — object stores don't have a notion of partial writes or true directories, so these file systems fake it, and operations like "rename a directory with 10,000 files" become 10,000 individual API calls.

**`gocryptfs`** and **`encfs`** provide encrypted overlays. You point them at a directory of encrypted files, give them a passphrase, and they present a decrypted view at a mount point. Only the mounted view shows plaintext; the underlying directory remains encrypted on disk and can be safely synced to Dropbox, etc.

**`borgfs`** lets you mount a Borg backup repository as a read-only file system, so you can browse and `cp` files out of a backup snapshot without running an explicit restore command. **`archivemount`** does the same for tar/zip/etc., letting you treat an archive as a directory.

**`ntfs-3g`** is the standard read/write driver for NTFS on Linux and lives in userspace via FUSE for licensing and complexity reasons. **`mergerfs`** unions multiple directories into one (popular for home media servers — pool several disks into a single namespace without RAID). **`bindfs`** remaps ownership and permissions of an existing directory.

**`gitfs`** mounts a git repository so that every commit appears as a directory and every file at every revision is browsable as a regular file. **`squashfuse`** mounts squashfs images without root. **`AppImage`** internally uses libfuse to mount its own contents at runtime. Even **WSL1** used a FUSE-like mechanism to present the Windows file system to Linux processes (though WSL2 went a different route with a real VM).

The common thread: FUSE is the right answer whenever the "file system" is really a presentation layer over something else.

# io_uring

## What problem io_uring solves

To understand io_uring you have to understand what was wrong with the alternatives. Linux had three ways to do I/O before io_uring, and all of them had serious problems for high-performance applications.

**Synchronous syscalls** (`read`, `write`, `pread`, etc.) block the calling thread until the operation completes. If you want concurrency you need many threads, which is expensive in memory and context-switching overhead, and even with threads each individual operation pays the full cost of a syscall — and post-Spectre/Meltdown, syscall overhead got significantly worse because of KPTI and related mitigations.

**Non-blocking I/O with `epoll`** works beautifully for sockets but is essentially useless for regular files. The reason is that on Linux, regular files are always considered "ready" for reading from epoll's perspective — the kernel can't easily know whether a `read` will hit the page cache (instant) or trigger disk I/O (slow), so it just says "go ahead" and your `read` blocks anyway. So epoll isn't a real async file I/O solution.

**Linux AIO** (`io_submit`/`io_getevents`) was the kernel's previous attempt at async file I/O, and it's notorious. It only really works with `O_DIRECT` (bypassing the page cache), it can silently fall back to blocking behavior in many cases, the API is awkward, and it doesn't cover most operations — you can submit reads and writes but not `open`, `fsync`, `accept`, etc. Linus Torvalds himself has called it a disaster. Most applications avoided it.

So before io_uring, if you wanted to do millions of I/Os per second, you typically built a thread pool and ate the syscall overhead, or you used `O_DIRECT` + AIO and dealt with its limitations, or you used something exotic like SPDK that bypasses the kernel entirely.

## The core idea

io_uring, introduced by Jens Axboe in kernel 5.1 (2019), is built around two ring buffers shared between the application and the kernel via `mmap`: a **submission queue (SQ)** that userspace writes into, and a **completion queue (CQ)** that the kernel writes into. To start an operation, userspace fills out a submission queue entry (SQE) describing what to do — opcode, fd, buffer pointer, offset, flags — and advances the SQ tail. To collect results, userspace reads completion queue entries (CQEs) from the CQ head.

The crucial property is that *no syscall is needed in the steady state*. Both rings are in shared memory; the application just writes and reads. To actually wake the kernel up to process new submissions, you call `io_uring_enter`, but this can be batched (submit 1000 operations, one syscall), and with **SQ polling mode** the kernel runs a kernel thread that polls the submission queue, eliminating even that syscall — at the cost of burning a CPU. So the syscall overhead per I/O drops from "one syscall per op" to "one syscall per N ops" or even "zero syscalls per op", which is enormous when you're targeting millions of ops/sec.

The completion side has a similar property: completions appear in the CQ as the kernel finishes them, and you can either poll the CQ (zero syscalls) or call `io_uring_enter` with a `min_complete` argument to wait for some number of them.

## Beyond just files

A second major property of io_uring that distinguishes it from older AIO: it covers essentially everything. Reads and writes, yes, but also `openat`, `close`, `fsync`, `fallocate`, `statx`, `accept`, `connect`, `send`/`recv`, `sendmsg`/`recvmsg`, `poll`, `splice`, `mkdir`, `rename`, `unlink`, timeouts, cancellations — and more keep getting added. This means a server can do *all* its I/O — networking, disk, filesystem operations — through one unified asynchronous interface, with one event loop, no thread pool.

It also supports **linked operations**: you can chain SQEs so that the second runs only after the first completes successfully. This lets you express small dependency graphs (e.g. "open this file, then read the first 4KB, then close it") as a single batched submission, with the kernel handling sequencing internally.

## Performance features worth knowing

**Registered buffers and registered file descriptors** let you tell the kernel ahead of time about a set of buffers or fds you'll use repeatedly. The kernel pre-pins the buffer pages and pre-resolves the fds, so subsequent operations skip that per-op work. For a high-throughput server doing the same I/O over and over against the same fds, this is a substantial speedup.

**Fixed/direct descriptors** let io_uring open files into a slot in its own table rather than the process's main fd table, which is faster and avoids fd-table contention.

**Multi-shot operations**, like multi-shot accept or multi-shot recv, post one SQE and get many CQEs — every accepted connection or every received message generates a completion without resubmission. Great for accept loops and for receiving streams.

**`IORING_OP_SEND_ZC` and zero-copy support**: for very large transfers, io_uring can send data directly from user pages without copying through the kernel.

When you combine all of this — shared-memory ring, batched syscalls or no syscalls, registered buffers, multi-shot, zero-copy — you get an API that on serious workloads is substantially faster than epoll + threads, and qualitatively more capable than legacy AIO.

## Drawbacks and current state

io_uring is harder to use correctly than `read`/`write`. Lifetime management is tricky: when you submit a buffer for an async write, you cannot touch or free that buffer until the matching CQE arrives. Cancellation has subtle semantics. Error handling is per-CQE. Most people don't write to it directly — they use **liburing**, which provides helpers that smooth a lot of this out, or they use language runtimes built on top of it.

Security has been a recurring topic. Because io_uring can express almost any I/O the kernel supports, it has a wide attack surface, and there have been a number of CVEs. Some hardened environments (Google's ChromeOS, Android's seccomp policies, some container runtimes) disable it by default.

It is, however, the clear future of high-performance I/O on Linux. Database engines (ScyllaDB was an early adopter, PostgreSQL has been adding io_uring support), proxies, and runtimes like Rust's `tokio-uring` and `glommio` are all built on it. If you're writing a new system that needs to push the I/O envelope, io_uring is now the default choice rather than threads + blocking syscalls or libaio.

If you'd like, I can go deeper into the actual SQE/CQE data structures and walk through what a small liburing program looks like end to end, or I can compare io_uring to epoll for a network server specifically.
