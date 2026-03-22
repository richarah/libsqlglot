# libsqlglot Testing Framework

## Overview

libsqlglot has a comprehensive testing framework with **492 tests** covering all SQL dialects, features, and edge cases. The framework ensures robust, secure, and standards-compliant SQL parsing and transpilation across 45+ database dialects.

## Test Structure

### Test Files (53 total)

```
tests/
├── Core Functionality
│   ├── test_parser.cpp              - Parser fundamentals
│   ├── test_tokenizer.cpp           - Tokenizer correctness
│   ├── test_transpiler.cpp          - Cross-dialect transpilation
│   ├── test_generator.cpp           - SQL generation
│   └── test_optimizer.cpp           - Query optimization
│
├── Dialect Coverage
│   ├── test_all_dialects_comprehensive.cpp     - Universal SQL across all 45 dialects
│   ├── test_dialect_transpilation.cpp          - Dialect-to-dialect conversions
│   ├── test_dialect_transforms.cpp             - Dialect-specific transformations
│   ├── test_dialect_coverage.cpp               - Feature matrix validation
│   └── test_dialect_feature_combinations.cpp   - Feature combination fuzzing (NEW)
│
├── SQL Features
│   ├── test_advanced_sql.cpp       - Complex queries (CTEs, window functions)
│   ├── test_cte_windows_subqueries.cpp  - CTE and window function edge cases
│   ├── test_dml_statements.cpp     - INSERT, UPDATE, DELETE, MERGE
│   ├── test_grant_revoke.cpp       - Security/permissions (GRANT, REVOKE)
│   ├── test_utility_statements.cpp - ANALYZE, VACUUM, DELIMITER
│   └── test_scalar_functions.cpp   - Built-in functions
│
├── Procedural SQL
│   ├── test_stored_procedures.cpp  - CREATE PROCEDURE, functions
│   ├── test_begin_end_blocks.cpp   - BEGIN/END statement blocks
│   ├── test_if_statement.cpp       - Conditional logic
│   ├── test_for_loop.cpp          - FOR loops
│   ├── test_while_loop.cpp        - WHILE loops
│   ├── test_for_while_transpile.cpp - Loop transpilation
│   ├── test_cursors.cpp           - Cursor operations
│   ├── test_exceptions.cpp        - Exception handling
│   ├── test_raise.cpp             - RAISE statements
│   ├── test_assignments.cpp       - Variable assignments
│   ├── test_declare_keyword.cpp   - DECLARE statements
│   ├── test_loop_break_continue.cpp - Loop control
│   └── test_returns_comprehensive.cpp - RETURN statements
│
├── Edge Cases & Security
│   ├── test_error_recovery.cpp    - Error handling
│   ├── test_error_messages.cpp    - Error message quality
│   ├── test_security.cpp          - SQL injection patterns
│   ├── test_fk_check_constraints.cpp - Constraint validation
│   └── test_mad_queries.cpp       - Stress testing
│
├── Memory & Performance
│   ├── test_arena.cpp             - Arena allocator correctness
│   ├── test_intern.cpp            - String interning
│   └── test_performance.cpp       - Benchmarking
│
└── End-to-End
    └── test_end_to_end.cpp        - Full stack integration
```

## Test Categories

### 1. Universal SQL Tests

Test basic SQL statements across **all 45 dialects**:

- `SELECT`, `INSERT`, `UPDATE`, `DELETE`
- `JOIN` (INNER, LEFT, RIGHT, FULL, CROSS)
- `GROUP BY`, `HAVING`, `ORDER BY`, `LIMIT`
- Subqueries, `UNION`, `INTERSECT`, `EXCEPT`

**Coverage**: Every dialect must parse these correctly.

### 2. Dialect-Specific Feature Tests

Test features unique to specific dialects:

| Dialect | Features Tested |
|---------|----------------|
| **PostgreSQL** | ILIKE, array literals, JSON operators, PL/pgSQL |
| **MySQL** | Backtick identifiers, LIMIT syntax, stored procedures |
| **SQL Server** | TOP, bracket identifiers, T-SQL, BEGIN/END |
| **BigQuery** | QUALIFY, three-part names (project.dataset.table) |
| **Oracle** | FETCH FIRST, ROWNUM, PL/SQL, dual table |
| **Snowflake** | QUALIFY, ILIKE, array functions |
| **DuckDB** | PostgreSQL+ extensions, PIVOT |

### 3. Feature Combination Tests (NEW)

Test all combinations of SQL features:

- **70+ SQL templates** × **45 dialects** = 3,150+ test cases
- WHERE clause variations (=, >, <, IN, BETWEEN, LIKE, NULL, AND, OR)
- JOIN combinations (2-way, 3-way, multi-table)
- Aggregation + GROUP BY + HAVING combinations
- Subqueries in WHERE/FROM/SELECT
- CTE variations (simple, multiple, recursive)

**Goal**: Ensure feature interactions work correctly.

### 4. Fuzzing Tests

#### SQL Injection Resistance
```cpp
"SELECT * FROM users WHERE id = 1 OR 1=1"
"SELECT * FROM users; DROP TABLE users--"
"SELECT * FROM users WHERE id = 1'; DROP TABLE users--"
```
**Requirement**: Parser must handle gracefully without crashes.

#### Edge Cases
- **Deep nesting**: 50+ levels of subqueries (stack overflow protection)
- **Long identifiers**: 1000+ character names
- **Special characters**: Unicode, spaces, dashes in identifiers
- **Large queries**: 10,000+ token queries

#### Random Query Generation
- Generates 100+ random valid SQL queries
- Tests parser robustness against unexpected combinations

### 5. Security Tests

#### GRANT/REVOKE Comprehensive Coverage
- Basic permissions: `SELECT`, `INSERT`, `UPDATE`, `DELETE`
- Advanced: `EXECUTE`, `ALL`, `ALL PRIVILEGES`
- Column-level: `GRANT SELECT (id, name) ON users`
- Role management: `GRANT admin_role TO alice`
- Options: `WITH GRANT OPTION`, `WITH ADMIN OPTION`
- Revocation: `REVOKE GRANT OPTION FOR`, `REVOKE ADMIN OPTION FOR`

#### Utility Statements
- `ANALYZE` (statistics gathering)
- `VACUUM` (storage optimization)
- `DELIMITER` (batch script support)

### 6. Cross-Dialect Transpilation

Test **N × N dialect pairs** (selective sampling to avoid 45×45=2025 combinations):

```cpp
MySQL → PostgreSQL → BigQuery → Snowflake → Redshift
Oracle → SQL Server → DuckDB → ClickHouse
Hive → Spark → Presto → Trino
```

**Round-trip testing**: Parse → Transpile → Transpile back → Verify semantics preserved

### 7. Procedural SQL

Full coverage of stored procedure features:

- **Control flow**: IF/ELSE, CASE, FOR, WHILE, LOOP
- **Variables**: DECLARE, assignments (`:=`, `=`, `SET`)
- **Cursors**: DECLARE, OPEN, FETCH, CLOSE
- **Exceptions**: BEGIN/EXCEPTION/END, RAISE
- **Functions**: CREATE FUNCTION, RETURN
- **Procedures**: CREATE PROCEDURE, CALL

Tested across: **PostgreSQL** (PL/pgSQL), **MySQL** (stored procedures), **Oracle** (PL/SQL), **SQL Server** (T-SQL)

## Running Tests

### All Tests
```bash
docker compose -f docker/docker-compose.yml run --rm test
```

### Specific Test Categories
```bash
# Dialect tests only
./build/tests/libsqlglot_tests "[dialects]"

# Fuzzing tests only
./build/tests/libsqlglot_tests "[fuzzing]"

# Security tests
./build/tests/libsqlglot_tests "[security]"

# Performance tests
./build/tests/libsqlglot_tests "[performance]"
```

### Random Fuzzing (excluded by default)
```bash
./build/tests/libsqlglot_tests --run-excluded-tests "[.]"
```

## Test Metrics

| Metric | Value |
|--------|-------|
| **Total Tests** | 492 |
| **Test Files** | 53 |
| **Dialects Covered** | 45 |
| **SQL Templates** | 70+ |
| **Feature Combinations** | 3,150+ |
| **Pass Rate** | 100% |

## Code Quality Standards

### Memory Safety
✅ Arena allocator with:
- Integer overflow protection
- Maximum allocation limits (1GB)
- Alignment safety checks
- RAII with `std::unique_ptr`

✅ No manual memory management:
- No `malloc/free`
- No `new/delete` (except placement new in arena)
- No unsafe C functions (`strcpy`, `strcat`, `sprintf`)

### Parser Safety
✅ Bounds checking on all token access:
```cpp
void advance() {
    if (!is_at_end()) pos_++;  // Safe advancement
}
```

✅ Null pointer checks before string construction:
```cpp
if (is_at_end() || current().text == nullptr) {
    break;
}
```

### Build Configuration Separation

#### Release Build (Production)
```cmake
-O3                       # Full optimization
-march=x86-64             # Portable (no AVX/AVX2 for wheels)
-mtune=generic            # Generic tuning
-flto                     # Link-time optimization
-fmerge-all-constants     # Constant merging
-fvisibility=hidden       # Symbol hiding
```

Optional: `-march=native -mtune=native` for local builds with `LIBSQLGLOT_ENABLE_NATIVE=ON`

#### Debug Build (Development)
```cmake
-O0                       # No optimization
-g                        # Debug symbols
```

**Guarantee**: Debug builds never contaminate release artifacts.

## Best Practices

### Adding New Tests

1. **Create test file**: `tests/test_<feature>.cpp`
2. **Use descriptive tags**: `[category][subcategory]`
   ```cpp
   TEST_CASE("Feature description", "[category][subcategory]") {
       // Test code
   }
   ```
3. **Test all dialects**: Loop through `all_dialects` vector
4. **Add fuzzing**: Include edge cases and random generation
5. **Update this document**: Add to appropriate section

### Test Organization

- **One concept per file**: Don't mix unrelated features
- **Progressive complexity**: Basic → Intermediate → Advanced → Edge cases
- **Clear failure messages**: Use `INFO()` for context
- **Comprehensive coverage**: Test both success and failure paths

### Dialect-Specific Tests

When adding dialect-specific features:

1. Add to `DialectFeatures` in `dialects.h`
2. Create test in `test_dialect_feature_combinations.cpp`
3. Verify feature flag matches actual support
4. Test transpilation to/from other dialects

## Future Enhancements

- [ ] Property-based testing (QuickCheck-style)
- [ ] Mutation testing (inject bugs, verify tests catch them)
- [ ] Coverage analysis (code coverage metrics)
- [ ] Performance regression testing
- [ ] Continuous fuzzing integration
- [ ] Dialect compliance testing against vendor documentation

## Contributing

When submitting code:

1. ✅ **All 492 tests must pass**
2. ✅ Add tests for new features
3. ✅ Add fuzzing tests for edge cases
4. ✅ Update this document
5. ✅ Follow security best practices
6. ✅ Maintain code quality standards

## Continuous Integration

Tests run automatically on:
- Every commit
- Every pull request
- Nightly builds
- Release candidates

**Zero tolerance**: No failing tests in main branch.

---

Last updated: 2026-03-22
Version: 0.4.1
Test count: 492
