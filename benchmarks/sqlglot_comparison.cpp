/**
 * Benchmark comparison matching sqlglot's official benchmark suite
 *
 * Queries match: https://github.com/tobymao/sqlglot/tree/main/benchmarks
 */

#include <iostream>
#include <chrono>
#include <vector>
#include <string>
#include <iomanip>
#include "../include/libsqlglot/transpiler.h"
#include "../include/libsqlglot/arena.h"
#include "../include/libsqlglot/parser.h"
#include "../include/libsqlglot/generator.h"

using namespace libsqlglot;
using namespace std::chrono;

struct BenchmarkResult {
    std::string name;
    double avg_time;
    size_t iterations;
};

double benchmark_query(const std::string& sql, size_t iterations = 1000) {
    std::vector<double> times;
    times.reserve(iterations);

    for (size_t i = 0; i < iterations; ++i) {
        auto start = high_resolution_clock::now();

        Arena arena;
        Parser parser(arena, sql);
        auto expr = parser.parse();
        std::string output = Generator::generate(expr);

        auto end = high_resolution_clock::now();
        duration<double> elapsed = end - start;
        times.push_back(elapsed.count());
    }

    // Calculate average
    double sum = 0.0;
    for (double t : times) {
        sum += t;
    }
    return sum / times.size();
}

int main() {
    std::cout << "libsqlglot Benchmark Suite - Matching sqlglot queries\n";
    std::cout << "========================================================\n\n";

    std::vector<BenchmarkResult> results;

    // 1. tpch - Typical TPC-H style query
    {
        std::string sql = R"(
            SELECT
                l_returnflag,
                l_linestatus,
                SUM(l_quantity) as sum_qty,
                SUM(l_extendedprice) as sum_base_price,
                SUM(l_extendedprice * (1 - l_discount)) as sum_disc_price,
                SUM(l_extendedprice * (1 - l_discount) * (1 + l_tax)) as sum_charge,
                AVG(l_quantity) as avg_qty,
                AVG(l_extendedprice) as avg_price,
                AVG(l_discount) as avg_disc,
                COUNT(*) as count_order
            FROM lineitem
            WHERE l_shipdate <= '1998-12-01'
            GROUP BY l_returnflag, l_linestatus
            ORDER BY l_returnflag, l_linestatus
        )";
        double time = benchmark_query(sql);
        results.push_back({"tpch", time, 1000});
    }

    // 2. short - Simple SELECT
    {
        std::string sql = "SELECT a FROM b";
        double time = benchmark_query(sql);
        results.push_back({"short", time, 1000});
    }

    // 3. deep_arithmetic - Deeply nested arithmetic
    {
        std::string sql = "SELECT ((((((1 + 2) * 3) / 4) - 5) + 6) * 7) / 8 as result";
        double time = benchmark_query(sql);
        results.push_back({"deep_arithmetic", time, 1000});
    }

    // 4. large_in - Large IN clause
    {
        std::string sql = "SELECT * FROM users WHERE id IN (";
        for (int i = 0; i < 1000; ++i) {
            if (i > 0) sql += ", ";
            sql += std::to_string(i);
        }
        sql += ")";
        double time = benchmark_query(sql, 100);  // Fewer iterations for large query
        results.push_back({"large_in", time, 100});
    }

    // 5. values - Large VALUES clause
    {
        std::string sql = "INSERT INTO users (id, name) VALUES ";
        for (int i = 0; i < 500; ++i) {
            if (i > 0) sql += ", ";
            sql += "(" + std::to_string(i) + ", 'user" + std::to_string(i) + "')";
        }
        double time = benchmark_query(sql, 100);
        results.push_back({"values", time, 100});
    }

    // 6. many_joins - Multiple JOIN operations
    {
        std::string sql = R"(
            SELECT *
            FROM t1
            JOIN t2 ON t1.id = t2.id
            JOIN t3 ON t2.id = t3.id
            JOIN t4 ON t3.id = t4.id
            JOIN t5 ON t4.id = t5.id
            JOIN t6 ON t5.id = t6.id
            JOIN t7 ON t6.id = t7.id
            JOIN t8 ON t7.id = t8.id
            JOIN t9 ON t8.id = t9.id
            JOIN t10 ON t9.id = t10.id
        )";
        double time = benchmark_query(sql);
        results.push_back({"many_joins", time, 1000});
    }

    // 7. many_unions - Multiple UNION operations
    {
        std::string sql = "";
        for (int i = 0; i < 50; ++i) {
            if (i > 0) sql += " UNION ";
            sql += "SELECT " + std::to_string(i) + " as n";
        }
        double time = benchmark_query(sql);
        results.push_back({"many_unions", time, 1000});
    }

    // 8. nested_subqueries - Deep subquery nesting
    {
        std::string sql = R"(
            SELECT * FROM (
                SELECT * FROM (
                    SELECT * FROM (
                        SELECT * FROM (
                            SELECT * FROM users
                        ) a
                    ) b
                ) c
            ) d
        )";
        double time = benchmark_query(sql);
        results.push_back({"nested_subqueries", time, 1000});
    }

    // 9. many_columns - Wide SELECT with many columns
    {
        std::string sql = "SELECT ";
        for (int i = 0; i < 100; ++i) {
            if (i > 0) sql += ", ";
            sql += "col" + std::to_string(i);
        }
        sql += " FROM wide_table";
        double time = benchmark_query(sql);
        results.push_back({"many_columns", time, 1000});
    }

    // 10. large_case - Large CASE expression
    {
        std::string sql = "SELECT CASE ";
        for (int i = 0; i < 100; ++i) {
            sql += "WHEN x = " + std::to_string(i) + " THEN " + std::to_string(i * 10) + " ";
        }
        sql += "ELSE 0 END as result FROM t";
        double time = benchmark_query(sql);
        results.push_back({"large_case", time, 1000});
    }

    // 11. complex_where - Complex WHERE clause
    {
        std::string sql = R"(
            SELECT * FROM users
            WHERE (age > 18 AND age < 65)
                AND (status = 'active' OR status = 'pending')
                AND (score > 100 OR (level > 5 AND experience > 1000))
                AND created_at > '2020-01-01'
                AND updated_at < '2025-12-31'
        )";
        double time = benchmark_query(sql);
        results.push_back({"complex_where", time, 1000});
    }

    // 12. many_ctes - Multiple CTEs
    {
        std::string sql = R"(
            WITH cte1 AS (SELECT * FROM t1),
                 cte2 AS (SELECT * FROM t2),
                 cte3 AS (SELECT * FROM t3),
                 cte4 AS (SELECT * FROM t4),
                 cte5 AS (SELECT * FROM t5),
                 cte6 AS (SELECT * FROM cte1 JOIN cte2 ON cte1.id = cte2.id)
            SELECT * FROM cte6
        )";
        double time = benchmark_query(sql);
        results.push_back({"many_ctes", time, 1000});
    }

    // 13. many_windows - Multiple window functions
    {
        std::string sql = R"(
            SELECT
                id,
                ROW_NUMBER() OVER (ORDER BY id) as rn1,
                RANK() OVER (ORDER BY score) as rn2,
                DENSE_RANK() OVER (PARTITION BY category ORDER BY score DESC) as rn3,
                LAG(value) OVER (ORDER BY event_date) as lag_val,
                LEAD(value) OVER (ORDER BY event_date) as lead_val,
                SUM(amount) OVER (PARTITION BY user_id ORDER BY event_date) as running_sum
            FROM data
        )";
        double time = benchmark_query(sql);
        results.push_back({"many_windows", time, 1000});
    }

    // 14. nested_functions - Deeply nested function calls
    {
        std::string sql = R"(
            SELECT
                UPPER(LOWER(TRIM(SUBSTRING(CONCAT(COALESCE(name, ''), ' - '), 1, 10)))) as processed,
                ROUND(ABS(SQRT(POWER(x, 2) + POWER(y, 2))), 2) as distance
            FROM points
        )";
        double time = benchmark_query(sql);
        results.push_back({"nested_functions", time, 1000});
    }

    // 15. large_strings - Large string literals
    {
        std::string large_str(1000, 'x');
        std::string sql = "SELECT '" + large_str + "' as long_string FROM t";
        double time = benchmark_query(sql);
        results.push_back({"large_strings", time, 1000});
    }

    // 16. many_numbers - Many numeric literals
    {
        std::string sql = "SELECT ";
        for (int i = 0; i < 500; ++i) {
            if (i > 0) sql += " + ";
            sql += std::to_string(i);
        }
        sql += " as total";
        double time = benchmark_query(sql);
        results.push_back({"many_numbers", time, 1000});
    }

    // Print results
    std::cout << std::left << std::setw(25) << "Query"
              << std::right << std::setw(15) << "Time (μs)"
              << std::setw(15) << "Iterations" << "\n";
    std::cout << std::string(55, '-') << "\n";

    double total_time_seconds = 0.0;
    for (const auto& result : results) {
        double time_us = result.avg_time * 1'000'000;  // Convert to microseconds
        total_time_seconds += result.avg_time;
        std::cout << std::left << std::setw(25) << result.name
                  << std::right << std::setw(15) << std::fixed << std::setprecision(2) << time_us
                  << std::setw(15) << result.iterations << "\n";
    }

    std::cout << "\nNotes:\n";
    std::cout << "- Times are in microseconds (μs), average per query\n";
    std::cout << "- Includes full parse + generate cycle (round-trip)\n";
    std::cout << "- Compare with sqlglot benchmarks: https://github.com/tobymao/sqlglot#benchmarks\n";

    return 0;
}
