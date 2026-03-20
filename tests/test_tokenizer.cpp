#include <catch2/catch_test_macros.hpp>
#include <libsqlglot/tokenizer.h>

using namespace libsqlglot;

TEST_CASE("Tokenizer - Basic SELECT", "[tokenizer]") {
    Tokenizer tokenizer("SELECT * FROM users");
    auto tokens = tokenizer.tokenize_all();

    REQUIRE(tokens.size() == 5); // SELECT, *, FROM, users, EOF

    REQUIRE(tokens[0].type == TokenType::SELECT);
    REQUIRE(tokens[1].type == TokenType::STAR);
    REQUIRE(tokens[2].type == TokenType::FROM);
    REQUIRE(tokens[3].type == TokenType::IDENTIFIER);
    REQUIRE(tokens[4].type == TokenType::EOF_TOKEN);
}

TEST_CASE("Tokenizer - WHERE clause", "[tokenizer]") {
    Tokenizer tokenizer("SELECT id FROM users WHERE age > 18");
    auto tokens = tokenizer.tokenize_all();

    REQUIRE(tokens.size() == 9);

    REQUIRE(tokens[0].type == TokenType::SELECT);
    REQUIRE(tokens[1].type == TokenType::IDENTIFIER); // id
    REQUIRE(tokens[2].type == TokenType::FROM);
    REQUIRE(tokens[3].type == TokenType::IDENTIFIER); // users
    REQUIRE(tokens[4].type == TokenType::WHERE);
    REQUIRE(tokens[5].type == TokenType::IDENTIFIER); // age
    REQUIRE(tokens[6].type == TokenType::GT);
    REQUIRE(tokens[7].type == TokenType::NUMBER);
    REQUIRE(tokens[8].type == TokenType::EOF_TOKEN);
}

TEST_CASE("Tokenizer - String literals", "[tokenizer]") {
    Tokenizer tokenizer("SELECT 'hello' AS greeting");
    auto tokens = tokenizer.tokenize_all();

    REQUIRE(tokens.size() == 5);
    REQUIRE(tokens[0].type == TokenType::SELECT);
    REQUIRE(tokens[1].type == TokenType::STRING);
    REQUIRE(tokens[2].type == TokenType::AS);
    REQUIRE(tokens[3].type == TokenType::IDENTIFIER);
    REQUIRE(tokens[4].type == TokenType::EOF_TOKEN);
}

TEST_CASE("Tokenizer - Comments", "[tokenizer]") {
    Tokenizer tokenizer("SELECT -- comment\n* FROM users");
    auto tokens = tokenizer.tokenize_all();

    REQUIRE(tokens.size() == 5);
    REQUIRE(tokens[0].type == TokenType::SELECT);
    REQUIRE(tokens[1].type == TokenType::STAR);
    REQUIRE(tokens[2].type == TokenType::FROM);
}

TEST_CASE("Tokenizer - Numbers", "[tokenizer]") {
    Tokenizer tokenizer("SELECT 123, 456.78, 1.23e10, 0x1F, 0b1010");
    auto tokens = tokenizer.tokenize_all();

    // SELECT, 123, COMMA, 456.78, COMMA, 1.23e10, COMMA, 0x1F, COMMA, 0b1010, EOF
    REQUIRE(tokens.size() == 11);
    REQUIRE(tokens[1].type == TokenType::NUMBER);
    REQUIRE(tokens[3].type == TokenType::NUMBER);
    REQUIRE(tokens[5].type == TokenType::NUMBER);
    REQUIRE(tokens[7].type == TokenType::NUMBER);
    REQUIRE(tokens[9].type == TokenType::NUMBER);
}

TEST_CASE("Tokenizer - JOIN query", "[tokenizer]") {
    Tokenizer tokenizer("SELECT u.name FROM users u JOIN orders o ON u.id = o.user_id");
    auto tokens = tokenizer.tokenize_all();

    REQUIRE(tokens.size() > 10);

    bool found_join = false;
    bool found_on = false;
    for (const auto& tok : tokens) {
        if (tok.type == TokenType::JOIN) found_join = true;
        if (tok.type == TokenType::ON) found_on = true;
    }

    REQUIRE(found_join);
    REQUIRE(found_on);
}

TEST_CASE("Tokenizer - Position tracking", "[tokenizer]") {
    Tokenizer tokenizer("SELECT\nid\nFROM\nusers");
    auto tokens = tokenizer.tokenize_all();

    REQUIRE(tokens.size() == 5);

    // SELECT should be on line 1
    REQUIRE(tokens[0].line == 1);

    // id should be on line 2
    REQUIRE(tokens[1].line == 2);

    // FROM should be on line 3
    REQUIRE(tokens[2].line == 3);

    // users should be on line 4
    REQUIRE(tokens[3].line == 4);
}

TEST_CASE("Tokenizer - Operators", "[tokenizer]") {
    Tokenizer tokenizer("a <> b AND c >= d OR e <= f");
    auto tokens = tokenizer.tokenize_all();

    // a, <>, b, AND, c, >=, d, OR, e, <=, f, EOF = 12 tokens
    REQUIRE(tokens.size() == 12);

    REQUIRE(tokens[1].type == TokenType::NEQ);    // <>
    REQUIRE(tokens[3].type == TokenType::AND);
    REQUIRE(tokens[5].type == TokenType::GTE);    // >=
    REQUIRE(tokens[7].type == TokenType::OR);
    REQUIRE(tokens[9].type == TokenType::LTE);    // <=
    REQUIRE(tokens[11].type == TokenType::EOF_TOKEN);
}
