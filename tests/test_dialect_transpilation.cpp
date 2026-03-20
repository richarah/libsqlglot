#include <catch2/catch_test_macros.hpp>
#include <libsqlglot/transpiler.h>
#include <libsqlglot/dialects.h>

using namespace libsqlglot;

// ========================================================================
// PostgreSQL → Other Dialects
// ========================================================================

TEST_CASE("Transpile: PostgreSQL → MySQL", "[transpilation][postgres][mysql]") {
    std::string sql = "SELECT * FROM users WHERE active = TRUE LIMIT 10";
    std::string output = Transpiler::transpile(sql, Dialect::PostgreSQL, Dialect::MySQL);

    REQUIRE(!output.empty());
    REQUIRE(output.find("SELECT") != std::string::npos);
    REQUIRE(output.find("LIMIT") != std::string::npos);
}

TEST_CASE("Transpile: PostgreSQL → SQL Server (LIMIT to TOP)", "[transpilation][postgres][sqlserver]") {
    std::string sql = "SELECT * FROM users LIMIT 10";

    Arena arena;
    Parser parser(arena, sql);
    auto stmt = parser.parse_select();
    std::string output = Generator::generate(stmt, Dialect::SQLServer);

    REQUIRE(output.find("TOP") != std::string::npos);
    REQUIRE(output.find("LIMIT") == std::string::npos);
}

TEST_CASE("Transpile: PostgreSQL → BigQuery", "[transpilation][postgres][bigquery]") {
    std::string sql = "SELECT id, name FROM users WHERE score > 100";
    std::string output = Transpiler::transpile(sql, Dialect::PostgreSQL, Dialect::BigQuery);

    REQUIRE(!output.empty());
    REQUIRE(output.find("SELECT") != std::string::npos);
}

TEST_CASE("Transpile: PostgreSQL → DuckDB", "[transpilation][postgres][duckdb]") {
    std::string sql = "SELECT * FROM users ORDER BY created_at DESC LIMIT 20";
    std::string output = Transpiler::transpile(sql, Dialect::PostgreSQL, Dialect::DuckDB);

    REQUIRE(!output.empty());
    REQUIRE(output.find("LIMIT") != std::string::npos);
}

TEST_CASE("Transpile: PostgreSQL → Snowflake", "[transpilation][postgres][snowflake]") {
    std::string sql = "SELECT COUNT(*) FROM orders WHERE status = 'completed'";
    std::string output = Transpiler::transpile(sql, Dialect::PostgreSQL, Dialect::Snowflake);

    REQUIRE(!output.empty());
    REQUIRE(output.find("COUNT") != std::string::npos);
}

// ========================================================================
// MySQL → Other Dialects
// ========================================================================

TEST_CASE("Transpile: MySQL → PostgreSQL", "[transpilation][mysql][postgres]") {
    std::string sql = "SELECT * FROM users LIMIT 10";
    std::string output = Transpiler::transpile(sql, Dialect::MySQL, Dialect::PostgreSQL);

    REQUIRE(!output.empty());
    REQUIRE(output.find("LIMIT") != std::string::npos);
}

TEST_CASE("Transpile: MySQL → SQL Server (LIMIT to TOP)", "[transpilation][mysql][sqlserver]") {
    std::string sql = "SELECT * FROM products LIMIT 5";

    Arena arena;
    Parser parser(arena, sql);
    auto stmt = parser.parse_select();
    std::string output = Generator::generate(stmt, Dialect::SQLServer);

    REQUIRE(output.find("TOP") != std::string::npos);
    REQUIRE(output.find("LIMIT") == std::string::npos);
}

TEST_CASE("Transpile: MySQL → BigQuery", "[transpilation][mysql][bigquery]") {
    std::string sql = "SELECT user_id, SUM(amount) as total FROM transactions GROUP BY user_id";
    std::string output = Transpiler::transpile(sql, Dialect::MySQL, Dialect::BigQuery);

    REQUIRE(!output.empty());
    REQUIRE(output.find("SUM") != std::string::npos);
    REQUIRE(output.find("GROUP BY") != std::string::npos);
}

TEST_CASE("Transpile: MySQL → DuckDB", "[transpilation][mysql][duckdb]") {
    std::string sql = "SELECT * FROM sales WHERE sale_date >= '2024-01-01'";
    std::string output = Transpiler::transpile(sql, Dialect::MySQL, Dialect::DuckDB);

    REQUIRE(!output.empty());
    REQUIRE(output.find("SELECT") != std::string::npos);
}

// ========================================================================
// SQL Server → Other Dialects
// ========================================================================

TEST_CASE("Transpile: SQL Server → PostgreSQL", "[transpilation][sqlserver][postgres]") {
    std::string sql = "SELECT * FROM users WHERE id IN (1, 2, 3)";

    Arena arena;
    Parser parser(arena, sql);
    auto stmt = parser.parse_select();
    std::string output = Generator::generate(stmt, Dialect::PostgreSQL);

    REQUIRE(!output.empty());
    REQUIRE(output.find("SELECT") != std::string::npos);
}

TEST_CASE("Transpile: SQL Server → MySQL", "[transpilation][sqlserver][mysql]") {
    std::string sql = "SELECT COUNT(*) FROM orders";

    Arena arena;
    Parser parser(arena, sql);
    auto stmt = parser.parse_select();
    std::string output = Generator::generate(stmt, Dialect::MySQL);

    REQUIRE(!output.empty());
    REQUIRE(output.find("COUNT") != std::string::npos);
}

// ========================================================================
// BigQuery → Other Dialects
// ========================================================================

TEST_CASE("Transpile: BigQuery → PostgreSQL", "[transpilation][bigquery][postgres]") {
    std::string sql = "SELECT * FROM users LIMIT 50";
    std::string output = Transpiler::transpile(sql, Dialect::BigQuery, Dialect::PostgreSQL);

    REQUIRE(!output.empty());
    REQUIRE(output.find("LIMIT") != std::string::npos);
}

TEST_CASE("Transpile: BigQuery → MySQL", "[transpilation][bigquery][mysql]") {
    std::string sql = "SELECT user_id, name FROM users WHERE active = TRUE";

    Arena arena;
    Parser parser(arena, sql);
    auto stmt = parser.parse_select();
    std::string output = Generator::generate(stmt, Dialect::MySQL);

    REQUIRE(!output.empty());
    REQUIRE(output.find("SELECT") != std::string::npos);
}

// ========================================================================
// Snowflake → Other Dialects
// ========================================================================

TEST_CASE("Transpile: Snowflake → PostgreSQL", "[transpilation][snowflake][postgres]") {
    std::string sql = "SELECT * FROM products ORDER BY price DESC";
    std::string output = Transpiler::transpile(sql, Dialect::Snowflake, Dialect::PostgreSQL);

    REQUIRE(!output.empty());
    REQUIRE(output.find("ORDER BY") != std::string::npos);
}

TEST_CASE("Transpile: Snowflake → DuckDB", "[transpilation][snowflake][duckdb]") {
    std::string sql = "SELECT region, COUNT(*) as cnt FROM sales GROUP BY region";
    std::string output = Transpiler::transpile(sql, Dialect::Snowflake, Dialect::DuckDB);

    REQUIRE(!output.empty());
    REQUIRE(output.find("COUNT") != std::string::npos);
}

// ========================================================================
// DuckDB → Other Dialects
// ========================================================================

TEST_CASE("Transpile: DuckDB → PostgreSQL", "[transpilation][duckdb][postgres]") {
    std::string sql = "SELECT * FROM events WHERE event_timestamp > '2024-01-01'";
    std::string output = Transpiler::transpile(sql, Dialect::DuckDB, Dialect::PostgreSQL);

    REQUIRE(!output.empty());
    REQUIRE(output.find("SELECT") != std::string::npos);
}

TEST_CASE("Transpile: DuckDB → MySQL", "[transpilation][duckdb][mysql]") {
    std::string sql = "SELECT id, name FROM users LIMIT 100";
    std::string output = Transpiler::transpile(sql, Dialect::DuckDB, Dialect::MySQL);

    REQUIRE(!output.empty());
    REQUIRE(output.find("LIMIT") != std::string::npos);
}

// ========================================================================
// Complex Queries Across Dialects
// ========================================================================

TEST_CASE("Transpile: Complex CTE query across dialects", "[transpilation][complex]") {
    std::string sql = R"(
        WITH regional_sales AS (
            SELECT region, SUM(amount) as total
            FROM sales
            GROUP BY region
        )
        SELECT * FROM regional_sales WHERE total > 10000
    )";

    // Test multiple target dialects
    std::string pg = Transpiler::transpile(sql, Dialect::PostgreSQL, Dialect::PostgreSQL);
    std::string mysql = Transpiler::transpile(sql, Dialect::PostgreSQL, Dialect::MySQL);
    std::string bigquery = Transpiler::transpile(sql, Dialect::PostgreSQL, Dialect::BigQuery);

    REQUIRE(!pg.empty());
    REQUIRE(!mysql.empty());
    REQUIRE(!bigquery.empty());

    REQUIRE(pg.find("WITH") != std::string::npos);
    REQUIRE(mysql.find("WITH") != std::string::npos);
    REQUIRE(bigquery.find("WITH") != std::string::npos);
}

TEST_CASE("Transpile: Window functions across dialects", "[transpilation][complex]") {
    std::string sql = R"(
        SELECT
            user_id,
            ROW_NUMBER() OVER (ORDER BY score DESC) as rank
        FROM leaderboard
    )";

    Arena arena1, arena2, arena3;

    Parser parser1(arena1, sql);
    auto stmt1 = parser1.parse_select();
    std::string pg = Generator::generate(stmt1, Dialect::PostgreSQL);

    Parser parser2(arena2, sql);
    auto stmt2 = parser2.parse_select();
    std::string bigquery = Generator::generate(stmt2, Dialect::BigQuery);

    Parser parser3(arena3, sql);
    auto stmt3 = parser3.parse_select();
    std::string snowflake = Generator::generate(stmt3, Dialect::Snowflake);

    REQUIRE(pg.find("ROW_NUMBER") != std::string::npos);
    REQUIRE(bigquery.find("ROW_NUMBER") != std::string::npos);
    REQUIRE(snowflake.find("ROW_NUMBER") != std::string::npos);
}

TEST_CASE("Transpile: JOIN queries across dialects", "[transpilation][complex]") {
    std::string sql = R"(
        SELECT u.id, u.name, o.total
        FROM users u
        INNER JOIN orders o ON u.id = o.user_id
        WHERE o.status = 'completed'
    )";

    std::string mysql = Transpiler::transpile(sql, Dialect::MySQL, Dialect::MySQL);
    std::string postgres = Transpiler::transpile(sql, Dialect::MySQL, Dialect::PostgreSQL);
    std::string duckdb = Transpiler::transpile(sql, Dialect::MySQL, Dialect::DuckDB);

    REQUIRE(!mysql.empty());
    REQUIRE(!postgres.empty());
    REQUIRE(!duckdb.empty());

    REQUIRE(mysql.find("INNER JOIN") != std::string::npos);
    REQUIRE(postgres.find("INNER JOIN") != std::string::npos);
    REQUIRE(duckdb.find("INNER JOIN") != std::string::npos);
}

// ========================================================================
// Boolean Literal Transformations
// ========================================================================

TEST_CASE("Transpile: Boolean TRUE to PostgreSQL", "[transpilation][boolean]") {
    std::string sql = "SELECT * FROM users WHERE active = TRUE";

    Arena arena;
    Parser parser(arena, sql);
    auto stmt = parser.parse_select();
    std::string output = Generator::generate(stmt, Dialect::PostgreSQL);

    REQUIRE(output.find("TRUE") != std::string::npos);
}

TEST_CASE("Transpile: Boolean TRUE to SQL Server", "[transpilation][boolean]") {
    std::string sql = "SELECT * FROM users WHERE active = TRUE";

    Arena arena;
    Parser parser(arena, sql);
    auto stmt = parser.parse_select();
    std::string output = Generator::generate(stmt, Dialect::SQLServer);

    // SQL Server converts TRUE to 1
    REQUIRE(output.find("= 1") != std::string::npos);
}

// ========================================================================
// Round-trip Verification
// ========================================================================

TEST_CASE("Transpile: Round-trip preserves semantics", "[transpilation][roundtrip]") {
    std::string original = "SELECT id, name FROM users WHERE score > 100 LIMIT 50";

    // PostgreSQL → MySQL → PostgreSQL
    std::string mysql_version = Transpiler::transpile(original, Dialect::PostgreSQL, Dialect::MySQL);
    std::string back_to_pg = Transpiler::transpile(mysql_version, Dialect::MySQL, Dialect::PostgreSQL);

    // Both should contain the same semantic elements
    REQUIRE(back_to_pg.find("SELECT") != std::string::npos);
    REQUIRE(back_to_pg.find("WHERE") != std::string::npos);
    REQUIRE(back_to_pg.find("LIMIT") != std::string::npos);
}

// ========================================================================
// Multi-target Generation (Parse Once, Generate Many)
// ========================================================================

TEST_CASE("Transpile: Single parse, multiple targets", "[transpilation][multitarget]") {
    std::string sql = "SELECT name, email FROM users WHERE age >= 18";

    Arena arena;
    auto ast = Transpiler::parse(arena, sql);

    // Generate for multiple dialects from single AST
    std::string pg = Generator::generate(ast, Dialect::PostgreSQL);
    std::string mysql = Generator::generate(ast, Dialect::MySQL);
    std::string bigquery = Generator::generate(ast, Dialect::BigQuery);
    std::string duckdb = Generator::generate(ast, Dialect::DuckDB);
    std::string snowflake = Generator::generate(ast, Dialect::Snowflake);

    // All should be valid and non-empty
    REQUIRE(!pg.empty());
    REQUIRE(!mysql.empty());
    REQUIRE(!bigquery.empty());
    REQUIRE(!duckdb.empty());
    REQUIRE(!snowflake.empty());

    // All should contain core SELECT elements
    REQUIRE(pg.find("SELECT") != std::string::npos);
    REQUIRE(mysql.find("SELECT") != std::string::npos);
    REQUIRE(bigquery.find("SELECT") != std::string::npos);
    REQUIRE(duckdb.find("SELECT") != std::string::npos);
    REQUIRE(snowflake.find("SELECT") != std::string::npos);
}

// ========================================================================
// ILIKE Transformation
// ========================================================================

TEST_CASE("Transpile: ILIKE native support (PostgreSQL)", "[transpilation][ilike]") {
    std::string sql = "SELECT * FROM users WHERE name ILIKE 'john%'";

    Arena arena;
    Parser parser(arena, sql);
    auto stmt = parser.parse_select();
    std::string output = Generator::generate(stmt, Dialect::PostgreSQL);

    // PostgreSQL supports ILIKE natively
    REQUIRE(output.find("ILIKE") != std::string::npos);
}

TEST_CASE("Transpile: ILIKE polyfill (MySQL)", "[transpilation][ilike]") {
    std::string sql = "SELECT * FROM users WHERE name ILIKE 'john%'";

    Arena arena;
    Parser parser(arena, sql);
    auto stmt = parser.parse_select();
    std::string output = Generator::generate(stmt, Dialect::MySQL);

    // MySQL should transform ILIKE
    REQUIRE(output.find("LOWER") != std::string::npos);
    REQUIRE(output.find("LIKE") != std::string::npos);
}
