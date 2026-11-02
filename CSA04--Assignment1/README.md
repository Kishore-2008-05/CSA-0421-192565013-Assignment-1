# CSA04 – Operating Systems Assignment 1

**Title:** Evaluate and Justify the Operating-System Design of a Smart Hospital  
**Student name:** [Enter your name]  
**Register number:** [Enter your register number]  
**Submission date:** 02/11/2026  
**GitHub repository name:** `CSA04--Assignment1`

## Contents

This repository is organized into 12 task folders. Each task folder contains its written answer; practical tasks include source code, run scripts, output files and generated output captures where applicable. Tasks 11 and 12 include architecture diagrams.
- `Task01` through `Task12`: task-wise written answers.
- `Task05`: system-call C program, sample input, run script and output capture.
- `Task06`: completed file-copy C program, expected output, run script and output capture.
- `Task07`: completed process-control C program, expected output, run script and output capture.
- `Task10`: process/thread benchmark, run script, recorded timing note and output capture.
- `Task11` and `Task12`: architecture diagrams.

## Compiler and environment used for the recorded execution
- GCC: gcc (Debian 14.2.0-19) 14.2.0
- Platform: Linux 6.18.57 x86_64 GNU/Linux
- `strace`: not installed in this execution environment. Install it on Ubuntu/Debian with `sudo apt update && sudo apt install strace`.

Confirm these details against the environment where you personally re-run the programs.

## Compile and run
From repository root:

```bash
(cd Task05 && sh run_task05.sh)
(cd Task06 && sh run_task06.sh)
(cd Task07 && sh run_task07.sh)
(cd Task10 && sh run_task10.sh)
```

Equivalent compile commands:
```bash
gcc -std=c11 -Wall -Wextra -O2 Task05/system_calls.c -o Task05/system_calls
gcc -std=c11 -Wall -Wextra -O2 Task06/file_copy.c -o Task06/file_copy
gcc -std=c11 -Wall -Wextra -O2 Task07/process_control.c -o Task07/process_control
gcc -std=c11 -Wall -Wextra -O2 -pthread Task10/process_thread_bench.c -o Task10/process_thread_bench
```

## strace and time evidence to collect on your own Linux machine
```bash
cd Task05 && strace -o trace.txt ./system_calls
cd ../Task06 && strace -c ./file_copy
cd ../Task10 && /usr/bin/time -v ./process_thread_bench
```
The generated `output_capture.png` images are labelled output captures made from the execution records, not native screenshots from your personal desktop. Capture fresh terminal screenshots on your own Linux environment for the final submission.

## Actual recorded output
Task 06:
```text
buffer    1 bytes: 10001 read() calls
buffer  512 bytes:    21 read() calls
buffer 4096 bytes:     4 read() calls
```
Task 07:
```text
shell: running job 1
42
job 1 exit status 0
shell: running job 2
job 2 exit status 3
```
Task 10 one recorded run:
```text
Created and reaped 1000 processes: 0.316079 seconds
Created and joined 1000 threads:  0.060130 seconds
```
Timing results vary by machine and system load.

## Submission checklist
- Fill student name and register number.
- Create the repository named `CSA04--Assignment1` exactly as specified in the assignment brief.
- Add the faculty as collaborator if private.
- Commit progressively, at least one commit per task.
- Replace/augment output captures with personal terminal screenshots.
- Collect actual `strace` output and any required timing results.
- Paste the working GitHub URL into this README and the report cover page.
