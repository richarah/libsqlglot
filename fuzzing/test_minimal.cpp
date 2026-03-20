#include <libsqlglot/transpiler.h>
#include <libsqlglot/optimizer.h>
#include <libsqlglot/generator.h>
#include <libsqlglot/arena.h>
#include <iostream>

int main() {
    std::cout << "Test 1: Creating arena..." << std::endl;
    libsqlglot::Arena arena;
    std::cout << "Arena created successfully" << std::endl;

    std::cout << "Test 2: Parsing simple SQL..." << std::endl;
    try {
        auto ast = libsqlglot::Transpiler::parse(arena, "SELECT * FROM t");
        std::cout << "Parse result: " << (ast ? "success" : "null") << std::endl;

        if (ast) {
            std::cout << "AST type: " << static_cast<int>(ast->type) << std::endl;

            std::cout << "Test 3: Generating SQL..." << std::endl;
            try {
                auto sql = libsqlglot::Generator::generate(ast);
                std::cout << "Generated SQL: " << sql << std::endl;
            } catch (const std::exception& e) {
                std::cout << "Generator exception: " << e.what() << std::endl;
            } catch (...) {
                std::cout << "Generator crashed" << std::endl;
            }
        }
    } catch (const std::exception& e) {
        std::cout << "Parse exception: " << e.what() << std::endl;
    } catch (...) {
        std::cout << "Parse crashed" << std::endl;
    }

    std::cout << "All tests completed" << std::endl;
    return 0;
}
