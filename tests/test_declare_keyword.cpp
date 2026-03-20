#include <catch2/catch_test_macros.hpp>
#include <libsqlglot/parser.h>
#include <libsqlglot/generator.h>
#include <libsqlglot/arena.h>
#include <libsqlglot/keywords.h>

using namespace libsqlglot;

TEST_CASE("DECLARE keyword lookup", "[keywords][declare]") {
    // Test DECLARE keyword lookup
    TokenType result = KeywordLookup::lookup("DECLARE");
    REQUIRE(result == TokenType::DECLARE);
}

TEST_CASE("DECLARE simple variable", "[parser][declare]") {
    Arena arena;
    Parser parser(arena, "DECLARE x INTEGER");

    auto expr = parser.parse();
    REQUIRE(expr != nullptr);
    REQUIRE(expr->type == ExprType::DECLARE_VAR);

    auto* decl = static_cast<DeclareStmt*>(expr);
    REQUIRE(decl->variable_name == "x");
    REQUIRE(decl->type == "INTEGER");
    REQUIRE(decl->default_value == nullptr);

    // Test generation
    std::string sql = Generator::generate(expr);
    REQUIRE(sql == "DECLARE x INTEGER");
}

TEST_CASE("DECLARE with parameterized type", "[parser][declare]") {
    Arena arena;
    Parser parser(arena, "DECLARE name VARCHAR(255)");

    auto expr = parser.parse();
    REQUIRE(expr != nullptr);
    REQUIRE(expr->type == ExprType::DECLARE_VAR);

    auto* decl = static_cast<DeclareStmt*>(expr);
    REQUIRE(decl->variable_name == "name");
    REQUIRE(decl->type == "VARCHAR(255)");
    REQUIRE(decl->default_value == nullptr);

    // Test generation
    std::string sql = Generator::generate(expr);
    REQUIRE(sql == "DECLARE name VARCHAR(255)");
}

TEST_CASE("DECLARE with DEFAULT value", "[parser][declare]") {
    Arena arena;
    Parser parser(arena, "DECLARE count INTEGER DEFAULT 0");

    auto expr = parser.parse();
    REQUIRE(expr != nullptr);
    REQUIRE(expr->type == ExprType::DECLARE_VAR);

    auto* decl = static_cast<DeclareStmt*>(expr);
    REQUIRE(decl->variable_name == "count");
    REQUIRE(decl->type == "INTEGER");
    REQUIRE(decl->default_value != nullptr);

    // Test generation
    std::string sql = Generator::generate(expr);
    REQUIRE(sql == "DECLARE count INTEGER DEFAULT 0");
}

TEST_CASE("DECLARE with complex DEFAULT expression", "[parser][declare]") {
    Arena arena;
    Parser parser(arena, "DECLARE total DECIMAL(10,2) DEFAULT 100.50");

    auto expr = parser.parse();
    REQUIRE(expr != nullptr);
    REQUIRE(expr->type == ExprType::DECLARE_VAR);

    auto* decl = static_cast<DeclareStmt*>(expr);
    REQUIRE(decl->variable_name == "total");
    REQUIRE(decl->type == "DECIMAL(10,2)");
    REQUIRE(decl->default_value != nullptr);

    // Test generation
    std::string sql = Generator::generate(expr);
    REQUIRE(sql == "DECLARE total DECIMAL(10,2) DEFAULT 100.50");
}
