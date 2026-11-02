# Q1 – Processes and Process States (6 marks)

## Process-state model
`NEW → READY → RUNNING → TERMINATED`; a running process can move to `WAITING` when it blocks for disk/network/proctoring I/O, and `WAITING → READY` when the event completes. The scheduler dispatches a ready process to the CPU; preemption returns a running process to ready.

## PCB contents
A Process Control Block stores PID/PPID, process state, program counter, CPU registers, scheduling priority/queue links, memory-map/page-table references, open-file descriptors, credentials, signal state, accounting data and I/O status. Context switching saves/restores the CPU register and program-counter state through this kernel-managed record.

## Implementation/evidence
`process_demo.c` creates one child with `fork()`, prints PID/PPID, invokes `ps`, and waits for termination. While the child sleeps, inspect `/proc/<child-pid>/status`, `/proc/<pid>/stat` and `/proc/<pid>/maps`. Run `bash run.sh`.

## Evaluation for 2,000 exam sessions
A process has an independent virtual address space and kernel bookkeeping. 2,000 processes therefore increase page-table/address-space management, scheduler run-queue work, cache/TLB disruption and context-switch overhead. If sessions block on network/database I/O, CPU time may be low while many processes remain sleeping; if CPU-bound proctoring is active, runnable contention increases. A process switch can require address-space changes and TLB effects; a thread switch within one process generally retains the address space.

## Design decision
Prefer an event-driven front end with a bounded pool of worker threads/processes for CPU-heavy work. Keep fault-isolation boundaries for untrusted media decoding and critical services. One process per student offers strong isolation but scales poorly in memory and scheduling overhead. One thread per student is lighter but shares address space and can corrupt shared state; a crash may terminate the whole process. A fixed worker pool bounds concurrency and resource consumption while asynchronous I/O handles many mostly-waiting sessions.

## Alternative: thread per session
Threads share code, data, heap, open files and process credentials; each has its own stack, registers, program counter and thread-local storage. Thread creation/switching is usually cheaper than process creation/switching; stack reservation is typically far smaller than a full process address space (actual committed memory depends on runtime and stack configuration). A thread fault can terminate the whole process, so isolate risky components or use separate helper processes.

## Complexity
Creating and tracking N sessions is O(N) total bookkeeping. Per-session metadata is O(1), total state O(N). A worker pool uses O(W) workers plus O(N) queued session descriptors, with W bounded independently of N.
