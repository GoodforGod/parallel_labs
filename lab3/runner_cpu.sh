#!/bin/bash

# ./runner_final.sh 400 880
# N1 - 400
# N2 - 9200
# STEPS - 10
# STEP - (9200 - 400) / 10 = 880

N1=9200
./lab3-dynamic-mp-25 ${N1} > /dev/null &
LAB_PID=$!
echo ${LAB_PID}

CPU=$(top -b -n1 -p ${LAB_PID}) #| head -1 | awk '{print $9}')
echo ${CPU}
