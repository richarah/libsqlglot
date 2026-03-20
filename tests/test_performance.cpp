#include <catch2/catch_test_macros.hpp>
#include <catch2/benchmark/catch_benchmark.hpp>
#include "libsqlglot/transpiler.h"
#include "libsqlglot/arena.h"
#include "libsqlglot/optimizer.h"
#include "libsqlglot/schema.h"
#include "libsqlglot/type_checker.h"
#include <chrono>

using namespace libsqlglot;

TEST_CASE("Performance - Parse simple SELECT", "[benchmark][performance]") {
    const std::string sql = "SELECT id, name FROM users WHERE age > 18";

    BENCHMARK("Parse simple SELECT") {
        Arena arena;
        Parser parser(arena, sql);
        return parser.parse_select();
    };
}

TEST_CASE("Performance - Parse complex query", "[benchmark][performance]") {
    const std::string sql = R"(
        SELECT u.id, u.name, COUNT(o.order_id) as order_count
        FROM users u
        LEFT JOIN orders o ON u.id = o.user_id
        WHERE u.age > 18 AND u.active = TRUE
        GROUP BY u.id, u.name
        HAVING COUNT(o.order_id) > 5
        ORDER BY order_count DESC
        LIMIT 100
    )";

    BENCHMARK("Parse complex query") {
        Arena arena;
        Parser parser(arena, sql);
        return parser.parse_select();
    };
}

TEST_CASE("Performance - Constant folding optimization", "[benchmark][performance]") {
    Arena arena;

    // Create expression: (2 + 3) * (10 - 5)
    auto lit2 = arena.create<Literal>("2");
    auto lit3 = arena.create<Literal>("3");
    auto lit10 = arena.create<Literal>("10");
    auto lit5 = arena.create<Literal>("5");

    auto add = arena.create<BinaryOp>(ExprType::PLUS, lit2, lit3);
    auto sub = arena.create<BinaryOp>(ExprType::MINUS, lit10, lit5);
    auto mul = arena.create<BinaryOp>(ExprType::MUL, add, sub);

    BENCHMARK("Constant folding") {
        return Optimizer::fold_constants(mul, arena);
    };
}

TEST_CASE("Performance - Schema lookup", "[benchmark][performance]") {
    SchemaCatalog catalog;

    // Setup schema
    TableSchema users("users");
    users.add_column("id", DataType::INTEGER, false);
    users.add_column("name", DataType::VARCHAR, true);
    users.add_column("email", DataType::VARCHAR, true);
    users.add_column("age", DataType::INTEGER, true);
    users.add_column("created_at", DataType::TIMESTAMP, true);
    catalog.add_table("users", users);

    BENCHMARK("Schema lookup") {
        return catalog.get_table("users");
    };

    BENCHMARK("Column validation") {
        return catalog.validate_column("users", "email");
    };
}

TEST_CASE("Performance - Type inference", "[benchmark][performance]") {
    Arena arena;
    SchemaCatalog catalog;

    // Setup schema
    TableSchema products("products");
    products.add_column("id", DataType::INTEGER, false);
    products.add_column("price", DataType::DECIMAL, true);
    catalog.add_table("products", products);

    TypeChecker checker(catalog);

    // Create expression: price * 1.1
    auto price_col = arena.create<Column>("products", "price");
    auto factor = arena.create<Literal>("1.1");
    auto mul = arena.create<BinaryOp>(ExprType::MUL, price_col, factor);

    BENCHMARK("Type inference") {
        return checker.infer_type(mul);
    };
}

TEST_CASE("Performance - Full transpilation pipeline", "[benchmark][performance]") {
    const std::string sql = "SELECT * FROM users WHERE age > 18 AND active = TRUE";

    BENCHMARK("Full transpilation (ANSI to ANSI)") {
        return Transpiler::transpile(sql, Dialect::ANSI, Dialect::ANSI, true);
    };

    BENCHMARK("Full transpilation (ANSI to MySQL)") {
        return Transpiler::transpile(sql, Dialect::ANSI, Dialect::MySQL, true);
    };

    BENCHMARK("Full transpilation (ANSI to PostgreSQL)") {
        return Transpiler::transpile(sql, Dialect::ANSI, Dialect::PostgreSQL, true);
    };
}

TEST_CASE("Performance - CTE parsing", "[benchmark][performance]") {
    const std::string sql = R"(
        WITH regional_sales AS (
            SELECT region, SUM(amount) as total_sales
            FROM orders
            GROUP BY region
        ),
        top_regions AS (
            SELECT region
            FROM regional_sales
            WHERE total_sales > 1000000
        )
        SELECT *
        FROM orders
        WHERE region IN (SELECT region FROM top_regions)
    )";

    BENCHMARK("Parse CTE query") {
        Arena arena;
        Parser parser(arena, sql);
        return parser.parse_select();
    };
}

TEST_CASE("Performance - Window function parsing", "[benchmark][performance]") {
    const std::string sql = R"(
        SELECT
            employee_id,
            department,
            salary,
            ROW_NUMBER() OVER (PARTITION BY department ORDER BY salary DESC) as rank
        FROM employees
    )";

    BENCHMARK("Parse window function") {
        Arena arena;
        Parser parser(arena, sql);
        return parser.parse_select();
    };
}

TEST_CASE("Performance - Arena allocation", "[benchmark][performance]") {
    BENCHMARK("Arena creation and allocation") {
        Arena arena;
        Literal* last = nullptr;
        for (int i = 0; i < 100; ++i) {
            last = arena.create<Literal>("test");
        }
        // Use last to prevent optimization, return total allocated
        return last ? arena.total_allocated() : 0;
    };

    BENCHMARK("Arena with large allocations") {
        Arena arena;
        SelectStmt* last = nullptr;
        for (int i = 0; i < 1000; ++i) {
            last = arena.create<SelectStmt>();
        }
        // Use last to prevent optimization, return total allocated
        return last ? arena.total_allocated() : 0;
    };
}

TEST_CASE("Performance - Optimization pipeline", "[benchmark][performance]") {
    const std::string sql = R"(
        SELECT u.id, u.name
        FROM (
            SELECT id, name, age
            FROM users
            WHERE active = TRUE
        ) u
        WHERE u.age > 18 AND u.age < 65
    )";

    BENCHMARK("Full optimization pipeline") {
        Arena arena;
        auto expr = Transpiler::parse(arena, sql);
        auto stmt = static_cast<SelectStmt*>(expr);
        Transpiler::optimize(arena, stmt);
        return stmt;
    };
}

// Stress test: parse and optimize many queries
TEST_CASE("Stress Test - Multiple queries", "[performance][stress]") {
    SECTION("Parse many queries sequentially") {
        const std::vector<std::string> queries = {
            "SELECT * FROM users",
            "SELECT id, name FROM products WHERE price > 100",
            "SELECT u.*, o.* FROM users u JOIN orders o ON u.id = o.user_id",
            "SELECT COUNT(*) FROM users GROUP BY country",
            "SELECT * FROM users WHERE age BETWEEN 18 AND 65",
        };

        int count = 0;
        for (int i = 0; i < 20; ++i) {
            for (const auto& sql : queries) {
                Arena arena;
                Parser parser(arena, sql);
                parser.parse_select();
                ++count;
            }
        }
        REQUIRE(count == 100);
    }
}

// Memory safety test
TEST_CASE("Safety - Memory bounds checking", "[safety][performance]") {
    Arena arena;

    SECTION("Large query parsing - no buffer overflow") {
        std::string large_sql = "SELECT ";
        for (int i = 0; i < 100; ++i) {
            if (i > 0) large_sql += ", ";
            large_sql += "col" + std::to_string(i);
        }
        large_sql += " FROM table1";

        REQUIRE_NOTHROW([&]() {
            Parser parser(arena, large_sql);
            parser.parse_select();
        }());
    }

    SECTION("Deep nesting - recursion limit") {
        // Create deeply nested expression
        std::string nested_sql = "SELECT (((((((((1)))))))))";

        REQUIRE_NOTHROW([&]() {
            Parser parser(arena, nested_sql);
            parser.parse_select();
        }());
    }
}

// Correctness verification
TEST_CASE("Correctness - Optimizer preserves semantics", "[correctness]") {
    Arena arena;

    SECTION("Constant folding produces correct results") {
        // 2 + 3 should become 5
        auto lit2 = arena.create<Literal>("2");
        auto lit3 = arena.create<Literal>("3");
        auto add = arena.create<BinaryOp>(ExprType::PLUS, lit2, lit3);

        auto result = Optimizer::fold_constants(add, arena);
        REQUIRE(result->type == ExprType::LITERAL);
        REQUIRE(static_cast<Literal*>(result)->value == "5");
    }

    SECTION("Boolean simplification: FALSE AND x → FALSE") {
        auto false_lit = arena.create<Literal>("FALSE");
        auto col = arena.create<Column>("", "x");
        auto and_op = arena.create<BinaryOp>(ExprType::AND, false_lit, col);

        auto result = Optimizer::fold_constants(and_op, arena);
        REQUIRE(result->type == ExprType::LITERAL);
        REQUIRE(static_cast<Literal*>(result)->value == "FALSE");
    }

    SECTION("Boolean simplification: TRUE OR x → TRUE") {
        auto true_lit = arena.create<Literal>("TRUE");
        auto col = arena.create<Column>("", "x");
        auto or_op = arena.create<BinaryOp>(ExprType::OR, true_lit, col);

        auto result = Optimizer::fold_constants(or_op, arena);
        REQUIRE(result->type == ExprType::LITERAL);
        REQUIRE(static_cast<Literal*>(result)->value == "TRUE");
    }
}
