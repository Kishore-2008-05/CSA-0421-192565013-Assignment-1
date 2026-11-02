# TASK 8 – CPU States and Protection (3 marks)

User mode restricts application instructions and memory access. Kernel mode permits privileged operations such as configuring devices, page tables and interrupt controls. A hardware mode bit/privilege level distinguishes execution privilege. A user program requests privileged work through a system call, exception or interrupt.

Interrupts are asynchronous events from hardware (for example, a device signaling data ready). A trap/exception is a synchronous event caused by the current instruction or an explicit syscall. A timer interrupt lets the scheduler regain control, pre-empt a running task and enforce time sharing/priorities.

If any monitor program could disable interrupts, a faulty or malicious task could prevent timely sensor/alarm handling and starve other tasks. Therefore, interrupt control must remain privileged and only trusted kernel/driver code may manage it.

Memory protection:
The MMU and page tables map each process's virtual address space and enforce read/write/execute permissions. User-mode code cannot access kernel pages or another process's pages unless the OS deliberately shares memory. The kernel validates pointers and permissions at system-call boundaries.

Polling alternative:
If a sensor is checked every P milliseconds, the worst-case detection wait is approximately P plus processing/scheduling delay. To guarantee a 10 ms alarm deadline, P and all other worst-case delays must fit within 10 ms. Interrupt-driven notification can respond closer to interrupt latency and avoids continuously spending CPU cycles checking unchanged data. Polling may be simpler and can be predictable with a carefully chosen interval, but frequent polling wastes CPU and battery; infrequent polling increases detection delay. For safety-critical monitors, use validated interrupt-driven I/O with bounded latency, while retaining watchdog/timeouts as a fallback.
