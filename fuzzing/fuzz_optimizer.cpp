// Fuzzer targeting the SQL optimizer
// Build: g++ -std=c++23 -O2 -I../include fuzz_optimizer.cpp -o fuzz_optimizer
// Run: ./fuzz_optimizer

#include <libsqlglot/transpiler.h>
#include <libsqlglot/optimizer.h>
#include <libsqlglot/arena.h>
#include <iostream>
#include <random>
#include <string>
#include <vector>
#include <chrono>
#include <csignal>

volatile bool running = true;

void signal_handler(int) {
    running = false;
}

class OptimizerFuzzer {
public:
    OptimizerFuzzer() : gen(std::random_device{}()), dist(0, 255) {}

    std::string mutate(const std::string& base) {
        std::string result = base;
        int mutations = 1 + (dist(gen) % 3);

        for (int i = 0; i < mutations; ++i) {
            int op = dist(gen) % 4;
            if (result.empty()) break;

            switch (op) {
                case 0: // Insert optimization-relevant keywords
                    {
                        const char* keywords[] = {
                            "DISTINCT", "ALL", "UNION", "INTERSECT", "EXCEPT",
                            "GROUP BY", "HAVING", "WHERE", "AND", "OR", "NOT",
                            "IN", "EXISTS", "BETWEEN", "LIKE", "IS NULL",
                            "ORDER BY", "LIMIT", "OFFSET", "PARTITION BY",
                            "OVER", "ROW_NUMBER", "RANK", "DENSE_RANK",
                            "LAG", "LEAD", "FIRST_VALUE", "LAST_VALUE",
                            "COUNT", "SUM", "AVG", "MIN", "MAX", "STDDEV",
                            "CASE", "WHEN", "THEN", "ELSE", "END",
                            "CAST", "COALESCE", "NULLIF", "EXTRACT"
                        };
                        size_t idx = dist(gen) % (sizeof(keywords) / sizeof(keywords[0]));
                        size_t pos = result.empty() ? 0 : (dist(gen) % result.size());
                        result.insert(pos, std::string(" ") + keywords[idx] + " ");
                    }
                    break;
                case 1: // Add nested query
                    {
                        const char* patterns[] = {
                            " (SELECT * FROM t) ",
                            " (SELECT x FROM (SELECT * FROM t) s) ",
                            " IN (SELECT y FROM s) ",
                            " EXISTS (SELECT 1 FROM t WHERE x = y) "
                        };
                        size_t idx = dist(gen) % (sizeof(patterns) / sizeof(patterns[0]));
                        size_t pos = result.empty() ? 0 : (dist(gen) % result.size());
                        result.insert(pos, patterns[idx]);
                    }
                    break;
                case 2: // Duplicate expression
                    if (result.size() > 10) {
                        size_t start = dist(gen) % (result.size() - 10);
                        size_t len = 5 + (dist(gen) % 20);
                        std::string dup = result.substr(start, len);
                        result += " AND " + dup;
                    }
                    break;
                case 3: // Insert whitespace/comments
                    {
                        const char* whitespace[] = {" ", "\n", "\t", "  ", "   ", "    "};
                        size_t idx = dist(gen) % (sizeof(whitespace) / sizeof(whitespace[0]));
                        size_t pos = result.empty() ? 0 : (dist(gen) % result.size());
                        result.insert(pos, whitespace[idx]);
                    }
                    break;
            }
        }

        return result;
    }

private:
    std::mt19937 gen;
    std::uniform_int_distribution<> dist;
};

int main() {
    std::signal(SIGINT, signal_handler);
    std::signal(SIGTERM, signal_handler);

    OptimizerFuzzer fuzzer;

    // Corpus focused on optimization opportunities
    std::vector<std::string> corpus = {
        "SELECT * FROM (SELECT * FROM t) s",
        "SELECT x FROM t WHERE x = x",
        "SELECT DISTINCT x FROM t UNION SELECT DISTINCT x FROM t",
        "SELECT * FROM t WHERE 1=1",
        "SELECT * FROM t WHERE x IN (SELECT x FROM t)",
        "SELECT COUNT(*) FROM (SELECT DISTINCT x FROM t) s",
        "SELECT x, y FROM t WHERE x > 0 AND x > 0",
        "SELECT * FROM t JOIN t t2 ON t.id = t2.id",
        "SELECT SUM(x), SUM(x) FROM t",
        "SELECT * FROM t WHERE EXISTS (SELECT 1 FROM s WHERE s.x = t.x)",
        "SELECT * FROM t ORDER BY x, x",
        "SELECT CASE WHEN x > 0 THEN 1 ELSE 1 END FROM t",
        "SELECT COALESCE(x, x, x) FROM t",
        "SELECT * FROM t WHERE NOT (NOT (x > 0))",
        "SELECT x FROM t INTERSECT SELECT x FROM t",
        "WITH cte AS (SELECT * FROM t), cte2 AS (SELECT * FROM cte) SELECT * FROM cte2",
        "SELECT * FROM t WHERE x BETWEEN 5 AND 5",
        "SELECT x FROM t GROUP BY x HAVING COUNT(*) > 0",
        "SELECT NULL, NULL, NULL FROM t"
    };

    uint64_t iterations = 0;
    uint64_t crashes = 0;
    uint64_t parsed_ok = 0;
    auto start_time = std::chrono::steady_clock::now();

    std::cout << "Starting optimizer fuzzer...\n";
    std::cout << "Press Ctrl+C to stop\n\n";

    while (running) {
        std::string seed = corpus[iterations % corpus.size()];
        std::string mutated = fuzzer.mutate(seed);

        try {
            libsqlglot::Arena arena;
            auto ast = libsqlglot::Transpiler::parse(arena, mutated);

            // Try to optimize the parsed AST
            if (ast && ast->type == libsqlglot::ExprType::SELECT_STMT) {
                parsed_ok++;
                try {
                    auto select = static_cast<libsqlglot::SelectStmt*>(ast);

                    // Apply various optimizations
                    libsqlglot::Optimizer::qualify_columns(select);
                    libsqlglot::Optimizer::pushdown_predicates(select, arena);
                    libsqlglot::Optimizer::eliminate_subqueries(select, arena);

                    if (select->where) {
                        select->where = libsqlglot::Optimizer::normalize(select->where);
                        select->where = libsqlglot::Optimizer::fold_constants(select->where, arena);
                    }

                    // Add successful optimizations to corpus occasionally
                    if (iterations % 200 == 0 && corpus.size() < 1000) {
                        corpus.push_back(mutated);
                    }
                } catch (const std::exception& e) {
                    // Optimizer failure on valid parse
                } catch (...) {
                    crashes++;
                    std::cout << "\n=== OPTIMIZER CRASH ===\n";
                    std::cout << "Input: " << mutated << "\n";
                    std::cout << "======================\n\n";
                }
            }
        } catch (...) {
            // Parse failure is expected
        }

        iterations++;

        if (iterations % 10000 == 0) {
            auto now = std::chrono::steady_clock::now();
            auto elapsed = std::chrono::duration_cast<std::chrono::seconds>(now - start_time).count();
            double rate = iterations / (elapsed > 0 ? elapsed : 1);

            std::cout << "\rIterations: " << iterations
                      << " | Parsed: " << parsed_ok
                      << " | Corpus: " << corpus.size()
                      << " | Crashes: " << crashes
                      << " | Rate: " << static_cast<int>(rate) << "/s"
                      << std::flush;
        }
    }

    auto end_time = std::chrono::steady_clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::seconds>(end_time - start_time).count();

    std::cout << "\n\n=== Optimizer Fuzzing Summary ===\n";
    std::cout << "Total iterations: " << iterations << "\n";
    std::cout << "Successfully parsed: " << parsed_ok << "\n";
    std::cout << "Corpus size: " << corpus.size() << "\n";
    std::cout << "Crashes: " << crashes << "\n";
    std::cout << "Time: " << elapsed << "s\n";

    return crashes > 0 ? 1 : 0;
}
