#include <libsqlglot/transpiler.h>
#include <libsqlglot/optimizer.h>
#include <libsqlglot/arena.h>
#include <iostream>

int main() {
    // Test deeply nested subqueries that might cause infinite recursion
    const char* test_queries[] = {
        "SELECT * FROM (SELECT * FROM (SELECT * FROM (SELECT * FROM t) s1) s2) s3",
        "SELECT * FROM (SELECT * FROM (SELECT * FROM (SELECT * FROM (SELECT * FROM t) s1) s2) s3) s4",
        "SELECT * FROM t WHERE EXISTS (SELECT 1 FROM s WHERE x = y)",
    };

    for (int i = 0; i < 3; ++i) {
        std::cout << "\n=== Testing query " << i << " ===\n";
        std::cout << "SQL: " << test_queries[i] << "\n";

        try {
            libsqlglot::Arena arena;
            std::cout << "Parsing...\n" << std::flush;
            auto ast = libsqlglot::Transpiler::parse(arena, test_queries[i]);

            if (ast && ast->type == libsqlglot::ExprType::SELECT_STMT) {
                std::cout << "Parse OK, optimizing...\n" << std::flush;
                auto select = static_cast<libsqlglot::SelectStmt*>(ast);

                std::cout << "  eliminate_subqueries...\n" << std::flush;
                libsqlglot::Optimizer::eliminate_subqueries(select, arena);

                std::cout << "SUCCESS\n";
            } else {
                std::cout << "Parse returned null or not SELECT\n";
            }
        } catch (const std::exception& e) {
            std::cout << "Exception: " << e.what() << "\n";
            return 1;
        } catch (...) {
            std::cout << "Unknown exception/crash\n";
            return 1;
        }
    }

    std::cout << "\nAll tests passed!\n";
    return 0;
}
