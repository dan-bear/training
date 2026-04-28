Three excellent questions. Let me take them one at a time.

## 1. Does a filesystem register its `open` as the syscall handler?

**Not quite — and the distinction is important.** The syscall handler for `open` is a single, fixed function in the kernel (`do_sys_openat2` and friends). Filesystems don't replace it. What they do is plug into a layer *below* it called the **VFS — the Virtual File System**.

Here's the layering:

```
user space:          open("/mnt/data/foo", O_RDONLY)
                              │
kernel syscall entry:         │
sys_openat ──► do_sys_openat2 ──► (generic open logic:
                                    permission checks,
                                    fd allocation,
                                    path walking)
                              │
VFS layer:                    │  ← uniform interface
                              │     (struct inode_operations,
                              │      struct file_operations)
                              │
filesystem driver:        ext4 / btrfs / xfs / nfs / fuse / …
                              │
block layer / network:        │
                              ▼
                          actual storage
```

The kernel's generic `open` code does all the parts that are filesystem-independent: parsing the path, checking the process's permissions, allocating a file descriptor in your process's fd table, etc. But when it needs to actually look up `"foo"` inside `/mnt/data/`, it has to ask whoever owns that directory — and that's the filesystem.

The way filesystems "register" themselves is by providing **operation tables** — structs full of function pointers. Each inode in memory has a pointer to a `struct inode_operations` (with members like `.lookup`, `.create`, `.unlink`, …), and each open file has a pointer to a `struct file_operations` (with `.read`, `.write`, `.llseek`, `.mmap`, …). When a filesystem is mounted, the VFS sets up the in-memory inodes for that mount point with the filesystem's specific operation tables. So when generic open code calls `inode->i_op->lookup(...)`, on an ext4 mount that dispatches to `ext4_lookup`; on btrfs it dispatches to `btrfs_lookup`; on a FUSE mount it goes out to a userspace daemon.

So your intuition is right in spirit — different filesystems *do* have different implementations of the per-file operations — but the wiring is one level deeper than the syscall table. The syscall handler is shared; the *per-filesystem callbacks it invokes* are what differ. This is essentially polymorphism implemented in C: the syscall handler is the abstract caller, the operation structs are the vtables, and each filesystem is a concrete subclass.

This same pattern is why `read()` works uniformly on a regular file, a pipe, a socket, a `/proc` entry, and `/dev/null` — each of those has its own `file_operations` with a different `.read`.

## 2. The syscall instruction and the user→kernel transition

Let me describe what the `syscall` instruction actually does on x86-64 (other architectures have analogous instructions: `svc` on ARM64, `ecall` on RISC-V; the principle is the same).

**The CPU has privilege levels.** On x86, these are called **rings**. Ring 0 is kernel mode — full access to all instructions and all memory. Ring 3 is user mode — restricted; many instructions trap if you try to execute them, and you can only access pages marked accessible to user mode. Each page table entry has a "user/supervisor" bit that controls this.

**At boot, the kernel pre-arms the CPU** for syscalls by writing a few special registers called Model-Specific Registers (MSRs):
- `LSTAR` — the address the CPU should jump to when a `syscall` instruction executes.
- `STAR` — the code/data segment selectors to load for kernel mode.
- `SFMASK` — flags to clear on entry (e.g., disable interrupts during the transition window).

So the kernel has essentially told the CPU, *"if anyone in user mode executes `syscall`, jump here, switch to ring 0."*

**What `syscall` actually does, atomically, in microcode:**

1. Saves the user-mode instruction pointer (`RIP`) into `RCX` and the user flags (`RFLAGS`) into `R11`. This is how the CPU remembers where to come back to.
2. Loads `RIP` from `LSTAR` — i.e., jumps to the kernel entry point.
3. Switches the code segment to the kernel one (effectively flipping to ring 0).
4. Applies the flag mask from `SFMASK`.

Critically, **this all happens with a single instruction**, so there's no window where user code can hijack a half-switched state.

**On entry, the kernel still has work to do.** The CPU has switched privilege, but it hasn't switched stacks or address spaces — those are software's responsibility. The kernel entry stub:

1. Switches to a per-CPU **kernel stack** (the user stack pointer is untrusted; the kernel keeps its own).
2. Saves all the user-mode registers onto the kernel stack so they can be restored on return.
3. Reads the syscall number from `RAX` and the arguments from `RDI, RSI, RDX, R10, R8, R9` (the Linux x86-64 syscall ABI — slightly different from the regular function-call ABI).
4. With Meltdown/KPTI mitigations enabled on vulnerable CPUs, swaps to the kernel page tables (the `swapgs` + page-table-switch dance).
5. Indexes into the syscall table with the syscall number and calls the corresponding C function (e.g., `__x64_sys_openat`).

**On the way back**, the kernel puts the return value in `RAX`, restores the saved registers, switches page tables back, and executes `sysret` (the partner instruction to `syscall`). `sysret` does the inverse atomically: restores `RIP` from `RCX`, `RFLAGS` from `R11`, and switches back to ring 3. The user program resumes as if `syscall` were just a strange function call.

**The "translation"** in your question is really this: there's no translation of the *code* — the CPU is still executing native instructions the whole time. What changes is the privilege level and the context (stack, page tables on KPTI systems, register set). The CPU has hardware support for that transition, exposed via this dedicated instruction. Before `syscall`/`sysret` existed (Pentium era), Linux used the slower `int 0x80` software interrupt, which went through the full interrupt-descriptor-table machinery. `syscall` is a streamlined fast-path designed specifically for this purpose.

## 3. Bypassing syscalls for low-latency and heavy I/O

You're right that syscalls aren't free. The cost isn't just the instruction itself (a few hundred cycles); it's everything around it: register save/restore, possible page-table switch (KPTI), cache and TLB pollution from running kernel code, and — for I/O — copying data between user and kernel buffers. For a workload doing millions of operations per second, this dominates.

Several techniques sidestep it:

**`io_uring` (Linux, the modern answer).** Instead of one syscall per I/O, you set up two ring buffers in memory shared between the application and the kernel: a **submission queue** and a **completion queue**. Your app writes I/O requests directly into the submission ring (just memory writes — no syscall), and the kernel reads them and writes results into the completion ring. With `IORING_SETUP_SQPOLL`, a kernel thread polls the submission queue, so you can do thousands of I/Os without ever invoking a syscall — you just write to memory and the kernel notices. This is now the dominant high-performance I/O API on Linux, and databases, file servers, and proxies have moved to it.

**SPDK and DPDK (kernel bypass for storage and networking).** These are user-space libraries that take the kernel out of the loop entirely. The trick: unbind the device (NVMe SSD, NIC) from the kernel driver and let a user-space process drive the hardware directly via memory-mapped registers. With NVMe SSDs, this means your application talks to the SSD's submission and completion queues itself, in user space, with zero syscalls and zero copies. You get latencies close to the hardware limit (single-digit microseconds for an NVMe read). The trade-off: you've taken on the responsibilities of a driver — no kernel protections, one process effectively owns the device, and you implement your own scheduling/sharing if needed. Cloud storage systems and HFT shops use this heavily.

**`mmap` for files.** Map a file into your address space and access it as memory. The first access to each page faults into the kernel and reads it from disk, but subsequent accesses are just loads/stores. For random access to large files, this trades syscalls for page faults, which is often a win — and with `MAP_POPULATE` or huge pages, you can amortize the fault cost too.

**vDSO (the small-fry case).** A handful of syscalls that are pure reads of kernel-maintained data — `gettimeofday`, `clock_gettime`, `getcpu` — are implemented as user-space functions in a special page (the vDSO) the kernel maps into every process. The kernel publishes the time data to that page; user space reads it directly. No mode switch at all. This is why `clock_gettime` on Linux is essentially as fast as a function call.

**Userspace networking stacks** (mTCP, Seastar, Snabb) do the same trick as SPDK but for NICs: poll the network card directly, run the TCP/IP stack in user space, never enter the kernel on the data path.

**The common pattern across all of these:** the syscall is a synchronous, per-operation request-response across a privilege boundary, and that's exactly what's expensive. So you replace it with either (a) **batched, asynchronous communication via shared memory** (io_uring), or (b) **direct hardware access from user space** (SPDK, DPDK), or (c) **memory-mapped data the kernel keeps fresh** (vDSO, mmap). In each case the kernel still plays a role — setting up the shared region, managing permissions, handling rare slow paths — but it's removed from the hot path.

For your specific question about heavy SSD I/O: the modern answer in Linux is **io_uring** for general applications, and **SPDK** when you genuinely need every microsecond and are willing to dedicate hardware to the workload. A well-tuned io_uring application can saturate a modern NVMe drive (millions of IOPS) using a single core.
