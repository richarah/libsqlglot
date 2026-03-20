#!/bin/bash
# Simple continuous fuzzing - runs fuzzers in cycles forever
cd "$(dirname "$0")"

echo "========================================="
echo "  CONTINUOUS FUZZING - RUNNING FOREVER"
echo "========================================="
echo ""

ITERATION=0

while true; do
    ITERATION=$((ITERATION + 1))
    echo ""
    echo "=== Fuzzing Iteration #${ITERATION} at $(date) ==="
    echo ""
    
    # Run each fuzzer for 60 seconds
    echo "Running fuzzers for 60 seconds..."
    
    timeout 60 ./simple_fuzzer > logs/simple_${ITERATION}.log 2>&1 &
    timeout 60 ./fuzz_edge_cases > logs/edge_${ITERATION}.log 2>&1 &
    timeout 60 ./fuzz_optimizer > logs/opt_${ITERATION}.log 2>&1 &
    timeout 60 ./fuzz_generator > logs/gen_${ITERATION}.log 2>&1 &
    
    wait
    
    echo "Iteration #${ITERATION} complete"
    
    # Show stats
    echo "Stats:"
    tail -1 logs/simple_${ITERATION}.log | grep "Iterations:" || echo "  simple: done"
    tail -1 logs/edge_${ITERATION}.log | grep "Iterations:" || echo "  edge: done"
    
    sleep 5
done
