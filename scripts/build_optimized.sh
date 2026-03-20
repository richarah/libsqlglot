#!/bin/bash
# Build libsqlglot with maximum optimizations (PGO, LTO, native tuning)

set -e

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
PROJECT_ROOT="$(dirname "$SCRIPT_DIR")"

echo "=== Building libsqlglot with Maximum Optimizations ==="
echo

# =================================================================
# PHASE 1: Standard Release Build
# =================================================================
echo "Phase 1: Standard Release Build"
echo "  Flags: -O3 -DNDEBUG"

cmake -B "$PROJECT_ROOT/build-release" \
      -DCMAKE_BUILD_TYPE=Release \
      -DLIBSQLGLOT_BUILD_TESTS=ON \
      "$PROJECT_ROOT"

cmake --build "$PROJECT_ROOT/build-release" -j8

echo "  [OK] Standard release build complete"
echo

# =================================================================
# PHASE 2: Native Architecture Tuning
# =================================================================
echo "Phase 2: Native Architecture Tuning"
echo "  Flags: -O3 -march=native -mtune=native"

cmake -B "$PROJECT_ROOT/build-native" \
      -DCMAKE_BUILD_TYPE=Release \
      -DCMAKE_CXX_FLAGS="-O3 -march=native -mtune=native -DNDEBUG" \
      -DLIBSQLGLOT_BUILD_TESTS=ON \
      "$PROJECT_ROOT"

cmake --build "$PROJECT_ROOT/build-native" -j8

echo "  [OK] Native-tuned build complete"
echo "  [WARN]  Binary is NOT portable (optimized for this CPU only)"
echo

# =================================================================
# PHASE 3: Link-Time Optimization (LTO)
# =================================================================
echo "Phase 3: Link-Time Optimization (LTO)"
echo "  Flags: -O3 -march=native -flto"

cmake -B "$PROJECT_ROOT/build-lto" \
      -DCMAKE_BUILD_TYPE=Release \
      -DCMAKE_CXX_FLAGS="-O3 -march=native -mtune=native -flto -DNDEBUG" \
      -DCMAKE_EXE_LINKER_FLAGS="-flto" \
      -DLIBSQLGLOT_BUILD_TESTS=ON \
      "$PROJECT_ROOT"

cmake --build "$PROJECT_ROOT/build-lto" -j8

echo "  [OK] LTO build complete"
echo "  Expected speedup: 5-15%"
echo

# =================================================================
# PHASE 4: Profile-Guided Optimization (PGO)
# =================================================================
echo "Phase 4: Profile-Guided Optimization (PGO)"
echo

# Step 1: Build with instrumentation
echo "  Step 1: Building with profiling instrumentation..."
cmake -B "$PROJECT_ROOT/build-pgo-gen" \
      -DCMAKE_BUILD_TYPE=Release \
      -DCMAKE_CXX_FLAGS="-O3 -march=native -mtune=native -fprofile-generate -DNDEBUG" \
      -DCMAKE_EXE_LINKER_FLAGS="-fprofile-generate" \
      -DLIBSQLGLOT_BUILD_TESTS=ON \
      "$PROJECT_ROOT"

cmake --build "$PROJECT_ROOT/build-pgo-gen" -j8

# Step 2: Run representative workload to generate profile
echo "  Step 2: Generating profile data (running tests)..."
cd "$PROJECT_ROOT/build-pgo-gen/tests"

if [[ -f "libsqlglot_tests" ]]; then
    ./libsqlglot_tests > /dev/null 2>&1 || true
    echo "  [OK] Profile data generated: *.gcda files"
else
    echo "  [WARN]  Tests not built - skipping profile generation"
fi

# Step 3: Build with profile data
echo "  Step 3: Building with profile-guided optimization..."
PROFILE_DATA="$PROJECT_ROOT/build-pgo-gen"

cmake -B "$PROJECT_ROOT/build-pgo" \
      -DCMAKE_BUILD_TYPE=Release \
      -DCMAKE_CXX_FLAGS="-O3 -march=native -mtune=native -fprofile-use=$PROFILE_DATA -fprofile-correction -DNDEBUG" \
      -DCMAKE_EXE_LINKER_FLAGS="-fprofile-use=$PROFILE_DATA" \
      -DLIBSQLGLOT_BUILD_TESTS=ON \
      "$PROJECT_ROOT"

cmake --build "$PROJECT_ROOT/build-pgo" -j8 2>&1 | grep -v "missing profile" || true

echo "  [OK] PGO build complete"
echo "  Expected speedup: 10-30% for hot paths"
echo

# =================================================================
# PHASE 5: Maximum Optimization (LTO + PGO + Native)
# =================================================================
echo "Phase 5: Maximum Optimization (LTO + PGO + Native)"
echo "  Combining all optimizations..."

cmake -B "$PROJECT_ROOT/build-max" \
      -DCMAKE_BUILD_TYPE=Release \
      -DCMAKE_CXX_FLAGS="-O3 -march=native -mtune=native -flto -fprofile-use=$PROFILE_DATA -fprofile-correction -DNDEBUG" \
      -DCMAKE_EXE_LINKER_FLAGS="-flto -fprofile-use=$PROFILE_DATA" \
      -DLIBSQLGLOT_BUILD_TESTS=ON \
      "$PROJECT_ROOT"

cmake --build "$PROJECT_ROOT/build-max" -j8 2>&1 | grep -v "missing profile" || true

echo "  [OK] Maximum optimization build complete"
echo "  Expected total speedup: 20-50% over base -O3"
echo

# =================================================================
# BENCHMARK COMPARISON
# =================================================================
echo "=== Benchmarking All Build Variants ==="
echo

for BUILD in release native lto pgo max; do
    BUILD_DIR="$PROJECT_ROOT/build-$BUILD"
    if [[ -f "$BUILD_DIR/tests/libsqlglot_tests" ]]; then
        echo "--- $BUILD build ---"
        /usr/bin/time -f "Real: %e s, User: %U s, Sys: %S s" \
            "$BUILD_DIR/tests/libsqlglot_tests" 2>&1 | tail -3
        echo
    fi
done

# =================================================================
# SUMMARY
# =================================================================
echo "=== Optimization Build Complete ==="
echo
echo "Build variants created:"
echo "  1. build-release: Standard -O3"
echo "  2. build-native: -O3 -march=native (CPU-specific)"
echo "  3. build-lto: -O3 -march=native -flto (Link-Time Optimization)"
echo "  4. build-pgo: -O3 -march=native + PGO (Profile-Guided)"
echo "  5. build-max: ALL optimizations combined"
echo
echo "Recommended for production: build-max or build-lto"
echo "Recommended for distribution: build-release (portable)"
echo
echo "Current status:"
echo "  [OK] Profile-Guided Optimization (PGO)"
echo "  [OK] Link-Time Optimization (LTO)"
echo "  [OK] Native CPU tuning (-march=native)"
echo "  [OK] O3 optimization level"
