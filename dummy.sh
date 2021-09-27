#!/bin/bash
rm output.obj
gcc -std=c99 lc3bsim2.c -o simulate
./simulate output.obj <<EOF
run 1
quit
EOF