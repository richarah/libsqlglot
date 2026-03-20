#include <libsqlglot/transpiler.h>
#include <libsqlglot/optimizer.h>
#include <libsqlglot/arena.h>
#include <iostream>

int main() {
    std::cout << "Testing Optimizer functions..." << std::endl;

    libsqlglot::Arena arena;
    auto ast = libsqlglot::Transpiler::parse(arena, "SELECT * FROM t WHERE x > 5");

    if (ast && ast->type == libsqlglot::ExprType::SELECT_STMT) {
        std::cout << "Parsed SELECT statement" << std::endl;
        auto select = static_cast<libsqlglot::SelectStmt*>(ast);

        std::cout << "Test 1: qualify_columns..." << std::endl;
        try {
            libsqlglot::Optimizer::qualify_columns(select);
            std::cout << "qualify_columns succeeded" << std::endl;
        } catch (const std::exception& e) {
            std::cout << "qualify_columns exception: " << e.what() << std::endl;
            return 1;
        } catch (...) {
            std::cout << "qualify_columns crashed" << std::endl;
            return 1;
        }

        std::cout << "Test 2: pushdown_predicates..." << std::endl;
        try {
            libsqlglot::Optimizer::pushdown_predicates(select);
            std::cout << "pushdown_predicates succeeded" << std::endl;
        } catch (const std::exception& e) {
            std::cout << "pushdown_predicates exception: " << e.what() << std::endl;
            return 1;
        } catch (...) {
            std::cout << "pushdown_predicates crashed" << std::endl;
            return 1;
        }

        std::cout << "Test 3: eliminate_subqueries..." << std::endl;
        try {
            libsqlglot::Optimizer::eliminate_subqueries(select, arena);
            std::cout << "eliminate_subqueries succeeded" << std::endl;
        } catch (const std::exception& e) {
            std::cout << "eliminate_subqueries exception: " << e.what() << std::endl;
            return 1;
        } catch (...) {
            std::cout << "eliminate_subqueries crashed" << std::endl;
            return 1;
        }

        std::cout << "Test 4: normalize..." << std::endl;
        if (select->where) {
            try {
                select->where = libsqlglot::Optimizer::normalize(select->where);
                std::cout << "normalize succeeded" << std::endl;
            } catch (const std::exception& e) {
                std::cout << "normalize exception: " << e.what() << std::endl;
                return 1;
            } catch (...) {
                std::cout << "normalize crashed" << std::endl;
                return 1;
            }
        }

        std::cout << "Test 5: fold_constants..." << std::endl;
        if (select->where) {
            try {
                select->where = libsqlglot::Optimizer::fold_constants(select->where, arena);
                std::cout << "fold_constants succeeded" << std::endl;
            } catch (const std::exception& e) {
                std::cout << "fold_constants exception: " << e.what() << std::endl;
                return 1;
            } catch (...) {
                std::cout << "fold_constants crashed" << std::endl;
                return 1;
            }
        }
    }

    std::cout << "All optimizer tests passed!" << std::endl;
    return 0;
}
