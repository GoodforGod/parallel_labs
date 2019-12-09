#!/bin/bash

# ./runner_final.sh 400 880
# N1 - 400
# N2 - 9200
# STEPS - 10
# STEP - (9200 - 400) / 10 = 880

labs=(lab4-mp)

runs=()

labs_source=()

suffixes=()

for lab in ${labs_source[@]}
do
    labs+=(${lab})
    for suffix in ${suffixes[@]}
    do
        labs+=(${lab}${suffix})
    done
done


for lab in ${labs[@]}
do
    for i in {0..10}
    do
        iteration=()
        N=$(($1 + i * $2))
        for run in {1..10}
        do
            millis=$(./${lab} ${N} | tail -1 | grep -Eo "[0-9]+$")
            iteration+=(${millis})
        done

        sum=$(echo "${iteration[@]/%/+} 0" | bc)
        avg=$((sum / 10))
#        echo "$lab: All: ${iteration[@]} for i: $i"
#        echo "$lab: Average: $avg for i: $i"
        runs+=(${avg})
    done

    last=$(($1 + 10 * $2))
    echo "$lab: From '$1' To '$last' with '$2' Step"
    echo "$lab: ALL: ${runs[@]}"
    sum=$(echo "${runs[@]/%/+} 0" | bc)
    avg=$((sum / 10))
    runs=()
    echo "$lab: AVG: $avg"
    echo '-------------------------------------------'
done
