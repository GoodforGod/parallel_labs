#!/bin/bash

labs=(lab5 lab5-runner)

suffixes=()

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

