# libsqlglot

sqlglot, in C++. 37x faster for simple queries, 1650x for complex `WHERE`. Performance gap scales with query complexity. See [Benchmarks](#benchmarks).

Parses SQL into an AST, generates SQL from the AST, transpiles between 31+ dialects. Full stored procedure support. Fail-fast errors with exact line and column. Python bindings at 95-98% of C++ speed (`import libsqlglot as sqlglot` and go).

Inspired by the original [sqlglot](https://github.com/tobymao/sqlglot), which did the hard work of mapping every dialect quirk across 31+ databases. libsqlglot does the easy part: free it from Python.

## What this covers

The full SQL surface: SELECT, INSERT, UPDATE, DELETE, CREATE TABLE, ALTER TABLE, DROP TABLE, TRUNCATE, MERGE, plus stored procedures (CALL, RETURN, DECLARE, IF/ELSEIF/ELSE, WHILE, FOR loops). Also handles CTEs, window functions, subqueries, and various JOIN types. See [SQL support](#sql-support)

31+ dialects. See [Supported SQL dialects](#supported-sql-dialects).

## C++ API

```cpp
#include <libsqlglot/transpiler.h>

using namespace libsqlglot;

// Transpile between dialects
std::string output = Transpiler::transpile(
    "SELECT * FROM users WHERE age > 18",
    Dialect::MySQL,
    Dialect::PostgreSQL
);

// Parse, optimise, generate
Arena arena;
auto stmt = Transpiler::parse(arena, "SELECT name FROM users");
Transpiler::optimize(arena, stmt);
std::string sql = Transpiler::generate(stmt, Dialect::DuckDB);
```

## Python bindings

```python
import libsqlglot as sqlglot

# Transpile
sql = sqlglot.transpile(
    "SELECT * FROM users LIMIT 10",
    sqlglot.Dialect.MySQL,
    sqlglot.Dialect.PostgreSQL
)

# Parse and generate
stmt = sqlglot.parse("SELECT id, name FROM users")
sql = stmt.sql(dialect=sqlglot.Dialect.DuckDB, pretty=True)

# AST traversal
columns = stmt.find_all(sqlglot.ExprType.COLUMN)
stmt.walk(lambda node: print(node.type))

# Optimise
optimized = sqlglot.optimize(stmt)
```

**Python API**: `parse()`, `parse_one()`, `generate()`, `transpile()`, `optimize()`, `diff()`, `.sql()`, `.find_all()`, `.walk()`, `select()` builder

**Performance**: 95-98% of C++ speed. Overhead is ~125ns per call (10ns function call + 100ns string marshal + 15ns misc). On typical 2.5μs parse, this is 5% overhead. On complex 25μs parse, 0.5% overhead.

**Memory**: Thread-local arenas, zero runtime dependencies.

### Where libsqlglot differs from Python sqlglot

| | libsqlglot | Python sqlglot |
|---|---|---|
| **Performance** | 37-1650x faster (504x avg) | Baseline |
| **Stored procedures** | Full support (PL/pgSQL, T-SQL, MySQL, PL/SQL) | Limited (`exp.Command` passthrough) |
| **Error handling** | Fail-fast with precise errors (line, column, context) | Error recovery (IDE-friendly, slower) |
| **Memory** | Arena allocation (O(1) cleanup) | Garbage collection |
| **Optimizer** | Column qualification, predicate pushdown, constant folding, subquery elimination | Same + additional passes + full execution engine |
| **Codebase** | 7,245 lines C++ | 50,000+ lines Python |
| **Binary** | 15KB lib + 258KB Python extension | N/A |

Everything else (SQL coverage, 31+ dialects, zero runtime deps) is the same.

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

**Compiled sizes** (stripped, -O3): C++ library 15KB, Python extension 258KB.

**Code quality**: Compiles with `-Wall -Wextra -Wpedantic -Werror`. Zero runtime dependencies. No RTTI. Passes 26,037 assertions across 240 test cases. Fuzz-tested with libFuzzer + AddressSanitizer.

## Architecture

7,245 lines of C++ headers, 15 files, no `.cpp` files. See `include/libsqlglot/` for the full layout. The big ones: `parser.h` (1924 lines), `generator.h` (1286), `expression.h` (965, 118 expression types). Entry point is `transpiler.h` (86 lines).

### Memory management

Arena allocation: all AST nodes allocated in contiguous chunks, freed together in O(1) time. String interning deduplicates identifiers. Tokenisation is zero-copy via string_view. Everything uses RAII, no manual delete calls.

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

240 test cases, 26,037 assertions, all passing.

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

26,037 assertions covering SQL injection, buffer overflow, stack overflow (recursion depth at 256, adjustable via `Parser::kMaxRecursionDepth` in `parser.h`), memory corruption (arena prevents use-after-free and double-free), integer overflow, and encoding attacks (UTF-8 identifiers rejected, UTF-8 string literals accepted). All pass.

## Fuzzing

There is a libFuzzer target in `fuzzing/fuzz_parser.cpp`:

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

## Error Messages

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

### Real-world analytics query

```cpp
// Complex query: multiple CTEs, window functions, aggregates, multiple JOINs
std::string sql = R"(
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

Arena arena;
auto stmt = Transpiler::parse(arena, sql);

// Pretty-print
Generator::Options opts;
opts.pretty = true;
std::string formatted = Generator::generate(stmt, Dialect::PostgreSQL, opts);
```

## Benchmarks

Benchmarks run on x86-64 with -O3. libsqlglot (C++ and Python bindings) compared against Python sqlglot and its C extension.

Times in seconds. Ratio shows libsqlglot time vs sqlglot[c] time. Speedup shows how many times faster. Python bindings add ~125ns overhead (95-98% of C++ performance).

| Query              | sqlglot    | sqlglot[c] | libsqlglot | Ratio    | Speedup  |
|--------------------|------------|------------|------------|----------|----------|
| tpch               | 0.002709   | 0.000740   | 0.000007   | 0.00946x | 105.71x  |
| short              | 0.000226   | 0.000075   | 0.000002   | 0.0267x  | 37.50x   |
| deep_arithmetic    | 0.007760   | 0.002015   | 0.000003   | 0.00149x | 671.67x  |
| large_in           | 0.407987   | 0.101644   | 0.000123   | 0.00121x | 826.37x  |
| values             | 0.466734   | 0.113762   | 0.000159   | 0.00140x | 715.48x  |
| many_joins         | 0.011943   | 0.002701   | 0.000006   | 0.00222x | 450.17x  |
| many_unions        | 0.041321   | 0.008291   | 0.000019   | 0.00229x | 436.37x  |
| nested_subqueries  | 0.001200   | 0.000235   | 0.000003   | 0.0128x  | 78.33x   |
| many_columns       | 0.011821   | 0.002825   | 0.000013   | 0.00460x | 217.31x  |
| large_case         | 0.035822   | 0.008593   | 0.000036   | 0.00419x | 238.69x  |
| complex_where      | 0.032710   | 0.006602   | 0.000004   | 0.00061x | 1650.50x |
| many_ctes          | 0.017610   | 0.003630   | 0.000004   | 0.00110x | 907.50x  |
| many_windows       | 0.020790   | 0.005751   | 0.000006   | 0.00104x | 958.50x  |
| nested_functions   | 0.000703   | 0.000189   | 0.000005   | 0.0265x  | 37.80x   |
| large_strings      | 0.005073   | 0.001480   | 0.000004   | 0.00270x | 370.00x  |
| many_numbers       | 0.103898   | 0.024483   | 0.000067   | 0.00274x | 365.42x  |

**Avg speedup: 504.21x faster than sqlglot[c]**

libsqlglot achieves 37-1650x speedup over sqlglot's C extension through:
- Arena allocation (O(1) cleanup)
- Perfect hash keyword lookup (O(1))
- Zero-copy tokenisation via string_view
- Compile-time optimisations (C++23 constexpr)
- Cache-friendly memory layout (spatial locality, cacheline utilisation, no fragmentation unlike malloc/new per node)

## Supported SQL dialects

31+ dialects with full parse and generation support:

**Production RDBMS**: PostgreSQL, MySQL, MariaDB, SQLite, Oracle, SQL Server, DB2

**Data warehousing**: BigQuery, Snowflake, Redshift, Athena, Databricks

**Analytics**: DuckDB, ClickHouse, Presto, Trino, Hive, Spark, Impala, Drill

**Specialised**: CockroachDB, TimescaleDB, Greenplum, Vertica, Teradata, Netezza, Phoenix, Calcite, Dremio, Pinot, StarRocks, Doris

Each dialect includes proper identifier quoting, keyword handling, function name translation, and syntax transformations (e.g. LIMIT vs TOP vs FETCH FIRST).

## Licence

Apache 2.0