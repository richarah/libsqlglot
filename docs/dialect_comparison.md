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

## Grammar Sources to Check

- [grammars-v4](https://github.com/antlr/grammars-v4) - Official ANTLR grammar repository
- [DuckDB source](https://github.com/duckdb/duckdb) - May have Lemon/parser files
- [Presto source](https://github.com/prestodb/presto) - Java-based parser
- [BigQuery documentation](https://cloud.google.com/bigquery/docs/reference/standard-sql) - May need custom grammar
- Individual database repositories for parser/grammar files
