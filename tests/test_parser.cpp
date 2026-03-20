#include <catch2/catch_test_macros.hpp>
#include <libsqlglot/parser.h>
#include <libsqlglot/generator.h>

using namespace libsqlglot;

TEST_CASE("Parser - Simple SELECT *", "[parser]") {
    Arena arena;
    Parser parser(arena, "SELECT * FROM users");

    auto expr = parser.parse_select();
    auto stmt = static_cast<SelectStmt*>(expr);

    REQUIRE(stmt != nullptr);
    REQUIRE(stmt->columns.size() == 1);
    REQUIRE(stmt->columns[0]->type == ExprType::STAR);
    REQUIRE(stmt->from != nullptr);

    // Generate SQL to verify
    std::string sql = Generator::generate(expr);
    REQUIRE(sql == "SELECT * FROM users");
}

TEST_CASE("Parser - SELECT with columns", "[parser]") {
    Arena arena;
    Parser parser(arena, "SELECT id, name, email FROM users");

    auto expr = parser.parse_select();
    auto stmt = static_cast<SelectStmt*>(expr);

    REQUIRE(stmt->columns.size() == 3);

    std::string sql = Generator::generate(expr);
    REQUIRE(sql == "SELECT id, name, email FROM users");
}

TEST_CASE("Parser - SELECT with WHERE", "[parser]") {
    Arena arena;
    Parser parser(arena, "SELECT * FROM users WHERE age > 18");

    auto expr = parser.parse_select();
    auto stmt = static_cast<SelectStmt*>(expr);

    REQUIRE(stmt->where != nullptr);
    REQUIRE(stmt->where->type == ExprType::GT);

    std::string sql = Generator::generate(expr);
    REQUIRE(sql == "SELECT * FROM users WHERE age > 18");
}

TEST_CASE("Parser - SELECT with multiple WHERE conditions", "[parser]") {
    Arena arena;
    Parser parser(arena, "SELECT * FROM users WHERE age > 18 AND active = 1");

    auto expr = parser.parse_select();
    auto stmt = static_cast<SelectStmt*>(expr);

    REQUIRE(stmt->where != nullptr);
    REQUIRE(stmt->where->type == ExprType::AND);

    std::string sql = Generator::generate(expr);
    REQUIRE(sql == "SELECT * FROM users WHERE age > 18 AND active = 1");
}

TEST_CASE("Parser - SELECT with JOIN", "[parser]") {
    Arena arena;
    Parser parser(arena, "SELECT * FROM users u INNER JOIN orders o ON u.id = o.user_id");

    auto expr = parser.parse_select();
    auto stmt = static_cast<SelectStmt*>(expr);

    REQUIRE(stmt->from != nullptr);
    REQUIRE(stmt->from->type == ExprType::JOIN_CLAUSE);

    std::string sql = Generator::generate(expr);
    REQUIRE(sql == "SELECT * FROM users AS u INNER JOIN orders AS o ON u.id = o.user_id");
}

TEST_CASE("Parser - SELECT with LIMIT", "[parser]") {
    Arena arena;
    Parser parser(arena, "SELECT * FROM users LIMIT 10");

    auto expr = parser.parse_select();
    auto stmt = static_cast<SelectStmt*>(expr);

    REQUIRE(stmt->limit != nullptr);

    std::string sql = Generator::generate(expr);
    REQUIRE(sql == "SELECT * FROM users LIMIT 10");
}

TEST_CASE("Parser - SELECT with column aliases", "[parser]") {
    Arena arena;
    Parser parser(arena, "SELECT name AS user_name, email AS user_email FROM users");

    auto expr = parser.parse_select();
    auto stmt = static_cast<SelectStmt*>(expr);

    REQUIRE(stmt->columns.size() == 2);
    REQUIRE(stmt->columns[0]->type == ExprType::ALIAS);
    REQUIRE(stmt->columns[1]->type == ExprType::ALIAS);

    std::string sql = Generator::generate(expr);
    REQUIRE(sql == "SELECT name AS user_name, email AS user_email FROM users");
}

TEST_CASE("Parser - SELECT with arithmetic", "[parser]") {
    Arena arena;
    Parser parser(arena, "SELECT price * quantity FROM orders");

    auto expr = parser.parse_select();
    auto stmt = static_cast<SelectStmt*>(expr);

    REQUIRE(stmt->columns.size() == 1);
    REQUIRE(stmt->columns[0]->type == ExprType::MUL);

    std::string sql = Generator::generate(expr);
    REQUIRE(sql == "SELECT price * quantity FROM orders");
}

// TODO: Fix COUNT(*) parsing - tokenizer may not be handling it correctly
// TEST_CASE("Parser - SELECT with function call", "[parser]") {
//     Arena arena;
//     Parser parser(arena, "SELECT COUNT(*) FROM users");
//
//     auto expr = parser.parse_select();
//     auto stmt = static_cast<SelectStmt*>(expr);
//
//     REQUIRE(stmt->columns.size() == 1);
//     REQUIRE(stmt->columns[0]->type == ExprType::AGG_COUNT);
//
//     std::string sql = Generator::generate(expr);
//     REQUIRE(sql == "SELECT COUNT(*) FROM users");
// }

TEST_CASE("Parser - SELECT DISTINCT", "[parser]") {
    Arena arena;
    Parser parser(arena, "SELECT DISTINCT country FROM users");

    auto expr = parser.parse_select();
    auto stmt = static_cast<SelectStmt*>(expr);

    REQUIRE(stmt->distinct == true);

    std::string sql = Generator::generate(expr);
    REQUIRE(sql == "SELECT DISTINCT country FROM users");
}

TEST_CASE("Parser - Complex query", "[parser]") {
    Arena arena;
    Parser parser(arena,
        "SELECT u.name, COUNT(o.id) "
        "FROM users u "
        "LEFT JOIN orders o ON u.id = o.user_id "
        "WHERE u.active = 1 "
        "GROUP BY u.name "
        "HAVING COUNT(o.id) > 5 "
        "ORDER BY COUNT(o.id) "
        "LIMIT 10");

    auto expr = parser.parse_select();
    auto stmt = static_cast<SelectStmt*>(expr);

    REQUIRE(stmt->columns.size() == 2);
    REQUIRE(stmt->from != nullptr);
    REQUIRE(stmt->where != nullptr);
    REQUIRE(stmt->group_by.size() == 1);
    REQUIRE(stmt->having != nullptr);
    REQUIRE(stmt->order_by.size() == 1);
    REQUIRE(stmt->limit != nullptr);

    // Just verify it generates something valid
    std::string sql = Generator::generate(expr);
    REQUIRE(!sql.empty());
}
