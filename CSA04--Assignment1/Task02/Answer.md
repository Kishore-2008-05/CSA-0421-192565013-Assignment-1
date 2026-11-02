# TASK 2 – Types of Operating Systems (3 marks)

| Hospital component | Recommended OS type | Reason and rejected alternatives |
|---|---|---|
| Bedside monitors | Embedded hard real-time OS (e.g., QNX or suitably configured RTOS) | Bounded interrupt and task latency supports the 10 ms alarm deadline. A general-purpose desktop OS does not inherently guarantee it. |
| Nurses’ tablets | Handheld/mobile OS | Integrated power management, touch UI, wireless connectivity and application sandboxing. A server OS is unnecessarily large. |
| Doctors’ workstations | Desktop OS | Supports interactive GUI, clinical applications, peripherals and multitasking. A handheld OS would constrain workstation software. |
| Patient database | Clustered server OS deployment | Two or more nodes with shared/replicated storage, health checks and automatic fail-over reduce a single point of failure. |
| MRI imaging | Multiprocessor server OS | Uses multiple CPUs/cores and large memory bandwidth for parallel reconstruction. |
| Partner hospitals | Distributed-system architecture over secure network links | Each hospital retains local services while exchanging authorized records through interoperable APIs and replication. |

OS type comparison:
- Mainframe: high-volume centralized transaction processing; possible for very large centralized workloads, but not necessary as the only hospital platform.
- Desktop: interactive end-user computing.
- Multiprocessor: one computer uses multiple CPUs/cores; suitable for MRI processing.
- Distributed: multiple networked computers cooperate; suitable for multi-hospital records.
- Clustered: coordinated servers provide fail-over and service continuity; suitable for the database.
- Hard real-time: missing a deadline is unacceptable; bedside alarm path.
- Soft real-time: occasional deadline misses degrade quality but are not catastrophic; some imaging/display workloads may fit.
- Handheld: power-aware mobile computing; tablets.

SMP versus AMP for MRI:
Symmetric multiprocessing (SMP) lets processors share memory and the OS scheduler balance work dynamically. It is generally the practical choice for a general-purpose imaging server because workloads can be parallelized and load-balanced. Asymmetric multiprocessing (AMP) assigns processors fixed roles; it can be useful for specialized pipelines or isolated control tasks, but can create imbalance and requires explicit partitioning. Choose SMP for the main reconstruction server, with dedicated accelerators where justified.

Cluster versus one large multiprocessor:
A single large server may have lower initial complexity and excellent local interconnect performance, but remains a single failure domain: motherboard, power, OS crash or maintenance can stop the database. A cluster can fail over to another node within seconds if correctly configured and tested. Clustering costs more in hardware, networking, storage/replication and administration. Throughput can increase with processors, but not linearly because of synchronization, memory bandwidth and serial portions of the workload (Amdahl’s law). Memory capacity is limited by the single machine in a scale-up design; a cluster can add aggregate memory, although application data partitioning and distributed caching are required. For records that must remain available, a cluster is preferred.
