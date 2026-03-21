# Changelog

## [0.2.0] - 2026-03-21

### Added
- **C++26 Static Reflection**: Auto-generates 300+ keyword mappings from `TokenType` enum at compile time using `std::meta`
- **45 SQL Dialects**: Added 14 new dialects (BigQuery, Calcite, CockroachDB, Databricks, DB2, Doris, Dremio, Druid, DuckDB, Dune, Exasol, Fabric, Greenplum, Materialize, Netezza, Presto, RisingWave, SingleStore, Solr, Spark, Spark2, Tableau, TiDB, Vertica, YugabyteDB)
- **ANTLR Grammar Transpiler**: Automated grammar extraction from ANTLR grammars to C++ LUT
- **Dialect-Specific Features**: Comprehensive support for dialect-specific syntax (QUALIFY, ASOF joins, DISTKEY, VECTOR types, etc.)
- **Grammar Patterns**: 1.4M+ lines of generated grammar data from ANTLR sources
- **Operator Precedence**: Integrated operator precedence system with 70+ operators

### Changed
- **Compiler Requirements**: Now requires C++26 with GCC 16+ trunk (`-freflection`) or equivalent
- **Keywords System**: Replaced manual keyword definitions with reflection-based auto-generation
- **Header-Only Architecture**: Emphasized header-only design (19 headers, no `.cpp` files)
- **Build System**: Updated CMake to handle C++26 flags and reflection requirements
- **CI**: Skip builds on ubuntu-latest/macos-latest until GCC 16 reaches stable (C++26 reflection requirement)

### Improved
- **Zero Maintenance Keywords**: Keyword mappings automatically sync with TokenType enum changes
- **Compile-Time Hash Tables**: Perfect hash function for keyword lookup (300+ keywords, 8-slot collision resolution)
- **Documentation**: Comprehensive dialect features table with specific syntax for all 45 dialects

### Technical Details
- C++26 features: `std::meta`, advanced constexpr, compile-time string processing
- Keyword system: 100% compile-time, zero runtime cost
- Perfect hash: `(first * 31 + last + length) & 255` with 256 slots
- Grammar data: 2.4M+ lines from 17 ANTLR grammars

## [0.1.2] - Previous Release

Initial public release with 31 dialects, stored procedure support, and Python bindings.
