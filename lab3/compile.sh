#!/bin/bash

labs=(lab3-dynamic lab3-static lab3-guided)

suffixes=(-4 -8 -16 -25 -32 -128)

gcc -O2 -Wall -Werror -o lab3-mp lab3.c -lm -fopenmp
echo "OpenMP lab3.c compiled."

for lab in ${labs[@]}
do
    gcc -O2 -Wall -Werror -o ${lab}-mp ${lab}.c -lm -fopenmp
    echo "OpenMP $lab compiled."

    for suffix in ${suffixes[@]}
    do
        gcc -O2 -Wall -Werror -o ${lab}-mp${suffix} ${lab}${suffix}.c -lm -fopenmp
        echo "OpenMP $lab$suffix compiled."
    done
done

