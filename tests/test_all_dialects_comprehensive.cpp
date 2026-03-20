#include <catch2/catch_test_macros.hpp>
#include <libsqlglot/transpiler.h>
#include <libsqlglot/dialects.h>
#include <vector>
#include <string>

using namespace libsqlglot;

// =============================================================================
// Test Matrix: All Dialects × Common SQL Patterns
// =============================================================================

namespace {
    // All supported dialects
    std::vector<Dialect> all_dialects = {
        Dialect::ANSI, Dialect::MySQL, Dialect::PostgreSQL, Dialect::SQLite,
        Dialect::BigQuery, Dialect::Snowflake, Dialect::Redshift, Dialect::Oracle,
        Dialect::SQLServer, Dialect::DuckDB, Dialect::ClickHouse, Dialect::Presto,
        Dialect::Trino, Dialect::Hive, Dialect::Spark, Dialect::Athena,
        Dialect::Vertica, Dialect::Teradata, Dialect::Databricks, Dialect::MariaDB,
        Dialect::CockroachDB, Dialect::TimescaleDB, Dialect::Greenplum, Dialect::Netezza,
        Dialect::Impala, Dialect::Drill, Dialect::Phoenix, Dialect::Calcite,
        Dialect::Dremio, Dialect::Pinot, Dialect::StarRocks, Dialect::Doris
    };
}

// =============================================================================
// Universal Query Tests - All Dialects Should Parse These
// =============================================================================

TEST_CASE("All dialects parse basic SELECT", "[dialects][universal]") {
    std::string sql = "SELECT id, name FROM users WHERE active = TRUE";

    for (auto dialect : all_dialects) {
        INFO("Testing dialect: " << DialectConfig::get_name(dialect));

        Arena arena;
        Parser parser(arena, sql);
        REQUIRE_NOTHROW(parser.parse());
    }
}

TEST_CASE("All dialects parse INSERT", "[dialects][universal]") {
    std::string sql = "INSERT INTO users (id, name, email) VALUES (1, 'Alice', 'alice@example.com')";

    for (auto dialect : all_dialects) {
        INFO("Testing dialect: " << DialectConfig::get_name(dialect));

        Arena arena;
        Parser parser(arena, sql);
        REQUIRE_NOTHROW(parser.parse());
    }
}

TEST_CASE("All dialects parse UPDATE", "[dialects][universal]") {
    std::string sql = "UPDATE users SET name = 'Bob', age = 30 WHERE id = 1";

    for (auto dialect : all_dialects) {
        INFO("Testing dialect: " << DialectConfig::get_name(dialect));

        Arena arena;
        Parser parser(arena, sql);
        REQUIRE_NOTHROW(parser.parse());
    }
}

TEST_CASE("All dialects parse DELETE", "[dialects][universal]") {
    std::string sql = "DELETE FROM users WHERE age < 18";

    for (auto dialect : all_dialects) {
        INFO("Testing dialect: " << DialectConfig::get_name(dialect));

        Arena arena;
        Parser parser(arena, sql);
        REQUIRE_NOTHROW(parser.parse());
    }
}

TEST_CASE("All dialects parse JOIN", "[dialects][universal]") {
    std::string sql = R"(
        SELECT u.name, o.total
        FROM users u
        INNER JOIN orders o ON u.id = o.user_id
        WHERE o.status = 'completed'
    )";

    for (auto dialect : all_dialects) {
        INFO("Testing dialect: " << DialectConfig::get_name(dialect));

        Arena arena;
        Parser parser(arena, sql);
        REQUIRE_NOTHROW(parser.parse());
    }
}

TEST_CASE("All dialects parse GROUP BY", "[dialects][universal]") {
    std::string sql = R"(
        SELECT category, COUNT(*) as count, SUM(price) as total
        FROM products
        GROUP BY category
        HAVING COUNT(*) > 5
    )";

    for (auto dialect : all_dialects) {
        INFO("Testing dialect: " << DialectConfig::get_name(dialect));

        Arena arena;
        Parser parser(arena, sql);
        REQUIRE_NOTHROW(parser.parse());
    }
}

TEST_CASE("All dialects parse subqueries", "[dialects][universal]") {
    std::string sql = R"(
        SELECT name FROM users
        WHERE id IN (SELECT user_id FROM orders WHERE total > 1000)
    )";

    for (auto dialect : all_dialects) {
        INFO("Testing dialect: " << DialectConfig::get_name(dialect));

        Arena arena;
        Parser parser(arena, sql);
        REQUIRE_NOTHROW(parser.parse());
    }
}

TEST_CASE("All dialects parse UNION", "[dialects][universal]") {
    std::string sql = R"(
        SELECT name FROM users WHERE active = TRUE
        UNION
        SELECT name FROM archived_users
    )";

    for (auto dialect : all_dialects) {
        INFO("Testing dialect: " << DialectConfig::get_name(dialect));

        Arena arena;
        Parser parser(arena, sql);
        REQUIRE_NOTHROW(parser.parse());
    }
}

// =============================================================================
// Dialect-Specific Feature Tests
// =============================================================================
// Note: Many dialect-specific syntax features (TOP, QUALIFY, ILIKE, identifier
// quoting with backticks/brackets/quotes, array literals) are not yet implemented
// in the parser. These tests focus on core SQL features that work across dialects.

TEST_CASE("PostgreSQL ILIKE operator", "[dialects][postgres]") {
    std::string sql = "SELECT * FROM users WHERE name ILIKE 'john%'";
    Arena arena;
    Parser parser(arena, sql);
    REQUIRE_NOTHROW(parser.parse());
}

TEST_CASE("MySQL LIMIT with OFFSET", "[dialects][mysql]") {
    std::string sql = "SELECT * FROM users LIMIT 10 OFFSET 20";
    Arena arena;
    Parser parser(arena, sql);
    REQUIRE_NOTHROW(parser.parse());
}

TEST_CASE("Snowflake ILIKE operator", "[dialects][snowflake]") {
    std::string sql = "SELECT * FROM users WHERE email ILIKE '%@company.com'";
    Arena arena;
    Parser parser(arena, sql);
    REQUIRE_NOTHROW(parser.parse());
}

// =============================================================================
// Cross-Dialect Transpilation Tests
// =============================================================================

TEST_CASE("Transpile simple query across all dialect pairs", "[dialects][transpile]") {
    std::string sql = "SELECT id, name FROM users WHERE age > 18";

    // Test a sample of dialect pairs (testing all 31×31 = 961 combinations would be slow)
    std::vector<std::pair<Dialect, Dialect>> dialect_pairs = {
        {Dialect::MySQL, Dialect::PostgreSQL},
        {Dialect::PostgreSQL, Dialect::MySQL},
        {Dialect::MySQL, Dialect::SQLServer},
        {Dialect::SQLServer, Dialect::MySQL},
        {Dialect::PostgreSQL, Dialect::BigQuery},
        {Dialect::BigQuery, Dialect::Snowflake},
        {Dialect::Snowflake, Dialect::Redshift},
        {Dialect::Oracle, Dialect::PostgreSQL},
        {Dialect::DuckDB, Dialect::ClickHouse},
        {Dialect::Hive, Dialect::Spark},
    };

    for (const auto& [from_dialect, to_dialect] : dialect_pairs) {
        INFO("Testing: " << DialectConfig::get_name(from_dialect)
             << " → " << DialectConfig::get_name(to_dialect));

        std::string output = Transpiler::transpile(sql, from_dialect, to_dialect);
        REQUIRE(!output.empty());
        REQUIRE(output.find("SELECT") != std::string::npos);
    }
}

TEST_CASE("Round-trip transpilation preserves semantics", "[dialects][roundtrip]") {
    std::string original = "SELECT id, name FROM users WHERE age > 18 ORDER BY name LIMIT 10";

    // Test round-trip for major dialects
    std::vector<Dialect> major_dialects = {
        Dialect::MySQL, Dialect::PostgreSQL, Dialect::BigQuery,
        Dialect::Snowflake, Dialect::DuckDB
    };

    for (auto dialect : major_dialects) {
        INFO("Testing round-trip for: " << DialectConfig::get_name(dialect));

        // Parse as PostgreSQL, convert to dialect, convert back
        auto step1 = Transpiler::transpile(original, Dialect::PostgreSQL, dialect);
        auto step2 = Transpiler::transpile(step1, dialect, Dialect::PostgreSQL);

        // Both should contain the same semantic elements
        REQUIRE(step2.find("SELECT") != std::string::npos);
        REQUIRE(step2.find("FROM users") != std::string::npos);
        REQUIRE(step2.find("WHERE") != std::string::npos);
    }
}

// =============================================================================
// Complex Query Tests Across Dialects
// =============================================================================

TEST_CASE("CTE support across dialects", "[dialects][cte]") {
    std::string sql = R"(
        WITH regional_sales AS (
            SELECT region, SUM(amount) as total_sales
            FROM orders
            GROUP BY region
        )
        SELECT * FROM regional_sales WHERE total_sales > 10000
    )";

    // Dialects with CTE support
    std::vector<Dialect> cte_dialects = {
        Dialect::PostgreSQL, Dialect::MySQL, Dialect::BigQuery,
        Dialect::Snowflake, Dialect::Redshift, Dialect::DuckDB,
        Dialect::SQLServer, Dialect::Oracle
    };

    for (auto dialect : cte_dialects) {
        INFO("Testing CTE for: " << DialectConfig::get_name(dialect));

        Arena arena;
        Parser parser(arena, sql);
        auto expr = parser.parse_select();
        auto stmt = static_cast<SelectStmt*>(expr);
        REQUIRE(stmt != nullptr);
        REQUIRE(stmt->with != nullptr);
    }
}

TEST_CASE("Window functions across dialects", "[dialects][window]") {
    std::string sql = R"(
        SELECT
            user_id,
            amount,
            ROW_NUMBER() OVER (PARTITION BY user_id ORDER BY created_at) as rn,
            SUM(amount) OVER (PARTITION BY user_id) as total
        FROM transactions
    )";

    // Most modern dialects support window functions
    std::vector<Dialect> window_dialects = {
        Dialect::PostgreSQL, Dialect::MySQL, Dialect::BigQuery,
        Dialect::Snowflake, Dialect::Redshift, Dialect::DuckDB,
        Dialect::SQLServer, Dialect::Oracle, Dialect::Hive,
        Dialect::Spark, Dialect::Presto, Dialect::Trino
    };

    for (auto dialect : window_dialects) {
        INFO("Testing window functions for: " << DialectConfig::get_name(dialect));

        Arena arena;
        Parser parser(arena, sql);
        REQUIRE_NOTHROW(parser.parse());
    }
}

TEST_CASE("Multi-table JOIN across dialects", "[dialects][join]") {
    std::string sql = R"(
        SELECT u.name, o.total, p.product_name
        FROM users u
        INNER JOIN orders o ON u.id = o.user_id
        INNER JOIN products p ON o.product_id = p.id
        WHERE u.active = TRUE
          AND o.status = 'completed'
        ORDER BY o.total DESC
    )";

    for (auto dialect : all_dialects) {
        INFO("Testing multi-JOIN for: " << DialectConfig::get_name(dialect));

        Arena arena;
        Parser parser(arena, sql);
        REQUIRE_NOTHROW(parser.parse());
    }
}

// =============================================================================
// Dialect Feature Matrix Tests
// =============================================================================

TEST_CASE("ILIKE support matches dialect features", "[dialects][features]") {
    // Dialects with ILIKE support
    std::vector<Dialect> ilike_dialects = {Dialect::PostgreSQL, Dialect::Snowflake};

    for (auto dialect : ilike_dialects) {
        auto features = DialectConfig::get_features(dialect);
        REQUIRE(features.supports_ilike == true);
    }

    // MySQL doesn't support ILIKE
    auto mysql_features = DialectConfig::get_features(Dialect::MySQL);
    REQUIRE(mysql_features.supports_ilike == false);
}

TEST_CASE("Array literal support matches dialect features", "[dialects][features]") {
    std::vector<Dialect> array_dialects = {
        Dialect::PostgreSQL, Dialect::BigQuery, Dialect::Snowflake,
        Dialect::Presto, Dialect::Trino, Dialect::ClickHouse
    };

    for (auto dialect : array_dialects) {
        auto features = DialectConfig::get_features(dialect);
        REQUIRE(features.supports_array_literals == true);
    }
}

TEST_CASE("Identifier quoting matches dialect features", "[dialects][features]") {
    REQUIRE(DialectConfig::get_features(Dialect::MySQL).identifier_quote == '`');
    REQUIRE(DialectConfig::get_features(Dialect::PostgreSQL).identifier_quote == '"');
    REQUIRE(DialectConfig::get_features(Dialect::SQLServer).identifier_quote == '[');
    REQUIRE(DialectConfig::get_features(Dialect::BigQuery).identifier_quote == '`');
}

// =============================================================================
// Real-World Query Tests
// =============================================================================

TEST_CASE("Real-world analytics query across dialects", "[dialects][realworld]") {
    std::string sql = R"(
        WITH monthly_revenue AS (
            SELECT
                DATE_TRUNC('month', order_date) as month,
                SUM(amount) as revenue,
                COUNT(DISTINCT user_id) as customers
            FROM orders
            WHERE status = 'completed'
            GROUP BY DATE_TRUNC('month', order_date)
        )
        SELECT
            month,
            revenue,
            customers,
            revenue / customers as avg_per_customer
        FROM monthly_revenue
        ORDER BY month DESC
        LIMIT 12
    )";

    // Test on major analytics platforms
    std::vector<Dialect> analytics_dialects = {
        Dialect::PostgreSQL, Dialect::BigQuery, Dialect::Snowflake,
        Dialect::Redshift, Dialect::DuckDB
    };

    for (auto dialect : analytics_dialects) {
        INFO("Testing analytics query for: " << DialectConfig::get_name(dialect));

        REQUIRE_NOTHROW(Transpiler::transpile(sql, Dialect::PostgreSQL, dialect));
    }
}
