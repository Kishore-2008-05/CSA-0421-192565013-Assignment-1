# TASK 1 – Requirements of Each Computing Environment (4 marks)

The hospital has six distinct computing environments. Requirements are ranked by patient-safety impact first, then availability, security, response time, throughput and energy efficiency.

| Environment | Ranked requirements (1 = highest) | Justification |
|---|---|---|
| Bedside monitors (500) | 1. Deterministic response ≤10 ms; 2. reliability; 3. sensor I/O accuracy; 4. integrity/security; 5. low memory/power | Missing an alarm deadline can harm a patient. A hard real-time design must bound worst-case response, not merely provide a good average. |
| Nurses’ tablets (120) | 1. security/privacy; 2. battery life for a shift; 3. wireless availability; 4. responsive UI; 5. manageable storage | Tablets are mobile and frequently disconnected. They need encryption, authentication, power management and safe offline handling. |
| Doctors’ workstations (80) | 1. security; 2. usability/responsiveness; 3. reliable access; 4. multitasking; 5. peripheral support | Clinical users need a responsive desktop UI, controlled access to records and support for approved imaging/clinical applications. |
| Patient-record database | 1. availability and durability; 2. confidentiality/integrity; 3. transaction correctness; 4. throughput; 5. recoverability | A database outage or corrupted record affects care. Redundancy, backups, access control and transaction logging are essential. |
| MRI imaging server | 1. throughput; 2. memory bandwidth/capacity; 3. availability; 4. parallel processing; 5. data integrity | MRI reconstruction is compute- and memory-intensive; multiple processors and high-speed storage/network I/O are useful. |
| Partner-hospital link | 1. confidentiality/integrity; 2. availability; 3. interoperability; 4. throughput; 5. auditability | Shared records require authenticated encrypted communication, authorization, audit logs and resilient network connectivity. |

Conflicts and trade-offs:
- Strict real-time scheduling reserves predictable CPU capacity, potentially reducing general-purpose throughput.
- Strong encryption and audit logging consume CPU and storage, but cannot be removed from patient-record systems.
- More background jobs and users increase throughput demand but can introduce scheduling delays.
- Tablets need rich clinical applications but limited battery and storage; background activity must be controlled.
- Replication improves availability but introduces consistency, network and operational complexity.

OS history applied:
- Batch systems suit scheduled backups and bulk image processing, not interactive alarms.
- Time-sharing supports many doctors and nurses using shared servers.
- Personal-computer OSs suit desktop workstations.
- Mobile OS principles (power management, wireless roaming, sandboxing) suit tablets.
- Real-time OS principles suit bedside monitors because deadlines matter.
- Distributed-system principles support three hospitals sharing records.

Single general-purpose OS alternative:
A single general-purpose OS simplifies administration and staff training, but ordinary time-sharing schedulers generally do not promise a hard 10 ms worst-case response. Under overload, contention, interrupts or driver delays, scheduling latency may exceed the deadline. It also has a larger memory/storage footprint than a small embedded RTOS. A common OS image can reduce administration variation, but a single configuration cannot simultaneously optimize deterministic response, tablet battery life, desktop usability and clustered database availability. A general-purpose OS with real-time extensions and strict configuration could reduce the gap, but must be validated against worst-case execution and hardware timing. Therefore, use purpose-fit OS profiles rather than one identical OS everywhere.
