#include <libsqlglot/transpiler.h>
#include <libsqlglot/optimizer.h>
#include <libsqlglot/arena.h>
#include <iostream>

int main() {
    // Test the corpus items one by one - including mutations that might crash
    const char* test_queries[] = {
        "SELECT * FROM (SELECT * FROM t) s",
        "SELECT x FROM t WHERE x = x",
        "SELECT DISTINCT x FROM t UNION SELECT DISTINCT x FROM t",
        "SELECT * FROM t WHERE 1=1",
        "SELECT * FROM t WHERE x IN (SELECT x FROM t)",
        "SELECT * FROM t ORDER BY x, x",
        "SELECT CASE WHEN x > 0 THEN 1 ELSE 1 END FROM t",
        "SELECT COALESCE(x, x, x) FROM t",
        "SELECT * FROM t WHERE NOT (NOT (x > 0))",
        "SELECT x FROM t INTERSECT SELECT x FROM t",
        "WITH cte AS (SELECT * FROM t), cte2 AS (SELECT * FROM cte) SELECT * FROM cte2",
    };

    for (int i = 0; i < 11; ++i) {
        std::cout << "\n=== Testing query " << i << " ===\n";
        std::cout << "SQL: " << test_queries[i] << "\n";

        try {
            libsqlglot::Arena arena;
            std::cout << "Parsing...\n" << std::flush;
            auto ast = libsqlglot::Transpiler::parse(arena, test_queries[i]);

            if (ast && ast->type == libsqlglot::ExprType::SELECT_STMT) {
                std::cout << "Parse OK, optimizing...\n" << std::flush;
                auto select = static_cast<libsqlglot::SelectStmt*>(ast);

                std::cout << "  qualify_columns...\n" << std::flush;
                libsqlglot::Optimizer::qualify_columns(select);

                std::cout << "  pushdown_predicates...\n" << std::flush;
                libsqlglot::Optimizer::pushdown_predicates(select, arena);

                std::cout << "  eliminate_subqueries...\n" << std::flush;
                libsqlglot::Optimizer::eliminate_subqueries(select, arena);

                if (select->where) {
                    std::cout << "  normalize...\n" << std::flush;
                    select->where = libsqlglot::Optimizer::normalize(select->where);

                    std::cout << "  fold_constants...\n" << std::flush;
                    select->where = libsqlglot::Optimizer::fold_constants(select->where, arena);
                }

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
