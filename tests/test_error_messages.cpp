/**
 * Test suite for improved error messages
 *
 * Verifies that ParseError includes:
 * - Line number
 * - Column number
 * - Context (the token that caused the error)
 * - Clear, human-readable messages
 */

#include <catch2/catch_test_macros.hpp>
#include "../include/libsqlglot/parser.h"
#include "../include/libsqlglot/arena.h"
#include <string>
#include <iostream>
#include <algorithm>

using namespace libsqlglot;

TEST_CASE("Error messages include line and column numbers", "[error][messages]") {
    Arena arena;

    SECTION("Missing column list in SELECT") {
        Parser parser(arena, "SELECT FROM users");
        try {
            parser.parse();
            FAIL("Should have thrown ParseError");
        } catch (const ParseError& e) {
            REQUIRE(e.line == 1);
            REQUIRE(e.column == 8);
            std::string msg(e.what());
            REQUIRE(msg.find("Line 1") != std::string::npos);
            REQUIRE(msg.find("column 8") != std::string::npos);
            REQUIRE(msg.find("FROM") != std::string::npos);
        }
    }

    SECTION("Missing table name after CREATE TABLE") {
        Parser parser(arena, "CREATE TABLE (id INT)");
        try {
            parser.parse();
            FAIL("Should have thrown ParseError");
        } catch (const ParseError& e) {
            REQUIRE(e.line == 1);
            REQUIRE(e.column == 14);
            std::string msg(e.what());
            REQUIRE(msg.find("table name") != std::string::npos);
            REQUIRE(msg.find("CREATE TABLE") != std::string::npos);
        }
    }

    SECTION("Invalid token in WHERE clause") {
        Parser parser(arena, "SELECT * FROM users WHERE");
        try {
            parser.parse();
            FAIL("Should have thrown ParseError");
        } catch (const ParseError& e) {
            REQUIRE(e.line == 1);
            // Error occurs at end of WHERE
            std::string msg(e.what());
            REQUIRE(msg.find("Line 1") != std::string::npos);
            REQUIRE(msg.find("column") != std::string::npos);
        }
    }

    SECTION("Invalid syntax in expression") {
        Parser parser(arena, "SELECT * FROM users WHERE");
        try {
            parser.parse();
            FAIL("Should have thrown ParseError");
        } catch (const ParseError& e) {
            REQUIRE(e.line == 1);
            std::string msg(e.what());
            REQUIRE(msg.find("Line 1") != std::string::npos);
            REQUIRE(msg.find("column") != std::string::npos);
        }
    }
}

TEST_CASE("Error messages include context token", "[error][messages]") {
    Arena arena;

    SECTION("Context shows unexpected token") {
        Parser parser(arena, "SELECT FROM users");
        try {
            parser.parse();
            FAIL("Should have thrown ParseError");
        } catch (const ParseError& e) {
            REQUIRE(!e.context.empty());
            REQUIRE(e.context == "FROM");
        }
    }

    SECTION("Context captured for invalid syntax") {
        Parser parser(arena, "SELECT * FROM UNION");
        try {
            parser.parse();
            FAIL("Should have thrown ParseError");
        } catch (const ParseError& e) {
            std::string msg(e.what());
            REQUIRE(!e.context.empty());
            REQUIRE(e.context == "UNION");
        }
    }
}

TEST_CASE("Error messages are human-readable", "[error][messages]") {
    Arena arena;

    SECTION("Clear message for missing table name") {
        Parser parser(arena, "CREATE TABLE");
        try {
            parser.parse();
            FAIL("Should have thrown ParseError");
        } catch (const ParseError& e) {
            std::string msg(e.what());
            // Should mention what was expected
            REQUIRE(msg.find("table name") != std::string::npos);
            // Should mention the context (what statement we're in)
            REQUIRE(msg.find("CREATE TABLE") != std::string::npos);
        }
    }

    SECTION("Clear message for unexpected token") {
        Parser parser(arena, "SELECT * FROM UNION");
        try {
            parser.parse();
            FAIL("Should have thrown ParseError");
        } catch (const ParseError& e) {
            std::string msg(e.what());
            REQUIRE(msg.find("Expected") != std::string::npos);
            REQUIRE(msg.find("UNION") != std::string::npos);
        }
    }

    SECTION("Missing keyword error is clear") {
        Parser parser(arena, "INSERT INTO users VALUES");
        try {
            parser.parse();
            FAIL("Should have thrown ParseError");
        } catch (const ParseError& e) {
            std::string msg(e.what());
            // Should mention what was expected
            REQUIRE(msg.find("Expected") != std::string::npos);
            // Should have line/column info
            REQUIRE(e.line == 1);
        }
    }
}

TEST_CASE("Error messages for multiline SQL", "[error][messages]") {
    Arena arena;

    SECTION("Error on second line") {
        std::string sql = "SELECT *\nFROM\nWHERE age > 18";
        Parser parser(arena, sql);
        try {
            parser.parse();
            FAIL("Should have thrown ParseError");
        } catch (const ParseError& e) {
            REQUIRE(e.line == 3);
            std::string msg(e.what());
            REQUIRE(msg.find("Line 3") != std::string::npos);
        }
    }

    SECTION("Error on third line") {
        std::string sql = "SELECT id, name\nFROM users\nWHERE";
        Parser parser(arena, sql);
        try {
            parser.parse();
            FAIL("Should have thrown ParseError");
        } catch (const ParseError& e) {
            REQUIRE(e.line == 3);
            std::string msg(e.what());
            REQUIRE(msg.find("Line 3") != std::string::npos);
        }
    }
}

TEST_CASE("Error messages demonstrate fail-fast behavior", "[error][messages]") {
    Arena arena;

    SECTION("First error stops parsing") {
        // Multiple errors in SQL - should only report first one
        Parser parser(arena, "SELECT FROM WHERE");
        try {
            parser.parse();
            FAIL("Should have thrown ParseError");
        } catch (const ParseError& e) {
            // Should get first error only (fail-fast)
            REQUIRE(e.line == 1);
            REQUIRE(e.column == 8);
            std::string msg(e.what());
            // First error: missing column list after SELECT
            REQUIRE(msg.find("Line 1") != std::string::npos);
        }
    }

    SECTION("No error recovery - precise single error") {
        Parser parser(arena, "SELECT * FROM");  // Missing table name
        try {
            parser.parse();
            FAIL("Should have thrown ParseError");
        } catch (const ParseError& e) {
            std::string msg(e.what());
            // Should report the precise location of the error
            REQUIRE(e.line == 1);
            REQUIRE(msg.find("table") != std::string::npos);
        }
    }
}

TEST_CASE("Error message edge cases", "[error][messages][edge_cases]") {
    Arena arena;

    SECTION("Empty SQL input") {
        Parser parser(arena, "");
        try {
            parser.parse();
            FAIL("Should have thrown ParseError for empty input");
        } catch (const ParseError& e) {
            std::string msg(e.what());
            REQUIRE(e.line == 1);
            // Should get a clear error
            REQUIRE(!msg.empty());
        }
    }

    SECTION("Only whitespace") {
        Parser parser(arena, "   \n\n  \t  ");
        try {
            parser.parse();
            FAIL("Should have thrown ParseError for whitespace-only input");
        } catch (const ParseError& e) {
            std::string msg(e.what());
            // Should report appropriate line
            REQUIRE(e.line >= 1);
        }
    }

    SECTION("Error at end of file") {
        Parser parser(arena, "SELECT * FROM users WHERE age >");
        try {
            parser.parse();
            FAIL("Should have thrown ParseError");
        } catch (const ParseError& e) {
            std::string msg(e.what());
            REQUIRE(e.line == 1);
            // Should indicate unexpected EOF or missing value
            REQUIRE(msg.find("column") != std::string::npos);
        }
    }

    SECTION("Very long line with error at end") {
        std::string sql = "SELECT ";
        for (int i = 0; i < 100; ++i) {
            sql += "col" + std::to_string(i) + ", ";
        }
        sql += "FROM users";  // Error: trailing comma before FROM

        Parser parser(arena, sql);
        try {
            parser.parse();
            FAIL("Should have thrown ParseError");
        } catch (const ParseError& e) {
            std::string msg(e.what());
            REQUIRE(e.line == 1);
            // Column number should be accurate even for long lines
            REQUIRE(e.column > 100);
            REQUIRE(msg.find("FROM") != std::string::npos);
        }
    }

    SECTION("Multiple errors - fail fast on first") {
        Parser parser(arena, "SELECT FROM WHERE GROUP BY");
        try {
            parser.parse();
            FAIL("Should have thrown ParseError");
        } catch (const ParseError& e) {
            // Should only report first error (missing column list)
            REQUIRE(e.line == 1);
            REQUIRE(e.column == 8);  // Position of FROM token
            std::string msg(e.what());
            REQUIRE(msg.find("FROM") != std::string::npos);
        }
    }

    SECTION("Nested subquery error") {
        Parser parser(arena, "SELECT * FROM (SELECT FROM inner_table) t");
        try {
            parser.parse();
            FAIL("Should have thrown ParseError");
        } catch (const ParseError& e) {
            std::string msg(e.what());
            REQUIRE(e.line == 1);
            // Error should be in the subquery
            REQUIRE(e.column > 15);  // After opening parenthesis
            REQUIRE(msg.find("FROM") != std::string::npos);
        }
    }

    SECTION("Error in CTE") {
        Parser parser(arena, "WITH cte AS (SELECT FROM users) SELECT * FROM cte");
        try {
            parser.parse();
            FAIL("Should have thrown ParseError");
        } catch (const ParseError& e) {
            std::string msg(e.what());
            REQUIRE(e.line == 1);
            // Error should be inside CTE definition
            REQUIRE(e.column > 13);  // After CTE opening
        }
    }

    SECTION("Multiline error with tabs") {
        std::string sql = "SELECT\n\t\tid,\n\t\tname\n\t\tFROM";
        Parser parser(arena, sql);
        try {
            parser.parse();
            FAIL("Should have thrown ParseError");
        } catch (const ParseError& e) {
            std::string msg(e.what());
            // Error on line 4 (the FROM line)
            REQUIRE(e.line == 4);
        }
    }

    SECTION("Missing closing parenthesis") {
        Parser parser(arena, "SELECT * FROM (SELECT * FROM users");
        try {
            parser.parse();
            FAIL("Should have thrown ParseError");
        } catch (const ParseError& e) {
            std::string msg(e.what());
            REQUIRE(e.line == 1);
            // Should mention missing closing paren or EOF
            REQUIRE(msg.find("Expected") != std::string::npos);
        }
    }

    SECTION("Invalid operator sequence") {
        Parser parser(arena, "SELECT * FROM users WHERE age > > 18");
        try {
            parser.parse();
            FAIL("Should have thrown ParseError");
        } catch (const ParseError& e) {
            std::string msg(e.what());
            REQUIRE(e.line == 1);
            // Error at second '>'
            REQUIRE(e.column > 30);
        }
    }

    SECTION("Reserved keyword as identifier without quotes") {
        Parser parser(arena, "SELECT select FROM users");
        try {
            parser.parse();
            FAIL("Should have thrown ParseError");
        } catch (const ParseError& e) {
            std::string msg(e.what());
            REQUIRE(e.line == 1);
            // Should error on the duplicate SELECT keyword (keywords are lowercase in context)
            std::string ctx = e.context;
            std::transform(ctx.begin(), ctx.end(), ctx.begin(), ::tolower);
            REQUIRE(ctx == "select");
        }
    }
}

TEST_CASE("Error message format examples", "[error][messages][examples]") {
    Arena arena;

    SECTION("Example 1: Missing column list") {
        Parser parser(arena, "SELECT FROM users");
        try {
            parser.parse();
            FAIL("Should have thrown");
        } catch (const ParseError& e) {
            // Example output: Line 1, column 8: Expected column list after SELECT (found: 'FROM')
            std::string msg(e.what());
            std::cout << "Example error 1: " << msg << "\n";
            REQUIRE(msg.find("Line 1, column 8") != std::string::npos);
        }
    }

    SECTION("Example 2: Missing table name in CREATE") {
        Parser parser(arena, "CREATE TABLE (id INT)");
        try {
            parser.parse();
            FAIL("Should have thrown");
        } catch (const ParseError& e) {
            // Example output: Line 1, column 14: Expected table name after CREATE TABLE (found: '(')
            std::string msg(e.what());
            std::cout << "Example error 2: " << msg << "\n";
            REQUIRE(msg.find("table name after CREATE TABLE") != std::string::npos);
        }
    }

    SECTION("Example 3: Multiline error") {
        std::string sql = "SELECT id,\n       name\nFROM";
        Parser parser(arena, sql);
        try {
            parser.parse();
            FAIL("Should have thrown");
        } catch (const ParseError& e) {
            // Example output: Line 3, column 1: Expected table name (found: '<EOF>')
            std::string msg(e.what());
            std::cout << "Example error 3: " << msg << "\n";
            REQUIRE(msg.find("Line 3") != std::string::npos);
        }
    }
}
