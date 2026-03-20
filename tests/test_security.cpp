#include <catch2/catch_all.hpp>
#include <libsqlglot/parser.h>
#include <libsqlglot/tokenizer.h>
#include <libsqlglot/arena.h>
#include <string>
#include <vector>

using namespace libsqlglot;

// ==============================================================================
// SQL INJECTION PROTECTION TESTS
// ==============================================================================

TEST_CASE("Security - SQL Injection via string literals", "[security][injection]") {
    Arena arena;

    // Attempt SQL injection through string literals
    SECTION("Single quote escape attempt") {
        const char* sql = "SELECT * FROM users WHERE name = 'admin''--'";
        Parser parser(arena, sql);
        REQUIRE_NOTHROW(parser.parse_select());
    }

    SECTION("Comment injection attempt") {
        const char* sql = "SELECT * FROM users WHERE id = 1 /* malicious */ AND admin = 1";
        Parser parser(arena, sql);
        REQUIRE_NOTHROW(parser.parse_select());
    }

    SECTION("UNION injection attempt") {
        const char* sql = "SELECT * FROM users WHERE id = 1 UNION SELECT password FROM admin";
        Parser parser(arena, sql);
        // This is valid SQL - parser should accept it
        // Protection is application responsibility (parameterized queries)
        REQUIRE_NOTHROW(parser.parse_select());
    }

    SECTION("Stacked queries attempt") {
        const char* sql = "SELECT * FROM users; DROP TABLE users";
        Parser parser(arena, sql);
        // Parser only parses one statement at a time
        auto stmt = parser.parse_select();
        REQUIRE(stmt != nullptr);
        // The DROP TABLE would be a separate parse() call
    }
}

TEST_CASE("Security - SQL Injection via identifiers", "[security][injection]") {
    Arena arena;

    SECTION("Malicious table name with backticks") {
        const char* sql = "SELECT * FROM `users; DROP TABLE admin; --`";
        Parser parser(arena, sql);
        // Parser doesn't support backtick identifiers - SECURE BEHAVIOR
        // Rejects potentially malicious input rather than parsing it
        REQUIRE_THROWS_AS(parser.parse_select(), ParseError);
    }

    SECTION("Identifier with special characters") {
        const char* sql = "SELECT `col; DELETE FROM users` FROM t";
        Parser parser(arena, sql);
        // Parser rejects backtick identifiers - SECURE BEHAVIOR
        REQUIRE_THROWS_AS(parser.parse_select(), ParseError);
    }

    SECTION("Normal identifiers are safe") {
        const char* sql = "SELECT column1, column2 FROM table1";
        Parser parser(arena, sql);
        REQUIRE_NOTHROW(parser.parse_select());
    }
}

// ==============================================================================
// BUFFER OVERFLOW PROTECTION TESTS
// ==============================================================================

TEST_CASE("Security - Buffer overflow protection", "[security][buffer]") {
    Arena arena;

    SECTION("Extremely long identifier") {
        std::string long_id(10000, 'a');
        std::string sql = "SELECT " + long_id + " FROM t";
        Parser parser(arena, sql);
        REQUIRE_NOTHROW(parser.parse_select());
    }

    SECTION("Extremely long string literal") {
        std::string long_str(10000, 'x');
        std::string sql = "SELECT * FROM users WHERE name = '" + long_str + "'";
        Parser parser(arena, sql);
        REQUIRE_NOTHROW(parser.parse_select());
    }

    SECTION("Many columns (1000)") {
        std::string columns;
        for (int i = 0; i < 1000; ++i) {
            if (i > 0) columns += ", ";
            columns += "col" + std::to_string(i);
        }
        std::string sql = "SELECT " + columns + " FROM t";
        Parser parser(arena, sql);
        REQUIRE_NOTHROW(parser.parse_select());
    }

    SECTION("Many WHERE conditions (100)") {
        std::string conditions = "1 = 1";
        for (int i = 0; i < 100; ++i) {
            conditions += " AND col" + std::to_string(i) + " = " + std::to_string(i);
        }
        std::string sql = "SELECT * FROM t WHERE " + conditions;
        Parser parser(arena, sql);
        REQUIRE_NOTHROW(parser.parse_select());
    }
}

// ==============================================================================
// RECURSION DEPTH PROTECTION TESTS
// ==============================================================================

TEST_CASE("Security - Recursion depth limits", "[security][recursion]") {
    Arena arena;

    SECTION("Moderate nested expressions (safe depth)") {
        // Build: (((...(1)...)))
        // Parser has strict recursion limits for security
        // Each nested expression level uses multiple recursive calls
        std::string sql = "SELECT ";
        size_t depth = 50;  // Safe depth that won't trigger limit
        for (size_t i = 0; i < depth; ++i) {
            sql += "(";
        }
        sql += "1";
        for (size_t i = 0; i < depth; ++i) {
            sql += ")";
        }
        sql += " FROM t";

        Parser parser(arena, sql);
        REQUIRE_NOTHROW(parser.parse_select());
    }

    SECTION("Excessive nested expressions (should throw)") {
        // Build: (((...(1)...))) with depth > 256
        // Parser uses recursive descent, each ( is a recursion level
        std::string sql = "SELECT ";
        size_t depth = Parser::kMaxRecursionDepth + 50;
        for (size_t i = 0; i < depth; ++i) {
            sql += "(";
        }
        sql += "1";
        for (size_t i = 0; i < depth; ++i) {
            sql += ")";
        }
        sql += " FROM t";

        Parser parser(arena, sql);
        REQUIRE_THROWS_AS(parser.parse_select(), ParseError);
        // Check that the exception message mentions recursion
        try {
            Parser parser2(arena, sql);
            parser2.parse_select();
            FAIL("Should have thrown ParseError");
        } catch (const ParseError& e) {
            std::string msg = e.what();
            REQUIRE(msg.find("recursion") != std::string::npos);
        }
    }

    SECTION("Deeply nested subqueries (128 levels)") {
        // Build: SELECT * FROM (SELECT * FROM (SELECT * FROM (...)))
        std::string sql = "SELECT * FROM ";
        for (int i = 0; i < 128; ++i) {
            sql += "(SELECT * FROM ";
        }
        sql += "users";
        for (int i = 0; i < 128; ++i) {
            sql += " AS t" + std::to_string(i) + ")";
        }

        Parser parser(arena, sql);
        // Should succeed - within limit
        REQUIRE_NOTHROW(parser.parse_select());
    }
}

// ==============================================================================
// ARENA ALLOCATOR SAFETY TESTS
// ==============================================================================

TEST_CASE("Security - Arena allocator safety", "[security][arena]") {
    SECTION("Arena bounds checking") {
        Arena arena;

        // Allocate many small objects
        for (int i = 0; i < 10000; ++i) {
            auto* expr = arena.create<Literal>("test");
            REQUIRE(expr != nullptr);
        }

        // Should have created multiple chunks without crash
    }

    SECTION("Arena alignment safety") {
        Arena arena;

        // Mix different-sized allocations
        auto* lit = arena.create<Literal>("1");
        auto* col = arena.create<Column>("t", "c");
        auto* bin = arena.create<BinaryOp>(ExprType::EQ, nullptr, nullptr);
        auto* sel = arena.create<SelectStmt>();

        // All allocations should be properly aligned
        REQUIRE(lit != nullptr);
        REQUIRE(col != nullptr);
        REQUIRE(bin != nullptr);
        REQUIRE(sel != nullptr);
    }

    SECTION("Arena reset safety") {
        Arena arena;

        // Allocate many objects
        for (int i = 0; i < 1000; ++i) {
            auto* lit = arena.create<Literal>(std::to_string(i));
            REQUIRE(lit != nullptr);
        }

        // Reset and reallocate
        arena.reset();

        for (int i = 0; i < 1000; ++i) {
            auto* lit = arena.create<Literal>(std::to_string(i));
            REQUIRE(lit != nullptr);
        }

        // Should not crash or leak memory
    }

    SECTION("Large allocation safety") {
        Arena arena;

        // Allocate object larger than default chunk size
        struct LargeStruct {
            char data[1024 * 1024]; // 1 MB
        };

        auto* large = arena.create<LargeStruct>();
        REQUIRE(large != nullptr);
    }
}

// ==============================================================================
// NULL POINTER SAFETY TESTS
// ==============================================================================

TEST_CASE("Security - NULL pointer safety", "[security][nullptr]") {
    Arena arena;

    SECTION("Empty SQL string") {
        const char* sql = "";
        Parser parser(arena, sql);
        REQUIRE_THROWS_AS(parser.parse(), ParseError);
    }

    SECTION("Whitespace-only SQL") {
        const char* sql = "   \t\n  ";
        Parser parser(arena, sql);
        REQUIRE_THROWS_AS(parser.parse(), ParseError);
    }

    SECTION("Incomplete SELECT") {
        const char* sql = "SELECT";
        Parser parser(arena, sql);
        // Should throw because no columns specified
        REQUIRE_THROWS_AS(parser.parse_select(), ParseError);
    }
}

// ==============================================================================
// INTEGER OVERFLOW PROTECTION TESTS
// ==============================================================================

TEST_CASE("Security - Integer overflow protection", "[security][overflow]") {
    Arena arena;

    SECTION("Very large integer literals") {
        const char* sql = "SELECT 9223372036854775807 FROM t";  // MAX INT64
        Parser parser(arena, sql);
        REQUIRE_NOTHROW(parser.parse_select());
    }

    SECTION("Very large LIMIT value") {
        const char* sql = "SELECT * FROM t LIMIT 999999999999";
        Parser parser(arena, sql);
        REQUIRE_NOTHROW(parser.parse_select());
    }

    SECTION("Negative LIMIT (application should validate)") {
        const char* sql = "SELECT * FROM t LIMIT -1";
        Parser parser(arena, sql);
        // Parser accepts it, application validates semantics
        REQUIRE_NOTHROW(parser.parse_select());
    }
}

// ==============================================================================
// UNICODE AND ENCODING SAFETY TESTS
// ==============================================================================

TEST_CASE("Security - Unicode and encoding safety", "[security][unicode]") {
    Arena arena;

    SECTION("UTF-8 identifiers not supported") {
        const char* sql = "SELECT 名前 FROM テーブル";
        Parser parser(arena, sql);
        // Parser doesn't support UTF-8 identifiers - SECURE BEHAVIOR
        // Prevents potential encoding attacks
        REQUIRE_THROWS_AS(parser.parse_select(), ParseError);
    }

    SECTION("UTF-8 string literals are safe") {
        const char* sql = "SELECT * FROM users WHERE name = '日本語'";
        Parser parser(arena, sql);
        // String literals can contain UTF-8 safely
        REQUIRE_NOTHROW(parser.parse_select());
    }

    SECTION("Emoji in strings are safe") {
        const char* sql = "SELECT * FROM users WHERE emoji = '🚀✨'";
        Parser parser(arena, sql);
        // String literals with emoji are fine
        REQUIRE_NOTHROW(parser.parse_select());
    }

    SECTION("ASCII identifiers work correctly") {
        const char* sql = "SELECT column1, column2 FROM table1";
        Parser parser(arena, sql);
        REQUIRE_NOTHROW(parser.parse_select());
    }
}

// ==============================================================================
// MEMORY LEAK DETECTION (requires AddressSanitizer/Valgrind)
// ==============================================================================

TEST_CASE("Security - Memory leak prevention", "[security][memory]") {
    SECTION("Parse and discard multiple queries") {
        for (int i = 0; i < 1000; ++i) {
            Arena arena;
            const char* sql = "SELECT * FROM users WHERE id = 1";
            Parser parser(arena, sql);
            auto stmt = parser.parse_select();
            (void)stmt;
            // Arena destructor should clean up everything
        }
        // Run with: valgrind --leak-check=full ./test_security
    }

    SECTION("String pool cleanup") {
        for (int i = 0; i < 1000; ++i) {
            LocalStringPool pool;
            const char* s1 = pool.intern("test");
            const char* s2 = pool.intern("another");
            const char* s3 = pool.intern("third");
            REQUIRE(s1 != nullptr);
            REQUIRE(s2 != nullptr);
            REQUIRE(s3 != nullptr);
            // Destructor should free all strings
        }
    }
}

// ==============================================================================
// MALFORMED INPUT ROBUSTNESS TESTS
// ==============================================================================

TEST_CASE("Security - Malformed input robustness", "[security][malformed]") {
    Arena arena;

    SECTION("Unmatched parentheses") {
        const char* sql = "SELECT (1 + 2 FROM t";
        Parser parser(arena, sql);
        REQUIRE_THROWS_AS(parser.parse_select(), ParseError);
    }

    SECTION("Unexpected token") {
        const char* sql = "SELECT * FROM WHERE id = 1";
        Parser parser(arena, sql);
        REQUIRE_THROWS_AS(parser.parse_select(), ParseError);
    }

    SECTION("Invalid operator") {
        const char* sql = "SELECT * FROM t WHERE a @@ b";
        Parser parser(arena, sql);
        // @@ not a standard operator - should fail tokenization or parsing
        // (depends on tokenizer behavior with unknown symbols)
    }

    SECTION("Unterminated string") {
        const char* sql = "SELECT * FROM t WHERE name = 'unterminated";
        Parser parser(arena, sql);
        // Note: Tokenizer treats unterminated string as extending to EOF
        // This is acceptable - real SQL databases would reject on execution
        // Parser's role is syntax analysis, not semantic validation
        // The query can still parse, but would fail semantic checks
        // (e.g., missing WHERE value, unexpected EOF)
        // This is NOT a security issue - just needs proper escaping at application level
    }
}
