#include <catch2/catch_test_macros.hpp>
#include "libsqlglot/transpiler.h"
#include "libsqlglot/arena.h"

using namespace libsqlglot;

TEST_CASE("UNBOUNDED FOLLOWING frame bound", "[parser][window]") {
    Arena arena;

    SECTION("ROWS BETWEEN UNBOUNDED PRECEDING AND UNBOUNDED FOLLOWING") {
        const char* sql = R"(
              SELECT
                SUM(amount) OVER (
                  ORDER BY created_at
                  ROWS BETWEEN UNBOUNDED PRECEDING AND UNBOUNDED FOLLOWING
                ) AS total
              FROM transactions
        )";
        REQUIRE_NOTHROW(Transpiler::parse(arena, sql));
    }

    SECTION("RANGE BETWEEN UNBOUNDED PRECEDING AND UNBOUNDED FOLLOWING") {
        const char* sql = R"(
              SELECT
                AVG(score) OVER (
                  PARTITION BY team_id
                  ORDER BY match_day
                  RANGE BETWEEN UNBOUNDED PRECEDING AND UNBOUNDED FOLLOWING
                ) AS season_avg
              FROM games
        )";
        REQUIRE_NOTHROW(Transpiler::parse(arena, sql));
    }
}
