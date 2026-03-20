#!/bin/bash
# CPU profiling with perf and gprof for libsqlglot

set -e

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
PROJECT_ROOT="$(dirname "$SCRIPT_DIR")"
BUILD_DIR="$PROJECT_ROOT/build"

echo "=== libsqlglot CPU Profiling ==="
echo

# =================================================================
# OPTION 1: perf (Linux performance analyzer)
# =================================================================
if command -v perf &> /dev/null; then
    echo "--- Using perf (Linux Performance Analyzer) ---"

    # Build in Release mode with debug symbols
    echo "Building with debug symbols..."
    cmake -B "$BUILD_DIR" \
          -DCMAKE_BUILD_TYPE=RelWithDebInfo \
          -DLIBSQLGLOT_BUILD_TESTS=ON \
          > /dev/null 2>&1
    cmake --build "$BUILD_DIR" -j8 > /dev/null 2>&1

    TEST_BINARY="$BUILD_DIR/tests/libsqlglot_tests"
    OUTPUT_DIR="$PROJECT_ROOT/profiling_results"
    mkdir -p "$OUTPUT_DIR"

    # Record performance data
    echo "Recording performance data (this may take a minute)..."
    sudo perf record -F 999 -g -o "$OUTPUT_DIR/perf.data" "$TEST_BINARY" 2>&1 | grep -v "^$" || {
        echo "  [WARN]  perf record requires sudo permissions"
        echo "  Run: sudo ./scripts/profile_cpu.sh"
    }

    if [[ -f "$OUTPUT_DIR/perf.data" ]]; then
        # Generate report
        echo
        echo "Generating perf report..."
        sudo perf report -i "$OUTPUT_DIR/perf.data" --stdio > "$OUTPUT_DIR/perf_report.txt" 2>/dev/null || true

        echo "CPU Profile (Top 20 functions):"
        head -40 "$OUTPUT_DIR/perf_report.txt" | grep -A 20 "Overhead"

        echo
        echo "Full report saved to: $OUTPUT_DIR/perf_report.txt"
        echo "Interactive view: sudo perf report -i $OUTPUT_DIR/perf.data"

        # Generate flame graph if available
        if command -v flamegraph.pl &> /dev/null; then
            echo
            echo "Generating flame graph..."
            sudo perf script -i "$OUTPUT_DIR/perf.data" | \
                flamegraph.pl > "$OUTPUT_DIR/flamegraph.svg"
            echo "Flame graph saved to: $OUTPUT_DIR/flamegraph.svg"
        fi
    fi

# =================================================================
# OPTION 2: gprof (GNU profiler)
# =================================================================
elif command -v gprof &> /dev/null; then
    echo "--- Using gprof (GNU Profiler) ---"

    # Build with profiling enabled
    echo "Building with gprof instrumentation..."
    cmake -B "$BUILD_DIR" \
          -DCMAKE_BUILD_TYPE=Release \
          -DCMAKE_CXX_FLAGS="-pg -g" \
          -DCMAKE_EXE_LINKER_FLAGS="-pg" \
          -DLIBSQLGLOT_BUILD_TESTS=ON \
          > /dev/null 2>&1
    cmake --build "$BUILD_DIR" -j8 > /dev/null 2>&1

    TEST_BINARY="$BUILD_DIR/tests/libsqlglot_tests"
    OUTPUT_DIR="$PROJECT_ROOT/profiling_results"
    mkdir -p "$OUTPUT_DIR"

    # Run tests (generates gmon.out)
    echo "Running tests with gprof instrumentation..."
    cd "$BUILD_DIR/tests"
    ./libsqlglot_tests > /dev/null

    if [[ -f "gmon.out" ]]; then
        # Generate report
        echo
        echo "Generating gprof report..."
        gprof ./libsqlglot_tests gmon.out > "$OUTPUT_DIR/gprof_report.txt"

        echo "CPU Profile (Flat profile):"
        grep -A 30 "Flat profile:" "$OUTPUT_DIR/gprof_report.txt" | head -35

        echo
        echo "Full report saved to: $OUTPUT_DIR/gprof_report.txt"

        mv gmon.out "$OUTPUT_DIR/"
    fi

# =================================================================
# FALLBACK: Time-based sampling
# =================================================================
else
    echo "[WARN]  Neither perf nor gprof available"
    echo
    echo "To install:"
    echo "  - perf: sudo apt-get install linux-tools-generic"
    echo "  - gprof: part of build-essential"
    echo
    echo "Falling back to simple timing analysis..."

    cmake -B "$BUILD_DIR" \
          -DCMAKE_BUILD_TYPE=Release \
          -DLIBSQLGLOT_BUILD_TESTS=ON \
          > /dev/null 2>&1
    cmake --build "$BUILD_DIR" -j8 > /dev/null 2>&1

    TEST_BINARY="$BUILD_DIR/tests/libsqlglot_tests"

    echo
    echo "Running tests with time measurement..."
    /usr/bin/time -v "$TEST_BINARY" 2>&1 | grep -E "(User time|System time|Maximum resident|Page faults)"
fi

# =================================================================
# SUMMARY
# =================================================================
echo
echo "=== CPU Profiling Complete ==="
echo
echo "Analysis Tips:"
echo "  1. Look for hot functions taking >5% of total time"
echo "  2. Check for unexpected function calls in hot path"
echo "  3. Verify string operations aren't dominating"
echo "  4. Confirm hash map lookups are O(1)"
