#include <benchmark/benchmark.h>
#include <libsqlglot/transpiler.h>
#include <libsqlglot/parser.h>
#include <libsqlglot/tokenizer.h>
#include <string>

using namespace libsqlglot;

// =============================================================================
// Tokenizer Benchmarks - Hot Path #1
// =============================================================================
// The tokenizer is called for every query and processes every character

static void BM_Tokenizer_Simple(benchmark::State& state) {
    std::string sql = "SELECT id, name, email FROM users WHERE age > 18";
    LocalStringPool pool;

    for (auto _ : state) {
        Tokenizer tokenizer(sql, &pool);
        auto tokens = tokenizer.tokenize_all();
        benchmark::DoNotOptimize(tokens);
    }

    state.SetBytesProcessed(state.iterations() * sql.size());
}
BENCHMARK(BM_Tokenizer_Simple);

static void BM_Tokenizer_Complex(benchmark::State& state) {
    std::string sql = R"(
        WITH ranked AS (
            SELECT *,
                   ROW_NUMBER() OVER (PARTITION BY category ORDER BY price DESC) as rank
            FROM products
            WHERE price > 100
        )
        SELECT category, product, price, rank
        FROM ranked
        WHERE rank <= 10
        ORDER BY category, rank
    )";
    LocalStringPool pool;

    for (auto _ : state) {
        Tokenizer tokenizer(sql, &pool);
        auto tokens = tokenizer.tokenize_all();
        benchmark::DoNotOptimize(tokens);
    }

    state.SetBytesProcessed(state.iterations() * sql.size());
}
BENCHMARK(BM_Tokenizer_Complex);

static void BM_Tokenizer_LongIdentifiers(benchmark::State& state) {
    std::string sql = "SELECT very_long_column_name_with_many_underscores FROM "
                     "very_long_table_name_with_many_underscores WHERE "
                     "very_long_column_name_with_many_underscores > 100";
    LocalStringPool pool;

    for (auto _ : state) {
        Tokenizer tokenizer(sql, &pool);
        auto tokens = tokenizer.tokenize_all();
        benchmark::DoNotOptimize(tokens);
    }

    state.SetBytesProcessed(state.iterations() * sql.size());
}
BENCHMARK(BM_Tokenizer_LongIdentifiers);

// =============================================================================
// Parser Benchmarks - Hot Path #2
// =============================================================================
// Parser is the most complex and CPU-intensive component

static void BM_Parser_Simple(benchmark::State& state) {
    std::string sql = "SELECT * FROM users WHERE id = 1";

    for (auto _ : state) {
        Arena arena;
        Parser parser(arena, sql);
        auto result = parser.parse();
        benchmark::DoNotOptimize(result);
    }
}
BENCHMARK(BM_Parser_Simple);

static void BM_Parser_Join(benchmark::State& state) {
    std::string sql = "SELECT u.name, o.total FROM users u "
                     "INNER JOIN orders o ON u.id = o.user_id "
                     "WHERE o.status = 'completed'";

    for (auto _ : state) {
        Arena arena;
        Parser parser(arena, sql);
        auto result = parser.parse();
        benchmark::DoNotOptimize(result);
    }
}
BENCHMARK(BM_Parser_Join);

static void BM_Parser_MultiJoin(benchmark::State& state) {
    std::string sql = "SELECT * FROM users u "
                     "JOIN orders o ON u.id = o.user_id "
                     "JOIN products p ON o.product_id = p.id "
                     "JOIN categories c ON p.category_id = c.id";

    for (auto _ : state) {
        Arena arena;
        Parser parser(arena, sql);
        auto result = parser.parse();
        benchmark::DoNotOptimize(result);
    }
}
BENCHMARK(BM_Parser_MultiJoin);

static void BM_Parser_CTE(benchmark::State& state) {
    std::string sql = R"(
        WITH cte1 AS (SELECT * FROM users WHERE age > 18),
             cte2 AS (SELECT * FROM orders WHERE total > 100)
        SELECT * FROM cte1 JOIN cte2 ON cte1.id = cte2.user_id
    )";

    for (auto _ : state) {
        Arena arena;
        Parser parser(arena, sql);
        auto result = parser.parse();
        benchmark::DoNotOptimize(result);
    }
}
BENCHMARK(BM_Parser_CTE);

static void BM_Parser_WindowFunction(benchmark::State& state) {
    std::string sql = "SELECT *, ROW_NUMBER() OVER (PARTITION BY category ORDER BY price DESC) "
                     "FROM products";

    for (auto _ : state) {
        Arena arena;
        Parser parser(arena, sql);
        auto result = parser.parse();
        benchmark::DoNotOptimize(result);
    }
}
BENCHMARK(BM_Parser_WindowFunction);

static void BM_Parser_Subquery(benchmark::State& state) {
    std::string sql = "SELECT * FROM users WHERE id IN "
                     "(SELECT user_id FROM orders WHERE total > 1000)";

    for (auto _ : state) {
        Arena arena;
        Parser parser(arena, sql);
        auto result = parser.parse();
        benchmark::DoNotOptimize(result);
    }
}
BENCHMARK(BM_Parser_Subquery);

// =============================================================================
// Generator Benchmarks - Hot Path #3
// =============================================================================
// Generator converts AST back to SQL text

static void BM_Generator_Simple(benchmark::State& state) {
    std::string sql = "SELECT * FROM users WHERE id = 1";
    Arena arena;
    Parser parser(arena, sql);
    auto stmt = parser.parse();

    for (auto _ : state) {
        std::string result = Generator::generate(stmt);
        benchmark::DoNotOptimize(result);
    }
}
BENCHMARK(BM_Generator_Simple);

static void BM_Generator_Complex(benchmark::State& state) {
    std::string sql = R"(
        WITH ranked AS (
            SELECT *, ROW_NUMBER() OVER (PARTITION BY category ORDER BY price DESC) as rank
            FROM products
        )
        SELECT * FROM ranked WHERE rank <= 10
    )";
    Arena arena;
    Parser parser(arena, sql);
    auto stmt = parser.parse();

    for (auto _ : state) {
        std::string result = Generator::generate(stmt);
        benchmark::DoNotOptimize(result);
    }
}
BENCHMARK(BM_Generator_Complex);

// =============================================================================
// Full Pipeline Benchmarks - Hot Path #4
// =============================================================================
// Complete tokenize → parse → generate → transpile pipeline

static void BM_Transpile_Simple(benchmark::State& state) {
    std::string sql = "SELECT * FROM users WHERE age > 18";

    for (auto _ : state) {
        auto result = Transpiler::transpile(sql);
        benchmark::DoNotOptimize(result);
    }
}
BENCHMARK(BM_Transpile_Simple);

static void BM_Transpile_CrossDialect(benchmark::State& state) {
    std::string sql = "SELECT * FROM users WHERE age > 18 LIMIT 10";

    for (auto _ : state) {
        auto result = Transpiler::transpile(sql, Dialect::MySQL, Dialect::PostgreSQL);
        benchmark::DoNotOptimize(result);
    }
}
BENCHMARK(BM_Transpile_CrossDialect);

static void BM_Transpile_Complex(benchmark::State& state) {
    std::string sql = R"(
        WITH user_orders AS (
            SELECT u.id, u.name, COUNT(*) as order_count, SUM(o.total) as total_spent
            FROM users u
            JOIN orders o ON u.id = o.user_id
            WHERE o.status = 'completed'
            GROUP BY u.id, u.name
        )
        SELECT * FROM user_orders WHERE total_spent > 1000 ORDER BY total_spent DESC
    )";

    for (auto _ : state) {
        auto result = Transpiler::transpile(sql);
        benchmark::DoNotOptimize(result);
    }
}
BENCHMARK(BM_Transpile_Complex);

// =============================================================================
// String Interning Benchmarks - Memory Hot Path
// =============================================================================
// String interning is critical for memory efficiency and lookup speed

static void BM_StringPool_Intern(benchmark::State& state) {
    LocalStringPool pool;
    std::vector<std::string> strings = {
        "SELECT", "FROM", "WHERE", "users", "orders", "products",
        "id", "name", "email", "age", "price", "quantity"
    };

    size_t idx = 0;
    for (auto _ : state) {
        const char* interned = pool.intern(strings[idx % strings.size()]);
        benchmark::DoNotOptimize(interned);
        idx++;
    }
}
BENCHMARK(BM_StringPool_Intern);

static void BM_StringPool_InternLong(benchmark::State& state) {
    LocalStringPool pool;
    std::string long_string(100, 'a');

    for (auto _ : state) {
        const char* interned = pool.intern(long_string);
        benchmark::DoNotOptimize(interned);
    }
}
BENCHMARK(BM_StringPool_InternLong);

// =============================================================================
// Arena Allocator Benchmarks - Memory Hot Path
// =============================================================================
// Arena allocation is used for all AST nodes

static void BM_Arena_Allocate(benchmark::State& state) {
    for (auto _ : state) {
        Arena arena;
        // Simulate typical parse workload - many small allocations
        for (int i = 0; i < 1000; ++i) {
            void* ptr = arena.allocate(64);
            benchmark::DoNotOptimize(ptr);
        }
    }
}
BENCHMARK(BM_Arena_Allocate);

static void BM_Arena_Create(benchmark::State& state) {
    struct TestNode {
        int value;
        const char* name;
        TestNode* left;
        TestNode* right;
    };

    for (auto _ : state) {
        Arena arena;
        // Simulate AST node creation
        for (int i = 0; i < 100; ++i) {
            auto node = arena.create<TestNode>();
            benchmark::DoNotOptimize(node);
        }
    }
}
BENCHMARK(BM_Arena_Create);

// =============================================================================
// Real-World Query Benchmarks
// =============================================================================
// Queries from actual production workloads

static void BM_RealWorld_Dashboard(benchmark::State& state) {
    std::string sql = R"(
        SELECT
            DATE_TRUNC('day', created_at) as date,
            COUNT(*) as total_orders,
            SUM(total) as revenue,
            AVG(total) as avg_order_value,
            COUNT(DISTINCT user_id) as unique_customers
        FROM orders
        WHERE created_at >= NOW() - INTERVAL '30 days'
        GROUP BY DATE_TRUNC('day', created_at)
        ORDER BY date DESC
    )";

    for (auto _ : state) {
        auto result = Transpiler::transpile(sql);
        benchmark::DoNotOptimize(result);
    }
}
BENCHMARK(BM_RealWorld_Dashboard);

static void BM_RealWorld_Report(benchmark::State& state) {
    std::string sql = R"(
        WITH monthly_revenue AS (
            SELECT
                DATE_TRUNC('month', o.created_at) as month,
                p.category,
                SUM(o.total) as revenue
            FROM orders o
            JOIN products p ON o.product_id = p.id
            WHERE o.status = 'completed'
            GROUP BY DATE_TRUNC('month', o.created_at), p.category
        ),
        category_rankings AS (
            SELECT
                month,
                category,
                revenue,
                RANK() OVER (PARTITION BY month ORDER BY revenue DESC) as rank
            FROM monthly_revenue
        )
        SELECT * FROM category_rankings WHERE rank <= 10
        ORDER BY month DESC, rank ASC
    )";

    for (auto _ : state) {
        auto result = Transpiler::transpile(sql);
        benchmark::DoNotOptimize(result);
    }
}
BENCHMARK(BM_RealWorld_Report);

BENCHMARK_MAIN();
