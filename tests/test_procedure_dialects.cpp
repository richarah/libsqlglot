#include <catch2/catch_test_macros.hpp>
#include <libsqlglot/transpiler.h>
#include <libsqlglot/dialects.h>

using namespace libsqlglot;

// Test to verify stored procedure dialect-awareness

TEST_CASE("Procedural constructs - Generic syntax parse and generate", "[procedures][dialects]") {
    std::string sql = "FOR i IN 1..10 LOOP RETURN i END LOOP";

    // Test that we can parse generic procedural syntax
    Arena arena;
    Parser parser(arena, sql);
    auto expr = parser.parse();

    REQUIRE(expr != nullptr);
    REQUIRE(expr->type == ExprType::FOR_LOOP);

    // Test that generation works (uses generic syntax)
    std::string generated = Generator::generate(expr);
    REQUIRE(generated == "FOR i IN 1..10 LOOP RETURN i END LOOP");
}

TEST_CASE("PL/pgSQL style - BEGIN END blocks (NOT IMPLEMENTED)", "[procedures][postgresql][!mayfail]") {
    // PL/pgSQL syntax: DECLARE ... BEGIN ... END
    std::string plpgsql = R"(
        DECLARE
            counter INTEGER := 0;
        BEGIN
            FOR i IN 1..10 LOOP
                counter := counter + i;
            END LOOP;
            RETURN counter;
        END;
    )";

    Arena arena;
    Parser parser(arena, plpgsql);

    // This will likely FAIL because parser doesn't handle BEGIN...END blocks
    auto expr = parser.parse();

    if (expr) {
        INFO("Parser accepted PL/pgSQL BEGIN...END block");
    } else {
        INFO("Parser does NOT handle PL/pgSQL BEGIN...END blocks");
    }

    // Document what we find
    REQUIRE(expr != nullptr);  // Expected to fail
}

TEST_CASE("T-SQL style - BEGIN END blocks (NOT IMPLEMENTED)", "[procedures][sqlserver][!mayfail]") {
    // T-SQL syntax
    std::string tsql = R"(
        BEGIN
            DECLARE @counter INT = 0
            WHILE @counter < 10
            BEGIN
                SET @counter = @counter + 1
            END
            RETURN @counter
        END
    )";

    Arena arena;
    Parser parser(arena, tsql);

    // This will likely FAIL because parser doesn't handle BEGIN...END blocks
    auto expr = parser.parse();

    if (expr) {
        INFO("Parser accepted T-SQL BEGIN...END block");
    } else {
        INFO("Parser does NOT handle T-SQL BEGIN...END blocks");
    }

    // Document what we find
    REQUIRE(expr != nullptr);  // Expected to fail
}

TEST_CASE("MySQL style - DELIMITER and BEGIN END (NOT IMPLEMENTED)", "[procedures][mysql][!mayfail]") {
    // MySQL procedure syntax
    std::string mysql_proc = R"(
        DELIMITER $$
        CREATE PROCEDURE test_proc()
        BEGIN
            DECLARE counter INT DEFAULT 0;
            WHILE counter < 10 DO
                SET counter = counter + 1;
            END WHILE;
        END$$
        DELIMITER ;
    )";

    Arena arena;
    Parser parser(arena, mysql_proc);

    auto expr = parser.parse();

    if (expr) {
        INFO("Parser accepted MySQL DELIMITER and procedure definition");
    } else {
        INFO("Parser does NOT handle MySQL DELIMITER or CREATE PROCEDURE");
    }

    // Document what we find
    REQUIRE(expr != nullptr);  // Expected to fail
}

TEST_CASE("What IS supported - Generic procedural constructs", "[procedures][supported]") {
    // What the parser DOES support (based on keywords.h and parser.h)

    SECTION("CALL statement") {
        std::string sql = "CALL my_procedure(1, 'test', NULL)";
        Arena arena;
        Parser parser(arena, sql);
        auto expr = parser.parse();
        REQUIRE(expr != nullptr);
        REQUIRE(expr->type == ExprType::CALL_PROCEDURE);
    }

    SECTION("RETURN statement") {
        std::string sql = "RETURN 42";
        Arena arena;
        Parser parser(arena, sql);
        auto expr = parser.parse();
        REQUIRE(expr != nullptr);
        REQUIRE(expr->type == ExprType::RETURN_STMT);
    }

    SECTION("DECLARE statement") {
        std::string sql = "DECLARE counter INTEGER";
        Arena arena;
        Parser parser(arena, sql);
        auto expr = parser.parse();
        REQUIRE(expr != nullptr);
        REQUIRE(expr->type == ExprType::DECLARE_VAR);
    }

    SECTION("IF statement") {
        std::string sql = "IF x > 10 THEN RETURN x END IF";
        Arena arena;
        Parser parser(arena, sql);
        auto expr = parser.parse();
        REQUIRE(expr != nullptr);
        REQUIRE(expr->type == ExprType::IF_STMT);
    }

    SECTION("WHILE loop") {
        std::string sql = "WHILE x > 0 DO RETURN x END WHILE";
        Arena arena;
        Parser parser(arena, sql);
        auto expr = parser.parse();
        REQUIRE(expr != nullptr);
        REQUIRE(expr->type == ExprType::WHILE_LOOP);
    }

    SECTION("FOR loop") {
        std::string sql = "FOR i IN 1..10 LOOP RETURN i END LOOP";
        Arena arena;
        Parser parser(arena, sql);
        auto expr = parser.parse();
        REQUIRE(expr != nullptr);
        REQUIRE(expr->type == ExprType::FOR_LOOP);
    }
}

TEST_CASE("Cross-dialect transpilation - NOT dialect-aware", "[procedures][transpilation]") {
    // Test if the generator produces dialect-specific syntax
    std::string generic_for_loop = "FOR i IN 1..10 LOOP RETURN i END LOOP";

    Arena arena;
    Parser parser(arena, generic_for_loop);
    auto expr = parser.parse();
    REQUIRE(expr != nullptr);

    // Generate for different dialects
    std::string ansi_output = Generator::generate(expr, Dialect::ANSI);
    std::string postgres_output = Generator::generate(expr, Dialect::PostgreSQL);
    std::string sqlserver_output = Generator::generate(expr, Dialect::SQLServer);
    std::string mysql_output = Generator::generate(expr, Dialect::MySQL);

    INFO("ANSI output: " << ansi_output);
    INFO("PostgreSQL output: " << postgres_output);
    INFO("SQL Server output: " << sqlserver_output);
    INFO("MySQL output: " << mysql_output);

    // All outputs should be IDENTICAL (not dialect-aware)
    REQUIRE(ansi_output == generic_for_loop);
    REQUIRE(postgres_output == generic_for_loop);
    REQUIRE(sqlserver_output == generic_for_loop);
    REQUIRE(mysql_output == generic_for_loop);

    INFO("RESULT: Generator outputs GENERIC syntax for all dialects - NOT dialect-aware");
}
