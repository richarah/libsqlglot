#include <catch2/catch_test_macros.hpp>
#include <catch2/benchmark/catch_benchmark.hpp>
#include "libsqlglot/transpiler.h"
#include "libsqlglot/arena.h"
#include <fstream>
#include <sstream>

using namespace libsqlglot;

std::string read_file(const std::string& path) {
    std::ifstream file(path);
    if (!file.is_open()) {
        throw std::runtime_error("Could not open file: " + path);
    }
    std::stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}

TEST_CASE("Mad Queries - Stress Tests", "[mad_queries][stress]") {
    const std::string base_path = "../../benchmarks/mad_queries/";

    SECTION("Query 1: Deep CTEs with windows") {
        auto sql = read_file(base_path + "query1_deep_ctes_windows.sql");
        Arena arena;
        REQUIRE_NOTHROW(Transpiler::parse(arena, sql));

        BENCHMARK("Parse Query 1") {
            Arena arena;
            return Transpiler::parse(arena, sql);
        };
    }

    SECTION("Query 2: Deep CASE expressions") {
        auto sql = read_file(base_path + "query2_deep_case.sql");
        Arena arena;
        REQUIRE_NOTHROW(Transpiler::parse(arena, sql));

        BENCHMARK("Parse Query 2") {
            Arena arena;
            return Transpiler::parse(arena, sql);
        };
    }

    SECTION("Query 3: Multiple subqueries") {
        auto sql = read_file(base_path + "query3_multiple_subqueries.sql");
        Arena arena;
        REQUIRE_NOTHROW(Transpiler::parse(arena, sql));

        BENCHMARK("Parse Query 3") {
            Arena arena;
            return Transpiler::parse(arena, sql);
        };
    }

    SECTION("Query 4: Complex joins with windows") {
        auto sql = read_file(base_path + "query4_complex_joins_windows.sql");
        Arena arena;
        REQUIRE_NOTHROW(Transpiler::parse(arena, sql));

        BENCHMARK("Parse Query 4") {
            Arena arena;
            return Transpiler::parse(arena, sql);
        };
    }

    SECTION("Query 5: UNION with EXTRACT") {
        auto sql = read_file(base_path + "query5_union_extract.sql");
        Arena arena;
        REQUIRE_NOTHROW(Transpiler::parse(arena, sql));

        BENCHMARK("Parse Query 5") {
            Arena arena;
            return Transpiler::parse(arena, sql);
        };
    }

    SECTION("Query 6: String concatenation") {
        auto sql = read_file(base_path + "query6_string_concat.sql");
        Arena arena;
        REQUIRE_NOTHROW(Transpiler::parse(arena, sql));

        BENCHMARK("Parse Query 6") {
            Arena arena;
            return Transpiler::parse(arena, sql);
        };
    }

    SECTION("Query 7: Correlated subqueries") {
        auto sql = read_file(base_path + "query7_correlated_subqueries.sql");
        Arena arena;
        REQUIRE_NOTHROW(Transpiler::parse(arena, sql));

        BENCHMARK("Parse Query 7") {
            Arena arena;
            return Transpiler::parse(arena, sql);
        };
    }

    SECTION("Query 8: Complex WHERE clause") {
        auto sql = read_file(base_path + "query8_complex_where.sql");
        Arena arena;
        REQUIRE_NOTHROW(Transpiler::parse(arena, sql));

        BENCHMARK("Parse Query 8") {
            Arena arena;
            return Transpiler::parse(arena, sql);
        };
    }
}
