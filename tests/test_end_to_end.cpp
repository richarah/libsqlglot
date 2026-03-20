#include <catch2/catch_test_macros.hpp>
#include <libsqlglot/arena.h>
#include <libsqlglot/expression.h>
#include <libsqlglot/generator.h>

using namespace libsqlglot;

TEST_CASE("End-to-end - Simple SELECT *", "[e2e]") {
    Arena arena;

    // Build AST: SELECT * FROM users
    auto stmt = arena.create<SelectStmt>();
    stmt->columns.push_back(arena.create<Star>());
    stmt->from = arena.create<TableRef>("users");

    // Generate SQL
    std::string sql = Generator::generate(stmt);

    REQUIRE(sql == "SELECT * FROM users");
}

TEST_CASE("End-to-end - SELECT with columns", "[e2e]") {
    Arena arena;

    // Build AST: SELECT id, name FROM users
    auto stmt = arena.create<SelectStmt>();
    stmt->columns.push_back(arena.create<Column>("id"));
    stmt->columns.push_back(arena.create<Column>("name"));
    stmt->from = arena.create<TableRef>("users");

    std::string sql = Generator::generate(stmt);

    REQUIRE(sql == "SELECT id, name FROM users");
}

TEST_CASE("End-to-end - SELECT with WHERE", "[e2e]") {
    Arena arena;

    // Build AST: SELECT * FROM users WHERE age > 18
    auto stmt = arena.create<SelectStmt>();
    stmt->columns.push_back(arena.create<Star>());
    stmt->from = arena.create<TableRef>("users");

    auto age_col = arena.create<Column>("age");
    auto eighteen = arena.create<Literal>("18");
    stmt->where = arena.create<BinaryOp>(ExprType::GT, age_col, eighteen);

    std::string sql = Generator::generate(stmt);

    REQUIRE(sql == "SELECT * FROM users WHERE age > 18");
}

TEST_CASE("End-to-end - SELECT with table alias", "[e2e]") {
    Arena arena;

    // Build AST: SELECT u.name FROM users AS u
    auto stmt = arena.create<SelectStmt>();
    stmt->columns.push_back(arena.create<Column>("u", "name"));
    stmt->from = arena.create<TableRef>("users", "u");

    std::string sql = Generator::generate(stmt);

    REQUIRE(sql == "SELECT u.name FROM users AS u");
}

TEST_CASE("End-to-end - SELECT with JOIN", "[e2e]") {
    Arena arena;

    // Build AST: SELECT * FROM users u JOIN orders o ON u.id = o.user_id
    auto stmt = arena.create<SelectStmt>();
    stmt->columns.push_back(arena.create<Star>());

    auto users = arena.create<TableRef>("users", "u");
    auto orders = arena.create<TableRef>("orders", "o");

    auto u_id = arena.create<Column>("u", "id");
    auto o_user_id = arena.create<Column>("o", "user_id");
    auto join_condition = arena.create<BinaryOp>(ExprType::EQ, u_id, o_user_id);

    stmt->from = arena.create<JoinClause>(JoinClause::JoinType::INNER, users, orders, join_condition);

    std::string sql = Generator::generate(stmt);

    REQUIRE(sql == "SELECT * FROM users AS u INNER JOIN orders AS o ON u.id = o.user_id");
}

TEST_CASE("End-to-end - SELECT with multiple conditions", "[e2e]") {
    Arena arena;

    // Build AST: SELECT * FROM users WHERE age > 18 AND active = 'true'
    auto stmt = arena.create<SelectStmt>();
    stmt->columns.push_back(arena.create<Star>());
    stmt->from = arena.create<TableRef>("users");

    auto age_col = arena.create<Column>("age");
    auto eighteen = arena.create<Literal>("18");
    auto age_condition = arena.create<BinaryOp>(ExprType::GT, age_col, eighteen);

    auto active_col = arena.create<Column>("active");
    auto true_val = arena.create<Literal>("'true'");  // String literal, not boolean
    auto active_condition = arena.create<BinaryOp>(ExprType::EQ, active_col, true_val);

    stmt->where = arena.create<BinaryOp>(ExprType::AND, age_condition, active_condition);

    std::string sql = Generator::generate(stmt);

    REQUIRE(sql == "SELECT * FROM users WHERE age > 18 AND active = 'true'");
}

TEST_CASE("End-to-end - SELECT with column alias", "[e2e]") {
    Arena arena;

    // Build AST: SELECT name AS user_name FROM users
    auto stmt = arena.create<SelectStmt>();

    auto name_col = arena.create<Column>("name");
    auto aliased = arena.create<Alias>(name_col, "user_name");
    stmt->columns.push_back(aliased);
    stmt->from = arena.create<TableRef>("users");

    std::string sql = Generator::generate(stmt);

    REQUIRE(sql == "SELECT name AS user_name FROM users");
}

TEST_CASE("End-to-end - SELECT with LIMIT", "[e2e]") {
    Arena arena;

    // Build AST: SELECT * FROM users LIMIT 10
    auto stmt = arena.create<SelectStmt>();
    stmt->columns.push_back(arena.create<Star>());
    stmt->from = arena.create<TableRef>("users");
    stmt->limit = arena.create<Literal>("10");

    std::string sql = Generator::generate(stmt);

    REQUIRE(sql == "SELECT * FROM users LIMIT 10");
}
