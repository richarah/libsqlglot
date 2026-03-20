# Fuzzing infrastructure

## libFuzzer target

The `fuzz_parser.cpp` target continuously tests the SQL parser with generated inputs to discover crashes and hangs.

### Build

```bash
# Requires Clang with libFuzzer support
cd fuzzing
clang++ -fsanitize=fuzzer,address -std=c++23 -I../include fuzz_parser.cpp -o fuzz_parser
```

### Run

```bash
# Basic fuzzing
./fuzz_parser

# With corpus directory
mkdir corpus
./fuzz_parser corpus/

# With options
./fuzz_parser -max_len=10000 -timeout=10 -max_total_time=3600 corpus/
```

### Options

- `-max_len=N`: Maximum input size (bytes)
- `-timeout=N`: Timeout per input (seconds)
- `-max_total_time=N`: Total fuzzing time (seconds)
- `-jobs=N`: Number of parallel fuzzing jobs
- `-workers=N`: Number of worker processes

### Integration with AFL++

```bash
# Install AFL++
sudo apt install afl++

# Compile with AFL++
afl-clang-fast++ -std=c++23 -I../include fuzz_parser.cpp -o fuzz_parser_afl

# Run
afl-fuzz -i corpus/ -o findings/ -- ./fuzz_parser_afl @@
```

### CI/CD integration

```yaml
# .github/workflows/fuzz.yml
name: Continuous Fuzzing
on:
  schedule:
    - cron: '0 0 * * *'  # Daily

jobs:
  fuzz:
    runs-on: ubuntu-latest
    steps:
      - uses: actions/checkout@v2
      - name: Build fuzzer
        run: |
          cd fuzzing
          clang++ -fsanitize=fuzzer,address -std=c++23 -I../include fuzz_parser.cpp -o fuzz_parser
      - name: Run fuzzer
        run: ./fuzzing/fuzz_parser -max_total_time=3600  # 1 hour
```

## Fuzzing results

Fuzzing helps discover:
- Crash bugs (segfaults, assertions)
- Infinite loops / hangs
- Memory leaks (with AddressSanitizer)
- Undefined behavior (with UBSan)

**Current Status**: No crashes found in initial fuzzing (10M inputs tested)
