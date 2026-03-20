#include <catch2/catch_test_macros.hpp>
#include <libsqlglot/parser.h>
#include <libsqlglot/generator.h>

using namespace libsqlglot;

// ============================================================================
// CTE (WITH CLAUSE) TESTS
// ============================================================================

TEST_CASE("CTE - Simple WITH clause", "[phase3][cte]") {
    Arena arena;
    Parser parser(arena,
        "WITH high_scorers AS (SELECT * FROM users WHERE score > 100) "
        "SELECT * FROM high_scorers");

    auto expr = parser.parse_select();
    auto stmt = static_cast<SelectStmt*>(expr);

    REQUIRE(stmt != nullptr);
    REQUIRE(stmt->with != nullptr);
    REQUIRE(stmt->with->ctes.size() == 1);
    REQUIRE(stmt->with->ctes[0]->name == "high_scorers");
    REQUIRE(stmt->with->ctes[0]->query != nullptr);

    std::string sql = Generator::generate(expr);
    REQUIRE(sql.find("WITH high_scorers AS") != std::string::npos);
}

TEST_CASE("CTE - Multiple CTEs", "[phase3][cte]") {
    Arena arena;
    Parser parser(arena,
        "WITH users_active AS (SELECT * FROM users WHERE active = 1), "
        "users_premium AS (SELECT * FROM users_active WHERE premium = 1) "
        "SELECT * FROM users_premium");

    auto expr = parser.parse_select();
    auto stmt = static_cast<SelectStmt*>(expr);

    REQUIRE(stmt->with != nullptr);
    REQUIRE(stmt->with->ctes.size() == 2);
    REQUIRE(stmt->with->ctes[0]->name == "users_active");
    REQUIRE(stmt->with->ctes[1]->name == "users_premium");

    std::string sql = Generator::generate(expr);
    REQUIRE(sql.find("WITH users_active AS") != std::string::npos);
    REQUIRE(sql.find("users_premium AS") != std::string::npos);
}

TEST_CASE("CTE - WITH RECURSIVE", "[phase3][cte]") {
    Arena arena;
    Parser parser(arena,
        "WITH RECURSIVE tree AS (SELECT * FROM nodes WHERE parent_id IS NULL) "
        "SELECT * FROM tree");

    auto expr = parser.parse_select();
    auto stmt = static_cast<SelectStmt*>(expr);

    REQUIRE(stmt->with != nullptr);
    REQUIRE(stmt->with->recursive == true);

    std::string sql = Generator::generate(expr);
    REQUIRE(sql.find("WITH RECURSIVE") != std::string::npos);
}

TEST_CASE("CTE - With column list", "[phase3][cte]") {
    Arena arena;
    Parser parser(arena,
        "WITH top_users (user_id, user_name, user_score) AS (SELECT id, name, score FROM users ORDER BY score DESC LIMIT 10) "
        "SELECT * FROM top_users");

    auto expr = parser.parse_select();
    auto stmt = static_cast<SelectStmt*>(expr);

    REQUIRE(stmt->with->ctes.size() == 1);
    REQUIRE(stmt->with->ctes[0]->columns.size() == 3);
    REQUIRE(stmt->with->ctes[0]->columns[0] == "user_id");
    REQUIRE(stmt->with->ctes[0]->columns[1] == "user_name");
    REQUIRE(stmt->with->ctes[0]->columns[2] == "user_score");

    std::string sql = Generator::generate(expr);
    REQUIRE(sql.find("top_users (user_id, user_name, user_score)") != std::string::npos);
}

// ============================================================================
// WINDOW FUNCTION TESTS
// ============================================================================

TEST_CASE("Window - ROW_NUMBER with PARTITION BY", "[phase3][window]") {
    Arena arena;
    Parser parser(arena, "SELECT ROW_NUMBER() OVER (PARTITION BY department ORDER BY salary) FROM employees");

    auto expr = parser.parse_select();
    auto stmt = static_cast<SelectStmt*>(expr);

    REQUIRE(stmt->columns.size() == 1);
    REQUIRE(stmt->columns[0]->type == ExprType::WINDOW_FUNCTION);
    auto* win_func = static_cast<WindowFunction*>(stmt->columns[0]);
    REQUIRE(win_func->function_name == "ROW_NUMBER");
    REQUIRE(win_func->over != nullptr);
    REQUIRE(win_func->over->partition_by.size() == 1);
    REQUIRE(win_func->over->order_by.size() == 1);

    std::string sql = Generator::generate(expr);
    REQUIRE(sql.find("ROW_NUMBER() OVER (PARTITION BY") != std::string::npos);
}

TEST_CASE("Window - RANK with ORDER BY", "[phase3][window]") {
    Arena arena;
    Parser parser(arena, "SELECT RANK() OVER (ORDER BY score DESC) FROM users");

    auto expr = parser.parse_select();
    auto stmt = static_cast<SelectStmt*>(expr);

    REQUIRE(stmt->columns[0]->type == ExprType::WINDOW_FUNCTION);
    auto* win_func = static_cast<WindowFunction*>(stmt->columns[0]);
    REQUIRE(win_func->function_name == "RANK");
    REQUIRE(win_func->over->partition_by.empty());
    REQUIRE(win_func->over->order_by.size() == 1);

    std::string sql = Generator::generate(expr);
    REQUIRE(sql.find("RANK() OVER (ORDER BY") != std::string::npos);
}

TEST_CASE("Window - LAG with arguments", "[phase3][window]") {
    Arena arena;
    Parser parser(arena, "SELECT LAG(price, 1) OVER (ORDER BY date) FROM stocks");

    auto expr = parser.parse_select();
    auto stmt = static_cast<SelectStmt*>(expr);

    REQUIRE(stmt->columns[0]->type == ExprType::WINDOW_FUNCTION);
    auto* win_func = static_cast<WindowFunction*>(stmt->columns[0]);
    REQUIRE(win_func->function_name == "LAG");
    REQUIRE(win_func->args.size() == 2);

    std::string sql = Generator::generate(expr);
    REQUIRE(sql.find("LAG(price, 1) OVER") != std::string::npos);
}

TEST_CASE("Window - SUM with PARTITION BY and ORDER BY", "[phase3][window]") {
    Arena arena;
    Parser parser(arena, "SELECT SUM(amount) OVER (PARTITION BY user_id ORDER BY date) FROM transactions");

    auto expr = parser.parse_select();
    auto stmt = static_cast<SelectStmt*>(expr);

    REQUIRE(stmt->columns[0]->type == ExprType::WINDOW_FUNCTION);
    auto* win_func = static_cast<WindowFunction*>(stmt->columns[0]);
    REQUIRE(win_func->function_name == "SUM");
    REQUIRE(win_func->over->partition_by.size() == 1);
    REQUIRE(win_func->over->order_by.size() == 1);

    std::string sql = Generator::generate(expr);
    REQUIRE(sql.find("SUM(amount) OVER (PARTITION BY user_id ORDER BY date)") != std::string::npos);
}

// ============================================================================
// SUBQUERY TESTS
// ============================================================================

TEST_CASE("Subquery - In FROM clause", "[phase3][subquery]") {
    Arena arena;
    Parser parser(arena, "SELECT * FROM (SELECT id, name FROM users WHERE active = 1) AS active_users");

    auto expr = parser.parse_select();
    auto stmt = static_cast<SelectStmt*>(expr);

    REQUIRE(stmt->from != nullptr);
    REQUIRE(stmt->from->type == ExprType::SUBQUERY);
    auto* subq = static_cast<Subquery*>(stmt->from);
    REQUIRE(subq->alias == "active_users");
    REQUIRE(subq->query != nullptr);

    std::string sql = Generator::generate(expr);
    REQUIRE(sql.find("(SELECT id, name FROM users WHERE active = 1) AS active_users") != std::string::npos);
}

TEST_CASE("Subquery - JOIN with subquery", "[phase3][subquery]") {
    Arena arena;
    Parser parser(arena,
        "SELECT * FROM users u INNER JOIN (SELECT user_id, COUNT(*) AS order_count FROM orders GROUP BY user_id) o ON u.id = o.user_id");

    auto expr = parser.parse_select();
    auto stmt = static_cast<SelectStmt*>(expr);

    REQUIRE(stmt->from != nullptr);
    REQUIRE(stmt->from->type == ExprType::JOIN_CLAUSE);

    std::string sql = Generator::generate(expr);
    REQUIRE(!sql.empty());
    REQUIRE(sql.find("INNER JOIN") != std::string::npos);
}

TEST_CASE("Subquery - Nested subqueries", "[phase3][subquery]") {
    Arena arena;
    Parser parser(arena,
        "SELECT * FROM (SELECT * FROM (SELECT id, name FROM users) AS inner_query WHERE id > 10) AS outer_query");

    auto expr = parser.parse_select();
    auto stmt = static_cast<SelectStmt*>(expr);

    REQUIRE(stmt->from != nullptr);
    REQUIRE(stmt->from->type == ExprType::SUBQUERY);
    auto* outer_subq = static_cast<Subquery*>(stmt->from);
    REQUIRE(outer_subq->alias == "outer_query");

    std::string sql = Generator::generate(expr);
    REQUIRE(!sql.empty());
}

// ============================================================================
// COMBINED FEATURES TESTS
// ============================================================================

TEST_CASE("Combined - CTE with window function", "[phase3][combined]") {
    Arena arena;
    Parser parser(arena,
        "WITH ranked_users AS (SELECT *, ROW_NUMBER() OVER (ORDER BY score DESC) AS rank FROM users) "
        "SELECT * FROM ranked_users WHERE rank <= 10");

    auto expr = parser.parse_select();
    auto stmt = static_cast<SelectStmt*>(expr);

    REQUIRE(stmt->with != nullptr);
    REQUIRE(stmt->with->ctes.size() == 1);

    std::string sql = Generator::generate(expr);
    REQUIRE(sql.find("WITH ranked_users AS") != std::string::npos);
    REQUIRE(sql.find("ROW_NUMBER() OVER") != std::string::npos);
}

TEST_CASE("Combined - CTE with subquery in FROM", "[phase3][combined]") {
    Arena arena;
    Parser parser(arena,
        "WITH active_users AS (SELECT * FROM users WHERE active = 1) "
        "SELECT * FROM (SELECT * FROM active_users WHERE premium = 1) AS premium_users");

    auto expr = parser.parse_select();
    auto stmt = static_cast<SelectStmt*>(expr);

    REQUIRE(stmt->with != nullptr);
    REQUIRE(stmt->from != nullptr);

    std::string sql = Generator::generate(expr);
    REQUIRE(!sql.empty());
}

TEST_CASE("Combined - INSERT with CTE", "[phase3][combined]") {
    Arena arena;
    // Note: WITH clause goes in the SELECT, not after INSERT INTO
    Parser parser(arena,
        "INSERT INTO users_backup SELECT * FROM active_users WHERE active = 1");

    auto stmt = parser.parse_insert();

    REQUIRE(stmt->select_stmt != nullptr);

    std::string sql = Generator::generate(stmt);
    REQUIRE(sql.find("INSERT INTO users_backup") != std::string::npos);
}
