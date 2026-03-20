#include <catch2/catch_test_macros.hpp>
#include <libsqlglot/transpiler.h>

using namespace libsqlglot;

TEST_CASE("String scalar functions", "[scalar][functions][string]") {
    SECTION("SUBSTRING function") {
        std::string sql = "SELECT SUBSTRING(name, 1, 10) FROM users";
        Arena arena;
        Parser parser(arena, sql);
        auto expr = parser.parse();

        REQUIRE(expr != nullptr);
        REQUIRE(expr->type == ExprType::SELECT_STMT);
    }

    SECTION("SUBSTR function") {
        std::string sql = "SELECT SUBSTR(name, 1, 10) FROM users";
        Arena arena;
        Parser parser(arena, sql);
        auto expr = parser.parse();

        REQUIRE(expr != nullptr);
    }

    SECTION("LENGTH function") {
        std::string sql = "SELECT LENGTH(name) FROM users";
        Arena arena;
        Parser parser(arena, sql);
        auto expr = parser.parse();

        REQUIRE(expr != nullptr);
    }

    SECTION("TRIM function") {
        std::string sql = "SELECT TRIM(name) FROM users";
        Arena arena;
        Parser parser(arena, sql);
        auto expr = parser.parse();

        REQUIRE(expr != nullptr);
    }

    SECTION("UPPER function") {
        std::string sql = "SELECT UPPER(name) FROM users";
        Arena arena;
        Parser parser(arena, sql);
        auto expr = parser.parse();

        REQUIRE(expr != nullptr);
    }

    SECTION("LOWER function") {
        std::string sql = "SELECT LOWER(name) FROM users";
        Arena arena;
        Parser parser(arena, sql);
        auto expr = parser.parse();

        REQUIRE(expr != nullptr);
    }

    SECTION("REPLACE function") {
        std::string sql = "SELECT REPLACE(name, 'old', 'new') FROM users";
        Arena arena;
        Parser parser(arena, sql);
        auto expr = parser.parse();

        REQUIRE(expr != nullptr);
    }

    SECTION("CONCAT function") {
        std::string sql = "SELECT CONCAT(first_name, ' ', last_name) FROM users";
        Arena arena;
        Parser parser(arena, sql);
        auto expr = parser.parse();

        REQUIRE(expr != nullptr);
    }
}

TEST_CASE("Math scalar functions", "[scalar][functions][math]") {
    SECTION("ROUND function") {
        std::string sql = "SELECT ROUND(price, 2) FROM products";
        Arena arena;
        Parser parser(arena, sql);
        auto expr = parser.parse();

        REQUIRE(expr != nullptr);
    }

    SECTION("FLOOR function") {
        std::string sql = "SELECT FLOOR(price) FROM products";
        Arena arena;
        Parser parser(arena, sql);
        auto expr = parser.parse();

        REQUIRE(expr != nullptr);
    }

    SECTION("CEIL function") {
        std::string sql = "SELECT CEIL(price) FROM products";
        Arena arena;
        Parser parser(arena, sql);
        auto expr = parser.parse();

        REQUIRE(expr != nullptr);
    }

    SECTION("ABS function") {
        std::string sql = "SELECT ABS(balance) FROM accounts";
        Arena arena;
        Parser parser(arena, sql);
        auto expr = parser.parse();

        REQUIRE(expr != nullptr);
    }

    SECTION("POWER function") {
        std::string sql = "SELECT POWER(2, 10) FROM dual";
        Arena arena;
        Parser parser(arena, sql);
        auto expr = parser.parse();

        REQUIRE(expr != nullptr);
    }

    SECTION("SQRT function") {
        std::string sql = "SELECT SQRT(area) FROM shapes";
        Arena arena;
        Parser parser(arena, sql);
        auto expr = parser.parse();

        REQUIRE(expr != nullptr);
    }
}

TEST_CASE("Nested and complex scalar function usage", "[scalar][functions][complex]") {
    SECTION("Nested string functions") {
        std::string sql = "SELECT UPPER(TRIM(SUBSTRING(name, 1, 10))) FROM users";
        Arena arena;
        Parser parser(arena, sql);
        auto expr = parser.parse();

        REQUIRE(expr != nullptr);
    }

    SECTION("String function in WHERE clause") {
        std::string sql = "SELECT * FROM users WHERE LENGTH(name) > 10";
        Arena arena;
        Parser parser(arena, sql);
        auto expr = parser.parse();

        REQUIRE(expr != nullptr);
    }

    SECTION("Math function with expression") {
        std::string sql = "SELECT ROUND(price * quantity, 2) FROM order_items";
        Arena arena;
        Parser parser(arena, sql);
        auto expr = parser.parse();

        REQUIRE(expr != nullptr);
    }

    SECTION("Function in ORDER BY") {
        std::string sql = "SELECT name FROM users ORDER BY LOWER(name)";
        Arena arena;
        Parser parser(arena, sql);
        auto expr = parser.parse();

        REQUIRE(expr != nullptr);
    }

    SECTION("Function in GROUP BY") {
        std::string sql = "SELECT UPPER(category), COUNT(*) FROM products GROUP BY UPPER(category)";
        Arena arena;
        Parser parser(arena, sql);
        auto expr = parser.parse();

        REQUIRE(expr != nullptr);
    }
}
