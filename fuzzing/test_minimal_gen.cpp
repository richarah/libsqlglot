#include <libsqlglot/generator.h>
#include <libsqlglot/transpiler.h>
#include <libsqlglot/arena.h>
#include <iostream>

int main() {
    std::cout << "Starting minimal generator test\n";

    try {
        libsqlglot::Arena arena;
        auto ast = libsqlglot::Transpiler::parse(arena, "SELECT * FROM t");

        if (ast) {
            std::cout << "AST parsed successfully\n";
            auto sql = libsqlglot::Generator::generate(ast);
            std::cout << "Generated SQL: " << sql << "\n";
        }
    } catch (const std::exception& e) {
        std::cout << "Exception: " << e.what() << "\n";
        return 1;
    } catch (...) {
        std::cout << "Unknown exception\n";
        return 1;
    }

    std::cout << "Test completed\n";
    return 0;
}
