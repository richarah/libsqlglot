# libsqlglot Optimization Strategy

## Overview

This document outlines the comprehensive optimization strategy for libsqlglot, covering:
1. **Per-file optimization levels** (-O3, -O2, -Os)
2. **Profile-Guided Optimization (PGO)**
3. **Benchmarking and profiling methodology**
4. **Build configuration best practices**

## Optimization Philosophy

**Goal**: Maximum performance where it matters, minimal binary bloat where it doesn't.

### Key Principles

1. **Profile-driven**: Make optimization decisions based on actual profiling data
2. **Hot path focus**: Prioritize the 20% of code that accounts for 80% of execution time
3. **Size-aware**: Binary size matters for downloads, cache efficiency, and startup time
4. **Compile-time conscious**: Balance runtime performance with reasonable build times

## Optimization Levels

### -O3: Maximum Performance
**Use for**: Hot paths that are CPU-intensive and called frequently

**Characteristics**:
- Aggressive inlining (up to 2000 inline limit)
- Loop unrolling and vectorization
- Aggressive constant propagation
- More aggressive aliasing assumptions

**Best for**:
- Tokenizer (character-by-character processing)
- Parser (recursive descent, heavy branching)
- String interning (hash table lookups)
- Arena allocator (frequent small allocations)

**Code patterns that benefit**:
```cpp
// Tight loops
for (char c : source) {
    if (is_alpha(c)) { ... }  // Branch prediction benefits
}

// Frequent function calls that can be inlined
inline bool is_keyword(std::string_view token) {
    return keyword_map.find(token) != keyword_map.end();
}
```

### -O2: Balanced Optimization
**Use for**: Template-heavy code, moderate hot paths

**Characteristics**:
- Most optimizations without the compile-time cost of -O3
- Conservative inlining
- Good balance for most code

**Best for**:
- Template-heavy code (excessive -O3 inlining causes bloat)
- Medium-frequency paths (error handling, less common SQL features)
- Code with complex control flow

**Code patterns**:
```cpp
// Heavy template instantiation
template<typename Dialect>
class DialectGenerator { ... };  // Many specializations

// Complex branching (better with -O2 to avoid over-optimization)
if (complex_condition_1 && complex_condition_2) { ... }
```

### -Os: Optimize for Size
**Use for**: Cold paths, error handling, Python bindings

**Characteristics**:
- Prioritize code size over speed
- Minimal inlining
- Compact code generation

**Best for**:
- Error messages and error handling (rarely executed)
- Python bindings (large due to nanobind templates)
- Initialization code (run once)
- Rarely-used SQL features

**Code patterns**:
```cpp
// Error handling (cold path)
void throw_parse_error(const std::string& msg) {
    throw ParseError(msg);  // Rarely called
}

// Infrequently used features
void parse_obscure_sql_feature() {
    // Complex but rarely called
}
```

## Profile-Guided Optimization (PGO)

### Three-Phase Process

#### Phase 1: Instrument (-fprofile-generate)
```bash
cmake -B build -DCMAKE_BUILD_TYPE=Release \
      -DLIBSQLGLOT_PGO_GENERATE=ON
cmake --build build -j8
```

**Output**: Instrumented binary that records execution patterns

#### Phase 2: Training Workload
```bash
python3 scripts/profile_optimization.py
```

**Workload covers**:
- Simple SELECT queries (10,000 iterations)
- JOIN queries (5,000 iterations)
- Complex CTEs and window functions (2,000 iterations)
- Cross-dialect transpilation (5,000 iterations)
- Procedural SQL (2,000 iterations)
- DML statements (5,000 iterations)

**Profile data captured**:
- Branch probabilities
- Function call frequencies
- Hot/cold code paths
- Inlining opportunities

#### Phase 3: Optimized Build (-fprofile-use)
```bash
cmake -B build -DCMAKE_BUILD_TYPE=Release \
      -DLIBSQLGLOT_PGO_USE=ON
cmake --build build -j8
```

**Optimizations applied**:
- Hot functions inlined more aggressively
- Cold code moved out of hot paths
- Branch prediction optimized
- Function layout optimized for cache locality

### Expected Improvements

Based on typical PGO results for parsers/compilers:
- **10-30%** improvement in hot paths (tokenizer, parser)
- **5-15%** overall throughput improvement
- **Better cache utilization** through improved code layout
- **Reduced branch mispredictions**

## Per-File Optimization Matrix

### Hot Paths (-O3)
*After profiling, populate with actual hotspots*

| File | Reason | Expected Impact |
|------|--------|-----------------|
| `tokenizer.h` (inline methods) | Character processing, heavy branching | High |
| `parser.h` (parse methods) | Recursive descent, frequent calls | High |
| `intern.h` (string pool) | Hash lookups, called for every identifier | Medium-High |
| `arena.h` (allocate methods) | Called for every AST node | Medium |

### Size-Optimized (-Os)
| File | Reason | Binary Size Savings |
|------|--------|---------------------|
| `src/python/bindings.cpp` | Nanobind templates, large | ~500KB - 1MB |
| `src/python/expr_type_bindings_generated.h` | 124+ enum bindings | ~200KB |
| Error handling functions | Rarely executed | ~100KB |

### Template-Heavy (-O2)
| File | Reason | Compile Time Savings |
|------|--------|----------------------|
| Dialect-specific generators | Many template specializations | 30-50% |
| Expression visitor templates | Complex template recursion | 40-60% |

## Benchmarking Methodology

### Running Benchmarks

```bash
# Build with benchmarks enabled
cmake -B build -DCMAKE_BUILD_TYPE=Release \
      -DLIBSQLGLOT_BUILD_BENCHMARKS=ON
cmake --build build -j8

# Run all benchmarks
cd build
make run_benchmarks

# Or run specific benchmarks
./benchmarks/bench_optimization_levels
./benchmarks/bench_tokenizer
./benchmarks/bench_parser
```

### Benchmark Categories

1. **Tokenizer** (10 benchmarks)
   - Simple queries
   - Complex queries
   - Long identifiers
   - String literals
   - Comments

2. **Parser** (15 benchmarks)
   - Simple SELECT
   - JOINs (2-way, 3-way, multi-table)
   - CTEs (simple, multiple, recursive)
   - Window functions
   - Subqueries
   - Procedural SQL

3. **Generator** (5 benchmarks)
   - Simple output
   - Complex output
   - Dialect-specific transformations

4. **Full Pipeline** (8 benchmarks)
   - Simple transpilation
   - Cross-dialect transpilation
   - Real-world queries (dashboard, reports)

5. **Memory** (4 benchmarks)
   - Arena allocation
   - String interning
   - Memory access patterns

### Interpreting Results

**Good performance indicators**:
- Tokenizer: >1,000,000 ops/sec for simple queries
- Parser: >100,000 ops/sec for simple queries
- Full pipeline: >50,000 ops/sec for simple queries
- Real-world queries: >10,000 ops/sec

**Performance regression thresholds**:
- >5% regression in hot paths → investigate
- >10% regression → do not merge
- <2% regression → acceptable noise

## Build Configurations

### Development Build (Debug)
```bash
cmake -B build-debug -DCMAKE_BUILD_TYPE=Debug
```
- `-O0 -g`: No optimization, full debug symbols
- Fast compilation
- Easy debugging with GDB/LLDB

### Release Build (Portable)
```bash
cmake -B build -DCMAKE_BUILD_TYPE=Release
```
- `-O3 -march=x86-64 -mtune=generic`: Portable optimization
- Compatible with all x86-64 CPUs
- Suitable for distribution (wheels, packages)

### Release Build (Native)
```bash
cmake -B build -DCMAKE_BUILD_TYPE=Release \
      -DLIBSQLGLOT_ENABLE_NATIVE=ON
```
- `-O3 -march=native -mtune=native`: Machine-specific optimization
- Uses AVX, AVX2, AVX-512 if available
- 10-30% faster than portable
- **Only for local use** (not portable)

### PGO Build (Maximum Performance)
```bash
# Phase 1: Instrument
cmake -B build-pgo -DCMAKE_BUILD_TYPE=Release \
      -DLIBSQLGLOT_PGO_GENERATE=ON
cmake --build build-pgo -j8

# Phase 2: Train
python3 scripts/profile_optimization.py

# Phase 3: Optimize
cmake -B build-pgo -DCMAKE_BUILD_TYPE=Release \
      -DLIBSQLGLOT_PGO_USE=ON
cmake --build build-pgo -j8
```

Expected improvements:
- 15-30% faster than standard Release build
- Best for production deployments
- Requires representative training workload

## Profiling Tools

### perf (Linux)
```bash
# Record profile
perf record -g ./build/benchmarks/bench_parser

# Analyze hotspots
perf report

# Generate flamegraph
perf script | stackcollapse-perf.pl | flamegraph.pl > flamegraph.svg
```

### Valgrind (callgrind)
```bash
# Profile with callgrind
valgrind --tool=callgrind ./build/benchmarks/bench_parser

# Visualize with kcachegrind
kcachegrind callgrind.out.*
```

### gprof
```bash
# Build with -pg
cmake -B build -DCMAKE_BUILD_TYPE=Release \
      -DCMAKE_CXX_FLAGS="-pg"
cmake --build build -j8

# Run to generate gmon.out
./build/benchmarks/bench_parser

# Analyze
gprof ./build/benchmarks/bench_parser gmon.out
```

## Continuous Performance Monitoring

### Automated Benchmarks

Run benchmarks on every commit:
```yaml
# .github/workflows/benchmarks.yml
on: [push, pull_request]
jobs:
  benchmark:
    runs-on: ubuntu-latest
    steps:
      - uses: actions/checkout@v3
      - name: Build and run benchmarks
        run: |
          docker compose -f docker/docker-compose.yml run --rm build-benchmarks
      - name: Compare with baseline
        run: |
          python3 scripts/compare_benchmarks.py \
            baseline.json current.json --threshold 5
```

### Performance Regression Detection

Automatically fail CI if:
- Any benchmark regresses >10%
- Hot path benchmarks regress >5%
- Binary size increases >10%

## Future Optimizations

### Short-term (Next Release)
- [ ] Profile production workloads and populate hotspot lists
- [ ] Apply per-file optimization levels
- [ ] Run PGO training and measure improvements
- [ ] Add SIMD optimizations for tokenizer

### Medium-term (6 months)
- [ ] Implement custom memory allocator tuned for parser workload
- [ ] Add multi-threaded parsing for batch workloads
- [ ] Optimize string interning with faster hash function
- [ ] Add JIT compilation for frequently-used query patterns

### Long-term (1 year)
- [ ] Hardware-specific optimization profiles (x86, ARM, RISC-V)
- [ ] GPU acceleration for parallel query processing
- [ ] ML-based query optimization hints
- [ ] Automatic performance tuning based on workload

## Checklist: Adding New Code

When adding new features, consider:

- [ ] **Is this a hot path?** → Use -O3, add to benchmark suite
- [ ] **Is this cold code?** → Use -Os to reduce binary size
- [ ] **Is this template-heavy?** → Use -O2 to control compile time
- [ ] **Add benchmarks** for performance-critical features
- [ ] **Profile before optimizing** - don't guess!
- [ ] **Measure the impact** - verify optimizations actually help

## References

- [GCC Optimization Options](https://gcc.gnu.org/onlinedocs/gcc/Optimize-Options.html)
- [Profile-Guided Optimization](https://gcc.gnu.org/onlinedocs/gcc/Optimize-Options.html#index-fprofile-generate)
- [Google Benchmark User Guide](https://github.com/google/benchmark/blob/main/docs/user_guide.md)
- [Performance Engineering Principles](https://www.brendangregg.com/perf.html)

---

Last updated: 2026-03-22
Version: 0.4.1
