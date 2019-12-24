#!/bin/bash

# ./runner_final.sh 400 880
# N(min) - 40
# N1 - 400
# N2 - 9200
# STEPS - 10
# N(min) to N1 STEP - (400 - 40) / 10 = 36
# N1 to N2 STEP - (9200 - 400) / 10 = 880

labs=(lab4-runner-mp)

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

N_MIN_STEP=213
echo "N(min) to N1 processing..."
for lab in ${labs[@]}
do
    for i in {0..10}
    do
        iteration=()
        N=$((2200 - i * $N_MIN_STEP))
        for run in {1..3}
        do
            millis=$(./${lab} ${N} | tail -1 | grep -Eo "[0-9]+$")
            iteration+=(${millis})
        done

        sum=$(echo "${iteration[@]/%/+} 0" | bc)
        avg=$((sum / 3))
        runs+=(${avg})
#        echo "Iteration $i complete for N: $N, with avg: $avg"
    done

    last=$((33))
    echo "$lab: From '$1' To '$last' with '$N_MIN_STEP' Step"
    echo "$lab: ALL: ${runs[@]}"
    sum=$(echo "${runs[@]/%/+} 0" | bc)
    avg=$((sum / 10))
    runs=()
    echo "$lab: AVG: $avg"
    echo '-------------------------------------------'
done

echo "N1 to N2 processing..."

for lab in ${labs[@]}
do
    for i in {0..10}
    do
        iteration=()
        N=$(($1 + i * $2))
        for run in {1..3}
        do
            millis=$(./${lab} ${N} | tail -1 | grep -Eo "[0-9]+$")
            iteration+=(${millis})
        done

        sum=$(echo "${iteration[@]/%/+} 0" | bc)
        avg=$((sum / 3))
        runs+=(${avg})
#        echo "Iteration $i complete for N: $N, with avg: $avg"
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

