# TASK 12 – Re-evaluate and Adapt the Design (8 marks)

Decision: MODIFY the original design, rather than retain it unchanged or redesign everything.

A. Impact analysis (2 marks)
Home monitoring introduces untrusted networks, variable latency, intermittent connectivity, device diversity and a need for secure device identity. The cloud records service introduces multi-tenant isolation, shared identity, API security, data residency/governance, encryption, audit, backup and disaster recovery. The original local monitor RTOS remains relevant, but communication, security and distributed services must expand.

B. Evaluation of original design (2 marks)
The hospital's local real-time design remains appropriate for alarms generated at the bedside. It cannot assume internet delivery will meet the same 10 ms deadline: home Wi-Fi, broadband, cellular networks and cloud queues have variable latency and outages. Therefore, safety-critical local alarms must be generated on the device itself; remote transmission is supplementary. The original clustered database can continue local operation, but shared cloud records require secure replication, conflict resolution, availability design and strong identity/access controls.

C. Adaptation (2 marks)
- Home device: embedded RTOS or safety-appropriate embedded OS; local threshold detection, audible/visual alarm where appropriate, secure boot, signed firmware, encrypted storage and device certificates.
- Gateway/mobile app: mobile OS with authenticated pairing, encrypted communication, buffering during outages and user consent.
- Connectivity: TLS-protected authenticated APIs or message broker; device identity, certificate rotation, replay protection, rate limiting and monitoring.
- Cloud records: distributed, highly available service with encrypted databases, tenant/site isolation, role-based access, immutable audit logs, backups and disaster recovery.
- Hospital edge: local cache and store-and-forward gateway so care workflows continue during cloud/network outages.
- Interoperability: use agreed healthcare data formats/APIs and validate data provenance, timestamps, units and patient matching.

D. Evidence-based defence (2 marks)
Modify is the balanced choice because it preserves the validated local real-time alarm path while extending secure communication and distributed storage. A complete redesign would add cost and risk without removing the need for local deterministic monitoring. Retaining the design unchanged would fail to address remote-device identity, internet outages, cloud access control and multi-hospital consistency. The trade-off is greater cybersecurity and operations complexity, which is justified by remote access and shared records. End-to-end testing must include offline operation, delayed/replayed messages, credential revocation, fail-over, recovery and data reconciliation.
