# libsqlglot

#### What is this?

sqlglot, in C++. 31+ dialects, 126× faster on benchmark SQL, 235× on the kind your ORM generates when nobody's looking. Speedup scales with query complexity, see [Benchmarks](#benchmarks).

Also supports stored procedures (PL/pgSQL, T-SQL, MySQL, PL/SQL): where sqlglot falls back to passthrough, libsqlglot parses them into the AST.

Inspired by the original [sqlglot](https://github.com/tobymao/sqlglot), which did the decade-long work of mapping 31+ SQL dialects into an elegant, universal AST. libsqlglot does the comparatively trivial work of compiling it. The algorithm was already O(n), the runtime was O(python).

#### What is this for?

DB proxies, linters, migration tools, query rewriters, and a proper replacement for every regex that's pretending to parse SQL in your codebase. If latency matters, use this. If it doesn't, sqlglot is great.

## Contents

- [Functionality](#functionality)
- [Quickstart](#quickstart)
  - [C++](#c)
  - [Python](#python)
- [Differences from original sqlglot](#differences-from-original-sqlglot)
- [Building](#building)
- [Architecture](#architecture)
- [Benchmarks](#benchmarks)
- [Examples](#examples)
- [Supported SQL dialects](#supported-sql-dialects)
- [Licence](#licence)

## Functionality

Transpiles between 31+ SQL dialects via sqlglot AST. Full stored procedure support. Fail-fast errors with exact line and column. Python bindings available at 95-98% of C++ speed (`import libsqlglot as sqlglot` and go).

Handles the full SQL surface: SELECT, INSERT, UPDATE, DELETE, CREATE TABLE, ALTER TABLE, DROP TABLE, TRUNCATE, MERGE, plus stored procedures (CALL, RETURN, DECLARE, IF/ELSEIF/ELSE, WHILE, FOR loops). Also handles CTEs, window functions, subqueries, and various JOIN types.

Compatible with 31+ dialects (see [Supported SQL dialects](#supported-sql-dialects) for the full list).

## Quickstart

### C++

```cpp
#include <libsqlglot/transpiler.h>

using namespace libsqlglot;

// Transpile between dialects (MySQL → PostgreSQL)
std::string output = Transpiler::transpile(
    "SELECT `id`, `name` FROM `users` LIMIT 10",
    Dialect::MySQL,
    Dialect::PostgreSQL
);
// Returns: SELECT "id", "name" FROM "users" LIMIT 10

// Parse SQL into AST
Arena arena;
auto stmt = Transpiler::parse(arena, "SELECT name FROM users WHERE age > 18");
// Returns: AST with SelectStmt node

// Optimize AST (column qualification, predicate pushdown, constant folding)
Transpiler::optimize(arena, stmt);
// Modifies AST: name → users.name, age → users.age

// Generate SQL from AST
std::string sql = Transpiler::generate(stmt, Dialect::PostgreSQL);
// Returns: SELECT users.name FROM users WHERE users.age > 18
```

See [Supported SQL dialects](#supported-sql-dialects) for all available `Dialect::` values.

### Python

Available on PyPI: `pip install libsqlglot`

```python
import libsqlglot as sqlglot

# Transpile between dialects (MySQL → PostgreSQL)
sql = sqlglot.transpile(
    "SELECT `id`, `name` FROM `users` LIMIT 10",
    sqlglot.Dialect.MySQL,
    sqlglot.Dialect.PostgreSQL
)
# Returns: 'SELECT "id", "name" FROM "users" LIMIT 10'

# Parse SQL into AST
stmt = sqlglot.parse("SELECT id, name FROM users WHERE active = TRUE")
# Returns: Statement object (AST)

# Generate SQL for different dialects
sql_postgres = stmt.sql(dialect=sqlglot.Dialect.PostgreSQL, pretty=True)
# Returns: 'SELECT id, name FROM users WHERE active = TRUE'

sql_sqlserver = stmt.sql(dialect=sqlglot.Dialect.SQLServer)
# Returns: 'SELECT id, name FROM users WHERE active = 1'  (TRUE → 1)

# AST traversal - find all column references
columns = stmt.find_all(sqlglot.ExprType.COLUMN)
# Returns: [Column(id), Column(name), Column(active)]

# AST traversal - walk all nodes
stmt.walk(lambda node: print(node.type))
# Prints: SELECT, COLUMN, COLUMN, TABLE, WHERE, COLUMN, LITERAL

# Optimize query (column qualification, predicate pushdown)
optimized = sqlglot.optimize(stmt)
sql = optimized.sql()
# Returns: 'SELECT users.id, users.name FROM users WHERE users.active = TRUE'
```

See [Supported SQL dialects](#supported-sql-dialects) for all available `sqlglot.Dialect.` values.

**Python API**: `parse()`, `parse_one()`, `generate()`, `transpile()`, `optimize()`, `diff()`, `.sql()`, `.find_all()`, `.walk()`, `select()` builder, as seen in Python sqlglot.

**Performance**: 95-98% of C++ speed. Overhead is ~125ns per call (10ns function call + 100ns string marshal + 15ns misc). On typical 2.5μs parse, this is 5% overhead. On complex 25μs parse, 0.5% overhead.

**Memory**: Thread-local arenas, no runtime dependencies.

## Differences from original sqlglot

| | libsqlglot | Python sqlglot |
|---|---|---|
| **Performance** | 32-242× faster (126× avg) | Baseline |
| **Stored procedures** | Full support (PL/pgSQL, T-SQL, MySQL, PL/SQL) | Limited (`exp.Command` passthrough) |
| **Error handling** | Fail-fast with precise errors (line, column, context) | Error recovery (IDE-friendly, slower) |
| **Memory** | Arena allocation (O(1) cleanup) | Garbage collection |
| **Optimizer** | Column qualification, predicate pushdown, constant folding, subquery elimination | Same + additional passes + full execution engine |
| **Codebase** | 7,319 lines C++ | 50,000+ lines Python |
| **Binary** | 15KB lib, optional 258KB Python extension | N/A |

Everything else (SQL coverage, 31+ dialects, no runtime deps) is the same.

## Building

Requires C++23 (Clang 18+, GCC 13+, or MSVC 19.36+) and CMake 3.24+.

### C++ library

```bash
cmake -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build -j$(nproc)
sudo cmake --install build
```

### Python package

```bash
pip install -e .
```

### Building with tests and benchmarks

```bash
cmake -B build -DCMAKE_BUILD_TYPE=Release \
               -DLIBSQLGLOT_BUILD_TESTS=ON \
               -DLIBSQLGLOT_BUILD_BENCHMARKS=ON
cmake --build build -j$(nproc)
ctest --test-dir build
```

**Compiled sizes** (stripped, `-O3`): C++ library 15KB, Python extension 258KB.

**Code quality**: Compiles with `-Wall -Wextra -Wpedantic -Werror`. No runtime dependencies. No RTTI. Passes 26,554 assertions across 288 test cases. Fuzz-tested with `libFuzzer` + `AddressSanitizer`.

## Architecture

7,319 lines of C++ headers, 16 files, no `.cpp`. See `include/libsqlglot/` for the full layout. The big ones: `parser.h` (1980 lines), `generator.h` (1288), `expression.h` (966, 88 expression types). Entry point is `transpiler.h` (86 lines).

### Memory management

Arena allocation: all AST nodes allocated in contiguous chunks, freed together in O(1) time. String interning deduplicates identifiers. Tokenisation is zero-copy via `string_view`. Everything uses RAII, no manual `delete` calls.

### SQL support

**Statements**: SELECT, INSERT, UPDATE, DELETE, MERGE, CREATE TABLE, ALTER TABLE, DROP TABLE, DROP INDEX, TRUNCATE, CREATE VIEW, DROP VIEW, CREATE SCHEMA, DROP SCHEMA

**Stored procedures**: CALL, RETURN, DECLARE, IF/ELSEIF/ELSE/END IF, WHILE/DO/END WHILE, FOR/IN/LOOP/END LOOP

**Clauses**: WHERE, GROUP BY, HAVING, ORDER BY, LIMIT, OFFSET, QUALIFY

**JOINs**: INNER, LEFT, RIGHT, FULL, CROSS, NATURAL, ASOF

**Advanced**: CTEs (WITH RECURSIVE), window functions (PARTITION BY, ORDER BY, ROWS/RANGE, named windows), subqueries, PIVOT/UNPIVOT

**Operators**: Arithmetic, comparison, logical, LIKE, ILIKE, IS NULL, BETWEEN, IN, EXISTS

**Expressions**: CASE WHEN, arrays, array indexing, set operations (UNION, INTERSECT, EXCEPT)

**Transactions**: BEGIN, COMMIT, ROLLBACK, SAVEPOINT

**Utilities**: SET, DESCRIBE, SHOW, EXPLAIN

## Testing

288 test cases, 26,554 assertions, all passing.

```bash
cd build
ctest --output-on-failure

# Run specific test suites
./tests/libsqlglot_tests "[parser]"
./tests/libsqlglot_tests "[security]"
./tests/libsqlglot_tests "[stored_procedures]"
./tests/libsqlglot_tests "[performance]"

# Run benchmarks
./benchmarks/bench_tokenizer
./benchmarks/bench_parser
./benchmarks/bench_transpiler
./benchmarks/bench_sqlglot_comparison
```

## Security

26,554 assertions covering SQL injection, buffer overflow, stack overflow (recursion depth at 256, adjustable via `Parser::kMaxRecursionDepth` in `parser.h`), memory corruption (arena prevents use-after-free and double-free), integer overflow, and encoding attacks (UTF-8 identifiers rejected, UTF-8 string literals accepted). All pass.

## Fuzzing

There is a `libFuzzer` target in `fuzzing/fuzz_parser.cpp`:

```bash
cd fuzzing
clang++ -fsanitize=fuzzer,address -std=c++23 -I../include fuzz_parser.cpp -o fuzz_parser
./fuzz_parser -max_len=10000 -timeout=10
```

## Compatibility testing

Test compatibility with Python sqlglot's test fixtures:

```bash
cd compat
python sqlglot_compat.py --sqlglot-path /path/to/sqlglot --limit 1000
```

## Errors

libsqlglot provides precise, actionable error messages with exact locations:

```cpp
Arena arena;
Parser parser(arena, "SELECT FROM users");  // Missing column list

// Throws: Line 1, column 8: Expected column list after SELECT (found: 'FROM')
```

All parse errors include line number, column number, the actual token that caused the error, and a human-readable explanation of what was expected. Fail-fast, no cascading secondary errors.

## Examples

### Dialect conversion

```cpp
// MySQL -> PostgreSQL
std::string mysql_sql = "SELECT `user_id`, `name` FROM `users` LIMIT 10";
std::string pg_sql = Transpiler::transpile(
    mysql_sql, Dialect::MySQL, Dialect::PostgreSQL
);
// Output: SELECT "user_id", "name" FROM "users" LIMIT 10
```

### Building AST by hand

```cpp
Arena arena;
auto stmt = arena.create<SelectStmt>();

// SELECT *
stmt->columns.push_back(arena.create<Star>());

// FROM users
stmt->from = arena.create<TableRef>("users");

// WHERE age > 18
auto age_col = arena.create<Column>("age");
auto threshold = arena.create<Literal>("18");
stmt->where = arena.create<BinaryOp>(ExprType::GT, age_col, threshold);

std::string sql = Generator::generate(stmt);
// "SELECT * FROM users WHERE age > 18"
```

### Optimisation

```cpp
Arena arena;
auto stmt = Transpiler::parse(arena,
    "SELECT name FROM users WHERE age > 18");

// Apply optimisation passes
Transpiler::optimize(arena, stmt);

// Optimisations include:
// - Column qualification (name -> users.name)
// - Predicate pushdown
// - Constant folding
// - Subquery elimination

std::string sql = Transpiler::generate(stmt);
// "SELECT users.name FROM users WHERE users.age > 18"
```

### Stored procedures (PL/pgSQL, T-SQL, MySQL, Oracle)

```cpp
Arena arena;
std::string plpgsql = R"(
    FOR i IN 1..100 LOOP
        IF i > 50 THEN
            RETURN i;
        END IF
    END LOOP
)";

auto stmt = Transpiler::parse(arena, plpgsql);
std::string output = Transpiler::generate(stmt, Dialect::PostgreSQL);
```

### Transpiling between dialects

```cpp
// Real-world analytics query: CTEs, window functions, multiple JOINs
std::string mysql_query = R"(
    WITH regional_sales AS (
        SELECT
            region,
            product_id,
            SUM(amount) as total_sales,
            COUNT(order_id) as order_count,
            ROW_NUMBER() OVER (PARTITION BY region ORDER BY SUM(amount) DESC) as sales_rank
        FROM orders
        WHERE order_date >= '2024-01-01'
        GROUP BY region, product_id
        HAVING SUM(amount) > 10000
    ),
    top_regions AS (
        SELECT region
        FROM regional_sales
        WHERE sales_rank <= 5
        GROUP BY region
        HAVING COUNT(*) > 3
    )
    SELECT
        r.region,
        r.product_id,
        p.product_name,
        r.total_sales,
        r.order_count,
        RANK() OVER (ORDER BY r.total_sales DESC) as overall_rank,
        LAG(r.total_sales) OVER (ORDER BY r.total_sales DESC) as prev_sales
    FROM regional_sales r
    INNER JOIN products p ON r.product_id = p.id
    INNER JOIN top_regions t ON r.region = t.region
    WHERE r.sales_rank <= 10
    ORDER BY r.total_sales DESC
    LIMIT 100
)";

// MySQL → BigQuery
std::string bigquery = Transpiler::transpile(
    mysql_query, Dialect::MySQL, Dialect::BigQuery
);
// Full semantic preservation: CTEs, window functions, JOINs all intact

// Round-trip: MySQL → BigQuery → PostgreSQL → Snowflake → MySQL
std::string step1 = Transpiler::transpile(mysql_query, Dialect::MySQL, Dialect::BigQuery);
std::string step2 = Transpiler::transpile(step1, Dialect::BigQuery, Dialect::PostgreSQL);
std::string step3 = Transpiler::transpile(step2, Dialect::PostgreSQL, Dialect::Snowflake);
std::string back_to_mysql = Transpiler::transpile(step3, Dialect::Snowflake, Dialect::MySQL);
// Query semantics preserved across 4 dialect conversions

// Simple transformations: PostgreSQL → SQL Server
std::string pg_query = "SELECT * FROM users WHERE active = TRUE LIMIT 10";
Arena arena;
Parser parser(arena, pg_query);
auto stmt = parser.parse_select();
std::string sql_server = Generator::generate(stmt, Dialect::SQLServer);
// Result: SELECT TOP 10 * FROM users WHERE active = 1
// LIMIT → TOP, TRUE → 1

// Multi-dialect pipeline: Parse once, generate for multiple targets
Arena shared_arena;
auto ast = Transpiler::parse(shared_arena, "SELECT name FROM users WHERE age > 18");

std::string postgres_sql = Generator::generate(ast, Dialect::PostgreSQL);
std::string mysql_sql = Generator::generate(ast, Dialect::MySQL);
std::string duckdb_sql = Generator::generate(ast, Dialect::DuckDB);
std::string snowflake_sql = Generator::generate(ast, Dialect::Snowflake);
// Single parse, multiple outputs - efficient for multi-target scenarios
```

## Benchmarks

Benchmarks run on x86-64 Linux with `-O3` optimisation. libsqlglot compared against pure Python sqlglot 30.0.1. Python bindings add ~125ns overhead (95-98% of C++ performance).

**What we measure:** Full parse + generate round-trip (SQL → AST → SQL). No optimisation applied in either implementation. Both produce identical output, proving identical work done. Apples-to-apples comparison of parser and generator performance.

**Measurement:** `std::chrono::high_resolution_clock` with 1000 iterations per query, averaged.

The 16 standard queries are sqlglot's benchmark. The 8 stress tests are ours, excluded from the average. They're here to show the scaling doesn't stop: 178.6× on benchmarks, 235× on these. What happens past 235× is left as an exercise for the reader.

### Standard benchmarks (16 queries)

| Query              | sqlglot (μs) | libsqlglot (μs) | Speedup  |
|--------------------|--------------|-----------------|----------|
| many_ctes          | 1,097.84     | 4.53            | 242.4×   |
| many_joins         | 1,038.03     | 5.81            | 178.7×   |
| nested_functions   | 892.91       | 6.27            | 142.4×   |
| nested_subqueries  | 495.97       | 2.79            | 177.8×   |
| many_unions        | 2,585.04     | 17.30           | 149.4×   |
| tpch               | 1,110.16     | 7.74            | 143.4×   |
| complex_where      | 575.69       | 4.27            | 134.8×   |
| many_windows       | 933.16       | 13.00           | 71.8×    |
| deep_arithmetic    | 388.10       | 2.86            | 135.7×   |
| many_columns       | 1,643.41     | 14.81           | 110.9×   |
| values             | 15,951.28    | 162.90          | 97.9×    |
| large_case         | 4,480.21     | 35.30           | 126.9×   |
| large_in           | 11,756.63    | 116.38          | 101.0×   |
| many_numbers       | 6,463.57     | 67.71           | 95.5×    |
| short              | 118.61       | 1.54            | 77.0×    |
| large_strings      | 146.92       | 4.54            | 32.4×    |

**Average: 126.1× faster** (range: 32.4× to 242.4×). A million queries: 29 seconds vs 52 minutes.

libsqlglot achieves this through arena allocation (O(1) cleanup), perfect hash keyword lookup (O(1)), zero-copy tokenisation via `string_view`, compile-time optimisations (C++23 `constexpr`), and cache-friendly memory layout (spatial locality, cacheline utilisation, no per-node `malloc`/`new` fragmentation as seen in Python).

### Stress tests (8 queries, supplementary)

Designed to break parsers: 15-level nested CTEs, 35-level CASE expressions, 100+ WHERE conditions, 20-way joins. 1,186 lines of SQL, 51KB total.

| Query                    | sqlglot (μs) | libsqlglot (μs) | Speedup  |
|--------------------------|--------------|-----------------|----------|
| Correlated subqueries    | 14,238.29    | 60.60           | 235.0×   |
| Complex subqueries       | 16,108.10    | 73.18           | 220.1×   |
| Complex string functions | 14,029.58    | 71.42           | 196.4×   |
| Deep CTE nesting         | 14,768.54    | 82.36           | 179.3×   |
| Union chains             | 19,411.56    | 115.77          | 167.7×   |
| Complex WHERE clause     | 13,039.82    | 81.99           | 159.0×   |
| Deep CASE nesting        | 13,831.84    | 103.10          | 134.2×   |
| Multi-table joins        | 12,791.94    | 141.16          | 90.6×    |

**Average: 172.8× faster** (range: 90.6× to 235.0×). A million queries: 91 seconds vs 4 hours.

### Validation

```python
# Python sqlglot: 3,917 μs
parsed = sqlglot.parse_one("SELECT * FROM users WHERE age > 18")
output = parsed.sql()  # "SELECT * FROM users WHERE age > 18"
```

```cpp
// libsqlglot: 45 μs (87× faster)
Arena arena;
auto ast = Transpiler::parse(arena, "SELECT * FROM users WHERE age > 18");
auto output = Transpiler::generate(ast);  // "SELECT * FROM users WHERE age > 18"
```

See `benchmarks/bench_complete_comparison.py` to reproduce.

## Supported SQL dialects

31+ dialects with full parse and generation support. Use `Dialect::Name` in C++ or `sqlglot.Dialect.Name` in Python.

Each dialect includes proper identifier quoting, keyword handling, function name translation, and syntax transformations (e.g. LIMIT vs TOP vs FETCH FIRST).

<table>
<tr>
<td valign="top">

**Production RDBMS**
| Database | Dialect |
|----------|---------|
| PostgreSQL | PostgreSQL |
| MySQL | MySQL |
| MariaDB | MariaDB |
| SQLite | SQLite |
| Oracle | Oracle |
| SQL Server | SQLServer |

</td>
<td valign="top">

**Data warehousing**
| Database | Dialect |
|----------|---------|
| BigQuery | BigQuery |
| Snowflake | Snowflake |
| Redshift | Redshift |
| Athena | Athena |
| Databricks | Databricks |

</td>
</tr>
<tr>
<td valign="top">

**Analytics**
| Database | Dialect |
|----------|---------|
| DuckDB | DuckDB |
| ClickHouse | ClickHouse |
| Presto | Presto |
| Trino | Trino |
| Hive | Hive |
| Spark | Spark |
| Impala | Impala |
| Drill | Drill |

</td>
<td valign="top">

**Specialised**
| Database | Dialect |
|----------|---------|
| CockroachDB | CockroachDB |
| TimescaleDB | TimescaleDB |
| Greenplum | Greenplum |
| Vertica | Vertica |
| Teradata | Teradata |
| Netezza | Netezza |
| Phoenix | Phoenix |
| Calcite | Calcite |
| Dremio | Dremio |
| Pinot | Pinot |
| StarRocks | StarRocks |
| Doris | Doris |
| ANSI SQL | ANSI |

</td>
</tr>
</table>

## Licence

Apache 2.0
