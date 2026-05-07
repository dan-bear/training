# Storage Topics

## DaSE architecture VS shared-nothing architecture

## Erasure Coding

### Concept
- Promise - **Data** is split into k **data-shards**: D[0], ... , D[K-1] and m **parity-shards** calculated from the data-shards P[0],...,P[m-1], any subset of k shards from the unioned set of the data-shards and the parity-shards can be used to reconstruct the **Data**.
- Storage Overhead - given EC(k,m) the storage overhead is 1 + (m/k), a common scheme is EC(10,4) with overhead of 1.4. Better then replication that multiplies the storage overhead by replication-factor (3x replication => 3x storage overhead).
- Compute Overhead - any modification of the Data demands modification of the parity-shards that potentially reside in different failure-domains. Replication does not demand parity calculation.
- Width - the greater the ratio between the number of data-shard (k, also called EC width) and the number of parity-shards (m) the better the storage ratio, EC(100,4) overhead is 1.04 while EC(16,4) overead is 1.25. However, the reconstruction demands at least k shards, so reconstruction cost increases (compute and network) with k (width). Note that the probability for errors during reconstruction increases with the reconstruction time, so wide EC leads to more complex system.
- **local EC**
- **distributed EC**

## Object Storage

### In General
- Object storage manages data as discrete units called **objects** in a **flat namespace**. Each object contains:
   1. **The data itself** - the bytes (can be anything)
   2. **Metadata**- objects-management-system metadata (size, type, timestamps) and arbitrary user-defined key/value tags
   3. **A unique identifier** (the "key") used for retrieval.
- Objects live inside containers usually called **buckets**.
- The namespace within a bucket is flat — there are no real directories, though most systems let you use `/` in keys to simulate a hierarchy, e.g., `photos/2024/beach.jpg` is just a key with slashes in it, not nested folders.
- The design of object-management-systems is optimized for:
  1. **massive scale** (petabytes to exabytes)
  2. **high durability** through erasure coding or replication
  3. **parallel access** to objects from many clients
  4. **write-once-read-many** workloads - Objects are typically **immutable** once written, when an object needs to be modified it is usually replaced rather than modify a few bytes in place.

### Object Management Systems API
- Object storage is accessed over **HTTP(S) using a REST API**, not a kernel driver or filesystem mount.
- The de facto industry standard is the **Amazon S3 API**, which nearly every object store today claims to implements. Other notable APIs are OpenStack Swift, Azure Blob, and Google Cloud Storage's native API.
- Typical operations look roughly like this:
  1. **Object operations:** `PUT` (upload), `GET` (download), `HEAD` (fetch only metadata), `DELETE`, `COPY`
  2. **Bucket operations:** create bucket, delete bucket, list buckets, list objects in a bucket (with prefix filters and pagination)
  3. **Multipart upload:** initiate / upload-part / complete - for uploading huge objects in parallel chunks, with retry of individual parts
  4. **Range GETs:** request bytes N–M of an object, used heavily for video streaming and Parquet/ORC analytical reads
  5. **Pre-signed URLs:** time-limited signed URLs that let an unauthenticated client upload or download object directly
  6. **Access control:** bucket policies, ACLs, IAM, signed requests (AWS Signature v4)
  7. **Lifecycle and versioning:** rules to transition old objects to colder tiers or expire them; keep multiple versions of an object
  8. **Object lock / WORM:** prevent deletion for a retention period (compliance)
  9. **Notifications:** events on `PutObject` / `DeleteObject` pushed to a queue or function

### How it differs from block and file storage
- tuned for scale rather than low latency.
  1. Latency is tens to hundreds of milliseconds.
  2. The metadata is rich and queryable.
  3. Right fit for: backups and archives, media libraries, data lakes (Parquet/Iceberg/Delta), static website assets, container image registries, ML training datasets.
- A useful mental model to distinguish between block, file and object: block = dumb fast bytes; file = a tree you can edit; object = an HTTP-addressable blob with metadata, scaled out.

### Common products
- Open source:
  1. **MinIO** — S3-compatible, written in Go, very widely used for self-hosted and Kubernetes deployments. Often the default "I want S3 in my cluster" choice.
  2. **Ceph (RADOS Gateway)** — distributed storage cluster that exposes object (S3 + Swift), block (RBD), and file (CephFS) all from the same backend. Heavyweight but extremely flexible; the basis of many on-prem deployments.
- Enterprise / private-cloud (on-premise)
  1. **Dell ECS** (Elastic Cloud Storage)
  2. **NetApp StorageGRID**
  3. **VAST** (technically a disaggregated all-flash platform; presents S3 along with NFS/SMB)
- Public cloud
  1. **Amazon S3** — the original, and the API everyone clones
  2. **Azure Blob Storage** — Microsoft's; has its own native API plus an S3-compatible front
  3. **Google Cloud Storage (GCS)** — native API plus an S3-interoperability mode
- practical note: because the S3 API became the standard, you can often point the same client library at different products just by changing the endpoint URL and credentials. That portability is a big part of why object storage feels "standard" in a way that block and file storage never quite did.

## File Systems
- **io_uring**
- **linux page cache**
- **Virtual File System**
- **Distributed File System**
- **glibc**
-  

## NVME/TCP (Fabric)

## BTrees

## Log Structured Arrays

## Log Structured Merge Tree

## Snapshot Techniques

### LBA Chains ###

## Indexes
- elastic index, how to extend and shrink a distributed index.

## Thin and Thick Clones

## Rebalance Algorithms
- shared-nothing architectures
- disaggregate and share anything architectures

## Multi Tenancy

## Consistency Models (algo, pros and cons)
- **MVCC Concept**
- **Read After Write**
  1. If Write succeeds, any follower reader would see the written data.
  2. Consequences:
    - 2 concurrent writes will be serialized on arrival order, not on issue order
    - No native (without additional locking) atomic writes to multiple locations, as every write is applied once done.
    - No native atomic "rename" (metadata modification) as renaming means copy + Delete.
  4. Implementation Methods
  5. Products:
- **Eventual Consistency**
- **Optimistic Locking**
- **2-Phase-Locking**
- 

## AWS Storage Solutions
- **EFS**
- **S3**

## Companies and Products
- **Vast Data**
- **CEPH**
- **LakeFS**
- **Powerflex (Dell)**

## Inference Infrastructure
- **vLLM**

