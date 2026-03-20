#include <catch2/catch_test_macros.hpp>
#include "libsqlglot/optimizer.h"
#include "libsqlglot/expression.h"
#include "libsqlglot/arena.h"

using namespace libsqlglot;

TEST_CASE("Optimizer - Constant Folding - Arithmetic", "[optimizer]") {
    Arena arena;

    SECTION("Addition") {
        // 2 + 3 -> 5
        auto left = arena.create<Literal>("2");
        auto right = arena.create<Literal>("3");
        auto expr = arena.create<BinaryOp>(ExprType::PLUS, left, right);

        auto result = Optimizer::fold_constants(expr, arena);
        REQUIRE(result->type == ExprType::LITERAL);
        REQUIRE(static_cast<Literal*>(result)->value == "5");
    }

    SECTION("Subtraction") {
        // 10 - 3 -> 7
        auto left = arena.create<Literal>("10");
        auto right = arena.create<Literal>("3");
        auto expr = arena.create<BinaryOp>(ExprType::MINUS, left, right);

        auto result = Optimizer::fold_constants(expr, arena);
        REQUIRE(result->type == ExprType::LITERAL);
        REQUIRE(static_cast<Literal*>(result)->value == "7");
    }

    SECTION("Multiplication") {
        // 4 * 5 -> 20
        auto left = arena.create<Literal>("4");
        auto right = arena.create<Literal>("5");
        auto expr = arena.create<BinaryOp>(ExprType::MUL, left, right);

        auto result = Optimizer::fold_constants(expr, arena);
        REQUIRE(result->type == ExprType::LITERAL);
        REQUIRE(static_cast<Literal*>(result)->value == "20");
    }

    SECTION("Division") {
        // 15 / 3 -> 5
        auto left = arena.create<Literal>("15");
        auto right = arena.create<Literal>("3");
        auto expr = arena.create<BinaryOp>(ExprType::DIV, left, right);

        auto result = Optimizer::fold_constants(expr, arena);
        REQUIRE(result->type == ExprType::LITERAL);
        REQUIRE(static_cast<Literal*>(result)->value == "5");
    }

    SECTION("Division by zero - no folding") {
        // 10 / 0 -> unchanged
        auto left = arena.create<Literal>("10");
        auto right = arena.create<Literal>("0");
        auto expr = arena.create<BinaryOp>(ExprType::DIV, left, right);

        auto result = Optimizer::fold_constants(expr, arena);
        REQUIRE(result->type == ExprType::DIV);  // Unchanged
    }

    SECTION("Modulo") {
        // 17 % 5 -> 2
        auto left = arena.create<Literal>("17");
        auto right = arena.create<Literal>("5");
        auto expr = arena.create<BinaryOp>(ExprType::MOD, left, right);

        auto result = Optimizer::fold_constants(expr, arena);
        REQUIRE(result->type == ExprType::LITERAL);
        REQUIRE(static_cast<Literal*>(result)->value == "2");
    }
}

TEST_CASE("Optimizer - Constant Folding - Comparisons", "[optimizer]") {
    Arena arena;

    SECTION("Equality - true") {
        // 5 = 5 -> TRUE
        auto left = arena.create<Literal>("5");
        auto right = arena.create<Literal>("5");
        auto expr = arena.create<BinaryOp>(ExprType::EQ, left, right);

        auto result = Optimizer::fold_constants(expr, arena);
        REQUIRE(result->type == ExprType::LITERAL);
        REQUIRE(static_cast<Literal*>(result)->value == "TRUE");
    }

    SECTION("Equality - false") {
        // 5 = 3 -> FALSE
        auto left = arena.create<Literal>("5");
        auto right = arena.create<Literal>("3");
        auto expr = arena.create<BinaryOp>(ExprType::EQ, left, right);

        auto result = Optimizer::fold_constants(expr, arena);
        REQUIRE(result->type == ExprType::LITERAL);
        REQUIRE(static_cast<Literal*>(result)->value == "FALSE");
    }

    SECTION("Less than") {
        // 3 < 5 -> TRUE
        auto left = arena.create<Literal>("3");
        auto right = arena.create<Literal>("5");
        auto expr = arena.create<BinaryOp>(ExprType::LT, left, right);

        auto result = Optimizer::fold_constants(expr, arena);
        REQUIRE(result->type == ExprType::LITERAL);
        REQUIRE(static_cast<Literal*>(result)->value == "TRUE");
    }

    SECTION("Greater than") {
        // 10 > 5 -> TRUE
        auto left = arena.create<Literal>("10");
        auto right = arena.create<Literal>("5");
        auto expr = arena.create<BinaryOp>(ExprType::GT, left, right);

        auto result = Optimizer::fold_constants(expr, arena);
        REQUIRE(result->type == ExprType::LITERAL);
        REQUIRE(static_cast<Literal*>(result)->value == "TRUE");
    }
}

TEST_CASE("Optimizer - Constant Folding - Boolean Operations", "[optimizer]") {
    Arena arena;

    SECTION("AND - both true") {
        // TRUE AND TRUE -> TRUE
        auto left = arena.create<Literal>("TRUE");
        auto right = arena.create<Literal>("TRUE");
        auto expr = arena.create<BinaryOp>(ExprType::AND, left, right);

        auto result = Optimizer::fold_constants(expr, arena);
        REQUIRE(result->type == ExprType::LITERAL);
        REQUIRE(static_cast<Literal*>(result)->value == "TRUE");
    }

    SECTION("AND - one false") {
        // TRUE AND FALSE -> FALSE
        auto left = arena.create<Literal>("TRUE");
        auto right = arena.create<Literal>("FALSE");
        auto expr = arena.create<BinaryOp>(ExprType::AND, left, right);

        auto result = Optimizer::fold_constants(expr, arena);
        REQUIRE(result->type == ExprType::LITERAL);
        REQUIRE(static_cast<Literal*>(result)->value == "FALSE");
    }

    SECTION("OR - both false") {
        // FALSE OR FALSE -> FALSE
        auto left = arena.create<Literal>("FALSE");
        auto right = arena.create<Literal>("FALSE");
        auto expr = arena.create<BinaryOp>(ExprType::OR, left, right);

        auto result = Optimizer::fold_constants(expr, arena);
        REQUIRE(result->type == ExprType::LITERAL);
        REQUIRE(static_cast<Literal*>(result)->value == "FALSE");
    }

    SECTION("OR - one true") {
        // TRUE OR FALSE -> TRUE
        auto left = arena.create<Literal>("TRUE");
        auto right = arena.create<Literal>("FALSE");
        auto expr = arena.create<BinaryOp>(ExprType::OR, left, right);

        auto result = Optimizer::fold_constants(expr, arena);
        REQUIRE(result->type == ExprType::LITERAL);
        REQUIRE(static_cast<Literal*>(result)->value == "TRUE");
    }

    SECTION("NOT - true") {
        // NOT TRUE -> FALSE
        auto operand = arena.create<Literal>("TRUE");
        auto expr = arena.create<UnaryOp>(ExprType::NOT, operand);

        auto result = Optimizer::fold_constants(expr, arena);
        REQUIRE(result->type == ExprType::LITERAL);
        REQUIRE(static_cast<Literal*>(result)->value == "FALSE");
    }

    SECTION("NOT - false") {
        // NOT FALSE -> TRUE
        auto operand = arena.create<Literal>("FALSE");
        auto expr = arena.create<UnaryOp>(ExprType::NOT, operand);

        auto result = Optimizer::fold_constants(expr, arena);
        REQUIRE(result->type == ExprType::LITERAL);
        REQUIRE(static_cast<Literal*>(result)->value == "TRUE");
    }
}

TEST_CASE("Optimizer - Constant Folding - Boolean Simplifications", "[optimizer]") {
    Arena arena;

    SECTION("FALSE AND x -> FALSE") {
        auto left = arena.create<Literal>("FALSE");
        auto right = arena.create<Column>("", "x");
        auto expr = arena.create<BinaryOp>(ExprType::AND, left, right);

        auto result = Optimizer::fold_constants(expr, arena);
        REQUIRE(result->type == ExprType::LITERAL);
        REQUIRE(static_cast<Literal*>(result)->value == "FALSE");
    }

    SECTION("x AND FALSE -> FALSE") {
        auto left = arena.create<Column>("", "x");
        auto right = arena.create<Literal>("FALSE");
        auto expr = arena.create<BinaryOp>(ExprType::AND, left, right);

        auto result = Optimizer::fold_constants(expr, arena);
        REQUIRE(result->type == ExprType::LITERAL);
        REQUIRE(static_cast<Literal*>(result)->value == "FALSE");
    }

    SECTION("TRUE AND x -> x") {
        auto left = arena.create<Literal>("TRUE");
        auto right = arena.create<Column>("", "x");
        auto expr = arena.create<BinaryOp>(ExprType::AND, left, right);

        auto result = Optimizer::fold_constants(expr, arena);
        REQUIRE(result->type == ExprType::COLUMN);
        REQUIRE(static_cast<Column*>(result)->column == "x");
    }

    SECTION("x AND TRUE -> x") {
        auto left = arena.create<Column>("", "x");
        auto right = arena.create<Literal>("TRUE");
        auto expr = arena.create<BinaryOp>(ExprType::AND, left, right);

        auto result = Optimizer::fold_constants(expr, arena);
        REQUIRE(result->type == ExprType::COLUMN);
        REQUIRE(static_cast<Column*>(result)->column == "x");
    }

    SECTION("TRUE OR x -> TRUE") {
        auto left = arena.create<Literal>("TRUE");
        auto right = arena.create<Column>("", "x");
        auto expr = arena.create<BinaryOp>(ExprType::OR, left, right);

        auto result = Optimizer::fold_constants(expr, arena);
        REQUIRE(result->type == ExprType::LITERAL);
        REQUIRE(static_cast<Literal*>(result)->value == "TRUE");
    }

    SECTION("x OR TRUE -> TRUE") {
        auto left = arena.create<Column>("", "x");
        auto right = arena.create<Literal>("TRUE");
        auto expr = arena.create<BinaryOp>(ExprType::OR, left, right);

        auto result = Optimizer::fold_constants(expr, arena);
        REQUIRE(result->type == ExprType::LITERAL);
        REQUIRE(static_cast<Literal*>(result)->value == "TRUE");
    }

    SECTION("FALSE OR x -> x") {
        auto left = arena.create<Literal>("FALSE");
        auto right = arena.create<Column>("", "x");
        auto expr = arena.create<BinaryOp>(ExprType::OR, left, right);

        auto result = Optimizer::fold_constants(expr, arena);
        REQUIRE(result->type == ExprType::COLUMN);
        REQUIRE(static_cast<Column*>(result)->column == "x");
    }

    SECTION("x OR FALSE -> x") {
        auto left = arena.create<Column>("", "x");
        auto right = arena.create<Literal>("FALSE");
        auto expr = arena.create<BinaryOp>(ExprType::OR, left, right);

        auto result = Optimizer::fold_constants(expr, arena);
        REQUIRE(result->type == ExprType::COLUMN);
        REQUIRE(static_cast<Column*>(result)->column == "x");
    }
}

TEST_CASE("Optimizer - Constant Folding - NULL Propagation", "[optimizer]") {
    Arena arena;

    SECTION("NULL + 5 -> NULL") {
        auto left = arena.create<Literal>("NULL");
        auto right = arena.create<Literal>("5");
        auto expr = arena.create<BinaryOp>(ExprType::PLUS, left, right);

        auto result = Optimizer::fold_constants(expr, arena);
        REQUIRE(result->type == ExprType::LITERAL);
        REQUIRE(static_cast<Literal*>(result)->value == "NULL");
    }

    SECTION("10 - NULL -> NULL") {
        auto left = arena.create<Literal>("10");
        auto right = arena.create<Literal>("NULL");
        auto expr = arena.create<BinaryOp>(ExprType::MINUS, left, right);

        auto result = Optimizer::fold_constants(expr, arena);
        REQUIRE(result->type == ExprType::LITERAL);
        REQUIRE(static_cast<Literal*>(result)->value == "NULL");
    }

    SECTION("NULL = 5 -> NULL") {
        auto left = arena.create<Literal>("NULL");
        auto right = arena.create<Literal>("5");
        auto expr = arena.create<BinaryOp>(ExprType::EQ, left, right);

        auto result = Optimizer::fold_constants(expr, arena);
        REQUIRE(result->type == ExprType::LITERAL);
        REQUIRE(static_cast<Literal*>(result)->value == "NULL");
    }
}

TEST_CASE("Optimizer - Constant Folding - Nested Expressions", "[optimizer]") {
    Arena arena;

    SECTION("(2 + 3) * 4 -> 20") {
        auto left_inner = arena.create<Literal>("2");
        auto right_inner = arena.create<Literal>("3");
        auto inner = arena.create<BinaryOp>(ExprType::PLUS, left_inner, right_inner);
        auto right_outer = arena.create<Literal>("4");
        auto expr = arena.create<BinaryOp>(ExprType::MUL, inner, right_outer);

        auto result = Optimizer::fold_constants(expr, arena);
        REQUIRE(result->type == ExprType::LITERAL);
        REQUIRE(static_cast<Literal*>(result)->value == "20");
    }

    SECTION("(5 > 3) AND (10 = 10) -> TRUE") {
        auto left_cmp_left = arena.create<Literal>("5");
        auto left_cmp_right = arena.create<Literal>("3");
        auto left_cmp = arena.create<BinaryOp>(ExprType::GT, left_cmp_left, left_cmp_right);

        auto right_cmp_left = arena.create<Literal>("10");
        auto right_cmp_right = arena.create<Literal>("10");
        auto right_cmp = arena.create<BinaryOp>(ExprType::EQ, right_cmp_left, right_cmp_right);

        auto expr = arena.create<BinaryOp>(ExprType::AND, left_cmp, right_cmp);

        auto result = Optimizer::fold_constants(expr, arena);
        REQUIRE(result->type == ExprType::LITERAL);
        REQUIRE(static_cast<Literal*>(result)->value == "TRUE");
    }
}

TEST_CASE("Optimizer - Qualify Columns", "[optimizer]") {
    Arena arena;

    SECTION("Qualify unqualified column in SELECT") {
        auto col1 = arena.create<Column>("", "id");
        auto col2 = arena.create<Column>("", "name");

        auto table = arena.create<TableRef>("users", "u");
        auto stmt = arena.create<SelectStmt>();
        stmt->columns = {col1, col2};
        stmt->from = table;

        Optimizer::qualify_columns(stmt);

        REQUIRE(col1->table == "u");
        REQUIRE(col2->table == "u");
    }

    SECTION("Don't override already qualified column") {
        auto col1 = arena.create<Column>("other", "id");

        auto table = arena.create<TableRef>("users", "u");
        auto stmt = arena.create<SelectStmt>();
        stmt->columns = {col1};
        stmt->from = table;

        Optimizer::qualify_columns(stmt);

        REQUIRE(col1->table == "other");  // Should not change
    }

    SECTION("Qualify columns in WHERE clause") {
        auto col1 = arena.create<Column>("", "id");

        auto where_col = arena.create<Column>("", "active");
        auto where_val = arena.create<Literal>("1");
        auto where = arena.create<BinaryOp>(ExprType::EQ, where_col, where_val);

        auto table = arena.create<TableRef>("users", "u");
        auto stmt = arena.create<SelectStmt>();
        stmt->columns = {col1};
        stmt->from = table;
        stmt->where = where;

        Optimizer::qualify_columns(stmt);

        REQUIRE(col1->table == "u");
        REQUIRE(where_col->table == "u");
    }
}
