#!/bin/bash

gcc -O2 -Wall -Werror -o lab3-mp lab3.c -lm -fopenmp
echo 'OpenMP compiled.'

