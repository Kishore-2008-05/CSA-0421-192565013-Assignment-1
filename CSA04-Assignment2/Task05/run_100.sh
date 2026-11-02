#!/bin/sh
set -eu
gcc -std=c11 -Wall -Wextra -O2 -pthread bounded_buffer.c -o bounded_buffer
i=1
while [ "$i" -le 100 ]; do
  ./bounded_buffer 4 4
  i=$((i+1))
done
