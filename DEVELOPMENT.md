# Development

Build instructions for libsqlglot internals, grammar generation pipeline, and infrastructure.

## Contents

- [Building](#building)
- [Grammar Transpiler](#grammar-transpiler)
- [Keyword Generation](#keyword-generation)
- [Testing](#testing)
- [Code Quality](#code-quality)
- [Performance Profiling](#performance-profiling)
- [Release Process](#release-process)

## Building

### Docker (Recommended)

Docker automatically builds GCC trunk with C++26 reflection support:

```bash
# Build project (first time compiles GCC trunk, ~30-45 min)
docker compose -f docker/docker-compose.yml run --rm build

# Run tests
docker compose -f docker/docker-compose.yml run --rm test

# Build Python wheel
docker compose -f docker/docker-compose.yml run --rm wheel

# Development shell
docker compose -f docker/docker-compose.yml run --rm dev
```

See `docker/README.md` for full documentation.

### Standard build (native)

Requires GCC trunk with `-freflection` support:

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

**Location**: `scripts/antlr/`

**Docker wrapper**: `docker/grammar-transpiler/` (contains `Dockerfile` and `docker-compose.yml`)

### Docker setup (recommended)

```bash
# Extract all grammars and generate keywords.h
docker compose -f docker/grammar-transpiler/docker-compose.yml up extract-all

# Extract single dialect
docker compose -f docker/grammar-transpiler/docker-compose.yml up mysql

# Interactive debugging
docker compose -f docker/grammar-transpiler/docker-compose.yml run --rm transpiler /bin/bash
```

See `docker/grammar-transpiler/README.md` for full documentation.

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

**Standards**: C++26 (GCC trunk with `-freflection`, Clang 18+, MSVC 19.40+)

**Dependencies**: None (no runtime deps, no RTTI)

**Fuzzing**:

```bash
cd fuzzing
clang++ -fsanitize=fuzzer,address -std=c++26 -freflection -I../include fuzz_parser.cpp -o fuzz_parser
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
- LTO: 5-10% speedup
- PGO: 10-20% speedup
- Combined: 15-30% over baseline Release

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
├── docker/                   # Docker build environments
│   ├── Dockerfile            # GCC trunk + C++26 reflection
│   ├── docker-compose.yml
│   └── grammar-transpiler/   # ANTLR grammar transpiler
│       ├── Dockerfile
│       └── docker-compose.yml
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

## GitHub Actions CI/CD

Python wheel builds use Docker to compile GCC trunk with C++26 reflection support. No self-hosted runner required.

### How it works

1. **On push/PR**: CI builds in Docker, runs tests
2. **On release**: Builds manylinux wheels in Docker, publishes to PyPI

See `.github/workflows/ci.yml` and `.github/workflows/build-wheels.yml` for configuration.

### Local wheel testing

```bash
# Build wheel in Docker (same as CI)
docker compose -f docker/docker-compose.yml run --rm wheel

# Wheel appears in dist/
ls -lh dist/*.whl
```

## Release Process

libsqlglot uses an automated release process that publishes to both GitHub Releases and PyPI.

### Prerequisites

1. **GitHub CLI** (`gh`) installed and authenticated
2. **PyPI API token** configured as `PYPI_API_TOKEN` secret in GitHub repo settings

### Creating a Release

Use the automated release script:

```bash
./scripts/release.sh v0.1.3
```

**What the script does**:

1. Validates version format (must be `vX.Y.Z`)
2. Checks you're on `master` branch with clean working directory
3. Updates version in `CMakeLists.txt` and `pyproject.toml`
4. Commits version bump
5. Creates and pushes git tag
6. Creates GitHub release with auto-generated release notes

**What GitHub Actions does automatically**:

1. Builds Docker image with GCC trunk + reflection (~30-45 min, cached)
2. Builds manylinux Python wheels in Docker
3. Uploads wheels to GitHub release
4. Publishes wheels to PyPI using `PYPI_API_TOKEN`

### Manual Release (if script unavailable)

```bash
# 1. Update versions
VERSION=0.1.3
sed -i "s/^project(libsqlglot VERSION .*/project(libsqlglot VERSION $VERSION LANGUAGES CXX)/" CMakeLists.txt
sed -i "s/^version = .*/version = \"$VERSION\"/" pyproject.toml

# 2. Commit and tag
git add CMakeLists.txt pyproject.toml
git commit -m "Bump version to v$VERSION"
git tag -a "v$VERSION" -m "Release v$VERSION"
git push origin master v$VERSION

# 3. Create GitHub release (triggers wheel build and PyPI publish)
gh release create "v$VERSION" --title "Release v$VERSION" --generate-notes
```

### Monitoring Release

After creating the release:

1. Go to **Actions** tab in GitHub
2. Watch the "Build Wheels" workflow
3. Verify wheels are uploaded to GitHub release
4. Verify package appears on PyPI: https://pypi.org/project/libsqlglot/

### Troubleshooting

**Docker build timeout**: First build compiles GCC trunk (~30-45 min). Subsequent builds use cached layers.

**Wheel build fails**: Check Docker logs in GitHub Actions for GCC compilation errors

**PyPI upload fails**: Check `PYPI_API_TOKEN` secret is configured correctly

**Version conflict**: PyPI doesn't allow re-uploading same version - bump version and retry

## License

Apache 2.0
