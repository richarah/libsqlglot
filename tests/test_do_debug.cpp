#include <catch2/catch_test_macros.hpp>
#include <libsqlglot/keywords.h>
#include <iostream>

using namespace libsqlglot;

TEST_CASE("Debug DO keyword", "[debug]") {
    // Test hash calculation
    char upper[3];
    upper[0] = 'D';
    upper[1] = 'O';
    upper[2] = '\0';
    size_t len = 2;

    uint32_t hash = (upper[0] * 31 + upper[len - 1] + len) & 127;
    std::cout << "DO hash: " << hash << std::endl;
    std::cout << "Expected: 13" << std::endl;

    // Perform lookup
    auto result = KeywordLookup::lookup("DO");
    std::cout << "Lookup result: " << static_cast<int>(result) << std::endl;
    std::cout << "TokenType::DO: " << static_cast<int>(TokenType::DO) << std::endl;
    std::cout << "TokenType::IDENTIFIER: " << static_cast<int>(TokenType::IDENTIFIER) << std::endl;
    std::cout << std::endl;

    // Test WHILE
    std::cout << "WHILE hash: ";
    char while_upper[6] = "WHILE";
    size_t while_len = 5;
    uint32_t while_hash = (while_upper[0] * 31 + while_upper[while_len - 1] + while_len) & 127;
    std::cout << while_hash << std::endl;
    std::cout << "Expected: 83" << std::endl;
    auto while_result = KeywordLookup::lookup("WHILE");
    std::cout << "Lookup result: " << static_cast<int>(while_result) << std::endl;
    std::cout << "TokenType::WHILE: " << static_cast<int>(TokenType::WHILE) << std::endl;

    REQUIRE(hash == 13);
}
