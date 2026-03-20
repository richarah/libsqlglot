#include <benchmark/benchmark.h>
#include <libsqlglot/parser.h>
#include <libsqlglot/arena.h>

using namespace libsqlglot;

// Simple SELECT
static void BM_Parser_Simple(benchmark::State& state) {
    const char* sql = "SELECT * FROM users";
    
    for (auto _ : state) {
        Arena arena;
        Parser parser(arena, sql);
        auto stmt = parser.parse_select();
        benchmark::DoNotOptimize(stmt);
    }
    
    state.SetItemsProcessed(state.iterations());
}
BENCHMARK(BM_Parser_Simple);

// SELECT with WHERE
static void BM_Parser_WithWhere(benchmark::State& state) {
    const char* sql = "SELECT id, name, email FROM users WHERE age > 18 AND active = 1";
    
    for (auto _ : state) {
        Arena arena;
        Parser parser(arena, sql);
        auto stmt = parser.parse_select();
        benchmark::DoNotOptimize(stmt);
    }
    
    state.SetItemsProcessed(state.iterations());
}
BENCHMARK(BM_Parser_WithWhere);

// Complex JOIN
static void BM_Parser_ComplexJoin(benchmark::State& state) {
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
    
    for (auto _ : state) {
        Arena arena;
        Parser parser(arena, sql);
        auto stmt = parser.parse_select();
        benchmark::DoNotOptimize(stmt);
    }
    
    state.SetItemsProcessed(state.iterations());
}
BENCHMARK(BM_Parser_ComplexJoin);

// CTE
static void BM_Parser_CTE(benchmark::State& state) {
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
    
    for (auto _ : state) {
        Arena arena;
        Parser parser(arena, sql);
        auto stmt = parser.parse_select();
        benchmark::DoNotOptimize(stmt);
    }
    
    state.SetItemsProcessed(state.iterations());
}
BENCHMARK(BM_Parser_CTE);

// Window Function
static void BM_Parser_WindowFunction(benchmark::State& state) {
    const char* sql = R"(
        SELECT 
            id,
            name,
            score,
            ROW_NUMBER() OVER (PARTITION BY department ORDER BY score DESC) as rank,
            AVG(score) OVER (PARTITION BY department) as avg_score
        FROM employees
    )";
    
    for (auto _ : state) {
        Arena arena;
        Parser parser(arena, sql);
        auto stmt = parser.parse_select();
        benchmark::DoNotOptimize(stmt);
    }
    
    state.SetItemsProcessed(state.iterations());
}
BENCHMARK(BM_Parser_WindowFunction);

// INSERT
static void BM_Parser_Insert(benchmark::State& state) {
    const char* sql = "INSERT INTO users (id, name, email) VALUES (1, 'Alice', 'alice@example.com'), (2, 'Bob', 'bob@example.com')";
    
    for (auto _ : state) {
        Arena arena;
        Parser parser(arena, sql);
        auto stmt = parser.parse_insert();
        benchmark::DoNotOptimize(stmt);
    }
    
    state.SetItemsProcessed(state.iterations());
}
BENCHMARK(BM_Parser_Insert);

// UPDATE
static void BM_Parser_Update(benchmark::State& state) {
    const char* sql = "UPDATE users SET name = 'Updated', email = 'updated@example.com' WHERE id = 1 AND active = 1";
    
    for (auto _ : state) {
        Arena arena;
        Parser parser(arena, sql);
        auto stmt = parser.parse_update();
        benchmark::DoNotOptimize(stmt);
    }
    
    state.SetItemsProcessed(state.iterations());
}
BENCHMARK(BM_Parser_Update);

// CREATE TABLE
static void BM_Parser_CreateTable(benchmark::State& state) {
    const char* sql = R"(
        CREATE TABLE users (
            id INT PRIMARY KEY,
            name VARCHAR(255) NOT NULL,
            email VARCHAR(255) UNIQUE,
            age INT DEFAULT 0,
            active BOOLEAN DEFAULT TRUE
        )
    )";
    
    for (auto _ : state) {
        Arena arena;
        Parser parser(arena, sql);
        auto stmt = parser.parse_create_table();
        benchmark::DoNotOptimize(stmt);
    }
    
    state.SetItemsProcessed(state.iterations());
}
BENCHMARK(BM_Parser_CreateTable);

// Nested subqueries
static void BM_Parser_NestedSubqueries(benchmark::State& state) {
    const char* sql = R"(
        SELECT * FROM (
            SELECT * FROM (
                SELECT id, name FROM users WHERE active = 1
            ) t1 WHERE name LIKE 'A%'
        ) t2 WHERE id > 100
    )";
    
    for (auto _ : state) {
        Arena arena;
        Parser parser(arena, sql);
        auto stmt = parser.parse_select();
        benchmark::DoNotOptimize(stmt);
    }
    
    state.SetItemsProcessed(state.iterations());
}
BENCHMARK(BM_Parser_NestedSubqueries);

BENCHMARK_MAIN();
