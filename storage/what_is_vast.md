# VAST Data — Overview

## The core technology: DASE architecture

VAST's foundational innovation is its **Disaggregated, Shared-Everything (DASE)** architecture. Traditional storage systems use a "shared-nothing" design (originally introduced by Google ~20 years ago) where each node owns a piece of the data. VAST's DASE design instead decouples compute logic from system state, letting cluster CPUs access NVMe SSDs over commodity networks as if they were directly attached. This means CPUs and storage can scale independently, eliminating the "data islands" or tiers of legacy systems.

A few technical pillars make this work:

- **All-flash with QLC SSDs + Storage Class Memory (SCM).** VAST uses inexpensive, high-density QLC flash drives but extends their write life by absorbing writes first into Storage Class Memory, then writing optimally sized blocks to QLC. This gives flash performance at near-archive economics.
- **Similarity-based data reduction.** VAST's similarity technology globally identifies similar (not just identical) data patterns at fine granularity, reducing stored data by several times beyond traditional dedup.
- **Locally Decodable Erasure Coding (LDEC).** A new error-correction approach that delivers about 60 million years mean-time-to-data-loss while keeping overhead as low as 2.7%, breaking the traditional tradeoff between resilience and efficiency.
- **NVMe-oF + DPUs.** Storage and compute nodes are connected over NVMe-over-Fabrics, with newer enclosures (Ceres) using NVIDIA BlueField DPUs to offload networking and storage processing.

## Main products (the VAST AI Operating System)

VAST has evolved from a pure storage company into what it now positions as a full "AI Operating System" — a unified data stack. Its core integrated components are:

- **VAST DataStore** — an all-flash, scalable storage system for files, objects, and volumes (NFS, SMB, S3, Block, Kubernetes CSI), originally called Universal Storage. It anchors very large AI datasets with high availability.
- **VAST DataBase** — an AI-native database that unifies transactional and analytical workloads (writes in rows, stores in columns, fully ACID), with an integrated vector store for real-time AI and hybrid queries across structured and semantic data.
- **VAST DataSpace** — a globally distributed namespace spanning on-prem, cloud, and edge locations, scaling to exabytes and trillions of files/objects.
- **VAST DataEngine** — a serverless execution and orchestration engine that runs compute close to data using event triggers, Python functions, and a native Kafka-compatible broker.
- **VAST SyncEngine** — a data discovery and migration service that indexes and synchronizes external data sources into DataSpace and triggers enrichment pipelines on ingest.
- **VAST InsightEngine** (with NVIDIA) — a real-time vector embedding and retrieval engine providing model orchestration and pipeline observability for RAG (retrieval-augmented generation) and agentic workflows.
- **VAST AgentEngine** — available in 2026, a production-grade deployment layer for AI agents with containerized runtimes, lifecycle management, MCP integration, and full auditability across multi-agent stacks.

## What customers actually use it for

VAST's products are typically used wherever organizations need to feed enormous datasets into expensive compute (especially GPUs) without storage becoming the bottleneck. The main application areas:

**Large-scale AI training and inference.** This is the flagship use case. AI labs use VAST to train trillion-parameter models on multi-billion-dollar GPU clusters, relying on its asynchronous parallel checkpointing to avoid GPU idle time and its 99.999% uptime to keep clusters productive. VAST is the data foundation for over 30 AI cloud service providers worldwide, including CoreWeave, and it is a certified storage partner for NVIDIA Cloud Partners with deep DGX integration.

**High-Performance Computing (HPC).** HPC teams traditionally had to use specialized parallel file systems like Lustre, GPFS, or BeeGFS to get the performance they needed. VAST delivers similar parallel I/O performance over standard NFS, lets teams consolidate scratch and nearline tiers into a single flash tier, and supports both unstructured (NFS, SMB, S3) and structured data — useful for life sciences, simulations, and research workloads.

**RAG and agentic AI.** The InsightEngine and AgentEngine target enterprises building retrieval-augmented generation systems and deploying autonomous agents, with NVIDIA-library-accelerated vector search and real-time SQL.

**Real-time analytics and data lakehouse consolidation.** A common pattern is replacing fragmented systems — for example, a leading cybersecurity company replaced multiple Elasticsearch clusters with VAST DataBase to analyze 2 billion malware files and enable real-time threat correlation across years of historical data.

**Media, broadcast, and archival workloads.** The NHL uses VAST to streamline workflows across live production and archival footage, providing fast access to media assets while modernizing for AI. Other typical buyers include life sciences/genomics, financial services, government/sovereign AI initiatives, and backup/archive consolidation.


# Shared Nothing / DaSE

Great question — this gets at the deepest architectural difference between the two designs. Let me walk through it concretely.

## The fundamental distinction

In a **shared-nothing** system, each node bundles three things together: CPU, memory, and the drives plugged into it. No other node can read or write those drives directly — they have to go through that node's CPU. "Owning" data means owning the drives the data lives on.

In **DASE**, those three things are decoupled. There are stateless **CNodes** (just CPUs running the VAST software) and **DBoxes / JBOFs** (enclosures full of SCM and QLC SSDs, with no real compute of their own beyond a DPU). Every CNode can directly read and write every drive in the cluster over NVMe-over-Fabrics. There is no concept of a drive "belonging" to a particular CNode.

That single distinction changes everything about how a write is handled.

## Shared-nothing: the 3-replica write (think Ceph RBD with size=3)

Setup: you have, say, 12 nodes. Each has 24 SSDs directly attached. A placement algorithm (CRUSH in Ceph's case) deterministically maps every block to exactly 3 specific nodes — call them N3, N7, and N11.

When the client writes a 4KB block:

1. The client (or gateway) computes the placement and identifies N3 as the **primary** OSD for that block, with N7 and N11 as secondaries.
2. The write is sent over the network to N3.
3. N3's CPU writes the block to its journal/WAL on its locally-attached SSD, **and in parallel** forwards the write over the network to N7 and N11.
4. N7's CPU writes to N7's local SSD. N11's CPU writes to N11's local SSD. Each ACKs back to N3.
5. Once all three have persisted durably, N3 ACKs the client.

Now you have three full physical copies of the block, sitting on drives that are each "behind" a different CPU. The properties that fall out of this:

- **3× raw capacity overhead** for every byte of usable data.
- **Network amplification**: one client write becomes two internode replication writes.
- **If N7 dies**, every block whose placement included N7 is now under-replicated. The cluster has to read surviving copies from other nodes and write fresh copies somewhere else — a slow, network-bound rebuild that scales with how much data N7 held.
- **Scaling is coupled**: you can't add capacity without also adding CPU, because drives only exist behind nodes. Adding a node also forces rebalancing — CRUSH remaps placements, and a chunk of existing data has to migrate.
- **Hardware must be roughly homogeneous** within a pool, because each node has to keep up with its share of the work.

## DASE: the same write in VAST

Setup: you have, say, 8 CNodes (stateless containers) and 4 DBoxes. Each DBox holds some SCM SSDs (high-endurance, for write buffering) and a lot of QLC SSDs (cheap, dense, for the actual data). All 8 CNodes are connected to all 4 DBoxes over NVMe-oF. There is no "primary" anything for any block.

When the client writes a 4KB block:

1. The client sends the write to whichever CNode it gets load-balanced to — they're stateless and interchangeable.
2. The CNode writes the block synchronously to **multiple SCM devices** in different DBoxes (for redundancy across failure domains). It does this directly over NVMe-oF — no other CPU is in the path.
3. As soon as the block is durable on redundant SCM, the CNode ACKs the client. The write is done from the client's perspective.
4. **Asynchronously, in the background**, the system aggregates many such small writes sitting in SCM and packs them into a very wide **erasure-coded stripe** using VAST's Locally Decodable Erasure Code. A stripe might span ~150 drives across many DBoxes, with a small number of parity strips.
5. The stripe is written across QLC SSDs throughout the cluster. Once it's persisted on QLC, the SCM space can be reclaimed for new writes.

Notice what's missing: there is no "3-replica" step. The block is never replicated three times to three separate machines. The durability story has two layers:

- **Short-term durability** comes from landing on redundant SCM devices in different failure domains.
- **Long-term durability** comes from a wide EC stripe that spans far more failure domains than 3, with overhead as low as ~2.7% instead of 200%.

If you literally configured a "3-replica block device" on top of DASE, the system would still be writing erasure-coded stripes underneath — the replication factor at the volume layer would just be a logical abstraction, not three physical copies behind three different CPUs.

Now let me show this side-by-side so the data flow is clearer:## Why this changes everything downstream

The "where does the data physically live and who can reach it" question cascades into almost every operational property of the system:

**Capacity overhead.** Three full copies vs. one wide EC stripe with ~2.7% parity overhead. That's roughly the difference between 33% effective capacity and 97% effective capacity for the same raw flash.

**Failure recovery.** When a node fails in shared-nothing, only the 2 surviving replicas can serve reads for that data, and rebuild traffic is bounded by the throughput of the source nodes. When a drive fails in DASE, every other drive in the cluster participates in the rebuild — read in parallel from hundreds of drives, recompute the missing strip via LDEC, write to spare capacity. Rebuild times scale with cluster width, not with the size of one node's drive.

**Scaling.** Shared-nothing forces you to add CPU and capacity together (because drives only exist behind nodes) and triggers data rebalancing every time you do. DASE lets you add a DBox when you only need more space, or a CNode when you only need more performance, with no rebalancing — because no CNode "owns" any data to rebalance.

**Hardware refresh.** In shared-nothing, the homogeneity requirement turns generation transitions painful (mixing old and new nodes in one pool is usually unsupported or unwise). In DASE, old DBoxes and new DBoxes coexist; old CNodes and new CNodes coexist; nothing requires them to match.

**Write amplification on the wire.** Shared-nothing 3-replica means every client write generates 2 internal network writes (primary → 2 secondaries). DASE generates writes to multiple SCM devices, but those devices are already in the storage tier — there's no "internode" replication chatter happening over and over.

The reason VAST insists DASE is "the first new scale-out architecture in 20 years" is that breaking the bundling of CPU+drives lets them pick a *completely different* durability mechanism (very wide EC instead of replication), which then unlocks the cascade of properties above. In a shared-nothing world, very wide EC is theoretically possible but operationally painful — rebuilds across 150 nodes are slow and expensive — so 3-replica remains the pragmatic default. DASE makes wide EC the natural choice, which is how they get archive-grade economics out of all-flash hardware.




