#include <catch2/catch_test_macros.hpp>
#include <libsqlglot/parser.h>
#include <libsqlglot/generator.h>

using namespace libsqlglot;

// ============================================================================
// INSERT TESTS
// ============================================================================

TEST_CASE("INSERT - Simple VALUES", "[phase3][insert]") {
    Arena arena;
    Parser parser(arena, "INSERT INTO users (name, email) VALUES ('Alice', 'alice@example.com')");

    auto stmt = parser.parse_insert();

    REQUIRE(stmt != nullptr);
    REQUIRE(stmt->table != nullptr);
    REQUIRE(stmt->table->table == "users");
    REQUIRE(stmt->columns.size() == 2);
    REQUIRE(stmt->columns[0] == "name");
    REQUIRE(stmt->columns[1] == "email");
    REQUIRE(stmt->values.size() == 1);
    REQUIRE(stmt->values[0].size() == 2);

    std::string sql = Generator::generate(stmt);
    REQUIRE(sql == "INSERT INTO users (name, email) VALUES ('Alice', 'alice@example.com')");
}

TEST_CASE("INSERT - Multiple rows", "[phase3][insert]") {
    Arena arena;
    Parser parser(arena,
        "INSERT INTO users (name, age) VALUES ('Alice', 25), ('Bob', 30), ('Charlie', 35)");

    auto stmt = parser.parse_insert();

    REQUIRE(stmt->values.size() == 3);
    REQUIRE(stmt->values[0].size() == 2);
    REQUIRE(stmt->values[1].size() == 2);
    REQUIRE(stmt->values[2].size() == 2);

    std::string sql = Generator::generate(stmt);
    REQUIRE(sql == "INSERT INTO users (name, age) VALUES ('Alice', 25), ('Bob', 30), ('Charlie', 35)");
}

TEST_CASE("INSERT - SELECT subquery", "[phase3][insert]") {
    Arena arena;
    Parser parser(arena, "INSERT INTO users_backup SELECT * FROM users WHERE active = 1");

    auto stmt = parser.parse_insert();

    REQUIRE(stmt->select_stmt != nullptr);
    REQUIRE(stmt->values.empty());

    std::string sql = Generator::generate(stmt);
    REQUIRE(sql == "INSERT INTO users_backup SELECT * FROM users WHERE active = 1");
}

TEST_CASE("INSERT - Without column list", "[phase3][insert]") {
    Arena arena;
    Parser parser(arena, "INSERT INTO users VALUES (1, 'Alice', 'alice@example.com')");

    auto stmt = parser.parse_insert();

    REQUIRE(stmt->columns.empty());
    REQUIRE(stmt->values.size() == 1);

    std::string sql = Generator::generate(stmt);
    REQUIRE(sql == "INSERT INTO users VALUES (1, 'Alice', 'alice@example.com')");
}

// ============================================================================
// UPDATE TESTS
// ============================================================================

TEST_CASE("UPDATE - Simple SET", "[phase3][update]") {
    Arena arena;
    Parser parser(arena, "UPDATE users SET name = 'Bob', age = 30 WHERE id = 1");

    auto stmt = parser.parse_update();

    REQUIRE(stmt != nullptr);
    REQUIRE(stmt->table->table == "users");
    REQUIRE(stmt->assignments.size() == 2);
    REQUIRE(stmt->assignments[0].first == "name");
    REQUIRE(stmt->assignments[1].first == "age");
    REQUIRE(stmt->where != nullptr);

    std::string sql = Generator::generate(stmt);
    REQUIRE(sql == "UPDATE users SET name = 'Bob', age = 30 WHERE id = 1");
}

TEST_CASE("UPDATE - Without WHERE", "[phase3][update]") {
    Arena arena;
    Parser parser(arena, "UPDATE products SET price = 19.99");

    auto stmt = parser.parse_update();

    REQUIRE(stmt->assignments.size() == 1);
    REQUIRE(stmt->where == nullptr);

    std::string sql = Generator::generate(stmt);
    REQUIRE(sql == "UPDATE products SET price = 19.99");
}

TEST_CASE("UPDATE - With FROM clause (PostgreSQL)", "[phase3][update]") {
    Arena arena;
    Parser parser(arena, "UPDATE orders SET status = 'shipped' FROM users WHERE orders.user_id = users.id");

    auto stmt = parser.parse_update();

    REQUIRE(stmt->from != nullptr);
    REQUIRE(stmt->where != nullptr);

    std::string sql = Generator::generate(stmt);
    REQUIRE(!sql.empty());
}

// ============================================================================
// DELETE TESTS
// ============================================================================

TEST_CASE("DELETE - Simple WHERE", "[phase3][delete]") {
    Arena arena;
    Parser parser(arena, "DELETE FROM users WHERE age < 18");

    auto stmt = parser.parse_delete();

    REQUIRE(stmt != nullptr);
    REQUIRE(stmt->table->table == "users");
    REQUIRE(stmt->where != nullptr);

    std::string sql = Generator::generate(stmt);
    REQUIRE(sql == "DELETE FROM users WHERE age < 18");
}

TEST_CASE("DELETE - Without WHERE", "[phase3][delete]") {
    Arena arena;
    Parser parser(arena, "DELETE FROM temp_table");

    auto stmt = parser.parse_delete();

    REQUIRE(stmt->where == nullptr);

    std::string sql = Generator::generate(stmt);
    REQUIRE(sql == "DELETE FROM temp_table");
}

TEST_CASE("DELETE - With USING clause", "[phase3][delete]") {
    Arena arena;
    Parser parser(arena, "DELETE FROM orders USING users WHERE orders.user_id = users.id");

    auto stmt = parser.parse_delete();

    REQUIRE(stmt->using_clause != nullptr);
    REQUIRE(stmt->where != nullptr);

    std::string sql = Generator::generate(stmt);
    REQUIRE(!sql.empty());
}

// ============================================================================
// CREATE TABLE TESTS
// ============================================================================

TEST_CASE("CREATE TABLE - Simple definition", "[phase3][create]") {
    Arena arena;
    Parser parser(arena, "CREATE TABLE users (id INTEGER PRIMARY KEY, name VARCHAR, email VARCHAR UNIQUE)");

    auto stmt = parser.parse_create_table();

    REQUIRE(stmt != nullptr);
    REQUIRE(stmt->table->table == "users");
    REQUIRE(stmt->columns.size() == 3);
    REQUIRE(stmt->columns[0].name == "id");
    REQUIRE(stmt->columns[0].type == "INTEGER");
    REQUIRE(stmt->columns[0].primary_key == true);
    REQUIRE(stmt->columns[1].name == "name");
    REQUIRE(stmt->columns[2].unique == true);

    std::string sql = Generator::generate(stmt);
    REQUIRE(sql.find("CREATE TABLE users") != std::string::npos);
    REQUIRE(sql.find("id INTEGER PRIMARY KEY") != std::string::npos);
}

TEST_CASE("CREATE TABLE - IF NOT EXISTS", "[phase3][create]") {
    Arena arena;
    Parser parser(arena, "CREATE TABLE IF NOT EXISTS products (id INTEGER, name VARCHAR)");

    auto stmt = parser.parse_create_table();

    REQUIRE(stmt->if_not_exists == true);

    std::string sql = Generator::generate(stmt);
    REQUIRE(sql.find("IF NOT EXISTS") != std::string::npos);
}

TEST_CASE("CREATE TABLE - AS SELECT", "[phase3][create]") {
    Arena arena;
    Parser parser(arena, "CREATE TABLE users_backup AS SELECT * FROM users WHERE active = 1");

    auto stmt = parser.parse_create_table();

    REQUIRE(stmt->as_select != nullptr);
    REQUIRE(stmt->columns.empty());

    std::string sql = Generator::generate(stmt);
    REQUIRE(sql == "CREATE TABLE users_backup AS SELECT * FROM users WHERE active = 1");
}

TEST_CASE("CREATE TABLE - NOT NULL and DEFAULT", "[phase3][create]") {
    Arena arena;
    Parser parser(arena, "CREATE TABLE users (id INTEGER PRIMARY KEY, name VARCHAR NOT NULL, status VARCHAR DEFAULT 'active')");

    auto stmt = parser.parse_create_table();

    REQUIRE(stmt->columns.size() == 3);
    REQUIRE(stmt->columns[1].not_null == true);
    REQUIRE(stmt->columns[2].default_value != nullptr);

    std::string sql = Generator::generate(stmt);
    REQUIRE(sql.find("NOT NULL") != std::string::npos);
    REQUIRE(sql.find("DEFAULT") != std::string::npos);
}
