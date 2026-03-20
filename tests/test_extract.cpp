#include <catch2/catch_test_macros.hpp>
#include "libsqlglot/transpiler.h"
#include "libsqlglot/arena.h"

using namespace libsqlglot;

TEST_CASE("EXTRACT function parsing", "[parser][extract]") {
    Arena arena;

    SECTION("EXTRACT YEAR") {
        REQUIRE_NOTHROW(Transpiler::parse(arena, "SELECT EXTRACT(YEAR FROM order_date) FROM orders"));
    }

    SECTION("EXTRACT MONTH") {
        REQUIRE_NOTHROW(Transpiler::parse(arena, "SELECT EXTRACT(MONTH FROM order_date) FROM orders"));
    }

    SECTION("EXTRACT DAY") {
        REQUIRE_NOTHROW(Transpiler::parse(arena, "SELECT EXTRACT(DAY FROM order_date) FROM orders"));
    }

    SECTION("EXTRACT in CAST") {
        REQUIRE_NOTHROW(Transpiler::parse(arena, "SELECT CAST(EXTRACT(YEAR FROM order_date) AS VARCHAR(10)) FROM orders"));
    }

    SECTION("Multiple EXTRACT calls") {
        REQUIRE_NOTHROW(Transpiler::parse(arena,
            "SELECT EXTRACT(YEAR FROM order_date), EXTRACT(MONTH FROM order_date) FROM orders"));
    }

    SECTION("EXTRACT in WHERE clause") {
        REQUIRE_NOTHROW(Transpiler::parse(arena,
            "SELECT * FROM orders WHERE EXTRACT(YEAR FROM order_date) = 2024"));
    }
}
