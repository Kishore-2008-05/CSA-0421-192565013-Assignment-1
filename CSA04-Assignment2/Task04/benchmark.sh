#!/bin/sh
set -eu
gcc -std=c11 -Wall -Wextra -O2 pipe_ipc.c -o pipe_ipc
gcc -std=c11 -Wall -Wextra -O2 shm_ipc.c -o shm_ipc -pthread -lrt
./pipe_ipc
./shm_ipc
echo "For 1, 10 and 100 MiB throughput, extend these demos to transfer a byte buffer"
echo "of each size, time with /usr/bin/time, and repeat at least 5 times."
