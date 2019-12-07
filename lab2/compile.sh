#!/bin/bash
#gcc -O2 -Wall -Werror -o lab1-amd *.c -c -Iframewave/lib

CURR_DIR=$(pwd)
export LD_LIBRARY_PATH="$CURR_DIR/framewave/lib:$LD_LIBRARY_PATH"

gcc -O2 -Wall -Werror -o lab2-amd lab2.c framewave/*.h -Lframewave/lib -lfwSignal -lfwBase -lm #-lrt
echo 'Sequential compiled.'

