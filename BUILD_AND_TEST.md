# Build and Test Instructions

## Quick Start

```bash
# Clean, build, and test everything
./scripts/comprehensive_test.sh
```

## Manual Steps

### 1. Clean Repository

```bash
# Remove build artifacts
rm -rf build build_test build_release

# Remove Python cache
find . -type d -name "__pycache__" -exec rm -rf {} +
find . -type f -name "*.pyc" -delete
```

### 2. Verify Dialects

Ensure all dialect patches are accurate (not confabulated):

```bash
python3 scripts/verify_dialects.py
```

Expected output:
```
✓ VERIFIED redshift
✓ VERIFIED duckdb
... (29 total)
✓ All patches verified successfully!
```

### 3. Configure Build

```bash
mkdir -p build && cd build

# Debug build with all features
cmake .. \
  -DCMAKE_BUILD_TYPE=Debug \
  -DLIBSQLGLOT_BUILD_TESTS=ON \
  -DLIBSQLGLOT_BUILD_BENCHMARKS=ON

# OR Release build
cmake .. \
  -DCMAKE_BUILD_TYPE=Release \
  -DLIBSQLGLOT_BUILD_TESTS=ON \
  -DLIBSQLGLOT_BUILD_BENCHMARKS=ON
```

### 4. Build

```bash
# Build all targets (merges 29 dialect grammars)
make -j$(nproc)

# OR build specific targets
make libsqlglot_tests          # Test executable
make merge_dialects            # Just dialect merging
make bench_tokenizer           # Tokenizer benchmark
make bench_parser              # Parser benchmark
```

### 5. Run Tests

```bash
# Run all tests
ctest --output-on-failure

# Run specific test suites
./tests/libsqlglot_tests "[dialect]"         # Dialect tests only
./tests/libsqlglot_tests "[tokenizer]"       # Tokenizer tests
./tests/libsqlglot_tests "[parser]"          # Parser tests

# Run with verbose output
./tests/libsqlglot_tests -v
```

Expected: **360/360 tests passing**

### 6. Run Benchmarks

```bash
# Tokenizer benchmark
./benchmarks/bench_tokenizer --benchmark_min_time=1s

# Parser benchmark
./benchmarks/bench_parser --benchmark_min_time=1s

# Transpiler benchmark
./benchmarks/bench_transpiler --benchmark_min_time=1s

# Compare with baseline
./benchmarks/bench_tokenizer --benchmark_out=current.json --benchmark_out_format=json
```

### 7. Run Fuzzing (Optional, Clang only)

```bash
# Configure with fuzzing enabled
mkdir -p build_fuzz && cd build_fuzz
CC=clang CXX=clang++ cmake .. \
  -DLIBSQLGLOT_FUZZ=ON \
  -DLIBSQLGLOT_BUILD_TESTS=OFF

make -j$(nproc)

# Run fuzz targets
./tests/fuzz/fuzz_tokenizer -max_total_time=60
./tests/fuzz/fuzz_parser -max_total_time=60
```

## Verification Checklist

- [ ] Repository cleaned
- [ ] All 29 dialect patches verified
- [ ] Build completes without errors
- [ ] All 360 tests pass
- [ ] Benchmarks run successfully
- [ ] 29 dialect grammars generated in `build/generated/grammar_data/`
- [ ] No confabulated dialect features

## Continuous Integration

For CI/CD pipelines:

```bash
# Full CI test suite
./scripts/comprehensive_test.sh

# Exit code 0 = success, non-zero = failure
echo $?
```

## Troubleshooting

**Problem**: Dialect verification fails
- **Solution**: Check `dialects/patches/*.json` against official documentation
- **Solution**: Run `python3 scripts/verify_dialects.py` for details

**Problem**: Tests fail
- **Solution**: Check for missing dialect keywords in `include/libsqlglot/tokens.h`
- **Solution**: Rebuild with `make clean && make`

**Problem**: Benchmarks show regression
- **Solution**: Profile with `perf record ./benchmarks/bench_tokenizer`
- **Solution**: Check operator text interning is not over-used

## Performance Targets

Based on antlr branch benchmarks:

- **Tokenizer**: ~3-10% overhead vs master (acceptable for 29 new dialects)
- **Parser**: ~0-4% overhead vs master
- **Transpiler**: Equivalent to master

## Dialect Coverage

- **Total**: 46 SQL dialects
- **Base grammars**: 17 (from ANTLR extraction)
- **Patches**: 29 (inheritance-based)
- **SQLGlot parity**: 100% (all 31+ dialects)
- **Additional**: +15 production databases
