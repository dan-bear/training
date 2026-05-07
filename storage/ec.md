## The problem LDEC solves

Recall the Reed-Solomon rebuild penalty: in an N+M scheme, reconstructing one lost shard requires reading **N surviving shards** from the network. Wider stripes give better storage efficiency (a 16+4 stripe is 25% overhead, a 100+4 is 4% overhead), but the wider you go, the more painful rebuilds become — and the longer rebuild takes, the higher the chance of additional failures during the rebuild window.

VAST frames this as the core tradeoff: with Reed-Solomon, reconstructing a missing strip requires reading every surviving data strip in the stripe, so very wide stripes mean very long rebuild times — which gets worse as individual drive capacities grow. The math backs you into a corner: efficiency *or* fast rebuild, pick one.

## The locally-decodable trick

The key idea behind any locally-decodable code is to add structure so that **single-failure recovery** (the overwhelmingly common case) only needs to touch a *local subset* of the stripe, not the whole thing. You still keep enough global parity to survive the rare multi-failure cases.

In VAST's specific scheme, an N+4 stripe can rebuild a lost drive by reading just one quarter of the surviving data — so one quarter of the I/O of a conventional Reed-Solomon rebuild. The "4" in N+4 is significant: there are four parity strips, and the way they're constructed lets each one cover a different quarter of the data strips, so a single missing strip can be reconstructed from its quarter plus one parity, instead of from the entire stripe.

This breaks the tradeoff. You can now have *both* very wide stripes (great efficiency) *and* fast rebuilds (small read amplification on failures).

## What VAST actually deploys

The numbers are pretty striking compared to typical enterprise RAID/EC schemes:

- A standard VAST cluster with more than 150 SSDs writes stripes of 146 data strips plus 4 parity strips (146D+4P), tolerating up to four concurrent SSD failures with around 2.7% storage overhead.
- Stripe widths range from 36+4 in small configurations up to 146+4 in larger ones, scaling with cluster size.
- Their broader platform documentation describes typical stripes of 150D+4P, the exact width depending on cluster generation.

For comparison, the widest Reed-Solomon stripe commonly seen in conventional arrays is 16D+4P, and most architects pick narrower stripes precisely because of the rebuild cost. VAST is running an order of magnitude wider.

The overhead difference compounds at scale: 2.7% versus 25% means a petabyte of usable data costs about 1.03 PB raw with VAST, versus 1.33 PB raw with 16+4 Reed-Solomon. Across an exabyte deployment that's a real money difference.

## Why VAST can get away with it (architecture context)

LDEC alone wouldn't be enough — it works because of the rest of the platform's design:

**QLC SSDs as the storage medium.** VAST's bet is on cheap, high-density QLC flash, where per-device cost is what you want to minimize. Wide stripes amortize the 4 parity strips over many data strips, dropping overhead toward zero. Without LDEC, wide stripes on QLC would be a non-starter because rebuild times would be catastrophic.

**Disaggregated shared-everything architecture.** Their CNodes (stateless compute) and DBoxes/EBoxes (storage enclosures) are separated. Rebuild work is parallelized across all the front-end servers in the system rather than serialized through a single controller, which further compresses rebuild time.

**Failure domain placement.** With 146 strips spread across far fewer than 146 enclosures, multiple strips of a single stripe live in the same box. Because the recovery limit is 4 strips and a single box holds many more than 4 strips of any stripe, the placement strategy relies on the box-level HA, not just the stripe-level coding, to keep data available. Newer "rack-scale resilience" mode trades a bit of overhead to also tolerate full enclosure or rack failures by capping how many strips of any stripe land in any one failure domain.

**Append-only, log-structured writes with grouped lifetimes.** VAST groups data of similar expected lifetime into the same stripe, so when garbage collection runs, an entire stripe can usually be discarded as a unit instead of needing expensive read-modify-write to consolidate live data. This sidesteps the classic problem with very wide stripes — that small in-place updates would force a massive read-modify-write across the whole stripe.

## How this relates to LRC more broadly

Microsoft's Azure Storage and Hadoop-EC use Local Reconstruction Codes that are conceptually in the same family: extra "local" parity covering subgroups of data strips, so the common single-failure case doesn't need a global rebuild. Azure's published LRC scheme is something like (12,2,2) — 12 data strips, 2 local parities (each covering 6 data strips), and 2 global parities — letting most rebuilds touch only 6 strips instead of 12.

VAST's LDEC sits in that broader family but is engineered for *much* wider stripes than Azure or Hadoop typically use, and is tightly integrated with their flash-native data layout. The "4" parity strips function as both global protection (any 4 failures recoverable, anywhere in the stripe) and local protection (single failures recoverable from a quarter of the data) — a design choice that, mathematically, requires the parity construction to satisfy both global MDS-like properties and local-group properties simultaneously. VAST hasn't published the precise generator matrices publicly, so the marketing materials are clearer on the *behavior* than the *exact construction*, but the family it belongs to (locally decodable / locally recoverable codes) is well-studied in coding theory.

## The takeaway

The interesting thing about LDEC isn't really the math in isolation — locally decodable codes have been a research topic for years. It's that VAST built an entire system around the assumption that you can have ultra-wide stripes safely, and then leaned into the consequences: cheap QLC media, very low storage overhead, and fast rebuilds even on huge drives. It's a good example of how a coding-theory choice ripples up into hardware economics and architecture choices, rather than being an isolated implementation detail.

Want me to go further on the math (a worked example of how a single-failure rebuild from one parity + one quarter of the data actually computes), or how this compares concretely to Azure's LRC and Hadoop-EC schemes?
