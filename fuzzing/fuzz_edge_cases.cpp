// Edge case fuzzer - focuses on boundary conditions and unusual inputs
// Build: g++ -std=c++23 -O2 -I../include fuzz_edge_cases.cpp -o fuzz_edge_cases
// Run: ./fuzz_edge_cases

#include <libsqlglot/transpiler.h>
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

class EdgeCaseFuzzer {
public:
    EdgeCaseFuzzer() : gen(std::random_device{}()), dist(0, 255) {}

    std::string generate_edge_case() {
        int case_type = dist(gen) % 20;

        switch (case_type) {
            case 0: // Empty/whitespace
                {
                    const char* empty[] = {"", " ", "  ", "\n", "\t", "\r\n", "   \n  \t  "};
                    return empty[dist(gen) % 7];
                }

            case 1: // Very long identifiers
                {
                    std::string id = "SELECT ";
                    int len = 100 + (dist(gen) % 1000);
                    for (int i = 0; i < len; ++i) {
                        id += 'a' + (dist(gen) % 26);
                    }
                    id += " FROM table1";
                    return id;
                }

            case 2: // Very long string literals
                {
                    std::string sql = "SELECT '";
                    int len = 100 + (dist(gen) % 1000);
                    for (int i = 0; i < len; ++i) {
                        sql += 'x';
                    }
                    sql += "' FROM t";
                    return sql;
                }

            case 3: // Deeply nested parentheses
                {
                    std::string sql = "SELECT ";
                    int depth = 10 + (dist(gen) % 50);
                    for (int i = 0; i < depth; ++i) sql += "(";
                    sql += "1";
                    for (int i = 0; i < depth; ++i) sql += ")";
                    sql += " FROM t";
                    return sql;
                }

            case 4: // Extremely large numbers
                {
                    int choice = dist(gen) % 6;
                    if (choice == 5) {
                        return "SELECT 9" + std::string(100, '9') + " FROM t";
                    }
                    const char* numbers[] = {
                        "SELECT 999999999999999999999999999999 FROM t",
                        "SELECT -999999999999999999999999999999 FROM t",
                        "SELECT 1e308 FROM t",
                        "SELECT 1e-308 FROM t",
                        "SELECT 0.00000000000000000000000001 FROM t"
                    };
                    return numbers[choice];
                }

            case 5: // NULL in various contexts
                {
                    const char* nulls[] = {
                        "SELECT NULL",
                        "SELECT NULL FROM NULL",
                        "SELECT NULL, NULL, NULL FROM t WHERE NULL = NULL",
                        "SELECT * FROM t WHERE x IS NULL AND y IS NOT NULL",
                        "INSERT INTO t VALUES (NULL, NULL, NULL)",
                        "UPDATE t SET x = NULL WHERE y = NULL",
                        "SELECT COALESCE(NULL, NULL, NULL)"
                    };
                    return nulls[dist(gen) % 7];
                }

            case 6: // Special characters in identifiers
                {
                    const char* special[] = {
                        "SELECT `strange-name` FROM t",
                        "SELECT \"column with spaces\" FROM t",
                        "SELECT [column_with_brackets] FROM t",
                        "SELECT `col`umn` FROM t",
                        "SELECT \"col\"\"umn\" FROM t"
                    };
                    return special[dist(gen) % 5];
                }

            case 7: // Unicode and emojis
                {
                    const char* unicode[] = {
                        "SELECT '🚀' AS emoji FROM t",
                        "SELECT '\u4e2d\u6587' FROM t",
                        "SELECT '\u0645\u0631\u062d\u0628\u0627' FROM t",
                        "SELECT 'Здравствуй мир' FROM t",
                        "SELECT '日本語テスト' FROM t"
                    };
                    return unicode[dist(gen) % 5];
                }

            case 8: // Escaping and quotes
                {
                    const char* quotes[] = {
                        "SELECT 'it''s' FROM t",
                        "SELECT 'quote: '' end' FROM t",
                        "SELECT \"double \"\"quote\"\"\" FROM t",
                        "SELECT 'backslash\\test' FROM t",
                        "SELECT 'tab\there' FROM t",
                        "SELECT 'newline\nhere' FROM t"
                    };
                    return quotes[dist(gen) % 6];
                }

            case 9: // Extreme recursion - CTEs
                {
                    int depth = 5 + (dist(gen) % 20);
                    std::string sql = "";
                    for (int i = 0; i < depth; ++i) {
                        sql += "WITH cte" + std::to_string(i) + " AS (SELECT ";
                        sql += (i == 0) ? "1 AS n" : "n + 1 FROM cte" + std::to_string(i - 1);
                        sql += ") ";
                    }
                    sql += "SELECT * FROM cte" + std::to_string(depth - 1);
                    return sql;
                }

            case 10: // Very wide SELECT (many columns)
                {
                    std::string sql = "SELECT ";
                    int cols = 100 + (dist(gen) % 500);
                    for (int i = 0; i < cols; ++i) {
                        if (i > 0) sql += ", ";
                        sql += "col" + std::to_string(i);
                    }
                    sql += " FROM t";
                    return sql;
                }

            case 11: // Pathological JOIN chains
                {
                    std::string sql = "SELECT * FROM t1";
                    int joins = 5 + (dist(gen) % 30);
                    for (int i = 2; i <= joins; ++i) {
                        sql += " JOIN t" + std::to_string(i);
                        sql += " ON t1.id = t" + std::to_string(i) + ".id";
                    }
                    return sql;
                }

            case 12: // Extremely complex WHERE clauses
                {
                    std::string sql = "SELECT * FROM t WHERE ";
                    int predicates = 10 + (dist(gen) % 50);
                    for (int i = 0; i < predicates; ++i) {
                        if (i > 0) sql += " AND ";
                        sql += "x" + std::to_string(i) + " = " + std::to_string(i);
                    }
                    return sql;
                }

            case 13: // Binary data / control characters
                {
                    std::string sql = "SELECT x'";
                    for (int i = 0; i < 20; ++i) {
                        char c = dist(gen) & 0xFF;
                        sql += (c < 16 ? "0" : "");
                        sql += "0123456789ABCDEF"[c >> 4];
                        sql += "0123456789ABCDEF"[c & 0x0F];
                    }
                    sql += "' FROM t";
                    return sql;
                }

            case 14: // Reserved keywords as identifiers
                {
                    const char* keywords[] = {
                        "SELECT SELECT FROM FROM",
                        "SELECT `FROM` FROM `SELECT`",
                        "SELECT WHERE FROM WHERE",
                        "SELECT `ORDER` FROM `GROUP`"
                    };
                    return keywords[dist(gen) % 4];
                }

            case 15: // Window functions edge cases
                {
                    const char* windows[] = {
                        "SELECT ROW_NUMBER() OVER () FROM t",
                        "SELECT SUM(x) OVER (ROWS BETWEEN UNBOUNDED PRECEDING AND UNBOUNDED FOLLOWING) FROM t",
                        "SELECT LAG(x, 999999) OVER (ORDER BY y) FROM t",
                        "SELECT LEAD(x, -1) OVER () FROM t"
                    };
                    return windows[dist(gen) % 4];
                }

            case 16: // Malformed but parseable edge cases
                {
                    const char* malformed[] = {
                        "SELECT * FROM",  // Incomplete
                        "SELECT FROM t",  // Missing column list
                        "SELECT * WHERE x = 1",  // Missing FROM
                        "SELECT * FROM t WHERE",  // Incomplete WHERE
                        "SELECT * FROM t GROUP BY",  // Incomplete GROUP BY
                        "SELECT , , FROM t"  // Empty columns
                    };
                    return malformed[dist(gen) % 6];
                }

            case 17: // Comments in unusual positions
                {
                    const char* comments[] = {
                        "SELECT /* comment */ * FROM t",
                        "SELECT * /* mid-query */ FROM t",
                        "SELECT * FROM t /* end comment */",
                        "-- line comment\nSELECT * FROM t",
                        "SELECT * FROM t -- trailing\n",
                        "SELECT /*/* nested? */*/ * FROM t"
                    };
                    return comments[dist(gen) % 6];
                }

            case 18: // Multiple statements
                {
                    const char* multi[] = {
                        "SELECT 1; SELECT 2",
                        "SELECT * FROM t; SELECT * FROM s",
                        "INSERT INTO t VALUES (1); SELECT * FROM t",
                        "CREATE TABLE test (id INT); DROP TABLE test"
                    };
                    return multi[dist(gen) % 4];
                }

            case 19: // Random byte injection
                {
                    std::string sql = "SELECT * FROM t WHERE x = ";
                    for (int i = 0; i < 10; ++i) {
                        sql += static_cast<char>(dist(gen));
                    }
                    return sql;
                }

            default:
                return "SELECT 1";
        }
    }

private:
    std::mt19937 gen;
    std::uniform_int_distribution<> dist;
};

int main() {
    std::signal(SIGINT, signal_handler);
    std::signal(SIGTERM, signal_handler);

    EdgeCaseFuzzer fuzzer;

    uint64_t iterations = 0;
    uint64_t crashes = 0;
    uint64_t parse_errors = 0;
    uint64_t parse_success = 0;
    auto start_time = std::chrono::steady_clock::now();

    std::cout << "Starting edge case fuzzer...\n";
    std::cout << "Press Ctrl+C to stop\n\n";

    while (running) {
        std::string test_case = fuzzer.generate_edge_case();

        try {
            libsqlglot::Arena arena;
            auto ast = libsqlglot::Transpiler::parse(arena, test_case);
            if (ast) {
                parse_success++;
            }
        } catch (const std::exception& e) {
            parse_errors++;
            // Expected - many edge cases are intentionally invalid
        } catch (...) {
            crashes++;
            std::cout << "\n=== EDGE CASE CRASH ===\n";
            std::cout << "Input: " << test_case << "\n";
            std::cout << "Length: " << test_case.size() << " bytes\n";
            std::cout << "=======================\n\n";
        }

        iterations++;

        if (iterations % 10000 == 0) {
            auto now = std::chrono::steady_clock::now();
            auto elapsed = std::chrono::duration_cast<std::chrono::seconds>(now - start_time).count();
            double rate = iterations / (elapsed > 0 ? elapsed : 1);

            std::cout << "\rIterations: " << iterations
                      << " | Success: " << parse_success
                      << " | Errors: " << parse_errors
                      << " | Crashes: " << crashes
                      << " | Rate: " << static_cast<int>(rate) << "/s"
                      << std::flush;
        }
    }

    auto end_time = std::chrono::steady_clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::seconds>(end_time - start_time).count();

    std::cout << "\n\n=== Edge Case Fuzzing Summary ===\n";
    std::cout << "Total iterations: " << iterations << "\n";
    std::cout << "Parse successes: " << parse_success << "\n";
    std::cout << "Parse errors: " << parse_errors << "\n";
    std::cout << "Crashes: " << crashes << "\n";
    std::cout << "Time: " << elapsed << "s\n";

    return crashes > 0 ? 1 : 0;
}
