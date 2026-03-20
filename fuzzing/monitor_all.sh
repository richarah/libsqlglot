#!/bin/bash
# Continuous fuzzing monitor
# Shows real-time stats from all running fuzzers

cd "$(dirname "$0")"

echo "==================================="
echo "   FUZZING CAMPAIGN MONITOR"
echo "==================================="
echo ""
echo "Press Ctrl+C to stop monitoring"
echo ""

while true; do
    clear
    echo "==================================="
    echo "   FUZZING STATUS REPORT"
    echo "   $(date)"
    echo "==================================="
    echo ""

    # Transpiler fuzzer
    if [ -f fuzzer_transpiler.log ]; then
        echo "📊 TRANSPILER FUZZER (simple_fuzzer)"
        tail -1 fuzzer_transpiler.log | grep -o "Iterations: [0-9]* | Corpus: [0-9]* | Crashes: [0-9]* | Rate: [0-9]*/s" || echo "  Status: Running..."
        echo ""
    fi

    # Optimizer fuzzer
    if [ -f fuzzer_optimizer.log ]; then
        echo "🔧 OPTIMIZER FUZZER (fuzz_optimizer)"
        tail -1 fuzzer_optimizer.log | grep -o "Iterations: [0-9]* | .* | Crashes: [0-9]* | Rate: [0-9]*/s" || echo "  Status: Running..."
        echo ""
    fi

    # Generator fuzzer
    if [ -f fuzzer_generator.log ]; then
        echo "⚙️  GENERATOR FUZZER (fuzz_generator)"
        tail -1 fuzzer_generator.log | grep -o "Iterations: [0-9]* | .* | Crashes: [0-9]* | Rate: [0-9]*/s" || echo "  Status: Running..."
        echo ""
    fi

    # Edge case fuzzer
    if [ -f fuzzer_edge_cases.log ]; then
        echo "🎯 EDGE CASE FUZZER (fuzz_edge_cases)"
        tail -1 fuzzer_edge_cases.log | grep -o "Iterations: [0-9]* | .* | Crashes: [0-9]* | Rate: [0-9]*/s" || echo "  Status: Running..."
        echo ""
    fi

    echo "==================================="
    echo ""

    # Check for crashes
    CRASHES=$(grep -h "CRASH" fuzzer_*.log 2>/dev/null | wc -l)
    if [ "$CRASHES" -gt 0 ]; then
        echo "⚠️  WARNING: $CRASHES crashes detected!"
        echo "Check logs for details"
        echo ""
    fi

    # Process stats
    echo "📈 SYSTEM STATUS"
    ps aux | grep -E "(simple_fuzzer|fuzz_optimizer|fuzz_generator|fuzz_edge)" | grep -v grep | awk '{printf "  PID %-8s  CPU: %5s%%  MEM: %5s%%  CMD: %s\n", $2, $3, $4, $11}' || echo "  No fuzzers running"
    echo ""

    echo "Refreshing in 5 seconds..."
    sleep 5
done
