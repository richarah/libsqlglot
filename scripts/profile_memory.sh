#!/bin/bash
# Memory profiling with Valgrind and Massif for libsqlglot

set -e

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
PROJECT_ROOT="$(dirname "$SCRIPT_DIR")"
BUILD_DIR="$PROJECT_ROOT/build"

echo "=== libsqlglot Memory Profiling ==="
echo

# Check if Valgrind is installed
if ! command -v valgrind &> /dev/null; then
    echo "ERROR: Valgrind not installed"
    echo "Install with: sudo apt-get install valgrind"
    exit 1
fi

# Check if ms_print is available
if ! command -v ms_print &> /dev/null; then
    echo "WARNING: ms_print not found (part of Valgrind)"
fi

# Build in Release mode with debug symbols
echo "Building with debug symbols..."
cmake -B "$BUILD_DIR" \
      -DCMAKE_BUILD_TYPE=RelWithDebInfo \
      -DCMAKE_CXX_FLAGS="-g" \
      -DLIBSQLGLOT_BUILD_TESTS=ON \
      > /dev/null 2>&1 || {
    echo "ERROR: Build failed"
    exit 1
}
cmake --build "$BUILD_DIR" -j8 > /dev/null 2>&1 || {
    echo "ERROR: Test build failed"
    exit 1
}

TEST_BINARY="$BUILD_DIR/tests/libsqlglot_tests"

if [[ ! -f "$TEST_BINARY" ]]; then
    echo "ERROR: Test executable not found: $TEST_BINARY"
    exit 1
fi

OUTPUT_DIR="$PROJECT_ROOT/profiling_results"
mkdir -p "$OUTPUT_DIR"

# =================================================================
# 1. MEMCHECK - Memory leak detection
# =================================================================
echo "--- Running Memcheck (leak detection) ---"
valgrind --leak-check=full \
         --show-leak-kinds=all \
         --track-origins=yes \
         --verbose \
         --log-file="$OUTPUT_DIR/memcheck.log" \
         "$TEST_BINARY" > /dev/null 2>&1 || true

echo "Memcheck results saved to: $OUTPUT_DIR/memcheck.log"

# Check for leaks
if grep -q "definitely lost: 0 bytes" "$OUTPUT_DIR/memcheck.log"; then
    echo "  [OK] No memory leaks detected"
else
    echo "  [WARN]  Memory leaks found - see log for details"
fi

# =================================================================
# 2. MASSIF - Heap profiling
# =================================================================
echo
echo "--- Running Massif (heap profiler) ---"
valgrind --tool=massif \
         --massif-out-file="$OUTPUT_DIR/massif.out" \
         --stacks=yes \
         "$TEST_BINARY" > /dev/null 2>&1 || true

echo "Massif results saved to: $OUTPUT_DIR/massif.out"

# Generate human-readable report
if command -v ms_print &> /dev/null; then
    ms_print "$OUTPUT_DIR/massif.out" > "$OUTPUT_DIR/massif.txt"

    # Extract peak memory usage
    PEAK_MB=$(grep "peak" "$OUTPUT_DIR/massif.txt" | head -1 | awk '{print $NF}' | sed 's/[^0-9.]//g')
    echo "  Peak memory usage: ${PEAK_MB} MB"

    # Extract key statistics
    echo
    echo "Memory Profile Summary:"
    grep -A 5 "Peak snapshot" "$OUTPUT_DIR/massif.txt" | head -6
else
    echo "  [WARN]  ms_print not available - install valgrind-dbg for visualization"
fi

# =================================================================
# 3. CACHEGRIND - Cache profiling
# =================================================================
echo
echo "--- Running Cachegrind (cache profiler) ---"
valgrind --tool=cachegrind \
         --cachegrind-out-file="$OUTPUT_DIR/cachegrind.out" \
         "$TEST_BINARY" > /dev/null 2>&1 || true

echo "Cachegrind results saved to: $OUTPUT_DIR/cachegrind.out"

# Extract cache statistics
if command -v cg_annotate &> /dev/null; then
    cg_annotate "$OUTPUT_DIR/cachegrind.out" > "$OUTPUT_DIR/cachegrind.txt" 2>&1 || true

    echo "  Cache Statistics:"
    grep "I   refs" "$OUTPUT_DIR/cachegrind.txt" | head -1 || true
    grep "D   refs" "$OUTPUT_DIR/cachegrind.txt" | head -1 || true
    grep "D1  miss" "$OUTPUT_DIR/cachegrind.txt" | head -1 || true
    grep "LL  miss" "$OUTPUT_DIR/cachegrind.txt" | head -1 || true
fi

# =================================================================
# 4. CALLGRIND - Call graph profiling
# =================================================================
echo
echo "--- Running Callgrind (call graph profiler) ---"
valgrind --tool=callgrind \
         --callgrind-out-file="$OUTPUT_DIR/callgrind.out" \
         "$TEST_BINARY" > /dev/null 2>&1 || true

echo "Callgrind results saved to: $OUTPUT_DIR/callgrind.out"
echo "  View with: kcachegrind $OUTPUT_DIR/callgrind.out"

# =================================================================
# SUMMARY
# =================================================================
echo
echo "=== Memory Profiling Complete ===="
echo
echo "Results saved to: $OUTPUT_DIR/"
echo
echo "Key files:"
echo "  - memcheck.log: Memory leak detection"
echo "  - massif.out: Heap memory usage over time"
echo "  - massif.txt: Human-readable heap report"
echo "  - cachegrind.out: CPU cache analysis"
echo "  - callgrind.out: Call graph (view with kcachegrind)"
echo
echo "Analysis Tips:"
echo "  1. Check memcheck.log for 'definitely lost' and 'possibly lost'"
echo "  2. Review massif.txt for peak memory and allocation patterns"
echo "  3. Use kcachegrind for visual analysis of callgrind.out"
echo "  4. Look for unexpected allocations or cache misses"
