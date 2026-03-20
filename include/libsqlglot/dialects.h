#pragma once

#include <string>
#include <unordered_map>
#include <functional>

namespace libsqlglot {

/// SQL Dialect enumeration - all supported dialects
enum class Dialect {
    // Phase 1: Already implemented (10 dialects)
    ANSI,
    MySQL,
    PostgreSQL,
    SQLite,
    BigQuery,
    Snowflake,
    Redshift,
    Oracle,
    SQLServer,
    DuckDB,
    ClickHouse,

    // Phase 2: To be implemented (21 dialects)
    Presto,
    Trino,
    Hive,
    Spark,
    Athena,
    Vertica,
    Teradata,
    Databricks,
    MariaDB,
    CockroachDB,
    TimescaleDB,
    Greenplum,
    Netezza,
    Impala,
    Drill,
    Phoenix,
    Calcite,
    Dremio,
    Pinot,
    StarRocks,
    Doris
};

} // namespace libsqlglot

// Hash specialization for Dialect enum to enable use in unordered_map
namespace std {
    template<>
    struct hash<libsqlglot::Dialect> {
        size_t operator()(libsqlglot::Dialect d) const noexcept {
            return hash<int>{}(static_cast<int>(d));
        }
    };
}

namespace libsqlglot {

/// Dialect-specific features and quirks
struct DialectFeatures {
    bool supports_cte = true;
    bool supports_recursive_cte = true;
    bool supports_window_functions = true;
    bool supports_array_literals = false;
    bool supports_json_ops = false;
    bool case_sensitive_identifiers = false;
    bool supports_pivot = false;
    bool supports_qualify = false;
    bool supports_ilike = false;
    bool supports_regex = false;
    bool supports_intersect = true;
    bool supports_except = true;

    // Quote characters
    char identifier_quote = '"';
    char string_quote = '\'';

    // NULL handling
    std::string null_ordering = "NULLS LAST";  // or "NULLS FIRST"

    // Limit syntax
    enum class LimitStyle {
        LIMIT_OFFSET,     // LIMIT n OFFSET m (PostgreSQL, MySQL)
        TOP,              // TOP n (SQL Server)
        FETCH_FIRST,      // FETCH FIRST n ROWS ONLY (Oracle, ANSI)
        ROWNUM            // WHERE ROWNUM <= n (Oracle legacy)
    } limit_style = LimitStyle::LIMIT_OFFSET;

    // String concatenation
    enum class ConcatOp {
        PIPES,            // || (PostgreSQL, Oracle)
        PLUS,             // + (SQL Server)
        CONCAT_FUNC       // CONCAT() function
    } concat_op = ConcatOp::CONCAT_FUNC;

    // Boolean literals
    std::string true_literal = "TRUE";
    std::string false_literal = "FALSE";

    // Stored procedure / procedural SQL features
    bool supports_begin_end_blocks = false;  // BEGIN...END for statement blocks (T-SQL, MySQL, PL/SQL)
    bool supports_for_loops = true;          // FOR i IN 1..10 LOOP syntax (PostgreSQL, Oracle, generic)
    std::string variable_prefix = "";        // @ for T-SQL, $ for PostgreSQL params, empty for others

    enum class AssignmentStyle {
        WALRUS,          // := (Oracle PL/SQL, PL/pgSQL)
        SET_KEYWORD,     // SET var = value (MySQL, T-SQL)
        EQUALS           // = (some contexts)
    } assignment_style = AssignmentStyle::WALRUS;
};

/// Dialect configuration - features and transformations
class DialectConfig {
public:
    static const DialectFeatures& get_features(Dialect dialect) {
        static std::unordered_map<Dialect, DialectFeatures> features = initialize_features();
        auto it = features.find(dialect);
        if (it != features.end()) {
            return it->second;
        }
        // Return ANSI default
        return features[Dialect::ANSI];
    }

    static std::string get_name(Dialect dialect) {
        switch (dialect) {
            case Dialect::ANSI: return "ANSI";
            case Dialect::MySQL: return "MySQL";
            case Dialect::PostgreSQL: return "PostgreSQL";
            case Dialect::SQLite: return "SQLite";
            case Dialect::BigQuery: return "BigQuery";
            case Dialect::Snowflake: return "Snowflake";
            case Dialect::Redshift: return "Redshift";
            case Dialect::Oracle: return "Oracle";
            case Dialect::SQLServer: return "SQL Server";
            case Dialect::DuckDB: return "DuckDB";
            case Dialect::ClickHouse: return "ClickHouse";
            case Dialect::Presto: return "Presto";
            case Dialect::Trino: return "Trino";
            case Dialect::Hive: return "Hive";
            case Dialect::Spark: return "Spark";
            case Dialect::Athena: return "Athena";
            case Dialect::Vertica: return "Vertica";
            case Dialect::Teradata: return "Teradata";
            case Dialect::Databricks: return "Databricks";
            case Dialect::MariaDB: return "MariaDB";
            case Dialect::CockroachDB: return "CockroachDB";
            case Dialect::TimescaleDB: return "TimescaleDB";
            case Dialect::Greenplum: return "Greenplum";
            case Dialect::Netezza: return "Netezza";
            case Dialect::Impala: return "Impala";
            case Dialect::Drill: return "Drill";
            case Dialect::Phoenix: return "Phoenix";
            case Dialect::Calcite: return "Calcite";
            case Dialect::Dremio: return "Dremio";
            case Dialect::Pinot: return "Pinot";
            case Dialect::StarRocks: return "StarRocks";
            case Dialect::Doris: return "Doris";
            default: return "Unknown";
        }
    }

private:
    static std::unordered_map<Dialect, DialectFeatures> initialize_features() {
        std::unordered_map<Dialect, DialectFeatures> features;

        // ANSI SQL (baseline)
        features[Dialect::ANSI] = DialectFeatures{};

        // PostgreSQL
        auto& postgres = features[Dialect::PostgreSQL];
        postgres.supports_array_literals = true;
        postgres.supports_json_ops = true;
        postgres.supports_ilike = true;
        postgres.supports_regex = true;
        postgres.identifier_quote = '"';
        postgres.concat_op = DialectFeatures::ConcatOp::PIPES;

        // MySQL / MariaDB
        auto& mysql = features[Dialect::MySQL];
        mysql.identifier_quote = '`';
        mysql.supports_ilike = false;
        mysql.concat_op = DialectFeatures::ConcatOp::CONCAT_FUNC;
        features[Dialect::MariaDB] = mysql;  // MariaDB is MySQL-compatible

        // SQLite
        auto& sqlite = features[Dialect::SQLite];
        sqlite.identifier_quote = '"';
        sqlite.supports_window_functions = true;  // Since 3.25.0
        sqlite.concat_op = DialectFeatures::ConcatOp::PIPES;

        // BigQuery
        auto& bigquery = features[Dialect::BigQuery];
        bigquery.supports_array_literals = true;
        bigquery.supports_qualify = true;
        bigquery.supports_pivot = true;
        bigquery.identifier_quote = '`';
        bigquery.concat_op = DialectFeatures::ConcatOp::PIPES;

        // Snowflake
        auto& snowflake = features[Dialect::Snowflake];
        snowflake.supports_array_literals = true;
        snowflake.supports_qualify = true;
        snowflake.supports_pivot = true;
        snowflake.supports_ilike = true;
        snowflake.supports_regex = true;
        snowflake.identifier_quote = '"';
        snowflake.concat_op = DialectFeatures::ConcatOp::PIPES;

        // Redshift (PostgreSQL-based)
        auto& redshift = features[Dialect::Redshift];
        redshift = postgres;  // Start with PostgreSQL features
        redshift.supports_pivot = false;

        // Oracle
        auto& oracle = features[Dialect::Oracle];
        oracle.identifier_quote = '"';
        oracle.concat_op = DialectFeatures::ConcatOp::PIPES;
        oracle.limit_style = DialectFeatures::LimitStyle::FETCH_FIRST;

        // SQL Server
        auto& sqlserver = features[Dialect::SQLServer];
        sqlserver.identifier_quote = '[';
        sqlserver.string_quote = '\'';
        sqlserver.concat_op = DialectFeatures::ConcatOp::PLUS;
        sqlserver.limit_style = DialectFeatures::LimitStyle::TOP;
        sqlserver.true_literal = "1";
        sqlserver.false_literal = "0";

        // DuckDB (PostgreSQL-compatible with extensions)
        auto& duckdb = features[Dialect::DuckDB];
        duckdb = postgres;  // PostgreSQL-compatible
        duckdb.supports_pivot = true;

        // ClickHouse
        auto& clickhouse = features[Dialect::ClickHouse];
        clickhouse.identifier_quote = '`';
        clickhouse.supports_array_literals = true;

        // Presto / Trino (Trino is Presto rebrand)
        auto& presto = features[Dialect::Presto];
        presto.supports_array_literals = true;
        presto.identifier_quote = '"';
        presto.concat_op = DialectFeatures::ConcatOp::PIPES;
        features[Dialect::Trino] = presto;

        // Hive
        auto& hive = features[Dialect::Hive];
        hive.identifier_quote = '`';
        hive.supports_pivot = false;
        hive.case_sensitive_identifiers = true;

        // Spark (Hive-compatible)
        auto& spark = features[Dialect::Spark];
        spark = hive;
        spark.supports_pivot = true;
        features[Dialect::Databricks] = spark;  // Databricks uses Spark SQL

        // Athena (Presto-based)
        features[Dialect::Athena] = presto;

        // Vertica (PostgreSQL-compatible)
        features[Dialect::Vertica] = postgres;

        // Teradata
        auto& teradata = features[Dialect::Teradata];
        teradata.identifier_quote = '"';
        teradata.concat_op = DialectFeatures::ConcatOp::PIPES;

        // CockroachDB (PostgreSQL-compatible)
        features[Dialect::CockroachDB] = postgres;

        // TimescaleDB (PostgreSQL extension)
        features[Dialect::TimescaleDB] = postgres;

        // Greenplum (PostgreSQL-based)
        features[Dialect::Greenplum] = postgres;

        // Netezza (PostgreSQL-based)
        features[Dialect::Netezza] = postgres;

        // Impala (Hive-compatible)
        features[Dialect::Impala] = hive;

        // Apache Drill
        auto& drill = features[Dialect::Drill];
        drill.supports_array_literals = true;
        drill.identifier_quote = '`';

        // Apache Phoenix (HBase SQL)
        auto& phoenix = features[Dialect::Phoenix];
        phoenix.identifier_quote = '"';

        // Apache Calcite
        auto& calcite = features[Dialect::Calcite];
        calcite.identifier_quote = '"';

        // Dremio
        auto& dremio = features[Dialect::Dremio];
        dremio.supports_array_literals = true;
        dremio.identifier_quote = '"';

        // Apache Pinot
        auto& pinot = features[Dialect::Pinot];
        pinot.identifier_quote = '"';
        pinot.supports_window_functions = false;  // Limited support

        // StarRocks / Doris (MySQL-compatible)
        features[Dialect::StarRocks] = mysql;
        features[Dialect::Doris] = mysql;

        return features;
    }
};

} // namespace libsqlglot
