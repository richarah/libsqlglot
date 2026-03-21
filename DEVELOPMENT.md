# Development

Build instructions for libsqlglot internals, grammar generation pipeline, and infrastructure.

## Contents

- [Building](#building)
- [Grammar Transpiler](#grammar-transpiler)
- [Keyword Generation](#keyword-generation)
- [Testing](#testing)
- [Code Quality](#code-quality)
- [Performance Profiling](#performance-profiling)

## Building

### Standard build

```bash
cmake -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build -j4
sudo cmake --install build
```

### With tests and benchmarks

```bash
cmake -B build -DCMAKE_BUILD_TYPE=Release \
               -DLIBSQLGLOT_BUILD_TESTS=ON \
               -DLIBSQLGLOT_BUILD_BENCHMARKS=ON
cmake --build build -j4
ctest --test-dir build
```

### Profile-Guided Optimization (PGO)

For production: 10-30% speedup via PGO.

```bash
# Step 1: Build with instrumentation
cmake -B build -DCMAKE_BUILD_TYPE=Release -DLIBSQLGLOT_PGO_GENERATE=ON
cmake --build build

# Step 2: Run representative workload
./build/benchmarks/bench_transpiler

# Step 3: Rebuild with profile data
cmake -B build -DCMAKE_BUILD_TYPE=Release -DLIBSQLGLOT_PGO_USE=ON
cmake --build build
```

**Optimizations enabled** (Release): LTO, constant merging, symbol visibility optimization.

## Grammar Transpiler

Automated pipeline: ANTLR → C++ parser generation. Converts .g4 grammars into libsqlglot parser code.

**Location**: `scripts/antlr/` (not root directory)

**Docker wrapper**: `build/grammar-transpiler/` (contains `Dockerfile.grammar-transpiler` and `docker-compose.grammar-transpiler.yml`)

### Docker setup (recommended)

```bash
# Build transpiler image
docker build -f build/grammar-transpiler/Dockerfile.grammar-transpiler -t libsqlglot-transpiler .

# List available SQL dialects
docker run --rm libsqlglot-transpiler --list-dialects

# Extract all grammars and generate keywords.h
docker run --rm \
    -v $(pwd)/generated:/workspace/generated \
    -v $(pwd)/include:/workspace/include \
    libsqlglot-transpiler --extract-all

# Interactive debugging
docker run --rm -it -v $(pwd):/workspace --entrypoint /bin/bash libsqlglot-transpiler
```

### Local usage

Requires Python 3.8+ and ANTLR community grammars.

```bash
# Clone grammars (17+ SQL dialects)
git clone --depth 1 https://github.com/antlr/grammars-v4 external/grammars-v4

# Generate parser for MySQL
python scripts/antlr/transpile.py --grammar mysql --output include/libsqlglot/parser_mysql_generated.h

# Generate only SIMPLE rules (fully auto-generated)
python scripts/antlr/transpile.py --grammar mysql --complexity simple

# Analyze complexity without generating code
python scripts/antlr/complexity_analyzer.py external/grammars-v4/.../MySQLParser.g4 --output MYSQL_COMPLEXITY.md
```

### Pipeline phases

1. **Parse** (.g4 → AST): `grammar_parser.py`
2. **Analyze** (complexity classification): `complexity_analyzer.py`
3. **Transform** (eliminate left-recursion, compute FIRST/FOLLOW): `grammar_transformer.py`
4. **Generate** (C++ code): `cpp_generator.py`
5. **Extract** (keywords): `keywords_generator.py`
6. **Orchestrate** (end-to-end): `transpile.py`

**Results** (MySQL):
- 253/755 rules (33.5%) fully auto-generated
- 300/755 rules (39.7%) template-assisted
- 202/755 rules (26.8%) manual scaffolding

**Output**: C++ header files ready for integration into `include/libsqlglot/parser.h`

**Documentation**: See `scripts/antlr/README.md` for detailed pipeline description and API reference.

## Keyword Generation

Auto-extracts keywords from all SQL dialects, generates perfect hash table.

```bash
# Regenerate keywords.h from all dialects
python scripts/generate_keywords.py

# Output: include/libsqlglot/keywords.h
```

**Hash function**: `(first * 31 + last + length) & 255` (256-slot table)

**Metrics**:
- 282 keywords
- 256 hash slots
- 89 slots with collisions (34.8%)
- Max 6 collisions per slot
- Average 1.53 probes per lookup

**Configuration**: `HashConfig` class in `generate_keywords.py` (lines 408-432)

**Performance**: O(1) lookup, <2% of total parse time. Further optimization (e.g., gperf) provides <2-5% gain on <2% workload.

## Testing

378 test cases, 27,127 assertions.

```bash
cd build
ctest --output-on-failure

# Run specific test suites
./tests/libsqlglot_tests "[parser]"
./tests/libsqlglot_tests "[security]"
./tests/libsqlglot_tests "[stored_procedures]"
./tests/libsqlglot_tests "[performance]"
./tests/libsqlglot_tests "[dialect_coverage]"

# Run benchmarks
./benchmarks/bench_tokenizer
./benchmarks/bench_parser
./benchmarks/bench_transpiler
./benchmarks/bench_sqlglot_comparison
```

**Dialect coverage tests**: `tests/test_dialect_coverage.cpp` validates 45 dialects with dialect-specific features (DISTKEY, ASOF, UPSERT, etc.)

**Compatibility testing** with Python sqlglot:

```bash
cd compat
python sqlglot_compat.py --sqlglot-path /path/to/sqlglot --limit 1000
```

## Code Quality

**Compiler flags** (Release): `-Wall -Wextra -Wpedantic -Werror`

**Standards**: C++23 (Clang 18+, GCC 13+, MSVC 19.36+)

**Dependencies**: None (no runtime deps, no RTTI)

**Fuzzing**:

```bash
cd fuzzing
clang++ -fsanitize=fuzzer,address -std=c++23 -I../include fuzz_parser.cpp -o fuzz_parser
./fuzz_parser -max_len=10000 -timeout=10
```

**Security**: 27,127 assertions cover SQL injection, buffer overflow, stack overflow (max recursion: 256), memory corruption, integer overflow, encoding attacks.

**Git hooks**: Pre-commit metrics update (line counts, test counts, binary sizes)

```bash
scripts/install_hooks.sh
```

**Hook configuration**: `.githooks/pre-commit` runs `scripts/update_readme_metrics.sh`

## Performance Profiling

### CPU profiling

```bash
scripts/profile_cpu.sh
# Output: prof/cpu_profile.txt
```

Requires `perf` (Linux) or `Instruments` (macOS).

### Memory profiling

```bash
scripts/profile_memory.sh
# Output: prof/memory_profile.txt
```

Requires `valgrind --tool=massif`.

### Build optimizations

```bash
scripts/build_optimized.sh
```

Enables LTO, PGO (2-pass), aggressive inlining.

**Expected gains**:
- LTO: 5-15% speedup
- PGO: 10-30% speedup
- Combined: 15-45% over baseline Release

## Directory Structure

```
.
├── include/libsqlglot/       # C++ headers (1,415,525 lines)
│   ├── tokenizer.h           # SQL tokenizer (409 lines)
│   ├── tokens.h              # Token type enum (340 lines)
│   ├── keywords.h            # Perfect hash keyword lookup (generated)
│   ├── parser.h              # Recursive descent parser (2,952 lines)
│   ├── generator.h           # SQL generator (1,639 lines)
│   ├── expression.h          # AST nodes (1,105 lines, 105 types)
│   └── transpiler.h          # Public API (86 lines)
│
├── scripts/                  # Build and generation scripts
│   ├── antlr/                # ANTLR→C++ transpiler pipeline
│   │   ├── transpile.py      # Main orchestrator
│   │   ├── grammar_parser.py # Parse .g4 files
│   │   ├── complexity_analyzer.py
│   │   ├── grammar_transformer.py
│   │   ├── cpp_generator.py  # Generate C++ code
│   │   └── keywords_generator.py
│   ├── generate_keywords.py  # Keyword hash table generator
│   └── update_readme_metrics.sh
│
├── build/grammar-transpiler/ # Docker setup for grammar transpiler
│   ├── Dockerfile.grammar-transpiler
│   └── docker-compose.grammar-transpiler.yml
│
├── tests/                    # 378 test cases, 27,127 assertions
│   ├── test_tokenizer.cpp
│   ├── test_parser.cpp
│   ├── test_dialect_coverage.cpp  # 45 dialects
│   └── test_stored_procedures.cpp
│
├── benchmarks/               # Performance benchmarks
│   ├── bench_tokenizer.cpp
│   ├── bench_parser.cpp
│   └── bench_transpiler.cpp
│
├── fuzzing/                  # libFuzzer + AddressSanitizer
│   └── fuzz_parser.cpp
│
├── compat/                   # Python sqlglot compatibility tests
│   └── sqlglot_compat.py
│
├── external/                 # Third-party dependencies
│   ├── grammars-v4/          # ANTLR SQL grammars (not tracked)
│   └── lemon/                # Lemon parser generator (future)
│
└── generated/                # Auto-generated files (gitignored)
    ├── lemon/                # Lemon output
    └── keywords_generated.h
```

## Metrics

**Lines of code**: 1,415,525 C++ headers
**Binary sizes**: 15KB lib, 258KB Python extension (stripped, -O3)
**Test coverage**: 378 tests, 27,127 assertions
**Dialects**: 45 SQL dialects
**Benchmarks**: 126× faster avg (32-242× range)

**Update metrics**:

```bash
scripts/update_readme_metrics.sh
# Updates README.md with current counts
```

## Self-Hosted GitHub Runner for Python Wheels

Python wheel builds require C++26 with GCC 16+ trunk (`-freflection`). Standard GitHub runners don't have this yet.

### Setup Self-Hosted Runner

**Prerequisites**:
- Ubuntu 20.04+ or Debian 11+
- GCC 16+ trunk built from source with C++26 reflection support
- Python 3.9+
- 16GB+ RAM (for wheel builds)

**1. Build GCC 16 Trunk**:

```bash
# Install dependencies
sudo apt-get update
sudo apt-get install -y build-essential libgmp-dev libmpfr-dev libmpc-dev flex bison

# Clone GCC trunk
git clone --depth 1 https://gcc.gnu.org/git/gcc.git /tmp/gcc-trunk
cd /tmp/gcc-trunk

# Configure with C++26 reflection
./configure --prefix=/usr/local/gcc-trunk --enable-languages=c,c++ --disable-multilib --disable-bootstrap

# Build (takes 1-2 hours with -j8)
make -j8

# Install
sudo make install
```

**2. Verify GCC 16+ Trunk**:

```bash
/usr/local/gcc-trunk/bin/g++ --version  # Should show 16.0.0 or higher
/usr/local/gcc-trunk/bin/g++ -std=c++26 -freflection -x c++ - <<< 'int main() {}' && echo "✅ C++26 reflection works"
```

**3. Add to PATH**:

```bash
export PATH="/usr/local/gcc-trunk/bin:$PATH"
export LD_LIBRARY_PATH="/usr/local/gcc-trunk/lib64:$LD_LIBRARY_PATH"

# Add to ~/.bashrc for persistence
echo 'export PATH="/usr/local/gcc-trunk/bin:$PATH"' >> ~/.bashrc
echo 'export LD_LIBRARY_PATH="/usr/local/gcc-trunk/lib64:$LD_LIBRARY_PATH"' >> ~/.bashrc
```

**4. Install GitHub Actions Runner**:

Follow GitHub's instructions:
1. Go to repo → Settings → Actions → Runners → New self-hosted runner
2. Download and configure runner for Linux x64
3. Install runner as a service: `sudo ./svc.sh install && sudo ./svc.sh start`

**5. Test Wheel Build Locally**:

```bash
git clone https://github.com/richarah/libsqlglot.git
cd libsqlglot
pip install cibuildwheel==2.16.2
python -m cibuildwheel --output-dir wheelhouse
```

**6. Trigger Workflow**:

Go to Actions → Build Wheels → Run workflow (or create a release)

### Troubleshooting

**"g++ not found"**: Ensure `/usr/local/gcc-trunk/bin` is in PATH
**"unrecognized option '-freflection'"**: GCC version too old, rebuild trunk
**"cannot find -lstdc++"**: Set `LD_LIBRARY_PATH` to GCC lib64 directory
**Wheel fails to import**: Ensure manylinux2014 compatibility

### Security

Self-hosted runners have access to repo secrets. Only use on trusted infrastructure.

## License

Apache 2.0
