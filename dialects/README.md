# SQL Dialect Support

libsqlglot supports **46 SQL dialects** through a patch-based system that extends 17 base grammars extracted from ANTLR.

## Architecture

### Base Grammars (17)
Extracted from ANTLR .g4 grammar files:
- `athena`, `clickhouse`, `derby`, `drill`, `hive`, `informix-sql`, `mariadb`, `mysql`, `phoenix`, `plsql`, `postgresql`, `snowflake`, `sqlite`, `starrocks`, `teradata`, `trino`, `tsql`

### Dialect Patches (29)
JSON files that extend base grammars with dialect-specific features:

**PostgreSQL Family** (10 dialects):
- `redshift` - Amazon Redshift (DISTKEY, SORTKEY, SUPER type)
- `duckdb` - DuckDB (QUALIFY, ASOF joins, LIST type)
- `cockroachdb` - CockroachDB (UPSERT, distributed features)
- `materialize` - Materialize (streaming, TAIL)
- `vertica` - Vertica (PROJECTION, SEGMENTED BY)
- `greenplum` - Greenplum (DISTRIBUTED BY)
- `risingwave` - RisingWave (EMIT CHANGES, watermarks)
- `timescaledb` - TimescaleDB (time_bucket, hypertables)
- `yugabytedb` - YugabyteDB (SPLIT INTO TABLETS)
- `dune` - Dune SQL (blockchain types)

**Hive/Spark Family** (4 dialects):
- `spark` - Apache Spark (CACHE TABLE, <=> operator)
- `databricks` - Databricks (OPTIMIZE, ZORDER, Delta Lake)
- `impala` - Apache Impala (COMPUTE STATS, UPSERT)
- `spark2` - Apache Spark 2.x

**MySQL Family** (3 dialects):
- `singlestore` - SingleStore (VECTOR type, SHARD KEY)
- `doris` - Apache Doris (DUPLICATE KEY, BITMAP)
- `tidb` - TiDB (AUTO_RANDOM, FLASHBACK)

**Trino Family** (2 dialects):
- `presto` - Presto (APPROX_DISTINCT, HYPERLOGLOG)
- `dremio` - Dremio (REFLECTION, VDS/PDS)

**Oracle/T-SQL** (2 dialects):
- `oracle` - Oracle Database (CONNECT BY, FLASHBACK)
- `fabric` - Microsoft Fabric (LAKEHOUSE, ML functions)

**Standalone** (8 dialects):
- `bigquery` - Google BigQuery (STRUCT, ARRAY, QUALIFY)
- `druid` - Apache Druid (TIME_FLOOR, DataSketches)
- `db2` - IBM DB2 (DECFLOAT, ORGANIZE BY)
- `netezza` - IBM Netezza (GROOM TABLE)
- `tableau` - Tableau (ZN, ATTR functions)
- `exasol` - Exasol (DISTRIBUTE BY, UDF scripts)
- `solr` - Apache Solr (SCORE, faceting)
- `calcite` - Apache Calcite (standard SQL framework)

## Patch Format

Each patch is a JSON file with the following structure:

```json
{
  "dialect_name": "example",
  "base_dialect": "postgresql",
  "description": "Description of the dialect",
  "keywords": {
    "add": [
      {"name": "KEYWORD", "token_type": "KEYWORD"}
    ],
    "remove": ["KEYWORD_TO_REMOVE"]
  },
  "operators": {
    "add": [
      {
        "symbol": "<=>",
        "token_type": "NULL_SAFE_EQ",
        "precedence": "comparison",
        "associativity": "left"
      }
    ]
  },
  "functions": {
    "add": [
      {"name": "FUNC_NAME", "category": "aggregate"}
    ]
  },
  "data_types": {
    "add": [
      {"name": "CUSTOM_TYPE", "token_type": "CUSTOM_TYPE"}
    ]
  },
  "syntax_features": {
    "supports_qualify": true,
    "identifier_quote_char": "\""
  }
}
```

## Build Process

The CMake build system automatically:
1. Finds all patch files in `dialects/patches/`
2. Maps each patch to its base grammar
3. Runs `scripts/merge_grammar.py` to merge base + patch
4. Outputs merged grammars to `build/generated/grammar_data/`

## Verification

Run `scripts/verify_dialects.py` to verify patches against known SQLGlot features and ensure accuracy.

## Testing

Comprehensive dialect tests in `tests/test_dialect_coverage.cpp` validate that each dialect correctly tokenizes dialect-specific SQL syntax.

## Coverage

- **Total dialects**: 46
- **SQLGlot parity**: 100% (all 31+ dialects covered)
- **Additional dialects**: +15 production databases
- **Test coverage**: 360+ tests passing

## Adding a New Dialect

1. Create `dialects/patches/your_dialect.json`
2. Specify base dialect and features
3. Update `PATCH_BASE_MAP` in `CMakeLists.txt`
4. Add tests in `tests/test_dialect_coverage.cpp`
5. Run `scripts/verify_dialects.py`
