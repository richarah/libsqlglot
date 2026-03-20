#include <catch2/catch_test_macros.hpp>
#include <libsqlglot/transpiler.h>

using namespace libsqlglot;

TEST_CASE("Transpiler - Simple parse and generate", "[transpiler]") {
    Arena arena;
    std::string sql = "SELECT * FROM users";

    auto expr = Transpiler::parse(arena, sql);
    auto stmt = static_cast<SelectStmt*>(expr);

    REQUIRE(stmt != nullptr);
    REQUIRE(stmt->columns.size() == 1);

    std::string output = Transpiler::generate(expr);
    REQUIRE(output == "SELECT * FROM users");
}

TEST_CASE("Transpiler - Parse, optimize, generate", "[transpiler]") {
    Arena arena;
    std::string sql = "SELECT name FROM users WHERE age > 18";

    auto expr = Transpiler::parse(arena, sql);
    auto stmt = static_cast<SelectStmt*>(expr);
    Transpiler::optimize(arena, stmt);
    std::string output = Transpiler::generate(expr);

    REQUIRE(!output.empty());
}

TEST_CASE("Transpiler - Full transpile API", "[transpiler]") {
    std::string sql = "SELECT id, name FROM users WHERE active = 1";

    std::string output = Transpiler::transpile(sql, Dialect::ANSI, Dialect::ANSI, true);

    REQUIRE(!output.empty());
    REQUIRE(output.find("SELECT") != std::string::npos);
    REQUIRE(output.find("FROM") != std::string::npos);
}

TEST_CASE("Transpiler - Complex query transpilation", "[transpiler]") {
    std::string sql = "SELECT u.id, u.name FROM users u WHERE u.age > 18";

    std::string output = Transpiler::transpile(sql);

    REQUIRE(!output.empty());
}

TEST_CASE("Optimizer - Qualify columns", "[optimizer]") {
    Arena arena;
    Parser parser(arena, "SELECT name FROM users");

    auto expr = parser.parse_select();
    auto stmt = static_cast<SelectStmt*>(expr);
    Optimizer::qualify_columns(stmt);

    // After qualifying, column should have table name
    REQUIRE(stmt->columns.size() == 1);
    auto col = static_cast<Column*>(stmt->columns[0]);
    REQUIRE(col->table == "users");
}

TEST_CASE("Dialect - Identifier quotes", "[dialect]") {
    auto& mysql = DialectConfig::get_features(Dialect::MySQL);
    auto& postgres = DialectConfig::get_features(Dialect::PostgreSQL);

    REQUIRE(mysql.identifier_quote == '`');
    REQUIRE(postgres.identifier_quote == '"');
}

TEST_CASE("Dialect - Feature support", "[dialect]") {
    auto& ansi = DialectConfig::get_features(Dialect::ANSI);
    auto& tsql = DialectConfig::get_features(Dialect::SQLServer);

    REQUIRE(ansi.limit_style == DialectFeatures::LimitStyle::LIMIT_OFFSET);
    REQUIRE(tsql.limit_style == DialectFeatures::LimitStyle::TOP);  // TSQL uses TOP
}

TEST_CASE("Dialect - Names", "[dialect]") {
    REQUIRE(DialectConfig::get_name(Dialect::DuckDB) == "DuckDB");
    REQUIRE(DialectConfig::get_name(Dialect::BigQuery) == "BigQuery");
}
