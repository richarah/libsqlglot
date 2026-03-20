# Implementation Plan for 100% Coverage

## Goal
Achieve 100% feature coverage across:
1. Universal SQL: 95% → 100%
2. Stored Procedures: 95% → 100%  
3. Dialect-Specific Features: 30% → 100%

---

## IMMEDIATE ACTION ITEMS (Next 2 Hours)

### Phase 1A: Universal SQL Completion (CRITICAL)
**Status**: 5% gap to close
**Estimated Time**: 2-3 hours

#### 1. Foreign Key Constraints (30 min)
- Tokenizer: Already has FOREIGN, KEY, REFERENCES
- Parser changes needed in `parse_create_table()`:
  - Add FOREIGN KEY (col) REFERENCES table (col)
  - Support ON DELETE/UPDATE CASCADE|SET NULL|RESTRICT
- Generator: Output FK clauses
- Tests: Create 5 test cases

#### 2. Check Constraints (20 min)
- Tokenizer: Already has CHECK
- Parser: Add CHECK (expression) in column constraints
- Generator: Output CHECK
- Tests: Create 3 test cases

#### 3. Table-Level Constraints (20 min)
- Parser: After column defs, parse PRIMARY KEY (cols), UNIQUE (cols)
- Generator: Output table constraints
- Tests: Create 3 test cases

#### 4. DROP TABLE (10 min)
- Parser: Replace error stub with implementation
- Generator: Output DROP TABLE
- Tests: Create 2 test cases

#### 5. Scalar Functions - Phase 1 (60 min)
**String Functions** (30 min):
- SUBSTRING(str, start, len)
- CONCAT(str1, str2, ...)
- LENGTH(str)
- UPPER(str), LOWER(str)

**Math Functions** (30 min):
- ROUND(num, decimals)
- FLOOR(num), CEIL(num)
- ABS(num)

Implementation approach:
- Parser: Add function name recognition
- Generator: Dialect-aware output (SUBSTRING vs SUBSTR, LENGTH vs LEN)
- Tests: 2 per function = 14 tests

---

## Phase 1B: Stored Procedures Completion (1 hour)

#### 1. LOOP...END LOOP Support (20 min)
- Parser: Add LOOP keyword handling (infinite loop)
- Add EXIT WHEN condition
- Tests: 3 test cases

#### 2. BREAK/CONTINUE in Loops (20 min)
- Parser: Add BREAK, CONTINUE keywords
- Map to EXIT, CONTINUE in PL/pgSQL
- Tests: 3 test cases

#### 3. Function RETURNS Testing (20 min)
- Already parsed, comprehensive testing needed
- Tests: 5 test cases for CREATE FUNCTION

---

## Phase 2: PostgreSQL 100% (HIGH PRIORITY)

### Estimated Time: 4-6 hours

#### 2.1 LATERAL JOIN (60 min)
```sql
-- Parser implementation
FROM table1
LATERAL JOIN LATERAL (SELECT ... WHERE table1.id = ...) t2
```
- Add LATERAL keyword check before JOIN parsing
- Tests: 4 test cases

#### 2.2 ON CONFLICT (Upsert) (90 min)
```sql
INSERT INTO table (...) VALUES (...)
ON CONFLICT (id) DO UPDATE SET col = EXCLUDED.col
ON CONFLICT DO NOTHING
```
- Parser: After INSERT VALUES, check for ON CONFLICT
- Add EXCLUDED keyword support
- Tests: 6 test cases

#### 2.3 RETURNING Complete (30 min)
- Extend current basic support to all DML
- Tests: INSERT/UPDATE/DELETE RETURNING, 4 tests

#### 2.4 FILTER in Aggregates (30 min)
```sql
COUNT(*) FILTER (WHERE condition)
```
- Parser: After aggregate function, check for FILTER
- Tests: 3 test cases

#### 2.5 TABLESAMPLE (30 min)
```sql
FROM table TABLESAMPLE BERNOULLI (10)
```
- Parser: After table reference, check for TABLESAMPLE
- Tests: 2 test cases

#### 2.6 DO Blocks (30 min)
```sql
DO $$ BEGIN ... END $$
```
- Parser: Add DO statement type
- Tests: 2 test cases

#### 2.7 Array Slicing (30 min)
```sql
array[1:3]
```
- Parser: In array index, check for : operator
- Tests: 3 test cases

#### 2.8 Minor Features (60 min)
- EXCLUDE in SELECT
- Composite types ROW(...)
- ENUM types
- Tests: 2-3 each

---

## Phase 3: MySQL 100% (HIGH PRIORITY)

### Estimated Time: 5-7 hours

#### 3.1 Backtick Identifiers (90 min) **SECURITY CRITICAL**
```sql
`column name with spaces`
`table_name`
```
- Tokenizer: Handle backticks in `tokenize_identifier()`
- Security: Validate content, prevent injection
- Limit: Max 64 chars (MySQL limit)
- Tests: 10 test cases including security tests

**Security measures**:
- No nested backticks
- No escape sequences
- ASCII only (no UTF-8)
- Length validation

#### 3.2 ON DUPLICATE KEY UPDATE (60 min)
```sql
INSERT INTO table (...) VALUES (...)
ON DUPLICATE KEY UPDATE col = VALUES(col)
```
- Parser: After INSERT VALUES
- Tests: 5 test cases

#### 3.3 INSERT IGNORE (15 min)
```sql
INSERT IGNORE INTO table ...
```
- Parser: Match IGNORE after INSERT
- Tests: 2 test cases

#### 3.4 REPLACE INTO (20 min)
```sql
REPLACE INTO table ...
```
- Parser: Like INSERT but with REPLACE keyword
- Tests: 2 test cases

#### 3.5 Index Hints (45 min)
```sql
FROM table FORCE INDEX (idx) USE INDEX (idx) IGNORE INDEX (idx)
```
- Parser: After table name, check for hint keywords
- Tests: 4 test cases

#### 3.6 GROUP_CONCAT (60 min)
```sql
GROUP_CONCAT(expr SEPARATOR ',' ORDER BY expr)
```
- Parser: Special aggregate with SEPARATOR
- Generator: Convert to STRING_AGG for others
- Tests: 5 test cases

#### 3.7 LOAD DATA INFILE (90 min) **SECURITY CRITICAL**
```sql
LOAD DATA LOCAL INFILE 'file.csv' INTO TABLE t
FIELDS TERMINATED BY ',' LINES TERMINATED BY '\n'
```
- Parser: LOAD DATA statement
- Security: Validate file paths, prevent traversal
- Tests: 6 tests (3 functional, 3 security)

**Security measures**:
- Whitelist directories only
- No ../ or absolute paths from untrusted sources
- Filename length limit

---

## Phase 4: T-SQL 100% (HIGH PRIORITY)

### Estimated Time: 4-5 hours

#### 4.1 TOP n Clause (60 min)
```sql
SELECT TOP 10 * FROM table
SELECT TOP 10 PERCENT * FROM table
SELECT TOP 10 WITH TIES * FROM table ORDER BY col
```
- Parser: After SELECT, check for TOP
- Generator: Convert to LIMIT for other dialects
- Tests: 6 test cases

#### 4.2 OUTPUT Clause (90 min)
```sql
INSERT INTO table OUTPUT INSERTED.* VALUES (...)
DELETE FROM table OUTPUT DELETED.* WHERE ...
UPDATE table SET ... OUTPUT INSERTED.*, DELETED.*
```
- Parser: After DML verb, check for OUTPUT
- Generator: Convert to RETURNING for PostgreSQL
- Tests: 6 test cases

#### 4.3 TRY...CATCH (60 min)
```sql
BEGIN TRY
  ...
END TRY
BEGIN CATCH
  SELECT ERROR_MESSAGE()
END CATCH
```
- Parser: New statement type
- Generator: Convert to EXCEPTION blocks
- Tests: 4 test cases

#### 4.4 GO Batch Separator (20 min)
- Parser: Treat as statement terminator
- Tests: 2 test cases

#### 4.5 System Variables (30 min)
```sql
@@IDENTITY, @@ROWCOUNT, @@ERROR
```
- Tokenizer: Handle @@ prefix
- Parser: System variable references
- Tests: 3 test cases

#### 4.6 THROW Statement (20 min)
```sql
THROW 50000, 'Error message', 1
```
- Parser: THROW statement
- Tests: 2 test cases

#### 4.7 PIVOT/UNPIVOT Fix (40 min)
- Current: Parsed but generation broken
- Fix generator implementation
- Tests: 4 test cases

---

## Phase 5: BigQuery 70% Target (MEDIUM PRIORITY)

### Estimated Time: 5-6 hours

#### 5.1 QUALIFY Clause (90 min) **HIGH VALUE**
```sql
SELECT col, ROW_NUMBER() OVER (...) as rn
FROM table
QUALIFY rn = 1
```
- Parser: After HAVING/ORDER BY, check for QUALIFY
- Generator: Wrap in subquery for other dialects
- Tests: 5 test cases

#### 5.2 Backtick Identifiers (reuse MySQL, 30 min)
```sql
`project.dataset.table`
```
- Extend MySQL implementation
- Handle 3-part names
- Tests: 4 test cases

#### 5.3 Struct Literals (90 min)
```sql
STRUCT(1 AS a, 'text' AS b, [1,2,3] AS c)
```
- Parser: STRUCT keyword with field list
- Tests: 5 test cases

#### 5.4 SAFE_CAST (30 min)
```sql
SAFE_CAST(expr AS type)
```
- Parser: Like CAST but SAFE_CAST keyword
- Generator: Convert to TRY_CAST or COALESCE
- Tests: 3 test cases

#### 5.5 Array OFFSET/ORDINAL (60 min)
```sql
array[OFFSET(0)]  -- 0-based
array[ORDINAL(1)] -- 1-based
```
- Parser: OFFSET() and ORDINAL() in array access
- Tests: 4 test cases

#### 5.6 Table Wildcards (60 min) **SECURITY CRITICAL**
```sql
SELECT * FROM `project.dataset.table_*`
WHERE _TABLE_SUFFIX = '20240101'
```
- Parser: Allow * in table names
- Security: Validate patterns
- Tests: 4 tests (2 functional, 2 security)

---

## Phase 6: Oracle 70% Target (MEDIUM PRIORITY)

### Estimated Time: 8-10 hours

#### 6.1 ROWNUM in Queries (90 min)
```sql
SELECT * FROM table WHERE ROWNUM <= 10
```
- Parser: ROWNUM as special column
- Generator: Convert to LIMIT for others
- Tests: 5 test cases

#### 6.2 CONNECT BY (4-5 hours) **COMPLEX**
```sql
SELECT employee, manager
FROM employees
START WITH manager IS NULL
CONNECT BY PRIOR employee = manager
```
- Parser: START WITH, CONNECT BY PRIOR clauses
- Generator: Convert to recursive CTE
- **Complexity**: Requires AST transformation
- Tests: 8-10 test cases

Implementation approach:
1. Parse hierarchical clauses
2. Build recursive CTE structure
3. Transform PRIOR references
4. Test extensively

#### 6.3 MERGE Complete (90 min)
- Fix existing MERGE parsing
- Add all clause variations
- Tests: 5 test cases

#### 6.4 Sequences (60 min)
```sql
CREATE SEQUENCE seq_name
SELECT seq_name.NEXTVAL, seq_name.CURRVAL FROM DUAL
```
- Parser: CREATE SEQUENCE
- Parser: .NEXTVAL, .CURRVAL accessors
- Tests: 4 test cases

#### 6.5 (+) Outer Join (60 min)
```sql
WHERE table1.col = table2.col(+)
```
- Parser: Detect (+) in WHERE clause
- Generator: Convert to LEFT JOIN
- Tests: 3 test cases

---

## Implementation Order (Optimized)

### Sprint 1 (8 hours): Foundation
**Goal**: Universal SQL 100%, Stored Procedures 100%

1. Hour 1-2: Universal SQL DDL (FK, CHECK, DROP TABLE)
2. Hour 3-4: Universal SQL Functions (strings, math)
3. Hour 5-6: Stored Procedures (LOOP, BREAK/CONTINUE)
4. Hour 7-8: Testing, verification, documentation

**Deliverables**:
- 30+ new test cases
- Documentation updates
- All Universal SQL at 100%
- All Stored Procedures at 100%

### Sprint 2 (10 hours): Security-Critical Features
**Goal**: Backtick identifiers, file paths

1. Hour 1-3: MySQL backtick identifiers (with security)
2. Hour 4-5: BigQuery backtick identifiers (extend MySQL)
3. Hour 6-8: MySQL LOAD DATA INFILE (with security)
4. Hour 9-10: Security testing, penetration tests

**Deliverables**:
- 25+ new test cases (15 functional, 10 security)
- Security audit documentation
- MySQL 70%+
- BigQuery 50%+

### Sprint 3 (10 hours): High-Value Features
**Goal**: TOP, OUTPUT, QUALIFY, LATERAL

1. Hour 1-2: T-SQL TOP clause
2. Hour 3-4: T-SQL OUTPUT clause
3. Hour 5-6: BigQuery QUALIFY clause
4. Hour 7-8: PostgreSQL LATERAL JOIN
5. Hour 9-10: PostgreSQL ON CONFLICT

**Deliverables**:
- 30+ new test cases
- T-SQL 90%+
- BigQuery 65%+
- PostgreSQL 80%+

### Sprint 4 (12 hours): Complex Features
**Goal**: CONNECT BY, TRY-CATCH, GROUP_CONCAT

1. Hour 1-5: Oracle CONNECT BY (complex)
2. Hour 6-7: T-SQL TRY...CATCH
3. Hour 8-9: MySQL GROUP_CONCAT
4. Hour 10-11: Oracle ROWNUM
5. Hour 12: Integration testing

**Deliverables**:
- 25+ new test cases
- Oracle 70%+
- T-SQL 100%
- MySQL 85%+

### Sprint 5 (8 hours): Remaining Features
**Goal**: Fill remaining gaps

1. Hour 1-2: PostgreSQL remaining (FILTER, TABLESAMPLE, DO, array slicing)
2. Hour 3-4: MySQL remaining (INSERT IGNORE, REPLACE, hints)
3. Hour 5-6: BigQuery remaining (STRUCT, SAFE_CAST, arrays)
4. Hour 7-8: Oracle remaining (sequences, outer join syntax, MERGE)

**Deliverables**:
- 20+ new test cases
- PostgreSQL 100%
- MySQL 100%
- BigQuery 90%+
- Oracle 85%+

### Sprint 6 (8 hours): Long Tail
**Goal**: Snowflake, DuckDB, ClickHouse basics

1. Hour 1-3: Snowflake high-priority (FLATTEN, stages, VARIANT)
2. Hour 4-6: DuckDB high-priority (EXCLUDE, REPLACE, file reading)
3. Hour 7-8: ClickHouse basics (ENGINE, PARTITION BY)

**Deliverables**:
- 25+ new test cases  
- Snowflake 60%+
- DuckDB 75%+
- ClickHouse 50%+

### Sprint 7 (4 hours): Final Testing & Documentation
**Goal**: 100% verification

1. Hour 1-2: Full regression testing
2. Hour 3: Performance benchmarks
3. Hour 4: Documentation completion

**Deliverables**:
- 1000+ total test cases
- 100% pass rate
- Performance report
- Complete documentation

---

## TOTAL ESTIMATED TIME: 60 hours (1.5 weeks full-time)

---

## Success Criteria (Final Verification)

### Coverage Verification
```bash
# Run all tests
./tests/libsqlglot_tests

# Expected: 1000+ tests, 100% pass rate

# Verify coverage by category
./tests/libsqlglot_tests "[universal]" # All pass
./tests/libsqlglot_tests "[procedures]" # All pass
./tests/libsqlglot_tests "[postgres]" # All pass
./tests/libsqlglot_tests "[mysql]" # All pass
./tests/libsqlglot_tests "[tsql]" # All pass
./tests/libsqlglot_tests "[oracle]" # All pass
./tests/libsqlglot_tests "[bigquery]" # All pass
```

### Security Verification
```bash
# Run security-specific tests
./tests/libsqlglot_tests "[security]" # All pass

# Manual security audit:
# - Backtick injection tests
# - Path traversal tests
# - SQL injection tests
# - Buffer overflow tests
# - Malformed input tests
```

### Performance Verification
```bash
# Run performance benchmarks
./tests/libsqlglot_tests "[performance]"

# Verify no regressions:
# - Parse time < 10ms for typical queries
# - Generate time < 5ms for typical queries
# - Memory usage < 100MB for typical workload
```

---

## Risk Mitigation

### Security Risks
1. **Backtick Identifiers**: Implemented first, security-reviewed
2. **File Paths**: Whitelist approach, strict validation
3. **Dynamic SQL**: Not implemented (too risky)

### Complexity Risks
1. **CONNECT BY**: Allocate 5 hours, allow for iteration
2. **Dialect Conversions**: Test exhaustively, verify semantics
3. **AST Transformations**: Code review required

### Schedule Risks
1. **Buffer**: 60h estimate + 20% = 72h total
2. **Parallel work**: Some sprints can overlap
3. **Incremental delivery**: Each sprint delivers value

---

## Next Immediate Actions

1. ✅ Review this plan (DONE - you're reading it!)
2. ⏭️ **START Sprint 1, Hour 1: Foreign Key Constraints**
3. Set up test tracking spreadsheet
4. Begin implementation

**Let's begin!**
