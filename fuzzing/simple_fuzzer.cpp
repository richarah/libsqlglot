// Simple mutation-based SQL fuzzer
// Build: g++ -std=c++23 -O2 -I../include -I../build/_deps/catch2-src/src simple_fuzzer.cpp -o simple_fuzzer
// Run: ./simple_fuzzer

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

class SQLFuzzer {
public:
    SQLFuzzer() : gen(std::random_device{}()), dist(0, 255) {}

    std::string mutate(const std::string& base) {
        std::string result = base;
        int mutations = 1 + (dist(gen) % 5);

        for (int i = 0; i < mutations; ++i) {
            int op = dist(gen) % 6;
            if (result.empty()) break;

            switch (op) {
                case 0: // Insert random char
                    if (!result.empty()) {
                        size_t pos = dist(gen) % (result.size() + 1);
                        result.insert(pos, 1, static_cast<char>(dist(gen)));
                    }
                    break;
                case 1: // Delete char
                    if (!result.empty()) {
                        size_t pos = dist(gen) % result.size();
                        result.erase(pos, 1);
                    }
                    break;
                case 2: // Replace char
                    if (!result.empty()) {
                        size_t pos = dist(gen) % result.size();
                        result[pos] = static_cast<char>(dist(gen));
                    }
                    break;
                case 3: // Duplicate substring
                    if (result.size() > 5) {
                        size_t start = dist(gen) % (result.size() - 5);
                        size_t len = 1 + (dist(gen) % 10);
                        result += result.substr(start, len);
                    }
                    break;
                case 4: // Insert SQL keyword
                    {
                        const char* keywords[] = {
                            "SELECT", "FROM", "WHERE", "AND", "OR", "UNION",
                            "JOIN", "LEFT", "RIGHT", "INNER", "OUTER", "ON",
                            "GROUP BY", "ORDER BY", "HAVING", "LIMIT", "OFFSET",
                            "INSERT", "UPDATE", "DELETE", "CREATE", "DROP",
                            "ALTER", "TABLE", "INDEX", "VIEW", "AS", "NULL",
                            "NOT", "IN", "LIKE", "BETWEEN", "CASE", "WHEN",
                            "THEN", "ELSE", "END", "OVER", "PARTITION BY",
                            "ROWS", "RANGE", "UNBOUNDED", "PRECEDING", "FOLLOWING",
                            "CURRENT ROW", "CAST", "EXTRACT", "COUNT", "SUM",
                            "AVG", "MIN", "MAX", "DISTINCT", "ALL", "ANY", "SOME"
                        };
                        size_t idx = dist(gen) % (sizeof(keywords) / sizeof(keywords[0]));
                        size_t pos = result.empty() ? 0 : (dist(gen) % result.size());
                        result.insert(pos, keywords[idx]);
                    }
                    break;
                case 5: // Bit flip
                    if (!result.empty()) {
                        size_t pos = dist(gen) % result.size();
                        result[pos] ^= (1 << (dist(gen) % 8));
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

    SQLFuzzer fuzzer;

    // Seed corpus
    std::vector<std::string> corpus = {
        "SELECT * FROM users",
        "SELECT id, name FROM products WHERE price > 100",
        "SELECT COUNT(*) FROM orders GROUP BY customer_id",
        "SELECT * FROM a JOIN b ON a.id = b.id",
        "SELECT SUM(x) OVER (PARTITION BY y ORDER BY z) FROM t",
        "SELECT * FROM t WHERE x IN (SELECT y FROM s)",
        "WITH cte AS (SELECT * FROM t) SELECT * FROM cte",
        "SELECT CASE WHEN x > 0 THEN 1 ELSE 0 END FROM t",
        "INSERT INTO t VALUES (1, 2, 3)",
        "UPDATE t SET x = 1 WHERE y = 2",
        "DELETE FROM t WHERE x > 100",
        "SELECT x FROM t UNION ALL SELECT y FROM s",
        "SELECT * FROM t ORDER BY x DESC LIMIT 10",
        "SELECT EXTRACT(YEAR FROM date_col) FROM t",
        "SELECT CAST(x AS INTEGER) FROM t",
        "SELECT ROW_NUMBER() OVER (ORDER BY x) FROM t",
        "SELECT FIRST_VALUE(x) OVER (ROWS BETWEEN UNBOUNDED PRECEDING AND UNBOUNDED FOLLOWING) FROM t",
        "SELECT * FROM t WHERE x BETWEEN 1 AND 100",
        "SELECT * FROM t WHERE name LIKE '%test%'",
        "SELECT COALESCE(x, y, z) FROM t"
    };

    uint64_t iterations = 0;
    uint64_t crashes = 0;
    uint64_t timeouts = 0;
    auto start_time = std::chrono::steady_clock::now();

    std::cout << "Starting fuzzer...\n";
    std::cout << "Press Ctrl+C to stop\n\n";

    while (running) {
        // Pick random seed from corpus
        std::string seed = corpus[iterations % corpus.size()];

        // Mutate it
        std::string mutated = fuzzer.mutate(seed);

        // Try to parse
        try {
            libsqlglot::Arena arena;
            auto result = libsqlglot::Transpiler::parse(arena, mutated);

            // If it parsed successfully, add to corpus occasionally
            if (iterations % 100 == 0 && corpus.size() < 1000) {
                corpus.push_back(mutated);
            }
        } catch (const std::exception& e) {
            // Expected - most random SQL is invalid
        } catch (...) {
            crashes++;
            std::cout << "\n=== CRASH DETECTED ===\n";
            std::cout << "Input: " << mutated << "\n";
            std::cout << "Length: " << mutated.size() << " bytes\n";
            std::cout << "======================\n\n";
        }

        iterations++;

        // Progress reporting every 10000 iterations
        if (iterations % 10000 == 0) {
            auto now = std::chrono::steady_clock::now();
            auto elapsed = std::chrono::duration_cast<std::chrono::seconds>(now - start_time).count();
            double rate = iterations / (elapsed > 0 ? elapsed : 1);

            std::cout << "\rIterations: " << iterations
                      << " | Corpus: " << corpus.size()
                      << " | Crashes: " << crashes
                      << " | Rate: " << static_cast<int>(rate) << "/s"
                      << std::flush;
        }
    }

    auto end_time = std::chrono::steady_clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::seconds>(end_time - start_time).count();

    std::cout << "\n\n=== Fuzzing Summary ===\n";
    std::cout << "Total iterations: " << iterations << "\n";
    std::cout << "Corpus size: " << corpus.size() << "\n";
    std::cout << "Crashes: " << crashes << "\n";
    std::cout << "Time: " << elapsed << "s\n";
    std::cout << "Avg rate: " << (iterations / (elapsed > 0 ? elapsed : 1)) << " iter/s\n";

    return crashes > 0 ? 1 : 0;
}
