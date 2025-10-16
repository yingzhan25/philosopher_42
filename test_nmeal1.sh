#!/bin/bash

# Fixed version test script
TEST_COUNT=100
PHILO_PROGRAM="./philo"
ARGS="5 800 200 200 7"

echo "Starting test: Running $TEST_COUNT times ./philo $ARGS"
echo "=============================================="

success_count=0

for ((i=1; i<=TEST_COUNT; i++))
do
    echo -n "Test $i/$TEST_COUNT: "

    # Run program and capture output
    OUTPUT=$($PHILO_PROGRAM $ARGS 2>&1)

    # Check if program exited normally
    if [ $? -ne 0 ]; then
        echo "Program exited abnormally"
        continue
    fi

    # Count eating times for each philosopher
    EAT_COUNT_PHILO1=$(echo "$OUTPUT" | grep "philo 1 is eating" | wc -l)
    EAT_COUNT_PHILO2=$(echo "$OUTPUT" | grep "philo 2 is eating" | wc -l)
    EAT_COUNT_PHILO3=$(echo "$OUTPUT" | grep "philo 3 is eating" | wc -l)
    EAT_COUNT_PHILO4=$(echo "$OUTPUT" | grep "philo 4 is eating" | wc -l)
    EAT_COUNT_PHILO5=$(echo "$OUTPUT" | grep "philo 5 is eating" | wc -l)

    # Check if all ate 7 times
    if [ $EAT_COUNT_PHILO1 -eq 7 ] && [ $EAT_COUNT_PHILO2 -eq 7 ] && \
       [ $EAT_COUNT_PHILO3 -eq 7 ] && [ $EAT_COUNT_PHILO4 -eq 7 ] && \
       [ $EAT_COUNT_PHILO5 -eq 7 ]; then
        echo "✓ All philosophers ate 7 times"
        ((success_count++))
    else
        echo "✗ Eating count mismatch: 1($EAT_COUNT_PHILO1) 2($EAT_COUNT_PHILO2) 3($EAT_COUNT_PHILO3) 4($EAT_COUNT_PHILO4) 5($EAT_COUNT_PHILO5)"
    fi
done

echo ""
echo "=============================================="
echo "Test completed! Statistics:"
echo "Success count: $success_count/$TEST_COUNT"
echo "Success rate: $(echo "scale=2; $success_count * 100 / $TEST_COUNT" | bc)%"