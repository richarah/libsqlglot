# Complete Implementation Plan - Based on SUPPORTED_FEATURES.md
## Goal: Implement ALL missing features marked with ❌

---

## Priority 1: Complete Universal SQL (Sprint 1 Remainder)

### 1.1 RETURNS Clause for Functions ⏰ 30 min
**Status**: Partially implemented
**Gap**: RETURNS TABLE(...), RETURNS SETOF need parsing

**Implementation**:
```sql
-- Need to support:
CREATE FUNCTION get_users() RETURNS TABLE(id INT, name VARCHAR)
CREATE FUNCTION get_ids() RETURNS SETOF INT
```

**Files to modify**:
- `parser.h`: Extend `parse_create_procedure()` to handle TABLE and SETOF return types
- `expression.h`: Add fields to store complex return types

**Tests**: 5 test cases (already written in test_returns_comprehensive.cpp)

### 1.2 Variable Assignment `:=` in DECLARE ⏰ 15 min
**Status**: Assignment works, but DECLARE x INT := value might not
**Gap**: Need to ensure `:=` works in DECLARE context

**Implementation**:
```sql
DECLARE i INT := 0;  -- Needs to work
```

**Files to modify**:
- `parser.h`: Check `parse_declare()` handles := correctly

**Tests**: 2 test cases (already written)

---

## Priority 2: Security-Critical Features (Sprint 2)

### 2.1 Backtick Identifiers - MySQL/BigQuery ⏰ 90 min 🔒 SECURITY
**Status**: Not implemented
**Risk**: SQL injection if not done carefully

**Implementation**:
```sql
SELECT `column name` FROM `table`
SELECT * FROM `project.dataset.table`
```

**Security Requirements**:
- Max 64 chars (MySQL limit)
- No nested backticks
- ASCII only
- No escape sequences
- Proper validation

**Files to modify**:
- `tokenizer.h`: Add backtick handling in `tokenize_identifier()`
- Add security validation

**Tests**: 15 tests (10 functional, 5 security)

### 2.2 LOAD DATA INFILE - MySQL ⏰ 90 min 🔒 SECURITY
**Status**: Not implemented
**Risk**: Path traversal, arbitrary file read

**Implementation**:
```sql
LOAD DATA LOCAL INFILE 'file.csv' INTO TABLE t
FIELDS TERMINATED BY ',' LINES TERMINATED BY '\n'
```

**Security Requirements**:
- Whitelist directories only
- No ../ paths
- Filename validation
- Length limits

**Files to modify**:
- `parser.h`: Add `parse_load_data()`
- `expression.h`: Add LoadDataStmt

**Tests**: 6 tests (3 functional, 3 security)

---

## Priority 3: High-Value Dialect Features (Sprint 3)

### 3.1 LATERAL JOIN - PostgreSQL ⏰ 60 min
**Status**: Keyword exists, not parsed

**Implementation**:
```sql
FROM table1
LATERAL JOIN (SELECT ... WHERE table1.id = ...) t2
```

**Files to modify**:
- `parser.h`: Check for LATERAL before JOIN in `parse_from_clause()`

**Tests**: 4 tests

### 3.2 ON CONFLICT (Upsert) - PostgreSQL ⏰ 90 min
**Status**: Not implemented

**Implementation**:
```sql
INSERT INTO table (...) VALUES (...)
ON CONFLICT (id) DO UPDATE SET col = EXCLUDED.col
ON CONFLICT DO NOTHING
```

**Files to modify**:
- `parser.h`: After INSERT VALUES, check for ON CONFLICT
- `expression.h`: Add EXCLUDED keyword support

**Tests**: 6 tests

### 3.3 QUALIFY Clause - BigQuery/Snowflake ⏰ 90 min
**Status**: Keyword exists, not parsed

**Implementation**:
```sql
SELECT col, ROW_NUMBER() OVER (...) as rn
FROM table
QUALIFY rn = 1
```

**Files to modify**:
- `parser.h`: After HAVING/ORDER BY, check for QUALIFY

**Tests**: 5 tests

### 3.4 TOP Clause - T-SQL ⏰ 60 min
**Status**: Keyword exists, not parsed

**Implementation**:
```sql
SELECT TOP 10 * FROM table
SELECT TOP 10 PERCENT * FROM table
SELECT TOP 10 WITH TIES * FROM table ORDER BY col
```

**Files to modify**:
- `parser.h`: After SELECT, check for TOP

**Tests**: 6 tests

### 3.5 OUTPUT Clause - T-SQL ⏰ 90 min
**Status**: Keyword exists, not parsed

**Implementation**:
```sql
INSERT INTO table OUTPUT INSERTED.* VALUES (...)
DELETE FROM table OUTPUT DELETED.* WHERE ...
UPDATE table SET ... OUTPUT INSERTED.*, DELETED.*
```

**Files to modify**:
- `parser.h`: After DML verb, check for OUTPUT

**Tests**: 6 tests

---

## Priority 4: Complex Features (Sprint 4)

### 4.1 CONNECT BY - Oracle ⏰ 5 hours 🔥 COMPLEX
**Status**: Keywords exist, not parsed

**Implementation**:
```sql
SELECT employee, manager
FROM employees
START WITH manager IS NULL
CONNECT BY PRIOR employee = manager
```

**Complexity**: Requires AST transformation to recursive CTE

**Files to modify**:
- `parser.h`: Parse START WITH, CONNECT BY PRIOR
- Add AST transformation logic

**Tests**: 10 tests

### 4.2 TRY...CATCH - T-SQL ⏰ 60 min
**Status**: Not implemented

**Implementation**:
```sql
BEGIN TRY
  ...
END TRY
BEGIN CATCH
  SELECT ERROR_MESSAGE()
END CATCH
```

**Files to modify**:
- `parser.h`: New statement type
- `expression.h`: TryCatchStmt

**Tests**: 4 tests

### 4.3 GROUP_CONCAT - MySQL ⏰ 60 min
**Status**: Not implemented

**Implementation**:
```sql
GROUP_CONCAT(expr SEPARATOR ',' ORDER BY expr)
```

**Files to modify**:
- `parser.h`: Special aggregate handling

**Tests**: 5 tests

---

## Priority 5: Remaining Features (Sprint 5)

### 5.1 FILTER in Aggregates - PostgreSQL ⏰ 30 min
```sql
COUNT(*) FILTER (WHERE condition)
```

### 5.2 TABLESAMPLE - PostgreSQL ⏰ 30 min
```sql
FROM table TABLESAMPLE BERNOULLI (10)
```

### 5.3 DO Blocks - PostgreSQL ⏰ 30 min
```sql
DO $$ BEGIN ... END $$
```

### 5.4 Array Slicing - PostgreSQL ⏰ 30 min
```sql
array[1:3]
```

### 5.5 ON DUPLICATE KEY UPDATE - MySQL ⏰ 60 min
```sql
INSERT INTO table (...) VALUES (...)
ON DUPLICATE KEY UPDATE col = VALUES(col)
```

### 5.6 INSERT IGNORE - MySQL ⏰ 15 min
```sql
INSERT IGNORE INTO table ...
```

### 5.7 REPLACE INTO - MySQL ⏰ 20 min
```sql
REPLACE INTO table ...
```

### 5.8 Index Hints - MySQL ⏰ 45 min
```sql
FROM table FORCE INDEX (idx) USE INDEX (idx) IGNORE INDEX (idx)
```

### 5.9 ROWNUM Usage - Oracle ⏰ 90 min
```sql
SELECT * FROM table WHERE ROWNUM <= 10
```

### 5.10 SAFE_CAST - BigQuery ⏰ 30 min
```sql
SAFE_CAST(expr AS type)
```

### 5.11 STRUCT Literals - BigQuery ⏰ 90 min
```sql
STRUCT(1 AS a, 'text' AS b, [1,2,3] AS c)
```

### 5.12 Array OFFSET/ORDINAL - BigQuery ⏰ 60 min
```sql
array[OFFSET(0)]  -- 0-based
array[ORDINAL(1)] -- 1-based
```

---

## Sprint Timeline

### Sprint 1 Completion: 45 minutes
- RETURNS TABLE/SETOF (30 min)
- DECLARE := validation (15 min)

### Sprint 2: Security - 3 hours
- Backtick identifiers (90 min)
- LOAD DATA INFILE (90 min)
- Security testing (60 min)

### Sprint 3: High-Value - 7 hours
- LATERAL JOIN (60 min)
- ON CONFLICT (90 min)
- QUALIFY (90 min)
- TOP (60 min)
- OUTPUT (90 min)
- Testing (90 min)

### Sprint 4: Complex - 8 hours
- CONNECT BY (300 min)
- TRY...CATCH (60 min)
- GROUP_CONCAT (60 min)
- Testing (60 min)

### Sprint 5: Remaining - 8 hours
- All remaining features (6 hours)
- Comprehensive testing (2 hours)

### Sprint 6: Long Tail Dialects - 8 hours
- Snowflake features
- DuckDB features
- ClickHouse features

### Sprint 7: Verification - 4 hours
- Full regression testing
- Performance benchmarks
- Documentation

**Total: ~38 hours to 100% coverage**

---

## Immediate Next Steps (RIGHT NOW)

1. ✅ Restore test_returns_comprehensive.cpp (don't remove tests!)
2. 🔄 Implement RETURNS TABLE/SETOF parsing (30 min)
3. 🔄 Fix DECLARE := in all contexts (15 min)
4. ✅ Run all tests and verify 100% pass
5. ✅ Mark Sprint 1 as COMPLETE

Then proceed to Sprint 2!
