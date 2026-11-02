# TASK 11 – Recommended Hospital OS Plan (4 marks)

Recommended deployment:
| Environment | OS type/structure | Services and protection | I/O and availability |
|---|---|---|---|
| Bedside monitors | Embedded hard RTOS; small microkernel-oriented design | Fixed-priority tasks, secure boot, signed updates, watchdog, minimal services | Interrupt-driven sensor I/O; bounded alarm path; local fail-safe alarm |
| Nurses’ tablets | Handheld/mobile OS | Device encryption, MFA, sandboxing, remote management, offline cache controls | Wi-Fi with secure VPN/API; battery-aware scheduling |
| Doctors’ workstations | Desktop OS | RBAC, endpoint protection, disk encryption, audit | LAN/Wi-Fi, standard peripherals |
| Patient database | Clustered Linux server OS; modular monolithic kernel | DB transactions, least privilege, encryption, audit, backups, replication | Redundant network/storage, health checks and automatic fail-over |
| MRI server | SMP multiprocessor Linux server | Parallel scheduling, resource monitoring, validated drivers | DMA-capable high-speed I/O, NVMe and high-speed network |
| Partner hospitals | Distributed services | Mutual authentication, authorization, encryption, audit and data governance | Secure APIs, replication and retry/idempotency |

Risks/limitations:
- RTOS and monitor hardware require formal timing validation, safety testing and controlled change management.
- Clusters need quorum, split-brain protection, tested backups and regular fail-over drills.
- Distributed records can have network partitions and replication delay; clinical workflows need clear source-of-truth and conflict handling.
- Mobile devices can be lost or disconnected; remote wipe and offline-data expiry are needed.
- Vendor compatibility, patching and staff training add operational cost.

Three-hospital suitability:
The design scales by retaining local real-time monitoring and local clinical operations at each hospital while using secure distributed services for record exchange. A central/cloud service can provide shared indexes and replicated records, but each site should have a local cache/continuity plan for network outages.

Two large virtualized servers alternative:
Virtualization can consolidate workloads and improve deployment flexibility, but placing hard real-time bedside monitoring on shared virtual hosts introduces hypervisor scheduling, device virtualization and noisy-neighbor latency. Memory and CPU overhead are incurred by the hypervisor and guest OSs; overcommit can cause unpredictable delays. Two servers also create correlated failure risk unless storage, networking and fail-over are carefully designed. Keep bedside monitor control on dedicated validated embedded hardware; virtualize suitable database/app services with reservations, redundancy and tested recovery.
