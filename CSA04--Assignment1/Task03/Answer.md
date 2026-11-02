# TASK 3 – Operating-System Structures (4 marks)

| Structure | Design | Reliability | Performance | Updating/maintenance |
|---|---|---|---|---|
| Monolithic/simple | Most OS services and drivers run in kernel space | A faulty driver can crash or corrupt the whole kernel | Usually low internal communication overhead | Changes can affect the whole kernel |
| Layered | OS divided into layers with defined interfaces | Clear boundaries aid reasoning and testing | Layer crossings can add overhead | Easier to isolate and replace layers |
| Microkernel | Minimal kernel; services/drivers run as user-space servers communicating by messages | Strong fault isolation; failed service may be restarted | Message passing/context switches can add overhead | Services can be updated independently |
| Modular | Core kernel plus loadable modules | Flexible, but a faulty kernel module can still crash kernel | Near-monolithic performance for many operations | Modules can be loaded/unloaded without rebuilding the whole kernel |
| Hybrid | Combines microkernel ideas with substantial kernel-space services | Depends on implementation; some isolation with practical performance | Designed to reduce microkernel overhead | Componentized but still complex |

Recommended structures:
1. Bedside monitors: a small microkernel-oriented RTOS is preferred where certified drivers and services can be isolated. Keep only the alarm path, sensor I/O, timer, scheduling, watchdog and essential logging. This limits the impact of noncritical service failure. Validate actual worst-case latency on the target hardware.
2. Database server: a mature modular monolithic kernel such as Linux is appropriate because it provides high-throughput networking, storage drivers, filesystems, observability and mature server tooling. Use a minimal, tested module set and controlled updates.

Platform examples:
- Linux: monolithic kernel with loadable modules (often described as modular monolithic).
- Windows: hybrid kernel architecture.
- Android: Linux-kernel-based stack with Android framework and HAL layers; kernel remains modular monolithic.
- FreeRTOS: small real-time kernel, commonly used in embedded systems; it is not a full desktop OS.
- QNX: microkernel-based real-time OS.

Monolithic alternative for bedside monitors:
A monolithic design can make a service call with fewer internal message-passing steps and often lower overhead. A microkernel may require a user-to-kernel transition plus IPC to a server and possibly a reply, adding latency. However, the microkernel can keep drivers/services outside the kernel and reduce fault propagation. A monolithic kernel may occupy more kernel memory because more services/drivers are resident, though actual memory depends on configuration. A faulty in-kernel sensor driver can crash or corrupt the whole monitor. The correct decision is not based on average call speed alone: the 10 ms worst-case deadline and fault containment make a small, validated RTOS/microkernel design preferable.
