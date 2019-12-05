#!/bin/bash

gcc -O2 -Wall -Werror -o lab1-seq lab2.c -lm
echo 'Sequential compiled.'

gcc -O2 -Wall -Werror -floop-parallelize-all -ftree-parallelize-loops=2 lab2.c -o lab1-par-2 -lm
echo 'Parallel 2 compiled.'

gcc -O2 -Wall -Werror -floop-parallelize-all -ftree-parallelize-loops=4 lab2.c -o lab1-par-4 -lm
echo 'Parallel 4 compiled.'

gcc -O2 -Wall -Werror -floop-parallelize-all -ftree-parallelize-loops=6 lab2.c -o lab1-par-6 -lm
echo 'Parallel 6 compiled.'

gcc -O2 -Wall -Werror -floop-parallelize-all -ftree-parallelize-loops=8 lab2.c -o lab1-par-8 -lm
echo 'Parallel 8 compiled.'
