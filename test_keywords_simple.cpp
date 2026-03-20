#include "include/libsqlglot/keywords.h"
#include "include/libsqlglot/tokens.h"
#include <iostream>
#include <string_view>

using namespace libsqlglot;

int main() {
    std::cout << "Testing keyword lookup:\n";

    auto intersect_type = KeywordLookup::lookup("INTERSECT");
    std::cout << "INTERSECT -> TokenType " << static_cast<int>(intersect_type)
              << " (expected " << static_cast<int>(TokenType::INTERSECT) << ")\n";

    auto except_type = KeywordLookup::lookup("EXCEPT");
    std::cout << "EXCEPT -> TokenType " << static_cast<int>(except_type)
              << " (expected " << static_cast<int>(TokenType::EXCEPT) << ")\n";

    auto set_type = KeywordLookup::lookup("SET");
    std::cout << "SET -> TokenType " << static_cast<int>(set_type)
              << " (expected " << static_cast<int>(TokenType::SET) << ")\n";

    auto or_type = KeywordLookup::lookup("OR");
    std::cout << "OR -> TokenType " << static_cast<int>(or_type)
              << " (expected " << static_cast<int>(TokenType::OR) << ")\n";

    return 0;
}
