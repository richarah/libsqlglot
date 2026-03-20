#include <benchmark/benchmark.h>
#include <libsqlglot/tokenizer.h>
#include <libsqlglot/arena.h>
#include <string_view>

using namespace libsqlglot;

// Simple SELECT
static void BM_Tokenizer_Simple(benchmark::State& state) {
    const char* sql = "SELECT * FROM users";
    LocalStringPool pool;
    
    for (auto _ : state) {
        Tokenizer tokenizer(sql, &pool);
        auto tokens = tokenizer.tokenize_all();
        benchmark::DoNotOptimize(tokens);
    }
    
    state.SetItemsProcessed(state.iterations());
}
BENCHMARK(BM_Tokenizer_Simple);

// SELECT with WHERE
static void BM_Tokenizer_WithWhere(benchmark::State& state) {
    const char* sql = "SELECT id, name, email FROM users WHERE age > 18 AND active = 1";
    LocalStringPool pool;
    
    for (auto _ : state) {
        Tokenizer tokenizer(sql, &pool);
        auto tokens = tokenizer.tokenize_all();
        benchmark::DoNotOptimize(tokens);
    }
    
    state.SetItemsProcessed(state.iterations());
}
BENCHMARK(BM_Tokenizer_WithWhere);

// Complex query with JOIN
static void BM_Tokenizer_ComplexJoin(benchmark::State& state) {
    const char* sql = R"(
        SELECT u.id, u.name, COUNT(o.id) as order_count
        FROM users u
        LEFT JOIN orders o ON u.id = o.user_id
        WHERE u.active = 1 AND u.age > 18
        GROUP BY u.id, u.name
        HAVING COUNT(o.id) > 5
        ORDER BY order_count DESC
        LIMIT 100
    )";
    LocalStringPool pool;
    
    for (auto _ : state) {
        Tokenizer tokenizer(sql, &pool);
        auto tokens = tokenizer.tokenize_all();
        benchmark::DoNotOptimize(tokens);
    }
    
    state.SetItemsProcessed(state.iterations());
}
BENCHMARK(BM_Tokenizer_ComplexJoin);

// CTE with subquery
static void BM_Tokenizer_CTE(benchmark::State& state) {
    const char* sql = R"(
        WITH active_users AS (
            SELECT id, name FROM users WHERE active = 1
        ),
        user_orders AS (
            SELECT user_id, COUNT(*) as order_count
            FROM orders
            GROUP BY user_id
        )
        SELECT au.name, uo.order_count
        FROM active_users au
        JOIN user_orders uo ON au.id = uo.user_id
        WHERE uo.order_count > 10
    )";
    LocalStringPool pool;
    
    for (auto _ : state) {
        Tokenizer tokenizer(sql, &pool);
        auto tokens = tokenizer.tokenize_all();
        benchmark::DoNotOptimize(tokens);
    }
    
    state.SetItemsProcessed(state.iterations());
}
BENCHMARK(BM_Tokenizer_CTE);

// Window function
static void BM_Tokenizer_WindowFunction(benchmark::State& state) {
    const char* sql = R"(
        SELECT 
            id,
            name,
            score,
            ROW_NUMBER() OVER (PARTITION BY department ORDER BY score DESC) as rank,
            AVG(score) OVER (PARTITION BY department) as avg_score
        FROM employees
    )";
    LocalStringPool pool;
    
    for (auto _ : state) {
        Tokenizer tokenizer(sql, &pool);
        auto tokens = tokenizer.tokenize_all();
        benchmark::DoNotOptimize(tokens);
    }
    
    state.SetItemsProcessed(state.iterations());
}
BENCHMARK(BM_Tokenizer_WindowFunction);

// String literals
static void BM_Tokenizer_StringLiterals(benchmark::State& state) {
    const char* sql = "SELECT 'hello', 'world', 'this is a test', '123', 'another string' FROM dual";
    LocalStringPool pool;
    
    for (auto _ : state) {
        Tokenizer tokenizer(sql, &pool);
        auto tokens = tokenizer.tokenize_all();
        benchmark::DoNotOptimize(tokens);
    }
    
    state.SetItemsProcessed(state.iterations());
}
BENCHMARK(BM_Tokenizer_StringLiterals);

// Numbers
static void BM_Tokenizer_Numbers(benchmark::State& state) {
    const char* sql = "SELECT 1, 2.5, 100, 999.999, 1.23e10, 0x1F, 0b1010 FROM dual";
    LocalStringPool pool;
    
    for (auto _ : state) {
        Tokenizer tokenizer(sql, &pool);
        auto tokens = tokenizer.tokenize_all();
        benchmark::DoNotOptimize(tokens);
    }
    
    state.SetItemsProcessed(state.iterations());
}
BENCHMARK(BM_Tokenizer_Numbers);

// Keywords
static void BM_Tokenizer_ManyKeywords(benchmark::State& state) {
    const char* sql = "SELECT DISTINCT id FROM users WHERE id IN (SELECT user_id FROM orders WHERE status = 'active') ORDER BY id LIMIT 10 OFFSET 20";
    LocalStringPool pool;
    
    for (auto _ : state) {
        Tokenizer tokenizer(sql, &pool);
        auto tokens = tokenizer.tokenize_all();
        benchmark::DoNotOptimize(tokens);
    }
    
    state.SetItemsProcessed(state.iterations());
}
BENCHMARK(BM_Tokenizer_ManyKeywords);

BENCHMARK_MAIN();
