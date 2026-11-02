# TASK 4 – Operating-System Services (4 marks)

| OS service | Monitors | Tablets | Workstations | Database | MRI server |
|---|---|---|---|---|---|
| User interface | Minimal alarm/status UI | Touch UI | Full GUI | Admin/monitoring tools | Admin/processing UI |
| Program execution | Fixed validated tasks | Clinical apps | Clinical apps | DB engine/services | Reconstruction software |
| I/O operations | Sensor, alarm, display | Touch, Wi-Fi, camera | Keyboard, display, network | Storage/network | Scanner/network/storage |
| File system | Small configuration/log store | Encrypted local cache | User/app files | Journals, data, backups | Large image datasets |
| Communication | Sensor buses, alarm network | Wi-Fi/VPN/API | LAN/API | Replication/client protocol | High-speed data transfer |
| Error detection | Watchdog, sensor validation | App/system health | System logs | ECC, checksums, DB recovery | ECC, job validation |
| Resource allocation | Fixed priorities/reservations | CPU and battery management | Multitasking | CPU, memory, I/O scheduling | Parallel CPU/GPU/memory |
| Accounting | Minimal event logs | Usage/security logs | Audit logs | Detailed transaction/audit logs | Job/resource logs |
| Protection/security | Secure boot, signed updates, restricted interfaces | Encryption, MFA, sandbox | RBAC, endpoint protection | Least privilege, encryption, audit | Access control and network isolation |

Services to minimize/remove from bedside monitors:
No general-purpose desktop shell, app store, print spooler, multimedia services, broad user account system, unnecessary network listeners or nonessential background daemons. Retain alarm scheduling, sensor drivers, watchdog, timekeeping, authenticated communication, secure boot, integrity checks and essential audit/event logs. Removing nonessential services reduces attack surface and resource contention.

Database essentials:
Reliable filesystem/storage stack, process and memory management, networking, synchronization, resource allocation, access control, encryption support, audit logging, error detection, backups, transaction recovery and monitoring.

Protecting one patient's records:
Use authenticated user identities, role-based access control (RBAC), least privilege, per-session authorization, database views/row-level controls where supported, process isolation, filesystem permissions, encryption in transit and at rest, audit trails, secure key management and session timeouts. A program must not gain access merely because it runs on the same server. Database authorization must be checked for each query/operation.

Full desktop OS on tablets alternative:
A full desktop OS may offer broad software compatibility, but extra services increase RAM, storage, background CPU use and update burden. More background work can increase startup time and reduce battery life. A reduced mobile OS generally offers better integrated power management and app sandboxing. Exact overhead depends on the chosen OS image and enabled services; measure on actual tablet hardware rather than inventing a fixed figure.
