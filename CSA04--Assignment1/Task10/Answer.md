# TASK 10 – Measure and Compare (4 marks)

Required commands (run from the task directory on Linux):
1. Compile: `gcc -std=c11 -Wall -Wextra -O2 file_copy.c -o file_copy`
2. Run: `./file_copy`
3. Trace summary: `strace -c ./file_copy`
4. Timing: `/usr/bin/time -v ./file_copy` (or `time ./file_copy`)
5. Process/thread benchmark: `gcc -std=c11 -Wall -Wextra -O2 process_thread_bench.c -o process_thread_bench -pthread && ./process_thread_bench`

Interpretation:
- Increasing copy buffer size should reduce read()/write() syscall counts approximately in proportion to n/b. The actual strace summary also includes startup, file-open/close, write and runtime calls.
- `time` reports elapsed (wall-clock), user CPU and system CPU time. System time generally reflects kernel work; user time reflects application execution. Tiny tests may round to 0.00 seconds, so repeat runs or increase workload.
- Process creation normally costs more memory and kernel bookkeeping than thread creation. Threads share the process address space and most resources; each still needs a stack and thread-control data. fork() uses copy-on-write on Linux, so memory pages are not eagerly duplicated unless modified.
- Measurements are machine- and load-dependent. Record actual results, OS/kernel/GCC versions and test conditions. Do not copy another machine’s timings as personal measurements.

Expected qualitative result:
| Experiment | Expected trend |
|---|---|
| Buffer 1 → 512 → 4096 bytes | Read calls fall 10001 → 21 → 4 for the provided 10,000-byte input |
| Larger buffers | Fewer syscall transitions, usually better sequential-copy throughput until diminishing returns |
| 1,000 threads vs 1,000 processes | Threads usually start with lower overhead; both take measurable time and are subject to system limits |
| user/system time | System time is more affected by syscall/process-management overhead; user time includes loop and application work |

The included benchmark prints measured elapsed time on the machine where it is executed. Its values are not predetermined expected constants.
