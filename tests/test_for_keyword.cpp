#include <catch2/catch_test_macros.hpp>
#include <libsqlglot/keywords.h>
#include <iostream>

using namespace libsqlglot;

TEST_CASE("FOR keyword lookup direct test", "[keywords][for]") {
    const char* text = "FOR";

    // Calculate hash manually
    char upper[17];
    size_t len = 3;
    for (size_t i = 0; i < len; ++i) {
        char c = text[i];
        upper[i] = (c >= 'a' && c <= 'z') ? (c - 32) : c;
    }
    upper[len] = '\0';

    uint32_t hash = (upper[0] * 31 + upper[len - 1] + len) & 127;

    std::cout << "Text: " << text << std::endl;
    std::cout << "Upper: " << upper << std::endl;
    std::cout << "First: " << (int)upper[0] << std::endl;
    std::cout << "Last: " << (int)upper[len-1] << std::endl;
    std::cout << "Len: " << len << std::endl;
    std::cout << "Hash: " << hash << std::endl;

    TokenType result = KeywordLookup::lookup("FOR");
    std::cout << "KeywordLookup::lookup(\"FOR\") = " << (int)result << std::endl;
    std::cout << "TokenType::FOR = " << (int)TokenType::FOR << std::endl;
    std::cout << "TokenType::IDENTIFIER = " << (int)TokenType::IDENTIFIER << std::endl;

    REQUIRE(hash == 79);
    REQUIRE(result == TokenType::FOR);
}
