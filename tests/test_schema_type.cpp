#include <catch2/catch_test_macros.hpp>
#include "libsqlglot/schema.h"
#include "libsqlglot/type_checker.h"
#include "libsqlglot/parser.h"
#include "libsqlglot/arena.h"

using namespace libsqlglot;

TEST_CASE("Schema - Basic table and column management", "[schema]") {
    SchemaCatalog catalog;

    SECTION("Add and retrieve table schema") {
        TableSchema users("users");
        users.add_column("id", DataType::INTEGER, false);
        users.add_column("name", DataType::VARCHAR, true);
        users.add_column("age", DataType::INTEGER, true);

        catalog.add_table("users", users);

        REQUIRE(catalog.has_table("users"));
        REQUIRE(catalog.has_table("USERS"));  // Case-insensitive

        auto schema = catalog.get_table("users");
        REQUIRE(schema != nullptr);
        REQUIRE(schema->columns.size() == 3);
    }

    SECTION("Find column in table") {
        TableSchema products("products");
        products.add_column("id", DataType::INTEGER, false);
        products.add_column("price", DataType::DECIMAL, true);

        catalog.add_table("products", products);

        auto schema = catalog.get_table("products");
        const auto* col = schema->find_column("price");
        REQUIRE(col != nullptr);
        REQUIRE(col->type == DataType::DECIMAL);

        // Case-insensitive
        const auto* col2 = schema->find_column("PRICE");
        REQUIRE(col2 != nullptr);
    }

    SECTION("Validate column exists") {
        TableSchema orders("orders");
        orders.add_column("order_id", DataType::BIGINT, false);
        orders.add_column("total", DataType::DECIMAL, true);

        catalog.add_table("orders", orders);

        REQUIRE(catalog.validate_column("orders", "order_id"));
        REQUIRE(catalog.validate_column("orders", "total"));
        REQUIRE_FALSE(catalog.validate_column("orders", "nonexistent"));
        REQUIRE_FALSE(catalog.validate_column("nonexistent_table", "order_id"));
    }

    SECTION("Get column type") {
        TableSchema employees("employees");
        employees.add_column("emp_id", DataType::INTEGER, false);
        employees.add_column("salary", DataType::DOUBLE, true);
        employees.add_column("hire_date", DataType::DATE, true);

        catalog.add_table("employees", employees);

        REQUIRE(catalog.get_column_type("employees", "emp_id") == DataType::INTEGER);
        REQUIRE(catalog.get_column_type("employees", "salary") == DataType::DOUBLE);
        REQUIRE(catalog.get_column_type("employees", "hire_date") == DataType::DATE);
        REQUIRE(catalog.get_column_type("employees", "nonexistent") == DataType::UNKNOWN);
    }
}

TEST_CASE("Type Inference - Literals", "[type_checker]") {
    Arena arena;
    SchemaCatalog catalog;
    TypeChecker checker(catalog);

    SECTION("Integer literal") {
        auto lit = arena.create<Literal>("42");
        REQUIRE(checker.infer_type(lit) == DataType::INTEGER);
    }

    SECTION("Float literal") {
        auto lit = arena.create<Literal>("3.14");
        REQUIRE(checker.infer_type(lit) == DataType::DOUBLE);
    }

    SECTION("Boolean literals") {
        auto true_lit = arena.create<Literal>("TRUE");
        auto false_lit = arena.create<Literal>("FALSE");
        REQUIRE(checker.infer_type(true_lit) == DataType::BOOLEAN);
        REQUIRE(checker.infer_type(false_lit) == DataType::BOOLEAN);
    }

    SECTION("NULL literal") {
        auto null_lit = arena.create<Literal>("NULL");
        REQUIRE(checker.infer_type(null_lit) == DataType::NULL_TYPE);
    }

    SECTION("String literal") {
        auto str_lit = arena.create<Literal>("'hello'");
        REQUIRE(checker.infer_type(str_lit) == DataType::VARCHAR);
    }
}

TEST_CASE("Type Inference - Arithmetic operations", "[type_checker]") {
    Arena arena;
    SchemaCatalog catalog;
    TypeChecker checker(catalog);

    SECTION("Integer arithmetic") {
        auto left = arena.create<Literal>("10");
        auto right = arena.create<Literal>("5");
        auto add = arena.create<BinaryOp>(ExprType::PLUS, left, right);

        REQUIRE(checker.infer_type(add) == DataType::INTEGER);
    }

    SECTION("Float arithmetic") {
        auto left = arena.create<Literal>("10.5");
        auto right = arena.create<Literal>("5");
        auto mul = arena.create<BinaryOp>(ExprType::MUL, left, right);

        REQUIRE(checker.infer_type(mul) == DataType::DOUBLE);
    }

    SECTION("Mixed integer and float") {
        auto int_lit = arena.create<Literal>("10");
        auto float_lit = arena.create<Literal>("3.14");
        auto div = arena.create<BinaryOp>(ExprType::DIV, int_lit, float_lit);

        // Should promote to DOUBLE
        REQUIRE(checker.infer_type(div) == DataType::DOUBLE);
    }
}

TEST_CASE("Type Inference - Comparisons and boolean logic", "[type_checker]") {
    Arena arena;
    SchemaCatalog catalog;
    TypeChecker checker(catalog);

    SECTION("Comparison operations return boolean") {
        auto left = arena.create<Literal>("10");
        auto right = arena.create<Literal>("5");
        auto gt = arena.create<BinaryOp>(ExprType::GT, left, right);

        REQUIRE(checker.infer_type(gt) == DataType::BOOLEAN);
    }

    SECTION("Boolean logic operations") {
        auto true_lit = arena.create<Literal>("TRUE");
        auto false_lit = arena.create<Literal>("FALSE");
        auto and_op = arena.create<BinaryOp>(ExprType::AND, true_lit, false_lit);

        REQUIRE(checker.infer_type(and_op) == DataType::BOOLEAN);
    }

    SECTION("IS NULL returns boolean") {
        auto col = arena.create<Column>("", "x");
        auto is_null = arena.create<UnaryOp>(ExprType::IS_NULL, col);

        REQUIRE(checker.infer_type(is_null) == DataType::BOOLEAN);
    }
}

TEST_CASE("Type Inference - Aggregate functions", "[type_checker]") {
    Arena arena;
    SchemaCatalog catalog;
    TypeChecker checker(catalog);

    SECTION("COUNT returns BIGINT") {
        auto star = arena.create<Star>();
        auto count = arena.create<FunctionCall>("COUNT", std::vector<Expression*>{star});
        count->type = ExprType::AGG_COUNT;

        REQUIRE(checker.infer_type(count) == DataType::BIGINT);
    }

    SECTION("AVG returns DOUBLE") {
        auto col = arena.create<Column>("", "salary");
        auto avg = arena.create<FunctionCall>("AVG", std::vector<Expression*>{col});
        avg->type = ExprType::AGG_AVG;

        REQUIRE(checker.infer_type(avg) == DataType::DOUBLE);
    }

    SECTION("SUM of INTEGER returns BIGINT") {
        auto int_col = arena.create<Literal>("10");  // Simulating integer column
        auto sum = arena.create<FunctionCall>("SUM", std::vector<Expression*>{int_col});
        sum->type = ExprType::AGG_SUM;

        REQUIRE(checker.infer_type(sum) == DataType::BIGINT);
    }
}

TEST_CASE("Type Validation - Arithmetic type checking", "[type_checker]") {
    Arena arena;
    SchemaCatalog catalog;
    TypeChecker checker(catalog);

    SECTION("Valid arithmetic: number + number") {
        auto left = arena.create<Literal>("10");
        auto right = arena.create<Literal>("5");
        auto add = arena.create<BinaryOp>(ExprType::PLUS, left, right);

        REQUIRE_NOTHROW(checker.validate_expression(add));
    }

    SECTION("Invalid arithmetic: string + number") {
        auto str = arena.create<Literal>("'hello'");
        auto num = arena.create<Literal>("5");
        auto add = arena.create<BinaryOp>(ExprType::PLUS, str, num);

        REQUIRE_THROWS_AS(checker.validate_expression(add), TypeCheckError);
    }
}

TEST_CASE("Type Validation - Comparison type checking", "[type_checker]") {
    Arena arena;
    SchemaCatalog catalog;
    TypeChecker checker(catalog);

    SECTION("Valid comparison: number = number") {
        auto left = arena.create<Literal>("10");
        auto right = arena.create<Literal>("5");
        auto eq = arena.create<BinaryOp>(ExprType::EQ, left, right);

        REQUIRE_NOTHROW(checker.validate_expression(eq));
    }

    SECTION("Valid comparison: string = string") {
        auto left = arena.create<Literal>("'abc'");
        auto right = arena.create<Literal>("'def'");
        auto eq = arena.create<BinaryOp>(ExprType::EQ, left, right);

        REQUIRE_NOTHROW(checker.validate_expression(eq));
    }
}

TEST_CASE("Type Validation - Boolean logic checking", "[type_checker]") {
    Arena arena;
    SchemaCatalog catalog;
    TypeChecker checker(catalog);

    SECTION("Valid boolean AND") {
        auto left = arena.create<Literal>("TRUE");
        auto right = arena.create<Literal>("FALSE");
        auto and_op = arena.create<BinaryOp>(ExprType::AND, left, right);

        REQUIRE_NOTHROW(checker.validate_expression(and_op));
    }

    SECTION("Invalid boolean AND: number AND boolean") {
        auto num = arena.create<Literal>("10");
        auto bool_val = arena.create<Literal>("TRUE");
        auto and_op = arena.create<BinaryOp>(ExprType::AND, num, bool_val);

        REQUIRE_THROWS_AS(checker.validate_expression(and_op), TypeCheckError);
    }
}

TEST_CASE("Type Validation - SELECT statement validation", "[type_checker]") {
    Arena arena;
    SchemaCatalog catalog;

    // Set up schema
    TableSchema users("users");
    users.add_column("id", DataType::INTEGER, false);
    users.add_column("name", DataType::VARCHAR, true);
    users.add_column("age", DataType::INTEGER, true);
    catalog.add_table("users", users);

    TypeChecker checker(catalog);

    SECTION("Valid SELECT with boolean WHERE") {
        Parser parser(arena, "SELECT * FROM users WHERE age > 18");
        auto expr = parser.parse_select();
        auto stmt = static_cast<SelectStmt*>(expr);

        REQUIRE_NOTHROW(checker.validate_select(stmt));
    }

    SECTION("Invalid SELECT: non-boolean WHERE") {
        // Manually create invalid query (WHERE age instead of WHERE age > 0)
        auto stmt = arena.create<SelectStmt>();
        stmt->columns.push_back(arena.create<Star>());
        stmt->from = arena.create<TableRef>("users");
        stmt->where = arena.create<Literal>("42");  // Non-boolean in WHERE

        REQUIRE_THROWS_AS(checker.validate_select(stmt), TypeCheckError);
    }
}

TEST_CASE("Schema - Column type inference with schema", "[schema][type_checker]") {
    Arena arena;
    SchemaCatalog catalog;

    // Set up schema
    TableSchema products("products");
    products.add_column("id", DataType::INTEGER, false);
    products.add_column("price", DataType::DECIMAL, true);
    products.add_column("description", DataType::TEXT, true);
    catalog.add_table("products", products);

    TypeChecker checker(catalog);

    SECTION("Infer column type from schema") {
        auto col = arena.create<Column>("products", "price");
        REQUIRE(checker.infer_type(col) == DataType::DECIMAL);
    }

    SECTION("Unknown column returns UNKNOWN") {
        auto col = arena.create<Column>("products", "nonexistent");
        REQUIRE(checker.infer_type(col) == DataType::UNKNOWN);
    }

    SECTION("Column without table qualifier returns UNKNOWN") {
        auto col = arena.create<Column>("", "price");
        REQUIRE(checker.infer_type(col) == DataType::UNKNOWN);
    }
}

TEST_CASE("Type Checker - NULL handling", "[type_checker]") {
    Arena arena;
    SchemaCatalog catalog;
    TypeChecker checker(catalog);

    SECTION("NULL in arithmetic propagates NULL type") {
        auto null_lit = arena.create<Literal>("NULL");
        auto num = arena.create<Literal>("10");
        auto add = arena.create<BinaryOp>(ExprType::PLUS, null_lit, num);

        REQUIRE(checker.infer_type(add) == DataType::NULL_TYPE);
    }

    SECTION("NULL is valid in arithmetic (no type error)") {
        auto null_lit = arena.create<Literal>("NULL");
        auto num = arena.create<Literal>("10");
        auto add = arena.create<BinaryOp>(ExprType::PLUS, null_lit, num);

        REQUIRE_NOTHROW(checker.validate_expression(add));
    }
}
