// Fuzzer targeting SQL generator (AST -> SQL)
// Build: g++ -std=c++23 -O2 -I../include fuzz_generator.cpp -o fuzz_generator
// Run: ./fuzz_generator

#include <libsqlglot/transpiler.h>
#include <libsqlglot/generator.h>
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

class GeneratorFuzzer {
public:
    GeneratorFuzzer() : gen(std::random_device{}()), dist(0, 255) {}

    std::string mutate(const std::string& base) {
        std::string result = base;
        int mutations = 1 + (dist(gen) % 4);

        for (int i = 0; i < mutations; ++i) {
            int op = dist(gen) % 5;
            if (result.empty()) break;

            switch (op) {
                case 0: // Insert complex expressions
                    {
                        const char* exprs[] = {
                            "CAST(x AS VARCHAR(100))",
                            "EXTRACT(YEAR FROM date_col)",
                            "SUBSTRING(str_col, 1, 10)",
                            "COALESCE(a, b, c, d)",
                            "CASE WHEN x > 0 THEN 'pos' WHEN x < 0 THEN 'neg' ELSE 'zero' END",
                            "ROW_NUMBER() OVER (PARTITION BY x ORDER BY y DESC)",
                            "ARRAY[1, 2, 3, 4, 5]",
                            "JSON_EXTRACT(data, '$.field')",
                            "REGEXP_REPLACE(text, '[0-9]', 'X')",
                            "DATE_ADD(dt, INTERVAL 7 DAY)"
                        };
                        size_t idx = dist(gen) % (sizeof(exprs) / sizeof(exprs[0]));
                        size_t pos = result.empty() ? 0 : (dist(gen) % result.size());
                        result.insert(pos, std::string(", ") + exprs[idx]);
                    }
                    break;
                case 1: // Add dialect-specific syntax
                    {
                        const char* syntax[] = {
                            " QUALIFY ROW_NUMBER() OVER (ORDER BY x) = 1",
                            " PIVOT (SUM(val) FOR category IN ('A', 'B', 'C'))",
                            " UNPIVOT (val FOR category IN (col1, col2, col3))",
                            " TABLESAMPLE (10 PERCENT)",
                            " FOR SYSTEM_TIME AS OF TIMESTAMP '2024-01-01'",
                            " LATERAL VIEW EXPLODE(array_col) t AS item"
                        };
                        size_t idx = dist(gen) % (sizeof(syntax) / sizeof(syntax[0]));
                        result += syntax[idx];
                    }
                    break;
                case 2: // Insert unicode/special characters
                    {
                        const char* special[] = {
                            "'\u4e2d\u6587'", // Chinese
                            "'\u0645\u0631\u062d\u0628\u0627'", // Arabic
                            "'Здравствуй'", // Russian
                            "'🚀🔥💯'", // Emojis
                            "'tab\there'", // Tab
                            "'new\nline'", // Newline
                            "'quote''escape'", // Quote escape
                            "'backslash\\path'"
                        };
                        size_t idx = dist(gen) % (sizeof(special) / sizeof(special[0]));
                        size_t pos = result.empty() ? 0 : (dist(gen) % result.size());
                        result.insert(pos, std::string(" ") + special[idx] + " ");
                    }
                    break;
                case 3: // Add deeply nested structures
                    {
                        std::string nested = " (";
                        int depth = 1 + (dist(gen) % 5);
                        for (int d = 0; d < depth; ++d) {
                            nested += "SELECT * FROM (";
                        }
                        nested += "SELECT 1";
                        for (int d = 0; d < depth; ++d) {
                            nested += ") t" + std::to_string(d);
                        }
                        nested += ") ";
                        result += nested;
                    }
                    break;
                case 4: // Insert large numbers/strings
                    {
                        const char* large[] = {
                            " 999999999999999999999999999999 ",
                            " -999999999999999999999999999999 ",
                            " 1e308 ",
                            " 'AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA' ",
                            " REPEAT('X', 10000) "
                        };
                        size_t idx = dist(gen) % (sizeof(large) / sizeof(large[0]));
                        result += large[idx];
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

    GeneratorFuzzer fuzzer;

    // Corpus for generator testing
    std::vector<std::string> corpus = {
        "SELECT * FROM table1",
        "SELECT a, b, c FROM t WHERE x > 100",
        "SELECT COUNT(*), SUM(price) FROM orders GROUP BY customer_id",
        "SELECT t1.*, t2.name FROM t1 JOIN t2 ON t1.id = t2.ref_id",
        "WITH RECURSIVE cte AS (SELECT 1 AS n UNION ALL SELECT n+1 FROM cte WHERE n < 10) SELECT * FROM cte",
        "SELECT DISTINCT category, AVG(price) OVER (PARTITION BY category) FROM products",
        "INSERT INTO logs (timestamp, message) VALUES (NOW(), 'test')",
        "UPDATE users SET last_login = NOW() WHERE id = 123",
        "DELETE FROM temp_table WHERE created_at < DATE_SUB(NOW(), INTERVAL 1 DAY)",
        "CREATE TABLE test (id INT PRIMARY KEY, name VARCHAR(100))",
        "SELECT CASE WHEN score >= 90 THEN 'A' WHEN score >= 80 THEN 'B' ELSE 'C' END AS grade FROM students"
    };

    uint64_t iterations = 0;
    uint64_t crashes = 0;
    uint64_t generated = 0;
    auto start_time = std::chrono::steady_clock::now();

    std::cout << "Starting generator fuzzer...\n";
    std::cout << "Press Ctrl+C to stop\n\n";

    while (running) {
        std::string seed = corpus[iterations % corpus.size()];
        std::string mutated = fuzzer.mutate(seed);

        try {
            libsqlglot::Arena arena;
            auto ast = libsqlglot::Transpiler::parse(arena, mutated);

            if (ast) {
                try {
                    // Try to generate SQL from the AST
                    auto sql = libsqlglot::Generator::generate(ast);
                    generated++;

                    // Try to parse the generated SQL (round-trip test)
                    try {
                        libsqlglot::Arena arena2;
                        libsqlglot::Transpiler::parse(arena2, sql);

                        // Add successful round-trips to corpus
                        if (iterations % 150 == 0 && corpus.size() < 1000) {
                            corpus.push_back(sql);
                        }
                    } catch (...) {
                        // Round-trip failure
                        std::cout << "\n=== ROUND-TRIP FAILURE ===\n";
                        std::cout << "Original: " << mutated << "\n";
                        std::cout << "Generated: " << sql << "\n";
                        std::cout << "========================\n\n";
                    }
                } catch (const std::exception& e) {
                    // Generation failure
                } catch (...) {
                    crashes++;
                    std::cout << "\n=== GENERATOR CRASH ===\n";
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
                      << " | Generated: " << generated
                      << " | Corpus: " << corpus.size()
                      << " | Crashes: " << crashes
                      << " | Rate: " << static_cast<int>(rate) << "/s"
                      << std::flush;
        }
    }

    auto end_time = std::chrono::steady_clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::seconds>(end_time - start_time).count();

    std::cout << "\n\n=== Generator Fuzzing Summary ===\n";
    std::cout << "Total iterations: " << iterations << "\n";
    std::cout << "Successfully generated: " << generated << "\n";
    std::cout << "Corpus size: " << corpus.size() << "\n";
    std::cout << "Crashes: " << crashes << "\n";
    std::cout << "Time: " << elapsed << "s\n";

    return crashes > 0 ? 1 : 0;
}
