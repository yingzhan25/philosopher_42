#!/bin/bash

# Quick test script
echo "Quick test: ./philo 5 800 200 200 - Running 20 times"
echo "======================================"

for i in {1..20}; do
    echo -n "Test $i: "
    OUTPUT=$(timeout 10s ./philo 5 800 200 200 2>&1)
    if echo "$OUTPUT" | grep -q "is died"; then
        DEATH_INFO=$(echo "$OUTPUT" | grep "is died" | head -1)
        echo "Death: $DEATH_INFO"
    else
        echo "Normal exit"
    fi
done