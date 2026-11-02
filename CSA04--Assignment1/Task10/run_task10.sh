#!/bin/sh
set -eu
gcc -std=c11 -Wall -Wextra -O2 -pthread process_thread_bench.c -o process_thread_bench
./process_thread_bench
/usr/bin/time -v ./process_thread_bench
