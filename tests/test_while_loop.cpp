#include <catch2/catch_test_macros.hpp>
#include <libsqlglot/parser.h>
#include <libsqlglot/generator.h>
#include <libsqlglot/arena.h>
#include <libsqlglot/keywords.h>

using namespace libsqlglot;

TEST_CASE("WHILE keyword lookup", "[keywords][while]") {
    REQUIRE(KeywordLookup::lookup("WHILE") == TokenType::WHILE);
    REQUIRE(KeywordLookup::lookup("DO") == TokenType::DO);
    REQUIRE(KeywordLookup::lookup("ENDWHILE") == TokenType::ENDWHILE);
}

TEST_CASE("Simple WHILE DO END WHILE", "[parser][while]") {
    Arena arena;
    Parser parser(arena, "WHILE x < 10 DO RETURN x END WHILE");

    auto expr = parser.parse();
    REQUIRE(expr != nullptr);
    REQUIRE(expr->type == ExprType::WHILE_LOOP);

    auto* while_loop = static_cast<WhileLoop*>(expr);
    REQUIRE(while_loop->condition != nullptr);
    REQUIRE(while_loop->body.size() == 1);

    // Test generation
    std::string sql = Generator::generate(expr);
    REQUIRE(sql == "WHILE x < 10 DO RETURN x END WHILE");
}

TEST_CASE("WHILE with ENDWHILE (single token)", "[parser][while]") {
    Arena arena;
    Parser parser(arena, "WHILE count > 0 DO RETURN count ENDWHILE");

    auto expr = parser.parse();
    REQUIRE(expr != nullptr);
    REQUIRE(expr->type == ExprType::WHILE_LOOP);

    auto* while_loop = static_cast<WhileLoop*>(expr);
    REQUIRE(while_loop->condition != nullptr);
    REQUIRE(while_loop->body.size() == 1);

    // Test generation (always outputs END WHILE)
    std::string sql = Generator::generate(expr);
    REQUIRE(sql == "WHILE count > 0 DO RETURN count END WHILE");
}

TEST_CASE("WHILE with multiple statements", "[parser][while]") {
    Arena arena;
    Parser parser(arena, "WHILE i < 100 DO DECLARE temp INTEGER; RETURN temp END WHILE");

    auto expr = parser.parse();
    REQUIRE(expr != nullptr);
    REQUIRE(expr->type == ExprType::WHILE_LOOP);

    auto* while_loop = static_cast<WhileLoop*>(expr);
    REQUIRE(while_loop->condition != nullptr);
    REQUIRE(while_loop->body.size() == 2);

    // Test generation
    std::string sql = Generator::generate(expr);
    REQUIRE(sql == "WHILE i < 100 DO DECLARE temp INTEGER RETURN temp END WHILE");
}

TEST_CASE("WHILE with complex condition", "[parser][while]") {
    Arena arena;
    Parser parser(arena, "WHILE x > 0 AND y < 100 DO RETURN x + y END WHILE");

    auto expr = parser.parse();
    REQUIRE(expr != nullptr);
    REQUIRE(expr->type == ExprType::WHILE_LOOP);

    auto* while_loop = static_cast<WhileLoop*>(expr);
    REQUIRE(while_loop->condition != nullptr);
    REQUIRE(while_loop->body.size() == 1);

    // Test generation
    std::string sql = Generator::generate(expr);
    REQUIRE(sql == "WHILE x > 0 AND y < 100 DO RETURN x + y END WHILE");
}
