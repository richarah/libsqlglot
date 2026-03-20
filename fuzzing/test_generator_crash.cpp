#include <libsqlglot/transpiler.h>
#include <libsqlglot/generator.h>
#include <libsqlglot/arena.h>
#include <iostream>

int main() {
    // Test the corpus items one by one
    const char* test_queries[] = {
        "SELECT * FROM table1",
        "SELECT a, b, c FROM t WHERE x > 100",
        "SELECT COUNT(*), SUM(price) FROM orders GROUP BY customer_id",
        "SELECT t1.*, t2.name FROM t1 JOIN t2 ON t1.id = t2.ref_id",
        "WITH RECURSIVE cte AS (SELECT 1 AS n UNION ALL SELECT n+1 FROM cte WHERE n < 10) SELECT * FROM cte",
    };

    for (int i = 0; i < 5; ++i) {
        std::cout << "\n=== Testing query " << i << " ===\n";
        std::cout << "SQL: " << test_queries[i] << "\n";

        try {
            libsqlglot::Arena arena;
            std::cout << "Parsing...\n" << std::flush;
            auto ast = libsqlglot::Transpiler::parse(arena, test_queries[i]);

            if (ast) {
                std::cout << "Parse OK, AST type=" << static_cast<int>(ast->type) << "\n" << std::flush;

                std::cout << "Generating...\n" << std::flush;
                auto sql = libsqlglot::Generator::generate(ast);

                std::cout << "Generated: " << sql << "\n";
                std::cout << "SUCCESS\n";
            } else {
                std::cout << "Parse returned null\n";
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
