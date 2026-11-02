#!/bin/sh
set -eu
gcc -std=c11 -Wall -Wextra -O2 process_control.c -o process_control
./process_control
