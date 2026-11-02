# TASK 9 – Memory Hierarchy and I/O Systems (4 marks)

Typical hierarchy (approximate values; hardware varies):
| Level | Typical latency | Relative capacity | Hospital use |
|---|---|---|---|
| CPU registers | <1 ns | Bytes–KB per core | Current instructions and operands |
| L1/L2/L3 cache | ~1–20 ns | KB–tens of MB | Hot database indexes and processing data |
| DRAM | ~50–100 ns | GBs–TBs | Active applications, DB cache, MRI working sets |
| NVMe SSD | ~10–100 µs | 100s GB–TBs | Patient records, database logs, recent MRI images |
| HDD | ~5–15 ms seek (plus transfer) | TBs | Large image archive and backups |
| Network/object storage | ~sub-ms to many ms or more | Scalable | Replicated records, off-site archive, shared hospital data |

Data placement:
- Monitor readings: keep the newest values in local RAM for immediate alarm processing; persist critical events to durable local storage and securely forward them to central records.
- Patient records: durable database storage on redundant SSD-backed storage with transaction logs, backups and replicated copies.
- MRI images: fast local NVMe/DRAM scratch space during reconstruction, then durable PACS/archive storage; use network storage for sharing and long-term retention.
- Caches: keep frequently used patient indexes/metadata in memory with authorization checks and invalidation/consistency rules. Caching reduces repeated storage/network latency but stale clinical data must not be presented as current without validation.

I/O methods:
- Programmed I/O: CPU repeatedly checks device status and moves data; simple but wastes CPU.
- Interrupt-driven I/O: device interrupts CPU when service is needed; suitable for event-driven low-volume device interactions.
- DMA: device/controller transfers blocks directly between device and RAM with limited CPU involvement; suitable for large MRI image transfers.

500 MB interrupt-per-word alternative:
Assume decimal 500 MB = 500,000,000 bytes and 4-byte words. Interrupts = 125,000,000. If “500 MiB” is intended, 524,288,000 / 4 = 131,072,000 interrupts. This is an enormous interrupt rate and would consume substantial CPU time. With DMA, a small number of interrupts can signal completion per block/batch, so CPU overhead is much lower. DMA needs appropriately sized buffers/descriptors and cache-coherency handling; interrupt-driven transfer may use smaller buffers but requires servicing every word/event. The assumption about word size must be stated because the question does not specify it.
