#!/bin/sh
set -eu
gcc -std=c11 -Wall -Wextra -O2 system_calls.c -o system_calls
printf 'Smart hospital system-call demonstration.\\n' > sample.txt
./system_calls
# For syscall tracing, install strace and run:
# strace -o trace.txt ./system_calls
# strace -c ./system_calls
