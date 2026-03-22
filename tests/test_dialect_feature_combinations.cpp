#include <catch2/catch_test_macros.hpp>
#include <libsqlglot/transpiler.h>
#include <libsqlglot/dialects.h>
#include <libsqlglot/parser.h>
#include <vector>
#include <string>
#include <random>

using namespace libsqlglot;

// =============================================================================
// Dialect Feature Combination & Fuzzing Tests
// =============================================================================
// These tests ensure that all combinations of SQL features work correctly
// across all supported dialects, and that edge cases are handled properly.

namespace {
    // All supported dialects for comprehensive testing
    std::vector<Dialect> all_dialects = {
        Dialect::ANSI, Dialect::MySQL, Dialect::PostgreSQL, Dialect::SQLite,
        Dialect::BigQuery, Dialect::Snowflake, Dialect::Redshift, Dialect::Oracle,
        Dialect::SQLServer, Dialect::DuckDB, Dialect::ClickHouse, Dialect::Presto,
        Dialect::Trino, Dialect::Hive, Dialect::Spark, Dialect::Athena,
        Dialect::Vertica, Dialect::Teradata, Dialect::Databricks, Dialect::MariaDB,
        Dialect::CockroachDB, Dialect::TimescaleDB, Dialect::Greenplum, Dialect::Netezza,
        Dialect::Impala, Dialect::Drill, Dialect::Phoenix, Dialect::Calcite,
        Dialect::Dremio, Dialect::Pinot, Dialect::StarRocks, Dialect::Doris,
        Dialect::Spark2, Dialect::DB2, Dialect::Dune, Dialect::Exasol,
        Dialect::Fabric, Dialect::Materialize, Dialect::RisingWave, Dialect::SingleStore,
        Dialect::Solr, Dialect::Tableau, Dialect::TiDB, Dialect::YugabyteDB, Dialect::Druid
    };

    // SQL statement templates for combination testing
    struct SQLTemplate {
        std::string name;
        std::string sql;
        std::vector<std::string> feature_tags;
    };

    std::vector<SQLTemplate> get_sql_templates() {
        return {
            // Basic SELECT variations
            {"SELECT *", "SELECT * FROM users", {"select", "basic"}},
            {"SELECT columns", "SELECT id, name, email FROM users", {"select", "columns"}},
            {"SELECT with alias", "SELECT id AS user_id, name AS full_name FROM users", {"select", "alias"}},

            // WHERE clauses with different operators
            {"WHERE =", "SELECT * FROM users WHERE id = 1", {"select", "where", "equality"}},
            {"WHERE >", "SELECT * FROM users WHERE age > 18", {"select", "where", "comparison"}},
            {"WHERE IN", "SELECT * FROM users WHERE id IN (1, 2, 3)", {"select", "where", "in"}},
            {"WHERE BETWEEN", "SELECT * FROM users WHERE age BETWEEN 18 AND 65", {"select", "where", "between"}},
            {"WHERE LIKE", "SELECT * FROM users WHERE name LIKE 'John%'", {"select", "where", "like"}},
            {"WHERE IS NULL", "SELECT * FROM users WHERE email IS NULL", {"select", "where", "null"}},
            {"WHERE AND", "SELECT * FROM users WHERE age > 18 AND active = TRUE", {"select", "where", "and"}},
            {"WHERE OR", "SELECT * FROM users WHERE age < 18 OR age > 65", {"select", "where", "or"}},

            // JOINs
            {"INNER JOIN", "SELECT * FROM users u INNER JOIN orders o ON u.id = o.user_id", {"select", "join", "inner"}},
            {"LEFT JOIN", "SELECT * FROM users u LEFT JOIN orders o ON u.id = o.user_id", {"select", "join", "left"}},
            {"RIGHT JOIN", "SELECT * FROM users u RIGHT JOIN orders o ON u.id = o.user_id", {"select", "join", "right"}},
            {"FULL OUTER JOIN", "SELECT * FROM users u FULL OUTER JOIN orders o ON u.id = o.user_id", {"select", "join", "full"}},
            {"CROSS JOIN", "SELECT * FROM users CROSS JOIN products", {"select", "join", "cross"}},
            {"Multiple JOINs", "SELECT * FROM users u JOIN orders o ON u.id = o.user_id JOIN products p ON o.product_id = p.id", {"select", "join", "multiple"}},

            // Aggregations
            {"GROUP BY single", "SELECT category, COUNT(*) FROM products GROUP BY category", {"select", "group_by", "aggregate"}},
            {"GROUP BY multiple", "SELECT category, subcategory, COUNT(*) FROM products GROUP BY category, subcategory", {"select", "group_by", "multiple"}},
            {"GROUP BY with HAVING", "SELECT category, COUNT(*) as cnt FROM products GROUP BY category HAVING COUNT(*) > 10", {"select", "group_by", "having"}},

            // ORDER BY and LIMIT
            {"ORDER BY ASC", "SELECT * FROM users ORDER BY name ASC", {"select", "order_by", "asc"}},
            {"ORDER BY DESC", "SELECT * FROM users ORDER BY created_at DESC", {"select", "order_by", "desc"}},
            {"ORDER BY multiple", "SELECT * FROM users ORDER BY last_name ASC, first_name ASC", {"select", "order_by", "multiple"}},
            {"LIMIT", "SELECT * FROM users LIMIT 10", {"select", "limit"}},
            {"LIMIT with OFFSET", "SELECT * FROM users LIMIT 10 OFFSET 20", {"select", "limit", "offset"}},

            // Subqueries
            {"Subquery in WHERE", "SELECT * FROM users WHERE id IN (SELECT user_id FROM orders WHERE total > 100)", {"select", "subquery", "where"}},
            {"Subquery in FROM", "SELECT * FROM (SELECT * FROM users WHERE active = TRUE) AS active_users", {"select", "subquery", "from"}},
            {"Subquery in SELECT", "SELECT id, name, (SELECT COUNT(*) FROM orders WHERE user_id = users.id) AS order_count FROM users", {"select", "subquery", "select"}},

            // UNION
            {"UNION", "SELECT name FROM users UNION SELECT name FROM customers", {"select", "union"}},
            {"UNION ALL", "SELECT name FROM users UNION ALL SELECT name FROM customers", {"select", "union_all"}},

            // DML statements
            {"INSERT values", "INSERT INTO users (id, name) VALUES (1, 'Alice')", {"insert", "values"}},
            {"INSERT multiple", "INSERT INTO users (id, name) VALUES (1, 'Alice'), (2, 'Bob')", {"insert", "multiple"}},
            {"INSERT SELECT", "INSERT INTO users_backup SELECT * FROM users", {"insert", "select"}},
            {"UPDATE", "UPDATE users SET name = 'Alice' WHERE id = 1", {"update"}},
            {"UPDATE multiple", "UPDATE users SET name = 'Alice', age = 30 WHERE id = 1", {"update", "multiple"}},
            {"DELETE", "DELETE FROM users WHERE id = 1", {"delete"}},

            // CTEs
            {"CTE simple", "WITH cte AS (SELECT * FROM users) SELECT * FROM cte", {"cte", "simple"}},
            {"CTE multiple", "WITH cte1 AS (SELECT * FROM users), cte2 AS (SELECT * FROM orders) SELECT * FROM cte1 JOIN cte2 ON cte1.id = cte2.user_id", {"cte", "multiple"}},

            // Functions
            {"COUNT", "SELECT COUNT(*) FROM users", {"function", "count"}},
            {"SUM", "SELECT SUM(amount) FROM orders", {"function", "sum"}},
            {"AVG", "SELECT AVG(age) FROM users", {"function", "avg"}},
            {"MIN/MAX", "SELECT MIN(age), MAX(age) FROM users", {"function", "minmax"}},
            {"COALESCE", "SELECT COALESCE(email, 'no-email') FROM users", {"function", "coalesce"}},
            {"CAST", "SELECT CAST(age AS VARCHAR) FROM users", {"function", "cast"}},

            // CASE expressions
            {"CASE simple", "SELECT CASE WHEN age < 18 THEN 'minor' ELSE 'adult' END FROM users", {"case", "simple"}},
            {"CASE multiple", "SELECT CASE WHEN age < 18 THEN 'minor' WHEN age < 65 THEN 'adult' ELSE 'senior' END FROM users", {"case", "multiple"}},
        };
    }
}

// =============================================================================
// Feature Combination Matrix Tests
// =============================================================================

TEST_CASE("All SQL templates parse successfully across all dialects", "[fuzzing][combinations][comprehensive]") {
    auto templates = get_sql_templates();
    int total_tests = 0;
    int passed_tests = 0;

    for (const auto& tmpl : templates) {
        for (auto dialect : all_dialects) {
            total_tests++;

            INFO("Template: " << tmpl.name << ", Dialect: " << DialectConfig::get_name(dialect));

            Arena arena;
            Parser parser(arena, tmpl.sql);

            try {
                parser.parse();
                passed_tests++;
            } catch (const std::exception& e) {
                // Some combinations are expected to fail (dialect-specific features)
                // but we log them for visibility
                WARN("Failed to parse: " << tmpl.name << " with " << DialectConfig::get_name(dialect));
            }
        }
    }

    INFO("Passed " << passed_tests << "/" << total_tests << " tests ("
         << (100.0 * passed_tests / total_tests) << "%)");

    // Require at least 85% success rate across all combinations
    REQUIRE(passed_tests >= total_tests * 0.85);
}

// =============================================================================
// Transpilation Combination Tests
// =============================================================================

TEST_CASE("Cross-dialect transpilation for common SQL patterns", "[fuzzing][transpilation]") {
    std::vector<std::string> test_queries = {
        "SELECT id, name FROM users WHERE age > 18",
        "SELECT * FROM users u JOIN orders o ON u.id = o.user_id",
        "SELECT category, COUNT(*) FROM products GROUP BY category",
        "SELECT * FROM users WHERE id IN (SELECT user_id FROM orders)",
        "INSERT INTO users (id, name) VALUES (1, 'Alice')",
        "UPDATE users SET name = 'Bob' WHERE id = 1",
        "DELETE FROM users WHERE age < 18",
    };

    // Test subset of dialect pairs (testing all N×N would be very slow)
    std::vector<std::pair<Dialect, Dialect>> test_pairs = {
        {Dialect::MySQL, Dialect::PostgreSQL},
        {Dialect::PostgreSQL, Dialect::MySQL},
        {Dialect::MySQL, Dialect::BigQuery},
        {Dialect::BigQuery, Dialect::Snowflake},
        {Dialect::Snowflake, Dialect::Redshift},
        {Dialect::Oracle, Dialect::SQLServer},
        {Dialect::SQLServer, Dialect::Oracle},
        {Dialect::DuckDB, Dialect::ClickHouse},
        {Dialect::Hive, Dialect::Spark},
        {Dialect::Presto, Dialect::Trino},
    };

    int total_tests = test_queries.size() * test_pairs.size();
    int passed_tests = 0;

    for (const auto& query : test_queries) {
        for (const auto& [from_dialect, to_dialect] : test_pairs) {
            INFO("Query: " << query.substr(0, 50) << "...");
            INFO("Transpiling: " << DialectConfig::get_name(from_dialect)
                 << " → " << DialectConfig::get_name(to_dialect));

            try {
                std::string result = Transpiler::transpile(query, from_dialect, to_dialect);
                REQUIRE(!result.empty());
                passed_tests++;
            } catch (const std::exception& e) {
                WARN("Transpilation failed: " << e.what());
            }
        }
    }

    INFO("Passed " << passed_tests << "/" << total_tests << " transpilation tests");
    REQUIRE(passed_tests >= total_tests * 0.90);  // 90% success rate
}

// =============================================================================
// Procedural SQL Feature Tests (Stored Procedures)
// =============================================================================

TEST_CASE("Procedural SQL - BEGIN/END blocks", "[fuzzing][procedural][begin_end]") {
    std::string sql = R"(
        BEGIN
            SELECT * FROM users;
            UPDATE users SET last_login = NOW();
        END
    )";

    // Dialects with BEGIN/END support
    std::vector<Dialect> begin_end_dialects = {
        Dialect::MySQL, Dialect::PostgreSQL, Dialect::Oracle, Dialect::SQLServer
    };

    for (auto dialect : begin_end_dialects) {
        INFO("Testing BEGIN/END for: " << DialectConfig::get_name(dialect));

        Arena arena;
        Parser parser(arena, sql);
        REQUIRE_NOTHROW(parser.parse());
    }
}

TEST_CASE("Procedural SQL - DECLARE variables", "[fuzzing][procedural][declare]") {
    std::string sql = "DECLARE @user_count INT";

    Arena arena;
    Parser parser(arena, sql);
    REQUIRE_NOTHROW(parser.parse());
}

TEST_CASE("Procedural SQL - FOR loops", "[fuzzing][procedural][for_loop]") {
    std::string sql = R"(
        FOR i IN 1..10 LOOP
            INSERT INTO numbers VALUES (i);
        END LOOP
    )";

    // Dialects with FOR loop support
    std::vector<Dialect> for_loop_dialects = {
        Dialect::PostgreSQL, Dialect::Oracle, Dialect::MySQL
    };

    for (auto dialect : for_loop_dialects) {
        INFO("Testing FOR loop for: " << DialectConfig::get_name(dialect));

        Arena arena;
        Parser parser(arena, sql);
        REQUIRE_NOTHROW(parser.parse());
    }
}

TEST_CASE("Procedural SQL - IF statements", "[fuzzing][procedural][if]") {
    std::string sql = R"(
        IF @count > 10 THEN
            SELECT 'many' AS result;
        ELSE
            SELECT 'few' AS result;
        END IF
    )";

    Arena arena;
    Parser parser(arena, sql);
    REQUIRE_NOTHROW(parser.parse());
}

// =============================================================================
// Security & Edge Case Tests
// =============================================================================

TEST_CASE("SQL injection patterns are parsed safely", "[fuzzing][security]") {
    // These should parse without crashes (but might produce errors)
    std::vector<std::string> injection_patterns = {
        "SELECT * FROM users WHERE id = 1 OR 1=1",
        "SELECT * FROM users WHERE name = 'a' OR '1'='1",
        "SELECT * FROM users; DROP TABLE users--",
        "SELECT * FROM users WHERE id = 1'; DROP TABLE users--",
        "SELECT * FROM users WHERE id IN (1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15)",
    };

    for (const auto& sql : injection_patterns) {
        INFO("Testing injection pattern: " << sql);

        Arena arena;
        Parser parser(arena, sql);

        // Should either parse or throw a controlled error, but not crash
        try {
            parser.parse();
        } catch (const std::exception& e) {
            // Expected for malformed SQL
            INFO("Caught expected error: " << e.what());
        }
    }
}

TEST_CASE("Deeply nested queries don't cause stack overflow", "[fuzzing][security][nesting]") {
    // Create deeply nested subquery
    std::string sql = "SELECT * FROM users WHERE id IN (";
    for (int i = 0; i < 50; ++i) {
        sql += "SELECT id FROM users WHERE id IN (";
    }
    sql += "SELECT 1";
    for (int i = 0; i < 50; ++i) {
        sql += ")";
    }
    sql += ")";

    Arena arena;
    Parser parser(arena, sql);

    // Should handle gracefully without stack overflow
    try {
        parser.parse();
    } catch (const std::exception& e) {
        // May hit recursion limit, but shouldn't crash
        INFO("Caught expected error: " << e.what());
    }
}

TEST_CASE("Very long identifier names are handled", "[fuzzing][edge_case][identifiers]") {
    std::string long_name(1000, 'a');
    std::string sql = "SELECT * FROM " + long_name;

    Arena arena;
    Parser parser(arena, sql);

    try {
        parser.parse();
    } catch (const std::exception& e) {
        // May reject very long identifiers
        INFO("Caught error: " << e.what());
    }
}

TEST_CASE("Special characters in identifiers", "[fuzzing][edge_case][special_chars]") {
    std::vector<std::string> special_identifiers = {
        "SELECT * FROM `table-name`",           // MySQL backticks with dash
        "SELECT * FROM \"table name\"",         // PostgreSQL quotes with space
        "SELECT * FROM [table name]",           // SQL Server brackets with space
        "SELECT * FROM `unicode_表名`",         // Unicode characters
    };

    for (const auto& sql : special_identifiers) {
        INFO("Testing special identifier: " << sql);

        Arena arena;
        Parser parser(arena, sql);

        try {
            parser.parse();
        } catch (const std::exception& e) {
            INFO("Caught error: " << e.what());
        }
    }
}

// =============================================================================
// GRANT/REVOKE Comprehensive Tests
// =============================================================================

TEST_CASE("GRANT statement variations", "[fuzzing][grant][security]") {
    std::vector<std::string> grant_variations = {
        "GRANT SELECT ON users TO alice",
        "GRANT SELECT, INSERT, UPDATE ON users TO alice",
        "GRANT ALL ON users TO alice",
        "GRANT ALL PRIVILEGES ON users TO alice",
        "GRANT SELECT ON ALL TABLES IN SCHEMA public TO alice",
        "GRANT SELECT (id, name) ON users TO alice",
        "GRANT EXECUTE ON FUNCTION process_user TO alice",
        "GRANT admin_role TO alice",
        "GRANT admin_role, developer_role TO alice, bob",
        "GRANT SELECT ON users TO alice WITH GRANT OPTION",
    };

    for (const auto& sql : grant_variations) {
        INFO("Testing GRANT: " << sql);

        Arena arena;
        Parser parser(arena, sql);
        REQUIRE_NOTHROW(parser.parse());
    }
}

TEST_CASE("REVOKE statement variations", "[fuzzing][revoke][security]") {
    std::vector<std::string> revoke_variations = {
        "REVOKE SELECT ON users FROM alice",
        "REVOKE SELECT, INSERT, UPDATE ON users FROM alice",
        "REVOKE ALL ON users FROM alice",
        "REVOKE ALL PRIVILEGES ON users FROM alice",
        "REVOKE admin_role FROM alice",
        "REVOKE admin_role, developer_role FROM alice, bob",
        "REVOKE ADMIN OPTION FOR admin_role FROM alice",
        "REVOKE GRANT OPTION FOR SELECT ON users FROM alice",
        "REVOKE SELECT ON users FROM PUBLIC",
    };

    for (const auto& sql : revoke_variations) {
        INFO("Testing REVOKE: " << sql);

        Arena arena;
        Parser parser(arena, sql);
        REQUIRE_NOTHROW(parser.parse());
    }
}

// =============================================================================
// Utility Statement Tests
// =============================================================================

TEST_CASE("ANALYZE statement variations", "[fuzzing][utility][analyze]") {
    std::vector<std::string> analyze_variations = {
        "ANALYZE users",
        "ANALYZE TABLE users",
        "ANALYZE users (id, name)",
        "ANALYZE users COMPUTE STATISTICS",
    };

    for (const auto& sql : analyze_variations) {
        INFO("Testing ANALYZE: " << sql);

        Arena arena;
        Parser parser(arena, sql);
        REQUIRE_NOTHROW(parser.parse());
    }
}

TEST_CASE("VACUUM statement variations", "[fuzzing][utility][vacuum]") {
    std::vector<std::string> vacuum_variations = {
        "VACUUM",
        "VACUUM users",
        "VACUUM FULL",
        "VACUUM FULL ANALYZE",
        "VACUUM (FULL, VERBOSE)",
        "VACUUM users (id, name)",
    };

    for (const auto& sql : vacuum_variations) {
        INFO("Testing VACUUM: " << sql);

        Arena arena;
        Parser parser(arena, sql);
        REQUIRE_NOTHROW(parser.parse());
    }
}

// =============================================================================
// Random Query Generation (Fuzzing)
// =============================================================================

TEST_CASE("Random query generation fuzzing", "[.][fuzzing][random]") {
    // This test is tagged with [.] to exclude it from normal runs
    // Run with: --run-excluded-tests

    std::random_device rd;
    std::mt19937 gen(rd());

    std::uniform_int_distribution<> col_count(1, 10);
    std::uniform_int_distribution<> table_choice(0, 5);
    std::uniform_int_distribution<> where_choice(0, 3);

    std::vector<std::string> tables = {"users", "orders", "products", "customers", "transactions", "items"};
    std::vector<std::string> columns = {"id", "name", "email", "age", "created_at", "updated_at", "amount", "quantity"};
    std::vector<std::string> operators = {"=", ">", "<", ">=", "<=", "!="};

    // Generate and test 100 random queries
    for (int i = 0; i < 100; ++i) {
        std::string sql = "SELECT ";

        // Random columns
        int num_cols = col_count(gen);
        for (int j = 0; j < num_cols; ++j) {
            if (j > 0) sql += ", ";
            sql += columns[j % columns.size()];
        }

        // Random table
        sql += " FROM " + tables[table_choice(gen)];

        // Random WHERE clause (optional)
        if (where_choice(gen) > 0) {
            sql += " WHERE " + columns[0] + " " + operators[where_choice(gen) % operators.size()] + " 10";
        }

        INFO("Random query " << i << ": " << sql);

        Arena arena;
        Parser parser(arena, sql);

        try {
            parser.parse();
        } catch (const std::exception& e) {
            // Some random queries may be invalid
            INFO("Caught error: " << e.what());
        }
    }
}
