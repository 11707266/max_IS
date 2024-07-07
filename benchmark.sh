#!/bin/bash

# Function to calculate the time difference in milliseconds
function calculate_time_diff() {
    start_time=$1
    end_time=$2
    diff=$((end_time - start_time))
    echo "Time taken: $diff ms"
}

# Run the tool 5 times and measure the time
for ((i=1; i<=5; i++))
do
    echo "Running iteration $i"
    start_time=$(date +%s%3N)
    ./tool
    end_time=$(date +%s%3N)
    calculate_time_diff $start_time $end_time
done