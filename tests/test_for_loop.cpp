#include <catch2/catch_test_macros.hpp>
#include <libsqlglot/parser.h>
#include <libsqlglot/generator.h>
#include <libsqlglot/arena.h>
#include <libsqlglot/keywords.h>

using namespace libsqlglot;

TEST_CASE("FOR keyword lookup", "[keywords][for]") {
    REQUIRE(KeywordLookup::lookup("FOR") == TokenType::FOR);
    REQUIRE(KeywordLookup::lookup("IN") == TokenType::IN);
    REQUIRE(KeywordLookup::lookup("LOOP") == TokenType::LOOP);
    REQUIRE(KeywordLookup::lookup("ENDLOOP") == TokenType::ENDLOOP);
}

TEST_CASE("Simple FOR loop", "[parser][for]") {
    Arena arena;
    Parser parser(arena, "FOR i IN 1..10 LOOP RETURN i END LOOP");

    auto expr = parser.parse();
    REQUIRE(expr != nullptr);
    REQUIRE(expr->type == ExprType::FOR_LOOP);

    auto* for_loop = static_cast<ForLoop*>(expr);
    REQUIRE(for_loop->variable == "i");
    REQUIRE(for_loop->start_value != nullptr);
    REQUIRE(for_loop->end_value != nullptr);
    REQUIRE(for_loop->body.size() == 1);

    // Test generation
    std::string sql = Generator::generate(expr);
    REQUIRE(sql == "FOR i IN 1..10 LOOP RETURN i END LOOP");
}

TEST_CASE("FOR loop with ENDLOOP (single token)", "[parser][for]") {
    Arena arena;
    Parser parser(arena, "FOR counter IN 0..99 LOOP RETURN counter ENDLOOP");

    auto expr = parser.parse();
    REQUIRE(expr != nullptr);
    REQUIRE(expr->type == ExprType::FOR_LOOP);

    auto* for_loop = static_cast<ForLoop*>(expr);
    REQUIRE(for_loop->variable == "counter");
    REQUIRE(for_loop->start_value != nullptr);
    REQUIRE(for_loop->end_value != nullptr);
    REQUIRE(for_loop->body.size() == 1);

    // Test generation (always outputs END LOOP)
    std::string sql = Generator::generate(expr);
    REQUIRE(sql == "FOR counter IN 0..99 LOOP RETURN counter END LOOP");
}

TEST_CASE("FOR loop with multiple statements", "[parser][for]") {
    Arena arena;
    Parser parser(arena, "FOR idx IN 1..100 LOOP DECLARE temp INTEGER; RETURN temp END LOOP");

    auto expr = parser.parse();
    REQUIRE(expr != nullptr);
    REQUIRE(expr->type == ExprType::FOR_LOOP);

    auto* for_loop = static_cast<ForLoop*>(expr);
    REQUIRE(for_loop->variable == "idx");
    REQUIRE(for_loop->start_value != nullptr);
    REQUIRE(for_loop->end_value != nullptr);
    REQUIRE(for_loop->body.size() == 2);

    // Test generation
    std::string sql = Generator::generate(expr);
    REQUIRE(sql == "FOR idx IN 1..100 LOOP DECLARE temp INTEGER RETURN temp END LOOP");
}

TEST_CASE("FOR loop with expressions", "[parser][for]") {
    Arena arena;
    Parser parser(arena, "FOR x IN start_val..end_val LOOP RETURN x * 2 END LOOP");

    auto expr = parser.parse();
    REQUIRE(expr != nullptr);
    REQUIRE(expr->type == ExprType::FOR_LOOP);

    auto* for_loop = static_cast<ForLoop*>(expr);
    REQUIRE(for_loop->variable == "x");
    REQUIRE(for_loop->start_value != nullptr);
    REQUIRE(for_loop->end_value != nullptr);
    REQUIRE(for_loop->body.size() == 1);

    // Test generation
    std::string sql = Generator::generate(expr);
    REQUIRE(sql == "FOR x IN start_val..end_val LOOP RETURN x * 2 END LOOP");
}

TEST_CASE("Nested FOR and WHILE loops", "[parser][for][while]") {
    Arena arena;
    Parser parser(arena, "FOR i IN 1..10 LOOP WHILE i > 0 DO RETURN i END WHILE END LOOP");

    auto expr = parser.parse();
    REQUIRE(expr != nullptr);
    REQUIRE(expr->type == ExprType::FOR_LOOP);

    auto* for_loop = static_cast<ForLoop*>(expr);
    REQUIRE(for_loop->variable == "i");
    REQUIRE(for_loop->body.size() == 1);
    REQUIRE(for_loop->body[0]->type == ExprType::WHILE_LOOP);

    // Test generation
    std::string sql = Generator::generate(expr);
    REQUIRE(sql == "FOR i IN 1..10 LOOP WHILE i > 0 DO RETURN i END WHILE END LOOP");
}

TEST_CASE("FOR loop with IF statement", "[parser][for][if]") {
    Arena arena;
    Parser parser(arena, "FOR n IN 1..20 LOOP IF n > 10 THEN RETURN n END IF END LOOP");

    auto expr = parser.parse();
    REQUIRE(expr != nullptr);
    REQUIRE(expr->type == ExprType::FOR_LOOP);

    auto* for_loop = static_cast<ForLoop*>(expr);
    REQUIRE(for_loop->variable == "n");
    REQUIRE(for_loop->body.size() == 1);
    REQUIRE(for_loop->body[0]->type == ExprType::IF_STMT);

    // Test generation
    std::string sql = Generator::generate(expr);
    REQUIRE(sql == "FOR n IN 1..20 LOOP IF n > 10 THEN RETURN n END IF END LOOP");
}
