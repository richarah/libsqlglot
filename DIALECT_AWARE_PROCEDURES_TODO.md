# Dialect-Aware Stored Procedure Implementation TODO

## Status: IN PROGRESS
Implementation started to add full dialect-aware stored procedure support.

## Completed So Far:
✅ Added procedure-specific features to DialectFeatures:
   - supports_begin_end_blocks
   - supports_for_loops
   - variable_prefix (for @var in T-SQL)
   - assignment_style (WALRUS vs SET_KEYWORD vs EQUALS)

✅ Added BEGIN_END_BLOCK expression type to ExprType enum

✅ Added BeginEndBlock struct to expression.h

✅ Created test_procedure_dialects.cpp with tests showing:
   - Current generic syntax works
   - PL/pgSQL BEGIN...END not yet supported
   - T-SQL BEGIN...END not yet supported
   - MySQL DELIMITER not yet supported
   - Cross-dialect transpilation outputs same generic syntax

## Still TODO (in order):

### 1. Add Keywords (tokens.h / keywords.h)
- [ ] Check if BEGIN token exists (may conflict with BEGIN TRANSACTION)
- [ ] Add END token if missing
- [ ] Handle BEGIN...END vs BEGIN TRANSACTION disambiguation in parser

### 2. Configure Dialect Features (dialects.h initialize_features())
For each major dialect, set:

**PostgreSQL (PL/pgSQL):**
```cpp
postgres.supports_begin_end_blocks = true;
postgres.supports_for_loops = true;
postgres.variable_prefix = "";  // No prefix, but $ for params
postgres.assignment_style = DialectFeatures::AssignmentStyle::WALRUS;  // :=
```

**SQL Server (T-SQL):**
```cpp
sqlserver.supports_begin_end_blocks = true;
sqlserver.supports_for_loops = false;  // No FOR loops, use WHILE
sqlserver.variable_prefix = "@";
sqlserver.assignment_style = DialectFeatures::AssignmentStyle::SET_KEYWORD;  // SET
```

**MySQL:**
```cpp
mysql.supports_begin_end_blocks = true;
mysql.supports_for_loops = true;  // LOOP...END LOOP
mysql.variable_prefix = "";
mysql.assignment_style = DialectFeatures::AssignmentStyle::SET_KEYWORD;  // SET
```

**Oracle (PL/SQL):**
```cpp
oracle.supports_begin_end_blocks = true;
oracle.supports_for_loops = true;
oracle.variable_prefix = "";
oracle.assignment_style = DialectFeatures::AssignmentStyle::WALRUS;  // :=
```

### 3. Parser Extensions (parser.h)
Add method: `Expression* parse_begin_end_block()`

```cpp
Expression* parse_begin_end_block() {
    expect(TokenType::BEGIN);

    auto* block = arena_.create<BeginEndBlock>();

    // Parse statements until END
    while (!check(TokenType::END) && !is_at_end()) {
        auto* stmt = parse_statement();
        if (stmt) {
            block->statements.push_back(stmt);
        }

        // Handle optional statement terminators (;)
        match(TokenType::SEMICOLON);
    }

    expect(TokenType::END);
    return block;
}
```

Add to `parse_statement()`:
```cpp
} else if (check(TokenType::BEGIN)) {
    return parse_begin_end_block();
```

### 4. Generator Extensions (generator.h)
Add method: `void visit_begin_end_block(const BeginEndBlock* block)`

```cpp
void visit_begin_end_block(const BeginEndBlock* block) {
    const auto& features = DialectConfig::get_features(dialect_);

    if (!features.supports_begin_end_blocks) {
        // For dialects without BEGIN...END, just output statements
        for (size_t i = 0; i < block->statements.size(); ++i) {
            if (i > 0) sql_ << " ";
            visit(block->statements[i]);
        }
        return;
    }

    sql_ << "BEGIN";

    for (auto* stmt : block->statements) {
        sql_ << " ";
        visit(stmt);
    }

    sql_ << " END";
}
```

Add to `visit()` switch:
```cpp
case ExprType::BEGIN_END_BLOCK:
    visit_begin_end_block(static_cast<const BeginEndBlock*>(expr));
    break;
```

### 5. FOR Loop → WHILE Transpilation for T-SQL
Modify `visit_for_loop()`:

```cpp
void visit_for_loop(const ForLoop* loop) {
    const auto& features = DialectConfig::get_features(dialect_);

    if (!features.supports_for_loops && dialect_ == Dialect::SQLServer) {
        // Transpile FOR loop to WHILE for T-SQL
        sql_ << "DECLARE @" << loop->variable << " INT = ";
        visit(loop->start_value);
        sql_ << " ";

        sql_ << "WHILE @" << loop->variable << " <= ";
        visit(loop->end_value);
        sql_ << " BEGIN ";

        for (auto* stmt : loop->body) {
            visit(stmt);
            sql_ << " ";
        }

        sql_ << "SET @" << loop->variable << " = @" << loop->variable << " + 1 ";
        sql_ << "END";
        return;
    }

    // Default: generic FOR loop syntax
    sql_ << "FOR " << loop->variable << " IN ";
    visit(loop->start_value);
    sql_ << "..";
    visit(loop->end_value);
    sql_ << " LOOP";

    for (auto* stmt : loop->body) {
        sql_ << " ";
        visit(stmt);
    }

    sql_ << " END LOOP";
}
```

### 6. Variable Prefix Support
Modify `visit_column()` or add variable reference handling:

```cpp
void visit_variable(const std::string& var_name) {
    const auto& features = DialectConfig::get_features(dialect_);
    sql_ << features.variable_prefix << var_name;
}
```

### 7. Comprehensive Tests
Add to test_procedure_dialects.cpp:

**Test BEGIN...END parsing:**
```cpp
TEST_CASE("T-SQL style BEGIN...END", "[procedures][tsql]") {
    std::string tsql = "BEGIN DECLARE @x INT RETURN @x END";

    Arena arena;
    Parser parser(arena, tsql);
    auto expr = parser.parse();

    REQUIRE(expr != nullptr);
    REQUIRE(expr->type == ExprType::BEGIN_END_BLOCK);

    // Generate for T-SQL
    std::string output = Generator::generate(expr, Dialect::SQLServer);
    REQUIRE(output.find("BEGIN") != std::string::npos);
    REQUIRE(output.find("END") != std::string::npos);
}
```

**Test FOR → WHILE transpilation:**
```cpp
TEST_CASE("FOR loop transpiled to WHILE for T-SQL", "[procedures][transpilation]") {
    std::string generic_for = "FOR i IN 1..10 LOOP RETURN i END LOOP";

    Arena arena;
    Parser parser(arena, generic_for);
    auto expr = parser.parse();

    // Generate for T-SQL should convert to WHILE
    std::string tsql_output = Generator::generate(expr, Dialect::SQLServer);

    REQUIRE(tsql_output.find("WHILE") != std::string::npos);
    REQUIRE(tsql_output.find("@i") != std::string::npos);
    REQUIRE(tsql_output.find("FOR") == std::string::npos);
}
```

**Test variable prefixes:**
```cpp
TEST_CASE("Variable prefixes dialect-aware", "[procedures][variables]") {
    // Test that T-SQL uses @variable
    // Test that PostgreSQL uses plain variable names
    // Test that Oracle uses plain variable names
}
```

### 8. Integration Testing
- [ ] Verify all 288 existing tests still pass
- [ ] Add PL/pgSQL specific tests
- [ ] Add T-SQL specific tests
- [ ] Add MySQL specific tests
- [ ] Add Oracle specific tests
- [ ] Test cross-dialect transpilation

### 9. Documentation
Once working, the README claim "Full support (PL/pgSQL, T-SQL, MySQL, PL/SQL)" will be TRUE:
- ✅ Can parse dialect-specific syntax
- ✅ Can generate dialect-specific output
- ✅ Can transpile between dialects
- ✅ Handles BEGIN...END blocks
- ✅ Handles FOR loops (or transpiles to WHILE)
- ✅ Handles variable prefixes
- ✅ Handles assignment styles

## Estimated Remaining Work:
- Keywords: 30 minutes
- Configure dialects: 1 hour
- Parser extensions: 2 hours
- Generator extensions: 3 hours
- FOR→WHILE transpilation: 1 hour
- Variable prefix support: 1 hour
- Comprehensive tests: 2 hours
- Integration testing: 1 hour
- Bug fixes: 2 hours

**Total: ~13-15 hours of focused development**

## Notes:
- BEGIN keyword may conflict with BEGIN TRANSACTION - need careful disambiguation
- Variable prefix handling needs to distinguish between variable references and column references
- Cross-dialect transpilation is complex - may need multiple iterations
- PL/pgSQL has additional features ($$, LANGUAGE clause) that are out of scope for initial implementation

## Files Modified So Far:
- include/libsqlglot/dialects.h (added procedure features)
- include/libsqlglot/expression.h (added BEGIN_END_BLOCK type and struct)
- tests/CMakeLists.txt (added test_procedure_dialects.cpp)
- tests/test_procedure_dialects.cpp (NEW - comprehensive dialect tests)
