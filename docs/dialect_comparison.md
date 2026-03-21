# SQL Dialect Coverage Comparison

## Current Status
- **libsqlglot**: 17 dialects extracted from ANTLR grammars
- **sqlglot (Python)**: 32 dialects supported

## Dialects We Have (17)

| Dialect | Source | Notes |
|---------|--------|-------|
| Athena | grammars-v4 | ✓ Also in sqlglot |
| ClickHouse | grammars-v4 | ✓ Also in sqlglot |
| Derby | grammars-v4 | Not in sqlglot |
| Drill | grammars-v4 | ✓ Also in sqlglot |
| Hive | grammars-v4 | ✓ Also in sqlglot |
| Informix SQL | grammars-v4 | Not in sqlglot |
| MariaDB | grammars-v4 | Not in sqlglot (covered by MySQL) |
| MySQL | grammars-v4 | ✓ Also in sqlglot |
| Phoenix | grammars-v4 | Not in sqlglot |
| PL/SQL (Oracle) | grammars-v4 | ✓ Also in sqlglot |
| PostgreSQL | grammars-v4 | ✓ Also in sqlglot |
| Snowflake | grammars-v4 | ✓ Also in sqlglot |
| SQLite | grammars-v4 | ✓ Also in sqlglot |
| StarRocks | grammars-v4 | ✓ Also in sqlglot |
| Teradata | grammars-v4 | ✓ Also in sqlglot |
| Trino | grammars-v4 | ✓ Also in sqlglot |
| T-SQL (SQL Server) | grammars-v4 | ✓ Also in sqlglot |

## Missing from libsqlglot (19 dialects)

### High Priority (widely used)
| Dialect | Importance | Notes |
|---------|------------|-------|
| **BigQuery** | ⭐⭐⭐⭐⭐ | Google Cloud, very popular |
| **DuckDB** | ⭐⭐⭐⭐⭐ | Fastest growing, analytics |
| **Redshift** | ⭐⭐⭐⭐ | AWS, widely used |
| **Databricks** | ⭐⭐⭐⭐ | Enterprise analytics |
| **Presto** | ⭐⭐⭐⭐ | Big data query engine |
| **Spark** | ⭐⭐⭐⭐ | Apache Spark SQL |

### Medium Priority
| Dialect | Importance | Notes |
|---------|------------|-------|
| **Spark2** | ⭐⭐⭐ | Legacy Spark |
| **Doris** | ⭐⭐⭐ | Apache Doris |
| **Dremio** | ⭐⭐⭐ | Data lakehouse |
| **Materialize** | ⭐⭐⭐ | Streaming SQL |
| **RisingWave** | ⭐⭐⭐ | Streaming database |
| **SingleStore** | ⭐⭐⭐ | Distributed SQL |

### Lower Priority
| Dialect | Importance | Notes |
|---------|------------|-------|
| **Druid** | ⭐⭐ | OLAP |
| **Dune** | ⭐⭐ | Blockchain analytics |
| **Exasol** | ⭐⭐ | High-performance analytics |
| **Fabric** | ⭐⭐ | Microsoft Fabric |
| **PRQL** | ⭐⭐ | Pipelined SQL alternative |
| **Solr** | ⭐⭐ | Search platform |
| **Tableau** | ⭐⭐ | BI platform |

## Next Steps

1. Search GitHub for ANTLR grammars for missing dialects
2. Look for Lemon grammar files (if any exist)
3. Consider writing custom grammars for high-priority missing dialects
4. Add grammar extraction support for new dialects

## Grammar Sources Found

### ANTLR Grammars (Can Use Directly)

| Dialect | Source | Status |
|---------|--------|--------|
| **BigQuery** | [Andrew0Hill/antlr-bq-grammar](https://github.com/Andrew0Hill/antlr-bq-grammar/blob/master/bigquery.g4) | ⭐ Ready to extract |
| **Presto** | [prestodb/presto](https://github.com/prestodb/presto/blob/master/presto-parser/src/main/antlr4/com/facebook/presto/sql/parser/SqlBase.g4) | ⭐ Ready to extract |
| **Spark** | [apache/spark](https://github.com/apache/spark/blob/master/sql/catalyst/src/main/antlr4/org/apache/spark/sql/catalyst/parser/SqlBase.g4) | ⭐ Ready to extract |
| **Spark (Lexer)** | [apache/spark SqlBaseLexer](https://github.com/apache/spark/blob/master/sql/api/src/main/antlr4/org/apache/spark/sql/catalyst/parser/SqlBaseLexer.g4) | ⭐ Ready to extract |

### Bison/Yacc Grammars (Can Convert to Lemon)

| Dialect | Source | Parser Type | Notes |
|---------|--------|-------------|-------|
| **DuckDB** | [duckdb/duckdb](https://github.com/duckdb/duckdb/tree/main/third_party/libpg_query/grammar) | Bison 2.3 + Flex 2.6.4 | Fork of PostgreSQL parser |
|  | Lexer: `third_party/libpg_query/scan.l` | | |
|  | Grammar: `third_party/libpg_query/grammar/statements/*.y` | | |

### PostgreSQL-Compatible (Can Use PostgreSQL Grammar)

| Dialect | Notes |
|---------|-------|
| **Redshift** | Based on PostgreSQL, can start with PostgreSQL grammar we already have |
| **RisingWave** | PostgreSQL-compatible streaming database |
| **Materialize** | PostgreSQL-compatible streaming SQL |

### Dialects Needing Research

| Dialect | Priority | Notes |
|---------|----------|-------|
| **Databricks** | ⭐⭐⭐⭐ | Likely based on Spark SQL |
| **Doris** | ⭐⭐⭐ | Apache project, may have grammar in source |
| **Dremio** | ⭐⭐⭐ | May use ANTLR or custom parser |
| **SingleStore** | ⭐⭐⭐ | Proprietary, grammar unknown |
| **Druid** | ⭐⭐ | Calcite-based SQL |
| **Exasol** | ⭐⭐ | Proprietary |
| **Fabric** | ⭐⭐ | Microsoft, likely T-SQL derivative |
| **PRQL** | ⭐⭐ | New language, has Rust parser |
| **Solr** | ⭐⭐ | Limited SQL support |
| **Tableau** | ⭐⭐ | BI platform, may not need full grammar |
| **Dune** | ⭐⭐ | Blockchain analytics |

## Next Steps for Grammar Extraction

### Phase 1: Add ANTLR Grammars (Immediate)
1. BigQuery - Download from Andrew0Hill/antlr-bq-grammar
2. Presto - Extract from prestodb/presto repository
3. Spark - Extract from apache/spark repository

### Phase 2: Convert Bison/Yacc to Lemon (Medium Effort)
1. DuckDB - Study libpg_query grammar structure
2. Create Bison → Lemon converter script
3. Test converted grammars

### Phase 3: PostgreSQL Derivatives (Low Effort)
1. Redshift - Use PostgreSQL grammar with Redshift-specific extensions
2. RisingWave - PostgreSQL + streaming extensions
3. Materialize - PostgreSQL + streaming extensions

### Phase 4: Research Remaining Dialects (As Needed)
1. Search each dialect's source repository for grammar files
2. Check if they use ANTLR, Bison, hand-written, or other parsers
3. Evaluate effort vs value for each

## Tools for Grammar Conversion

- **Bison → Lemon**: Both are LALR(1) parsers, conversion is straightforward
  - Lemon has simpler syntax
  - Can script the conversion for DuckDB grammars
- **ANTLR → Lemon**: More complex (ANTLR is LL(*))
  - Better to use ANTLR grammars with our existing extraction pipeline
  - Generate C++ lookup tables rather than convert
