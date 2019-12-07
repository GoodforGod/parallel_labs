#!/bin/bash
#gcc -O2 -Wall -Werror -o lab1-amd *.c -c -Iframewave/lib

gcc -O2 -Wall -Werror -o lab2-amd lab2.c -lm -Llib -lfwBase -lfwSignal #-lrt
echo 'Sequential compiled.'

