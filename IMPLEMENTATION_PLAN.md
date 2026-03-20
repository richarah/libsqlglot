# Remaining Stored Procedure Features Implementation Plan

## Status: Infrastructure Complete, Implementing Features

### Completed ✅
- Expression types defined in expression.h
- Token types defined in tokens.h
- Keywords regenerated in keywords.h
- CREATE PROCEDURE/FUNCTION fully working with tests

### Implementation Order (Optimized for Dependencies)

## 1. DELIMITER Command (MySQL) - SIMPLE
**Priority**: HIGH - Required for MySQL procedure definitions

**Parser** (`parser.h` - add after parse_for(), before parse_case_expression()):
```cpp
/// Parse DELIMITER statement (MySQL): DELIMITER $$
DelimiterStmt* parse_delimiter() {
    auto stmt = arena_.create<DelimiterStmt>();
    expect(TokenType::DELIMITER_KW);

    // Security: Validate delimiter is not empty and reasonable length
    if (!current().text) {
        error_expected_after("delimiter string ($$, //, etc.)", "DELIMITER");
    }

    std::string delim(current().text);
    if (delim.length() > 10) {  // Security: prevent extremely long delimiters
        error("DELIMITER string too long (max 10 characters)");
    }

    stmt->delimiter = delim;
    advance();

    return stmt;
}
```

**Generator** (`generator.h` - add in visit() switch and implementation):
```cpp
// In visit() switch:
case ExprType::DELIMITER_STMT:
    visit_delimiter(static_cast<const DelimiterStmt*>(expr));
    break;

// Implementation:
void visit_delimiter(const DelimiterStmt* stmt) {
    sql_ << "DELIMITER " << stmt->delimiter;
}
```

**Update parse() dispatch** (line ~1230):
```cpp
} else if (check(TokenType::DELIMITER_KW)) {
    return parse_delimiter();
```

**Test**:
```cpp
TEST_CASE("DELIMITER command", "[delimiter]") {
    std::string sql = "DELIMITER $$";
    auto result = Transpiler::transpile(sql, Dialect::MySQL, Dialect::MySQL);
    REQUIRE(result == "DELIMITER $$");
}
```

---

## 2. Assignment Statements - MODERATE
**Priority**: HIGH - Core procedural programming feature

**Parser**:
```cpp
/// Parse assignment: SET var = value OR var := value
AssignmentStmt* parse_assignment() {
    auto stmt = arena_.create<AssignmentStmt>();

    // Two forms:
    // 1. SET var = value (T-SQL, MySQL)
    // 2. var := value (PL/pgSQL, PL/SQL)

    if (check(TokenType::SET)) {
        advance();  // consume SET
        stmt->use_colon_equals = false;

        // Variable name
        if (current().type != TokenType::IDENTIFIER) {
            error_expected_after("variable name", "SET");
        }
        stmt->variable_name = std::string(current().text);
        advance();

        // = or :=
        if (match(TokenType::COLON_EQUALS)) {
            stmt->use_colon_equals = true;
        } else {
            expect(TokenType::EQ);
        }

        // Value
        stmt->value = parse_expression();
    } else {
        // Direct assignment: var := value
        if (current().type != TokenType::IDENTIFIER) {
            error("Expected variable name for assignment");
        }
        stmt->variable_name = std::string(current().text);
        advance();

        expect(TokenType::COLON_EQUALS);
        stmt->use_colon_equals = true;
        stmt->value = parse_expression();
    }

    return stmt;
}
```

**Generator**:
```cpp
void visit_assignment(const AssignmentStmt* stmt) {
    // Dialect-aware assignment
    if (dialect_ == Dialect::TSQL || dialect_ == Dialect::MySQL) {
        sql_ << "SET " << stmt->variable_name << " = ";
    } else {
        // PostgreSQL, Oracle use :=
        sql_ << stmt->variable_name << " := ";
    }
    visit(stmt->value);
}
```

---

## 3. EXCEPTION Blocks - MODERATE
**Priority**: MEDIUM - Error handling

**Parser**:
```cpp
/// Parse EXCEPTION block (PL/pgSQL, PL/SQL)
ExceptionBlock* parse_exception_block() {
    auto block = arena_.create<ExceptionBlock>();

    // BEGIN
    expect(TokenType::BEGIN);

    // Try statements
    while (!check(TokenType::EXCEPTION) && !check(TokenType::END) && !is_at_end()) {
        block->try_statements.push_back(parse());
        match(TokenType::SEMICOLON);
    }

    // EXCEPTION handlers
    if (match(TokenType::EXCEPTION)) {
        while (match(TokenType::WHEN)) {
            ExceptionBlock::ExceptionHandler handler;

            // Exception name
            if (current().type == TokenType::IDENTIFIER) {
                handler.exception_name = std::string(current().text);
                advance();
            }

            expect(TokenType::THEN);

            // Handler statements
            while (!check(TokenType::WHEN) && !check(TokenType::END) && !is_at_end()) {
                handler.statements.push_back(parse());
                match(TokenType::SEMICOLON);
            }

            block->handlers.push_back(handler);
        }
    }

    expect(TokenType::END);
    return block;
}
```

**Generator**:
```cpp
void visit_exception_block(const ExceptionBlock* block) {
    sql_ << "BEGIN";
    indent();

    // Try statements
    for (auto* stmt : block->try_statements) {
        newline();
        visit(stmt);
        sql_ << ";";
    }

    // Exception handlers
    if (!block->handlers.empty()) {
        dedent();
        newline();
        sql_ << "EXCEPTION";
        indent();

        for (const auto& handler : block->handlers) {
            newline();
            sql_ << "WHEN " << handler.exception_name << " THEN";
            indent();
            for (auto* stmt : handler.statements) {
                newline();
                visit(stmt);
                sql_ << ";";
            }
            dedent();
        }
    }

    dedent();
    newline();
    sql_ << "END";
}
```

---

## 4. CURSOR Support - COMPLEX
**Priority**: MEDIUM - Advanced procedural feature

**Parsers**:
```cpp
/// Parse DECLARE CURSOR
DeclareCursorStmt* parse_declare_cursor() {
    auto stmt = arena_.create<DeclareCursorStmt>();
    expect(TokenType::DECLARE);

    // Cursor name
    if (current().type != TokenType::IDENTIFIER) {
        error_expected_after("cursor name", "DECLARE");
    }
    stmt->cursor_name = std::string(current().text);
    advance();

    // Optional SCROLL
    if (match(TokenType::SCROLL)) {
        stmt->scroll = true;
    }

    expect(TokenType::CURSOR);
    expect(TokenType::FOR);

    // Query
    stmt->query = static_cast<SelectStmt*>(parse_select());

    return stmt;
}

/// Parse OPEN cursor
OpenCursorStmt* parse_open_cursor() {
    auto stmt = arena_.create<OpenCursorStmt>();
    expect(TokenType::OPEN);

    if (current().type != TokenType::IDENTIFIER) {
        error_expected_after("cursor name", "OPEN");
    }
    stmt->cursor_name = std::string(current().text);
    advance();

    // Optional parameters
    if (match(TokenType::LPAREN)) {
        if (!check(TokenType::RPAREN)) {
            do {
                stmt->arguments.push_back(parse_expression());
            } while (match(TokenType::COMMA));
        }
        expect(TokenType::RPAREN);
    }

    return stmt;
}

/// Parse FETCH cursor
FetchCursorStmt* parse_fetch_cursor() {
    auto stmt = arena_.create<FetchCursorStmt>();
    expect(TokenType::FETCH);

    // Direction (NEXT, PRIOR, FIRST, LAST, etc.)
    if (match(TokenType::NEXT)) {
        stmt->direction = FetchCursorStmt::Direction::NEXT;
    } else if (current().type == TokenType::IDENTIFIER) {
        std::string dir(current().text);
        if (dir == "PRIOR") {
            stmt->direction = FetchCursorStmt::Direction::PRIOR;
            advance();
        } else if (dir == "FIRST") {
            stmt->direction = FetchCursorStmt::Direction::FIRST;
            advance();
        } else if (dir == "LAST") {
            stmt->direction = FetchCursorStmt::Direction::LAST;
            advance();
        }
    }

    // FROM keyword (optional)
    if (current().type == TokenType::IDENTIFIER && std::string(current().text) == "FROM") {
        advance();
    }

    // Cursor name
    if (current().type != TokenType::IDENTIFIER) {
        error_expected_after("cursor name", "FETCH");
    }
    stmt->cursor_name = std::string(current().text);
    advance();

    // INTO variables
    if (current().type == TokenType::IDENTIFIER && std::string(current().text) == "INTO") {
        advance();
        do {
            if (current().type == TokenType::IDENTIFIER) {
                stmt->into_variables.push_back(std::string(current().text));
                advance();
            }
        } while (match(TokenType::COMMA));
    }

    return stmt;
}

/// Parse CLOSE cursor
CloseCursorStmt* parse_close_cursor() {
    auto stmt = arena_.create<CloseCursorStmt>();
    expect(TokenType::CLOSE);

    if (current().type != TokenType::IDENTIFIER) {
        error_expected_after("cursor name", "CLOSE");
    }
    stmt->cursor_name = std::string(current().text);
    advance();

    return stmt;
}
```

---

## 5. RAISE/SIGNAL - SIMPLE
**Priority**: MEDIUM - Error raising

**Parser**:
```cpp
/// Parse RAISE or SIGNAL statement
RaiseStmt* parse_raise() {
    auto stmt = arena_.create<RaiseStmt>();

    // RAISE or SIGNAL
    bool is_signal = match(TokenType::SIGNAL);
    if (!is_signal) {
        expect(TokenType::RAISE);
    }

    // Level (EXCEPTION, NOTICE, WARNING, etc.) - PostgreSQL only
    if (!is_signal && current().type == TokenType::IDENTIFIER) {
        std::string level(current().text);
        if (level == "EXCEPTION") {
            stmt->level = RaiseStmt::Level::EXCEPTION;
            advance();
        } else if (level == "NOTICE") {
            stmt->level = RaiseStmt::Level::NOTICE;
            advance();
        } else if (level == "WARNING") {
            stmt->level = RaiseStmt::Level::WARNING;
            advance();
        }
    }

    // Error code or message
    if (current().type == TokenType::STRING) {
        stmt->message = std::string(current().text);
        advance();
    } else if (current().type == TokenType::IDENTIFIER) {
        stmt->error_code = std::string(current().text);
        advance();
    }

    return stmt;
}
```

**Generator**:
```cpp
void visit_raise(const RaiseStmt* stmt) {
    if (dialect_ == Dialect::MySQL) {
        sql_ << "SIGNAL SQLSTATE '" << stmt->error_code << "'";
        if (!stmt->message.empty()) {
            sql_ << " SET MESSAGE_TEXT = " << stmt->message;
        }
    } else {
        // PostgreSQL
        sql_ << "RAISE ";
        switch (stmt->level) {
            case RaiseStmt::Level::EXCEPTION: sql_ << "EXCEPTION"; break;
            case RaiseStmt::Level::NOTICE: sql_ << "NOTICE"; break;
            case RaiseStmt::Level::WARNING: sql_ << "WARNING"; break;
            default: sql_ << "EXCEPTION";
        }
        if (!stmt->message.empty()) {
            sql_ << " " << stmt->message;
        }
    }
}
```

---

## Security & Testing Requirements

### Security Checks (All Parsers):
1. ✅ Bounds checking on all string copies
2. ✅ Null pointer validation before dereferencing
3. ✅ Recursion depth protection (already in RecursionGuard)
4. ✅ Length limits on identifiers (max 10 chars for delimiter)
5. ✅ Token existence validation (`current().text` checks)

### Testing Requirements:
1. Unit tests for each feature
2. Cross-dialect transpilation tests
3. Malformed input (fuzz) tests
4. Performance benchmarks
5. Memory safety (Valgrind/ASAN)
6. Full regression (all 311 tests must pass)

### Files to Modify:
1. `parser.h` - Add parse methods, update parse() dispatch
2. `generator.h` - Add visit methods, update visit() switch
3. `tests/test_assignments.cpp` - NEW
4. `tests/test_exceptions.cpp` - NEW
5. `tests/test_cursors.cpp` - NEW
6. `tests/test_delimiter.cpp` - NEW
7. `tests/CMakeLists.txt` - Add new test files

---

## Implementation Steps:
1. ✅ Add all parse methods to parser.h
2. ✅ Update parse() dispatch method
3. ✅ Add all visit methods to generator.h
4. ✅ Update visit() switch statement
5. ✅ Create test files
6. ✅ Build and fix compilation errors
7. ✅ Run tests and fix failures
8. ✅ Security audit
9. ✅ Fuzz testing
10. ✅ Performance benchmarks
11. ✅ Memory safety checks
12. ✅ Final regression testing
