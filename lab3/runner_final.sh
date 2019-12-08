#!/bin/bash

runs=()

labs=(lab3-mp)

# N1 - 300
# N2 - 7400
# STEP - 710
# STEPS - 10

for lab in ${labs[@]}
do
    for i in {0..10}
    do
        N=$(($1 + i * $2))
        millis=$(./${lab} ${N} | tail -1 | grep -Eo "[0-9]+$")
        runs+=(${millis})
        #echo "Seq $i run completed in $millis millis for N $N."
    done

    last=$(($1 + 10 * $2))
    echo "$lab: From '$1' To '$last' with '$2' Step"
    echo "ALL: ${runs[@]}"
    sum=$(echo "${runs[@]/%/+} 0" | bc)
    avg=$((sum / 10))
    runs=()
    echo "AVG: $avg"
done

