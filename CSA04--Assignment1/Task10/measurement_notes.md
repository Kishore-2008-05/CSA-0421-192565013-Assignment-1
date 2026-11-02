# Measurement notes

The process/thread benchmark was compiled with GCC and executed in the report-generation Linux environment.
Recorded run:
- 1,000 fork/wait process cycles: 0.316079 s
- 1,000 pthread create/join cycles: 0.060130 s

These are one-run measurements, not universal constants. Repeat several times on the student's own Linux system and report median/mean with OS, CPU and load conditions. `strace` was not installed in the report-generation environment; do not represent an uncollected strace table as actual evidence.
