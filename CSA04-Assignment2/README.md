# CSA04 Operating Systems – Assignment 2 (CO2)

**Title:** A Performance Analysis of OS Concurrency, Scheduling, and Deadlock Avoidance Algorithms Applied to Real-Time Examination, Telemetry, and Infrastructure Schedulers

> Replace the student placeholders before submission. Run every program on your own Linux system and replace/augment the included reference outputs with your own terminal screenshots and measurements.

## Student details
- Name: Kishore Kumar S
- Register number: 192565013
- GitHub repository: `CSA04-<192565013>-Assignment2
- Compiler: gcc (Ubuntu 15.2.0-16ubuntu1) 15.2.0
- Linux distribution/version: 26.04.1 LTS (Resolute Raccoon)"

## Build conventions
Typical C build command:
```bash
gcc -std=c11 -Wall -Wextra -O2 source.c -o program
```
For POSIX threads/semaphores:
```bash
gcc -std=c11 -Wall -Wextra -O2 -pthread source.c -o program
```
Some programs also use `-lrt` on older Linux systems for POSIX shared memory.

## Task map and run instructions
| Folder | Main files | Build/run |
|---|---|---|
| Task01 | `process_demo.c`, `run.sh` | `bash run.sh` |
| Task02 | `round_robin.c`, `scheduling.py` | `gcc -std=c11 -Wall -Wextra -O2 round_robin.c -o rr && ./rr`; `python3 scheduling.py` |
| Task03 | `camera_threads.c` | `gcc -std=c11 -Wall -Wextra -O2 -pthread camera_threads.c -o camera_threads && ./camera_threads` |
| Task04 | `pipe_ipc.c`, `shm_ipc.c`, `benchmark.sh` | `bash benchmark.sh` |
| Task05 | `bounded_buffer.c`, `run_100.sh` | `gcc -std=c11 -Wall -Wextra -O2 -pthread bounded_buffer.c -o bounded_buffer && ./bounded_buffer 4 4` |
| Task06 | `banker.c`, `banker_bench.c` | `gcc -std=c11 -Wall -Wextra -O2 banker.c -o banker && ./banker`; compile/run benchmark similarly |

## Result notes
- Task01 demonstrates forked child processes and inspects PID/state through `ps` and `/proc`.
- Task02 implements Round Robin and compares FCFS, SJF, SRTF, priority and RR for the assignment's four jobs. Priority values are an explicit assumption in the analysis because the sheet does not supply them.
- Task03 compares serial camera-frame work with one-thread-per-camera and bounded thread pools of 4, 8 and 16 workers.
- Task04 demonstrates pipe EOF signalling and POSIX shared memory with a process-shared semaphore. The benchmark script tests 1, 10 and 100 MiB; record your machine's timings.
- Task05 implements a bounded buffer with empty/full semaphores and a mutex. The command-line options select producer and consumer counts; the default is one each.
- Task06 implements the supplied Banker's safety/request logic and a scalable safety-algorithm benchmark.

## Evidence checklist
For each task, retain:
1. C source and any Python/shell/configuration files.
2. Exact compile and run commands.
3. Actual terminal output saved as `.txt`.
4. Your own terminal screenshot (not a generated illustration).
5. A short interpretation and complexity comparison.
6. At least one progressive Git commit for the task.

## Important execution note
Reference output files in this package are examples or expected-format captures. Timing results vary by CPU, Linux kernel, compiler, load, and virtualization. Do not present reference timings as measurements from your own laptop. Run the programs locally and replace the timing files/screenshots with your own evidence.

## Screenshot clarification
The PNGs under each `screenshots/` folder are clearly labelled reference captures. They are not native screenshots from your laptop. Capture your own terminal with the program running and add those images before final submission.
