#!/bin/bash

# Test parameters (you can modify these to test what you want)
PHILO_ARGS="5 800 200 200 7"

# Number of runs
TIMES=100

# Statistics
DIE_COUNT=0
SUCCESS_COUNT=0

echo "Starting test $TIMES times: parameters = ./philo $PHILO_ARGS"
echo "--------------------------------------------"

for ((i=1; i<=TIMES; i++))
do
    OUTPUT=$(./philo $PHILO_ARGS)
    echo "Run $i result:"
    echo "$OUTPUT" | tail -n 5  # Show only last 5 lines

    if echo "$OUTPUT" | grep -q "died"; then
        ((DIE_COUNT++))
        echo "❌ Philosopher died detected"
    else
        ((SUCCESS_COUNT++))
        echo "✅ All philosophers finished eating successfully"
    fi
    echo "--------------------------------------------"
    sleep 0.2
done

echo "Test completed!"
echo "Success count: $SUCCESS_COUNT / $TIMES"
echo "Death count: $DIE_COUNT / $TIMES"