#include <benchmark/benchmark.h>
#include <libsqlglot/transpiler.h>
#include <libsqlglot/dialects.h>

using namespace libsqlglot;

// Simple transpile
static void BM_Transpiler_Simple(benchmark::State& state) {
    const char* sql = "SELECT * FROM users";
    
    for (auto _ : state) {
        auto result = Transpiler::transpile(sql, Dialect::ANSI, Dialect::ANSI);
        benchmark::DoNotOptimize(result);
    }
    
    state.SetItemsProcessed(state.iterations());
}
BENCHMARK(BM_Transpiler_Simple);

// WITH WHERE
static void BM_Transpiler_WithWhere(benchmark::State& state) {
    const char* sql = "SELECT id, name FROM users WHERE age > 18 AND active = 1";
    
    for (auto _ : state) {
        auto result = Transpiler::transpile(sql, Dialect::ANSI, Dialect::PostgreSQL);
        benchmark::DoNotOptimize(result);
    }
    
    state.SetItemsProcessed(state.iterations());
}
BENCHMARK(BM_Transpiler_WithWhere);

// Complex JOIN
static void BM_Transpiler_ComplexJoin(benchmark::State& state) {
    const char* sql = R"(
        SELECT u.id, u.name, COUNT(o.id) as order_count
        FROM users u
        LEFT JOIN orders o ON u.id = o.user_id
        WHERE u.active = 1
        GROUP BY u.id, u.name
        HAVING COUNT(o.id) > 5
        ORDER BY order_count DESC
        LIMIT 100
    )";
    
    for (auto _ : state) {
        auto result = Transpiler::transpile(sql, Dialect::MySQL, Dialect::PostgreSQL);
        benchmark::DoNotOptimize(result);
    }
    
    state.SetItemsProcessed(state.iterations());
}
BENCHMARK(BM_Transpiler_ComplexJoin);

// CTE
static void BM_Transpiler_CTE(benchmark::State& state) {
    const char* sql = R"(
        WITH active_users AS (
            SELECT id, name FROM users WHERE active = 1
        )
        SELECT * FROM active_users WHERE id > 100
    )";
    
    for (auto _ : state) {
        auto result = Transpiler::transpile(sql, Dialect::ANSI, Dialect::PostgreSQL);
        benchmark::DoNotOptimize(result);
    }
    
    state.SetItemsProcessed(state.iterations());
}
BENCHMARK(BM_Transpiler_CTE);

// Window Function
static void BM_Transpiler_WindowFunction(benchmark::State& state) {
    const char* sql = R"(
        SELECT 
            id,
            name,
            ROW_NUMBER() OVER (ORDER BY score DESC) as rank
        FROM employees
    )";
    
    for (auto _ : state) {
        auto result = Transpiler::transpile(sql, Dialect::ANSI, Dialect::PostgreSQL);
        benchmark::DoNotOptimize(result);
    }
    
    state.SetItemsProcessed(state.iterations());
}
BENCHMARK(BM_Transpiler_WindowFunction);

// Dialect conversion: MySQL to Postgres
static void BM_Transpiler_MySQLToPostgres(benchmark::State& state) {
    const char* sql = "SELECT id, name FROM users LIMIT 10";
    
    for (auto _ : state) {
        auto result = Transpiler::transpile(sql, Dialect::MySQL, Dialect::PostgreSQL);
        benchmark::DoNotOptimize(result);
    }
    
    state.SetItemsProcessed(state.iterations());
}
BENCHMARK(BM_Transpiler_MySQLToPostgres);

// Dialect conversion: SQLite to BigQuery
static void BM_Transpiler_SQLiteToBigQuery(benchmark::State& state) {
    const char* sql = "SELECT * FROM users WHERE id IN (1, 2, 3)";
    
    for (auto _ : state) {
        auto result = Transpiler::transpile(sql, Dialect::SQLite, Dialect::BigQuery);
        benchmark::DoNotOptimize(result);
    }
    
    state.SetItemsProcessed(state.iterations());
}
BENCHMARK(BM_Transpiler_SQLiteToBigQuery);

// Multiple statements (batching)
static void BM_Transpiler_Batch10(benchmark::State& state) {
    std::vector<std::string> queries = {
        "SELECT * FROM users WHERE id = 1",
        "SELECT * FROM users WHERE id = 2",
        "SELECT * FROM users WHERE id = 3",
        "SELECT * FROM users WHERE id = 4",
        "SELECT * FROM users WHERE id = 5",
        "SELECT * FROM users WHERE id = 6",
        "SELECT * FROM users WHERE id = 7",
        "SELECT * FROM users WHERE id = 8",
        "SELECT * FROM users WHERE id = 9",
        "SELECT * FROM users WHERE id = 10",
    };
    
    for (auto _ : state) {
        for (const auto& sql : queries) {
            auto result = Transpiler::transpile(sql, Dialect::ANSI, Dialect::PostgreSQL);
            benchmark::DoNotOptimize(result);
        }
    }
    
    state.SetItemsProcessed(state.iterations() * queries.size());
}
BENCHMARK(BM_Transpiler_Batch10);

// Subquery
static void BM_Transpiler_Subquery(benchmark::State& state) {
    const char* sql = R"(
        SELECT * FROM users WHERE id IN (
            SELECT user_id FROM orders WHERE status = 'active'
        )
    )";
    
    for (auto _ : state) {
        auto result = Transpiler::transpile(sql, Dialect::ANSI, Dialect::PostgreSQL);
        benchmark::DoNotOptimize(result);
    }
    
    state.SetItemsProcessed(state.iterations());
}
BENCHMARK(BM_Transpiler_Subquery);

BENCHMARK_MAIN();
