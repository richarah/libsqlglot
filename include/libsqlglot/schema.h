#pragma once

#include <string>
#include <unordered_map>
#include <vector>
#include <memory>
#include <optional>

namespace libsqlglot {

/// SQL data type
enum class DataType {
    // Numeric types
    INTEGER, BIGINT, SMALLINT, TINYINT,
    FLOAT, DOUBLE, DECIMAL, NUMERIC,

    // String types
    VARCHAR, CHAR, TEXT,

    // Boolean
    BOOLEAN,

    // Date/Time
    DATE, TIME, TIMESTAMP, TIMESTAMPTZ, INTERVAL,

    // Binary
    BINARY, VARBINARY, BLOB,

    // Complex types
    ARRAY, MAP, STRUCT, JSON,

    // Special
    UNKNOWN, NULL_TYPE
};

/// Column schema information
struct ColumnSchema {
    std::string name;
    DataType type;
    bool nullable = true;
    bool primary_key = false;
    bool unique = false;
    std::optional<std::string> default_value;

    ColumnSchema(std::string n, DataType t)
        : name(std::move(n)), type(t) {}
};

/// Table schema information
struct TableSchema {
    std::string database;
    std::string schema;
    std::string name;
    std::vector<ColumnSchema> columns;
    std::vector<std::string> primary_keys;

    explicit TableSchema(std::string n) : name(std::move(n)) {}

    /// Find column by name (case-insensitive)
    const ColumnSchema* find_column(const std::string& col_name) const {
        for (const auto& col : columns) {
            if (strcasecmp_portable(col.name.c_str(), col_name.c_str()) == 0) {
                return &col;
            }
        }
        return nullptr;
    }

    /// Add column to schema
    void add_column(const std::string& name, DataType type, bool nullable = true) {
        columns.emplace_back(name, type);
        columns.back().nullable = nullable;
    }

private:
    static int strcasecmp_portable(const char* s1, const char* s2) {
        while (*s1 && *s2) {
            int c1 = (*s1 >= 'A' && *s1 <= 'Z') ? *s1 + 32 : *s1;
            int c2 = (*s2 >= 'A' && *s2 <= 'Z') ? *s2 + 32 : *s2;
            if (c1 != c2) return c1 - c2;
            s1++;
            s2++;
        }
        return *s1 - *s2;
    }
};

/// Schema catalog - stores all table schemas
class SchemaCatalog {
public:
    /// Add a table schema
    void add_table(const std::string& name, TableSchema schema) {
        tables_[to_lower(name)] = std::make_shared<TableSchema>(std::move(schema));
    }

    /// Get table schema by name
    std::shared_ptr<TableSchema> get_table(const std::string& name) const {
        auto it = tables_.find(to_lower(name));
        if (it != tables_.end()) {
            return it->second;
        }
        return nullptr;
    }

    /// Check if table exists
    bool has_table(const std::string& name) const {
        return tables_.find(to_lower(name)) != tables_.end();
    }

    /// Get column type from table.column reference
    DataType get_column_type(const std::string& table, const std::string& column) const {
        auto table_schema = get_table(table);
        if (!table_schema) return DataType::UNKNOWN;

        auto col_schema = table_schema->find_column(column);
        if (!col_schema) return DataType::UNKNOWN;

        return col_schema->type;
    }

    /// Validate that a column exists in a table
    bool validate_column(const std::string& table, const std::string& column) const {
        auto table_schema = get_table(table);
        if (!table_schema) return false;
        return table_schema->find_column(column) != nullptr;
    }

    /// Get all column names for a table
    std::vector<std::string> get_columns(const std::string& table) const {
        auto table_schema = get_table(table);
        if (!table_schema) return {};

        std::vector<std::string> result;
        for (const auto& col : table_schema->columns) {
            result.push_back(col.name);
        }
        return result;
    }

    /// Clear all schemas
    void clear() {
        tables_.clear();
    }

private:
    std::unordered_map<std::string, std::shared_ptr<TableSchema>> tables_;

    static std::string to_lower(const std::string& str) {
        std::string result = str;
        for (char& c : result) {
            if (c >= 'A' && c <= 'Z') c = c + 32;
        }
        return result;
    }
};

/// Global schema catalog instance
inline SchemaCatalog& get_global_catalog() {
    static SchemaCatalog catalog;
    return catalog;
}

} // namespace libsqlglot
