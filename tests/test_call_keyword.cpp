#include <catch2/catch_test_macros.hpp>
#include <libsqlglot/keywords.h>
#include <libsqlglot/tokenizer.h>
#include <libsqlglot/arena.h>
#include <iostream>

using namespace libsqlglot;

TEST_CASE("CALL keyword lookup", "[keywords][call]") {
    // Calculate hash manually
    const char* text = "CALL";
    char upper[17];
    size_t len = 4;
    for (size_t i = 0; i < len; ++i) {
        char c = text[i];
        upper[i] = (c >= 'a' && c <= 'z') ? (c - 32) : c;
    }
    upper[len] = '\0';

    uint32_t hash = (upper[0] * 31 + upper[len - 1] + len) & 127;
    std::cout << "Manual hash calculation for CALL:" << std::endl;
    std::cout << "  First char: " << upper[0] << " (" << (int)upper[0] << ")" << std::endl;
    std::cout << "  Last char: " << upper[len-1] << " (" << (int)upper[len-1] << ")" << std::endl;
    std::cout << "  Length: " << len << std::endl;
    std::cout << "  Hash: " << hash << std::endl;

    // Test keyword lookup
    TokenType result = KeywordLookup::lookup("CALL");
    std::cout << "KeywordLookup::lookup(\"CALL\") = " << (int)result << std::endl;
    std::cout << "TokenType::CALL = " << (int)TokenType::CALL << std::endl;
    std::cout << "TokenType::LEFT = " << (int)TokenType::LEFT << std::endl;
    std::cout << "TokenType::IDENTIFIER = " << (int)TokenType::IDENTIFIER << std::endl;

    REQUIRE(result == TokenType::CALL);
}

TEST_CASE("CALL keyword tokenization", "[tokenizer][call]") {
    Arena arena;
    LocalStringPool pool;
    Tokenizer tokenizer("CALL update_stats()", &pool);

    auto tokens = tokenizer.tokenize_all();

    std::cout << "Tokens:" << std::endl;
    for (size_t i = 0; i < tokens.size(); ++i) {
        std::cout << "  " << i << ": type=" << (int)tokens[i].type
                  << " text=" << (tokens[i].text ? tokens[i].text : "null") << std::endl;
    }

    REQUIRE(tokens.size() >= 4); // CALL, identifier, (, )
    REQUIRE(tokens[0].type == TokenType::CALL);
    REQUIRE(tokens[1].type == TokenType::IDENTIFIER);
}
