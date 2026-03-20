#include <libsqlglot/transpiler.h>
#include <libsqlglot/optimizer.h>
#include <libsqlglot/arena.h>
#include <iostream>
#include <vector>
#include <string>

int main() {
    std::cout << "Starting fuzzer loop test..." << std::endl;

    std::vector<std::string> corpus = {
        "SELECT * FROM (SELECT * FROM t) s",
        "SELECT x FROM t WHERE x = x",
        "SELECT DISTINCT x FROM t UNION SELECT DISTINCT x FROM t"
    };

    for (int i = 0; i < 10; ++i) {
        std::string sql = corpus[i % corpus.size()];
        std::cout << "Iteration " << i << ": " << sql << std::endl;

        try {
            libsqlglot::Arena arena;
            auto ast = libsqlglot::Transpiler::parse(arena, sql);

            if (ast && ast->type == libsqlglot::ExprType::SELECT_STMT) {
                auto select = static_cast<libsqlglot::SelectStmt*>(ast);

                libsqlglot::Optimizer::qualify_columns(select);
                libsqlglot::Optimizer::pushdown_predicates(select);
                libsqlglot::Optimizer::eliminate_subqueries(select, arena);

                if (select->where) {
                    select->where = libsqlglot::Optimizer::normalize(select->where);
                    select->where = libsqlglot::Optimizer::fold_constants(select->where, arena);
                }
            }
        } catch (...) {
            std::cout << "Caught exception in iteration " << i << std::endl;
        }
    }

    std::cout << "All iterations completed successfully!" << std::endl;
    return 0;
}
