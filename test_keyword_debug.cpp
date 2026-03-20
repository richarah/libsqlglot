#include "include/libsqlglot/tokens.h"
#include <string_view>
#include <cstdint>
#include <iostream>

using namespace libsqlglot;

// Copy the KeywordEntry struct and lookup logic with debug output
struct KeywordEntry {
    const char* keywords[4];
    uint8_t lengths[4];
    TokenType types[4];
};

static constexpr KeywordEntry test_entry = {
    {"SET", "INTERSECT", nullptr, nullptr},
    {3, 9, 0, 0},
    {TokenType::SET, TokenType::INTERSECT, TokenType::IDENTIFIER, TokenType::IDENTIFIER}
};

TokenType lookup_debug(std::string_view text) {
    if (text.empty() || text.size() > 16) {
        return TokenType::IDENTIFIER;
    }

    // Convert to uppercase
    char upper[17];
    size_t len = text.size();
    for (size_t i = 0; i < len; ++i) {
        char c = text[i];
        upper[i] = (c >= 'a' && c <= 'z') ? (c - 32) : c;
    }
    upper[len] = '\0';

    std::cout << "Looking up: " << upper << " (len=" << len << ")\n";
    std::cout << "Entry has " << test_entry.lengths[0] << " keywords\n";

    // Check each keyword in the entry
    for (int i = 0; i < 4; ++i) {
        std::cout << "  Slot " << i << ": ";
        if (test_entry.keywords[i] == nullptr) {
            std::cout << "nullptr, breaking\n";
            break;
        }
        std::cout << "keyword=\"" << test_entry.keywords[i]
                  << "\" len=" << (int)test_entry.lengths[i]
                  << " type=" << (int)test_entry.types[i] << "\n";

        if (len == test_entry.lengths[i]) {
            std::cout << "    Length matches! Checking chars:\n";
            bool match = true;
            for (size_t j = 0; j < len; ++j) {
                std::cout << "      [" << j << "] " << upper[j]
                          << " vs " << test_entry.keywords[i][j];
                if (upper[j] != test_entry.keywords[i][j]) {
                    std::cout << " MISMATCH\n";
                    match = false;
                    break;
                }
                std::cout << " OK\n";
            }
            if (match) {
                std::cout << "    MATCH! Returning type " << (int)test_entry.types[i] << "\n";
                return test_entry.types[i];
            }
        } else {
            std::cout << "    Length mismatch: " << len << " != " << (int)test_entry.lengths[i] << "\n";
        }
    }
    return TokenType::IDENTIFIER;
}

int main() {
    std::cout << "=== Testing SET ===\n";
    auto set_result = lookup_debug("SET");
    std::cout << "Result: " << (int)set_result << "\n\n";

    std::cout << "=== Testing INTERSECT ===\n";
    auto intersect_result = lookup_debug("INTERSECT");
    std::cout << "Result: " << (int)intersect_result << "\n\n";

    return 0;
}
