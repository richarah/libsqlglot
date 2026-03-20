#include <libsqlglot/transpiler.h>
#include <libsqlglot/optimizer.h>
#include <libsqlglot/arena.h>
#include <iostream>
#include <fstream>
#include <filesystem>
#include <vector>
#include <string>

int main() {
    std::vector<std::string> crash_files;

    for (const auto& entry : std::filesystem::directory_iterator("crash_samples")) {
        if (entry.path().extension() == ".sql") {
            crash_files.push_back(entry.path().string());
        }
    }

    std::sort(crash_files.begin(), crash_files.end());

    std::cout << "Testing optimizer on " << crash_files.size() << " samples...\n\n";

    int crashes = 0;
    int handled = 0;

    for (const auto& file : crash_files) {
        std::ifstream in(file);
        std::string sql((std::istreambuf_iterator<char>(in)), std::istreambuf_iterator<char>());

        std::cout << "Test: " << file << "\n";

        try {
            libsqlglot::Arena arena;
            auto ast = libsqlglot::Transpiler::parse(arena, sql);

            if (ast && ast->type == libsqlglot::ExprType::SELECT_STMT) {
                auto select = static_cast<libsqlglot::SelectStmt*>(ast);

                // Try all optimizer operations
                libsqlglot::Optimizer::qualify_columns(select);
                libsqlglot::Optimizer::pushdown_predicates(select, arena);
                libsqlglot::Optimizer::eliminate_subqueries(select, arena);

                if (select->where) {
                    select->where = libsqlglot::Optimizer::normalize(select->where);
                    select->where = libsqlglot::Optimizer::fold_constants(select->where, arena);
                }

                std::cout << "Result: Optimized successfully\n";
                handled++;
            } else {
                std::cout << "Result: Not a SELECT statement\n";
                handled++;
            }
        } catch (const std::exception& e) {
            std::cout << "Result: Exception: " << e.what() << "\n";
            handled++;
        } catch (...) {
            std::cout << "Result: CRASH in optimizer\n";
            crashes++;
        }

        std::cout << "\n";
    }

    std::cout << "=================================\n";
    std::cout << "Optimizer Summary:\n";
    std::cout << "  Total samples: " << crash_files.size() << "\n";
    std::cout << "  Handled gracefully: " << handled << "\n";
    std::cout << "  Crashes: " << crashes << "\n";
    std::cout << "=================================\n";

    return crashes > 0 ? 1 : 0;
}
