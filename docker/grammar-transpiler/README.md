# Grammar Transpiler Docker Environment

100% automated ANTLR → Lemon → C++ parser generation for SQL dialects.

## Overview

This Docker environment provides a complete toolchain for extracting grammar data from ANTLR grammar definitions and generating C++ lookup tables and headers for libsqlglot.

## Quick Start

From the project root:

```bash
# Extract ALL dialects and generate C++ headers (recommended)
docker compose -f docker/grammar-transpiler/docker-compose.yml up extract-all

# Extract a single dialect for testing
docker compose -f docker/grammar-transpiler/docker-compose.yml up mysql

# Generate keywords.h from all dialects
docker compose -f docker/grammar-transpiler/docker-compose.yml up keywords

# Interactive shell for debugging
docker compose -f docker/grammar-transpiler/docker-compose.yml run --rm transpiler /bin/bash
```

## Features

- **17+ SQL Dialects**: MySQL, PostgreSQL, SQLite, BigQuery, Snowflake, etc.
- **Automated Pipeline**: ANTLR grammars → extraction → C++ header generation
- **Lemon Integration**: Uses SQLite's Lemon parser generator
- **Zero Manual Maintenance**: All dialect data automatically extracted

## Output

Generated files are placed in:
- `generated/grammar_data/` - Extracted grammar JSON data
- `include/libsqlglot/` - C++ headers with lookup tables

## Supported Dialects

The transpiler extracts grammar data from the official ANTLR grammars-v4 repository for:

- MySQL
- PostgreSQL
- SQLite
- BigQuery
- Snowflake
- Hive
- Spark
- Presto
- And more...

## Architecture

1. **Grammar Extraction**: Parses ANTLR .g4 files
2. **Data Normalization**: Converts to standardized JSON format
3. **C++ Generation**: Creates compile-time lookup tables
4. **Header Output**: Generates dialect-specific headers

## Development

To modify the transpiler logic:

1. Edit scripts in `scripts/antlr/`
2. Rebuild the image:
   ```bash
   docker compose -f docker/grammar-transpiler/docker-compose.yml build
   ```
3. Test your changes:
   ```bash
   docker compose -f docker/grammar-transpiler/docker-compose.yml up extract-all
   ```

## Troubleshooting

### Grammar Not Found
Verify the grammar exists in ANTLR grammars-v4 repository.

### Permission Issues
Ensure the output directories are writable:
```bash
chmod -R 755 generated/ include/
```

### Build Failures
Check Docker logs:
```bash
docker compose -f docker/grammar-transpiler/docker-compose.yml logs transpiler
```

## CI/CD Integration

```yaml
# GitHub Actions example
- name: Generate Grammar Headers
  run: docker compose -f docker/grammar-transpiler/docker-compose.yml up extract-all
```
