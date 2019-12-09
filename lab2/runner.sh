#!/bin/bash

# grep -v "^\t* *//" lab2.c

runs=()
for i in {1..10}
do
	millis=$(./lab1-amd $1 | tail -1 | grep -Eo "[0-9]+$")
	runs+=(${millis})
	echo "$i run completed in $millis millis."
done

sum=$(echo "${runs[@]/%/+} 0" | bc)
avg=$((sum / 10))
echo "Average: $avg"
