#include <catch2/catch_test_macros.hpp>
#include <libsqlglot/transpiler.h>
#include <libsqlglot/dialects.h>

using namespace libsqlglot;

// Test LIMIT syntax transformations
TEST_CASE("Dialect - LIMIT to TOP (SQL Server)", "[dialect]") {
    std::string sql = "SELECT * FROM users LIMIT 10";

    // Parse in ANSI, generate for SQL Server
    Arena arena;
    Parser parser(arena, sql);
    auto stmt = parser.parse_select();

    std::string output = Generator::generate(stmt, Dialect::SQLServer);

    // SQL Server uses TOP instead of LIMIT
    REQUIRE(output.find("TOP") != std::string::npos);
    REQUIRE(output.find("LIMIT") == std::string::npos);
}

TEST_CASE("Dialect - LIMIT to FETCH FIRST (Oracle)", "[dialect]") {
    std::string sql = "SELECT * FROM users LIMIT 10";

    Arena arena;
    Parser parser(arena, sql);
    auto stmt = parser.parse_select();

    std::string output = Generator::generate(stmt, Dialect::Oracle);

    // Oracle uses FETCH FIRST ... ROWS ONLY
    REQUIRE(output.find("FETCH FIRST") != std::string::npos);
    REQUIRE(output.find("ROWS ONLY") != std::string::npos);
}

TEST_CASE("Dialect - LIMIT OFFSET (PostgreSQL)", "[dialect]") {
    std::string sql = "SELECT * FROM users LIMIT 10 OFFSET 5";

    Arena arena;
    Parser parser(arena, sql);
    auto stmt = parser.parse_select();

    std::string output = Generator::generate(stmt, Dialect::PostgreSQL);

    // PostgreSQL keeps LIMIT/OFFSET syntax
    REQUIRE(output.find("LIMIT 10") != std::string::npos);
    REQUIRE(output.find("OFFSET 5") != std::string::npos);
}

// Test boolean literal transformations
TEST_CASE("Dialect - Boolean TRUE/FALSE (PostgreSQL)", "[dialect]") {
    Arena arena;

    auto stmt = arena.create<SelectStmt>();
    stmt->columns.push_back(arena.create<Star>());
    stmt->from = arena.create<TableRef>("users");

    auto active = arena.create<Column>("active");
    auto true_lit = arena.create<Literal>("TRUE");
    stmt->where = arena.create<BinaryOp>(ExprType::EQ, active, true_lit);

    std::string output = Generator::generate(stmt, Dialect::PostgreSQL);

    // PostgreSQL uses TRUE/FALSE
    REQUIRE(output.find("TRUE") != std::string::npos);
}

TEST_CASE("Dialect - Boolean to 1/0 (SQL Server)", "[dialect]") {
    Arena arena;

    auto stmt = arena.create<SelectStmt>();
    stmt->columns.push_back(arena.create<Star>());
    stmt->from = arena.create<TableRef>("users");

    auto active = arena.create<Column>("active");
    auto true_lit = arena.create<Literal>("TRUE");
    stmt->where = arena.create<BinaryOp>(ExprType::EQ, active, true_lit);

    std::string output = Generator::generate(stmt, Dialect::SQLServer);

    // SQL Server uses 1/0 for booleans
    REQUIRE(output.find("= 1") != std::string::npos);
}

// Test ILIKE transformations
TEST_CASE("Dialect - ILIKE native support (PostgreSQL)", "[dialect]") {
    std::string sql = "SELECT * FROM users WHERE name ILIKE 'john%'";

    Arena arena;
    Parser parser(arena, sql);
    auto stmt = parser.parse_select();

    std::string output = Generator::generate(stmt, Dialect::PostgreSQL);

    // PostgreSQL supports ILIKE natively
    REQUIRE(output.find("ILIKE") != std::string::npos);
    REQUIRE(output.find("LOWER") == std::string::npos);
}

TEST_CASE("Dialect - ILIKE polyfill (MySQL)", "[dialect]") {
    std::string sql = "SELECT * FROM users WHERE name ILIKE 'john%'";

    Arena arena;
    Parser parser(arena, sql);
    auto stmt = parser.parse_select();

    std::string output = Generator::generate(stmt, Dialect::MySQL);

    // MySQL doesn't support ILIKE, should transform to LOWER() LIKE LOWER()
    REQUIRE(output.find("LOWER") != std::string::npos);
    REQUIRE(output.find("LIKE") != std::string::npos);
    REQUIRE(output.find("ILIKE") == std::string::npos);
}

TEST_CASE("Dialect - ILIKE polyfill (SQLite)", "[dialect]") {
    std::string sql = "SELECT * FROM users WHERE name ILIKE 'john%'";

    Arena arena;
    Parser parser(arena, sql);
    auto stmt = parser.parse_select();

    std::string output = Generator::generate(stmt, Dialect::SQLite);

    // SQLite doesn't support ILIKE, should transform
    REQUIRE(output.find("LOWER") != std::string::npos);
}

// Test identifier quoting
TEST_CASE("Dialect - Identifier quotes (MySQL)", "[dialect]") {
    auto& features = DialectConfig::get_features(Dialect::MySQL);
    REQUIRE(features.identifier_quote == '`');
}

TEST_CASE("Dialect - Identifier quotes (PostgreSQL)", "[dialect]") {
    auto& features = DialectConfig::get_features(Dialect::PostgreSQL);
    REQUIRE(features.identifier_quote == '"');
}

TEST_CASE("Dialect - Identifier quotes (SQL Server)", "[dialect]") {
    auto& features = DialectConfig::get_features(Dialect::SQLServer);
    REQUIRE(features.identifier_quote == '[');
}

// Test dialect feature flags
TEST_CASE("Dialect - CTE support", "[dialect]") {
    auto& postgres = DialectConfig::get_features(Dialect::PostgreSQL);
    auto& mysql = DialectConfig::get_features(Dialect::MySQL);

    REQUIRE(postgres.supports_cte == true);
    REQUIRE(mysql.supports_cte == true);
}

TEST_CASE("Dialect - Window function support", "[dialect]") {
    auto& postgres = DialectConfig::get_features(Dialect::PostgreSQL);
    auto& bigquery = DialectConfig::get_features(Dialect::BigQuery);

    REQUIRE(postgres.supports_window_functions == true);
    REQUIRE(bigquery.supports_window_functions == true);
}

TEST_CASE("Dialect - QUALIFY support (Snowflake)", "[dialect]") {
    auto& snowflake = DialectConfig::get_features(Dialect::Snowflake);
    auto& postgres = DialectConfig::get_features(Dialect::PostgreSQL);

    REQUIRE(snowflake.supports_qualify == true);
    REQUIRE(postgres.supports_qualify == false);
}

TEST_CASE("Dialect - INTERSECT support", "[dialect]") {
    auto& postgres = DialectConfig::get_features(Dialect::PostgreSQL);
    REQUIRE(postgres.supports_intersect == true);
}

TEST_CASE("Dialect - Array literal support (BigQuery)", "[dialect]") {
    auto& bigquery = DialectConfig::get_features(Dialect::BigQuery);
    auto& mysql = DialectConfig::get_features(Dialect::MySQL);

    REQUIRE(bigquery.supports_array_literals == true);
    REQUIRE(mysql.supports_array_literals == false);
}

// Test end-to-end dialect transpilation
TEST_CASE("Dialect - MySQL to PostgreSQL", "[dialect]") {
    std::string sql = "SELECT * FROM users LIMIT 10";

    std::string output = Transpiler::transpile(sql, Dialect::MySQL, Dialect::PostgreSQL);

    REQUIRE(!output.empty());
    REQUIRE(output.find("SELECT") != std::string::npos);
    REQUIRE(output.find("LIMIT") != std::string::npos);
}

TEST_CASE("Dialect - PostgreSQL to SQL Server", "[dialect]") {
    std::string sql = "SELECT * FROM users LIMIT 10";

    Arena arena;
    Parser parser(arena, sql);
    auto stmt = parser.parse_select();

    std::string output = Generator::generate(stmt, Dialect::SQLServer);

    // Should convert LIMIT to TOP
    REQUIRE(output.find("TOP") != std::string::npos);
}

TEST_CASE("Dialect - SQLite to BigQuery", "[dialect]") {
    std::string sql = "SELECT * FROM users WHERE id IN (1, 2, 3)";

    std::string output = Transpiler::transpile(sql, Dialect::SQLite, Dialect::BigQuery);

    REQUIRE(!output.empty());
    REQUIRE(output.find("SELECT") != std::string::npos);
}

// Test dialect names
TEST_CASE("Dialect - Name lookup", "[dialect]") {
    REQUIRE(DialectConfig::get_name(Dialect::PostgreSQL) == "PostgreSQL");
    REQUIRE(DialectConfig::get_name(Dialect::MySQL) == "MySQL");
    REQUIRE(DialectConfig::get_name(Dialect::SQLServer) == "SQL Server");
    REQUIRE(DialectConfig::get_name(Dialect::BigQuery) == "BigQuery");
    REQUIRE(DialectConfig::get_name(Dialect::Snowflake) == "Snowflake");
    REQUIRE(DialectConfig::get_name(Dialect::DuckDB) == "DuckDB");
    REQUIRE(DialectConfig::get_name(Dialect::ClickHouse) == "ClickHouse");
}

// Test Phase 2 dialects (not yet fully implemented, but framework exists)
TEST_CASE("Dialect - Phase 2 dialect names", "[dialect]") {
    REQUIRE(DialectConfig::get_name(Dialect::Presto) == "Presto");
    REQUIRE(DialectConfig::get_name(Dialect::Trino) == "Trino");
    REQUIRE(DialectConfig::get_name(Dialect::Hive) == "Hive");
    REQUIRE(DialectConfig::get_name(Dialect::Spark) == "Spark");
    REQUIRE(DialectConfig::get_name(Dialect::Athena) == "Athena");
    REQUIRE(DialectConfig::get_name(Dialect::Databricks) == "Databricks");
}

// Test concatenation operator differences
TEST_CASE("Dialect - Concat operator (PostgreSQL)", "[dialect]") {
    auto& postgres = DialectConfig::get_features(Dialect::PostgreSQL);
    REQUIRE(postgres.concat_op == DialectFeatures::ConcatOp::PIPES);
}

TEST_CASE("Dialect - Concat operator (SQL Server)", "[dialect]") {
    auto& sqlserver = DialectConfig::get_features(Dialect::SQLServer);
    REQUIRE(sqlserver.concat_op == DialectFeatures::ConcatOp::PLUS);
}

TEST_CASE("Dialect - Concat operator (MySQL)", "[dialect]") {
    auto& mysql = DialectConfig::get_features(Dialect::MySQL);
    REQUIRE(mysql.concat_op == DialectFeatures::ConcatOp::CONCAT_FUNC);
}
