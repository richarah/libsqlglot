#include <iostream>
#include <libsqlglot/tokenizer.h>

using namespace libsqlglot;

int main() {
    Tokenizer tokenizer("SELECT * FROM users");
    auto tokens = tokenizer.tokenize_all();

    std::cout << "Total tokens: " << tokens.size() << "\n";
    for (size_t i = 0; i < tokens.size(); ++i) {
        std::cout << i << ": type=" << static_cast<int>(tokens[i].type)
                  << " start=" << tokens[i].start
                  << " end=" << tokens[i].end << "\n";
    }
    return 0;
}
