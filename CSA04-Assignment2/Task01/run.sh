#!/bin/sh
set -eu
gcc -std=c11 -Wall -Wextra -O2 process_demo.c -o process_demo
./process_demo
