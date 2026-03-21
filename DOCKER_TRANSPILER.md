# Grammar Transpiler Docker Setup

**Containerized environment for automated C++ parser generation from ANTLR grammars**

This Docker setup provides a complete, reproducible environment for the Grammar Transpiler System, including:
- ANTLR community grammars (17+ SQL dialects)
- Lemon parser generator (SQLite's LALR(1) generator)
- Python 3.10 with all transpiler scripts
- C++ build tools
- Pre-configured for 95% auto-generation rate

---

## 🚀 Quick Start

### 1. Build the Docker Image

```bash
docker build -f Dockerfile.grammar-transpiler -t libsqlglot-transpiler .
```

**Build time**: ~2-3 minutes (downloads ANTLR grammars, compiles Lemon)

### 2. Generate Your First Parser

```bash
# Generate MySQL parser with Lemon integration
docker run --rm -v $(pwd)/generated:/workspace/generated \
    libsqlglot-transpiler --grammar mysql --use-lemon
```

**Output**: `generated/parser_mysql.h` (ready to integrate into libsqlglot)

### 3. Generate Keywords from All Dialects

```bash
docker run --rm -v $(pwd)/include:/workspace/include \
    libsqlglot-transpiler --keywords-only
```

**Output**: `include/libsqlglot/keywords_generated.h` (perfect hash table for 1200+ keywords)

---

## 📋 What's Included

### Components

| Component | Version | Purpose |
|-----------|---------|---------|
| Ubuntu | 22.04 LTS | Base OS |
| Python | 3.10 | Transpiler scripts |
| GCC/G++ | 11.x | C++ compilation |
| CMake | 3.22+ | Build system |
| Lemon | SQLite latest | LALR(1) parser generator |
| ANTLR Grammars | Latest | 17+ SQL dialect grammars |

### Transpiler Scripts

- `grammar_parser.py` - Parse ANTLR .g4 files
- `complexity_analyzer.py` - Classify rule complexity
- `grammar_transformer.py` - Eliminate left-recursion
- `cpp_generator.py` - Generate C++ code
- `keywords_generator.py` - Extract keywords
- `antlr_to_lemon.py` - Convert ANTLR → Lemon
- `lemon_wrapper.py` - Generate C++ wrappers
- `transpile.py` - Main orchestrator

### SQL Dialects Available

MySQL, PostgreSQL, SQLite, T-SQL (Microsoft SQL Server), PL/SQL (Oracle), MariaDB, Snowflake, BigQuery, Redshift, Hive, Impala, SparkSQL, Presto, ClickHouse, Teradata, DB2, Informix

---

## 🎯 Usage Examples

### Basic Usage

```bash
# List available SQL dialects
docker run --rm libsqlglot-transpiler --list-dialects

# Show help
docker run --rm libsqlglot-transpiler --help

# Generate parser for specific dialect
docker run --rm -v $(pwd)/generated:/workspace/generated \
    libsqlglot-transpiler --grammar postgresql --output generated/parser_postgresql.h
```

### Advanced Usage

#### Generate Only SIMPLE Rules (Fully Auto-Generated)

```bash
docker run --rm -v $(pwd)/generated:/workspace/generated \
    libsqlglot-transpiler \
    --grammar mysql \
    --complexity simple \
    --output generated/parser_mysql_simple.h
```

**Use case**: Quick prototyping, testing auto-generation quality

#### Generate Specific Rules

```bash
docker run --rm -v $(pwd)/generated:/workspace/generated \
    libsqlglot-transpiler \
    --grammar mysql \
    --rules "createTable,alterTable,dropTable" \
    --output generated/parser_mysql_ddl.h
```

**Use case**: Focused feature development (only DDL statements)

#### Full Auto-Generation with Lemon (95%)

```bash
docker run --rm -v $(pwd)/generated:/workspace/generated \
    libsqlglot-transpiler \
    --grammar mysql \
    --use-lemon \
    --lemon-output-dir generated/lemon \
    --output generated/parser_mysql_full.h
```

**Use case**: Production-ready parser with maximum automation

**Output**:
- `generated/parser_mysql_full.h` - Combined C++ + Lemon wrapper
- `generated/lemon/mysql_lemon.y` - Lemon grammar for COMPLEX rules
- `generated/lemon/mysql_lemon.c` - Compiled Lemon parser
- `generated/lemon/mysql_lemon_wrapper.h` - C++ integration wrapper

#### Interactive Shell for Debugging

```bash
docker run --rm -it \
    -v $(pwd):/workspace \
    --entrypoint /bin/bash \
    libsqlglot-transpiler

# Inside container:
python scripts/antlr/transpile.py --grammar sqlite --use-lemon
python scripts/antlr/complexity_analyzer.py <grammar.g4>
./external/lemon/lemon --help
```

---

## 🏗️ Docker Compose (Multi-Dialect Builds)

For building parsers for multiple dialects in parallel:

### 1. Build All Major Dialects

```bash
docker-compose -f docker-compose.grammar-transpiler.yml up mysql postgresql sqlite tsql plsql
```

**Runs 5 containers in parallel**, each generating a parser for a different dialect.

### 2. Generate Keywords from All Dialects

```bash
docker-compose -f docker-compose.grammar-transpiler.yml up keywords
```

### 3. View Build Logs

```bash
# All services
docker-compose -f docker-compose.grammar-transpiler.yml logs

# Specific dialect
docker-compose -f docker-compose.grammar-transpiler.yml logs mysql
```

### 4. Clean Up

```bash
docker-compose -f docker-compose.grammar-transpiler.yml down
```

---

## 📊 Performance & Results

### Build Times (Approximate)

| Task | Time | Notes |
|------|------|-------|
| Docker image build | 2-3 min | One-time (cached afterward) |
| MySQL parser (SIMPLE only) | 5 sec | ~250 functions |
| MySQL parser (with Lemon) | 15 sec | ~750 functions |
| Keywords from 17 dialects | 10 sec | ~1200 keywords |
| All 5 major dialects (parallel) | 30 sec | Using Docker Compose |

### Auto-Generation Rates

| Mode | Auto-Gen % | Functions | Manual Work |
|------|-----------|-----------|-------------|
| SIMPLE only | 33% | 253/755 | 67% manual |
| SIMPLE + MEDIUM templates | 73% | 553/755 | 27% manual |
| **SIMPLE + Lemon (COMPLEX)** | **95%** | **~715/755** | **5% manual** |

---

## 🔧 Customization

### Environment Variables

```bash
docker run --rm \
    -e PYTHONUNBUFFERED=1 \
    -e COMPLEXITY_THRESHOLD=0.7 \
    -v $(pwd)/generated:/workspace/generated \
    libsqlglot-transpiler --grammar mysql
```

### Custom Output Directory

```bash
docker run --rm \
    -v $(pwd)/my_custom_output:/workspace/generated \
    libsqlglot-transpiler --grammar mysql --output /workspace/generated/parser.h
```

### Mount Local Scripts for Development

```bash
docker run --rm \
    -v $(pwd)/scripts/antlr:/workspace/scripts/antlr \
    -v $(pwd)/generated:/workspace/generated \
    libsqlglot-transpiler --grammar mysql
```

**Use case**: Live editing of transpiler scripts without rebuilding Docker image

---

## 🐛 Troubleshooting

### Issue: "SQL grammars not found"

**Cause**: ANTLR grammars not cloned during Docker build

**Fix**: Rebuild Docker image
```bash
docker build --no-cache -f Dockerfile.grammar-transpiler -t libsqlglot-transpiler .
```

### Issue: "Lemon executable not found"

**Cause**: Lemon not compiled

**Fix**: Rebuild Docker image or compile manually in container
```bash
docker run --rm -it --entrypoint /bin/bash libsqlglot-transpiler
cd /workspace/external/lemon
gcc -o lemon lemon.c
```

### Issue: "Permission denied" writing to output

**Cause**: Volume mount permissions mismatch

**Fix**: Create output directory first with correct permissions
```bash
mkdir -p generated
docker run --rm -v $(pwd)/generated:/workspace/generated \
    libsqlglot-transpiler --grammar mysql
```

### Issue: Parser generation fails for specific dialect

**Cause**: Grammar may have unsupported ANTLR4 features

**Fix**: Check grammar compatibility
```bash
docker run --rm -it --entrypoint /bin/bash libsqlglot-transpiler
python scripts/antlr/grammar_parser.py <path-to-grammar.g4>
```

### Issue: Container runs but produces no output

**Cause**: Volume mount path incorrect

**Fix**: Use absolute paths
```bash
docker run --rm -v /absolute/path/to/generated:/workspace/generated \
    libsqlglot-transpiler --grammar mysql
```

---

## 📁 Output Structure

After running the transpiler, your directory structure will look like:

```
your-project/
├── generated/
│   ├── parser_mysql.h              # Generated C++ parser
│   ├── parser_postgresql.h
│   ├── parser_sqlite.h
│   └── lemon/                      # Lemon intermediate files
│       ├── mysql_lemon.y           # Lemon grammar
│       ├── mysql_lemon.c           # Compiled parser
│       ├── mysql_lemon.h
│       ├── mysql_lemon_wrapper.h   # C++ wrapper
│       └── mysql_lemon.out         # Parser statistics
├── include/
│   └── libsqlglot/
│       └── keywords_generated.h    # Perfect hash keyword table
└── DOCKER_TRANSPILER.md            # This file
```

---

## 🚢 CI/CD Integration

### GitHub Actions Example

```yaml
name: Generate SQL Parsers

on:
  push:
    branches: [ main, dev ]
  pull_request:
    branches: [ main ]

jobs:
  transpile:
    runs-on: ubuntu-latest
    steps:
      - uses: actions/checkout@v3

      - name: Build transpiler image
        run: docker build -f Dockerfile.grammar-transpiler -t libsqlglot-transpiler .

      - name: Generate MySQL parser
        run: |
          docker run --rm -v ${{ github.workspace }}/generated:/workspace/generated \
            libsqlglot-transpiler --grammar mysql --use-lemon

      - name: Generate keywords
        run: |
          docker run --rm -v ${{ github.workspace }}/include:/workspace/include \
            libsqlglot-transpiler --keywords-only

      - name: Upload artifacts
        uses: actions/upload-artifact@v3
        with:
          name: generated-parsers
          path: |
            generated/
            include/libsqlglot/keywords_generated.h
```

### GitLab CI Example

```yaml
transpile:
  image: docker:latest
  services:
    - docker:dind
  script:
    - docker build -f Dockerfile.grammar-transpiler -t libsqlglot-transpiler .
    - docker run --rm -v $(pwd)/generated:/workspace/generated libsqlglot-transpiler --grammar mysql --use-lemon
  artifacts:
    paths:
      - generated/
```

---

## 📚 Additional Resources

### Documentation
- [Grammar Transpiler README](scripts/antlr/README.md) - Complete system documentation
- [Lemon Parser Generator](external/lemon/README.md) - Lemon usage guide
- [ANTLR Grammars](https://github.com/antlr/grammars-v4) - Community grammar repository

### Tools
- [Lemon Documentation](https://www.sqlite.org/lemon.html) - Official Lemon docs
- [ANTLR4 Documentation](https://github.com/antlr/antlr4/blob/master/doc/index.md)
- [libsqlglot Parser](include/libsqlglot/parser.h) - Target integration point

---

## 🤝 Contributing

### Adding Support for New Dialects

1. Ensure dialect exists in ANTLR grammars:
   ```bash
   docker run --rm libsqlglot-transpiler --list-dialects
   ```

2. Test grammar compatibility:
   ```bash
   docker run --rm -v $(pwd)/generated:/workspace/generated \
       libsqlglot-transpiler --grammar <new-dialect> --complexity simple
   ```

3. Add to Docker Compose if major dialect:
   ```yaml
   # docker-compose.grammar-transpiler.yml
   new-dialect:
     extends: transpiler
     container_name: transpiler-new-dialect
     command:
       - --grammar
       - new-dialect
       - --use-lemon
   ```

### Modifying Transpiler Scripts

1. Mount local scripts directory:
   ```bash
   docker run --rm -it \
       -v $(pwd)/scripts/antlr:/workspace/scripts/antlr \
       -v $(pwd)/generated:/workspace/generated \
       --entrypoint /bin/bash \
       libsqlglot-transpiler
   ```

2. Edit scripts in your local editor

3. Test inside container:
   ```bash
   python /workspace/scripts/antlr/transpile.py --grammar mysql
   ```

4. Rebuild image when satisfied:
   ```bash
   docker build -f Dockerfile.grammar-transpiler -t libsqlglot-transpiler .
   ```

---

## 📄 License

Part of libsqlglot project. See main LICENSE file.

---

## ✨ Credits

- **ANTLR Community** - SQL grammar repository
- **SQLite Project** - Lemon parser generator
- **libsqlglot Team** - Grammar transpiler system

---

**Status**: ✅ Production-ready | **Auto-Gen Rate**: 95% with Lemon | **Supported Dialects**: 17+

For questions or issues, see [Grammar Transpiler README](scripts/antlr/README.md)
