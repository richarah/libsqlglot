#!/usr/bin/env python3
"""Generate perfect hash keyword table for libsqlglot"""

# List of SQL keywords with their token types
# Complete list from tokens.h
keywords = [
    # Keywords - SQL Standard
    ("SELECT", "SELECT"),
    ("INSERT", "INSERT"),
    ("UPDATE", "UPDATE"),
    ("DELETE", "DELETE"),
    ("MERGE", "MERGE"),
    ("CREATE", "CREATE"),
    ("DROP", "DROP"),
    ("ALTER", "ALTER"),
    ("TRUNCATE", "TRUNCATE"),
    ("FROM", "FROM"),
    ("WHERE", "WHERE"),
    ("HAVING", "HAVING"),
    ("GROUP", "GROUP"),
    ("ORDER", "ORDER"),
    ("LIMIT", "LIMIT"),
    ("OFFSET", "OFFSET"),
    ("JOIN", "JOIN"),
    ("INNER", "INNER"),
    ("LEFT", "LEFT"),
    ("RIGHT", "RIGHT"),
    ("FULL", "FULL"),
    ("CROSS", "CROSS"),
    ("OUTER", "OUTER"),
    ("ON", "ON"),
    ("USING", "USING"),
    ("NATURAL", "NATURAL"),
    ("UNION", "UNION"),
    ("INTERSECT", "INTERSECT"),
    ("EXCEPT", "EXCEPT"),
    ("MINUS", "MINUS_KW"),
    ("AS", "AS"),
    ("DISTINCT", "DISTINCT"),
    ("ALL", "ALL"),
    ("ANY", "ANY"),
    ("SOME", "SOME"),
    ("AND", "AND"),
    ("OR", "OR"),
    ("NOT", "NOT"),
    ("IN", "IN"),
    ("EXISTS", "EXISTS"),
    ("BETWEEN", "BETWEEN"),
    ("LIKE", "LIKE"),
    ("ILIKE", "ILIKE"),
    ("IS", "IS"),
    ("NULL", "NULL_KW"),
    ("TRUE", "TRUE"),
    ("FALSE", "FALSE"),
    ("CASE", "CASE"),
    ("WHEN", "WHEN"),
    ("THEN", "THEN"),
    ("ELSE", "ELSE"),
    ("END", "END"),
    ("ASC", "ASC"),
    ("DESC", "DESC"),
    ("NULLS", "NULLS"),
    ("FIRST", "FIRST"),
    ("LAST", "LAST"),
    ("WITH", "WITH"),
    ("RECURSIVE", "RECURSIVE"),
    ("VALUES", "VALUES"),
    ("DEFAULT", "DEFAULT"),
    ("SET", "SET"),
    ("RETURNING", "RETURNING"),

    # Data types
    ("INT", "INT"),
    ("INTEGER", "INTEGER"),
    ("BIGINT", "BIGINT"),
    ("SMALLINT", "SMALLINT"),
    ("TINYINT", "TINYINT"),
    ("FLOAT", "FLOAT"),
    ("DOUBLE", "DOUBLE"),
    ("REAL", "REAL"),
    ("DECIMAL", "DECIMAL"),
    ("NUMERIC", "NUMERIC"),
    ("CHAR", "CHAR"),
    ("VARCHAR", "VARCHAR"),
    ("TEXT", "TEXT"),
    ("STRING", "STRING_TYPE"),
    ("BOOLEAN", "BOOLEAN"),
    ("BOOL", "BOOL"),
    ("DATE", "DATE"),
    ("TIME", "TIME"),
    ("TIMESTAMP", "TIMESTAMP"),
    ("TIMESTAMPTZ", "TIMESTAMPTZ"),
    ("INTERVAL", "INTERVAL"),
    ("BINARY", "BINARY"),
    ("VARBINARY", "VARBINARY"),
    ("BLOB", "BLOB"),
    ("ARRAY", "ARRAY"),
    ("MAP", "MAP"),
    ("STRUCT", "STRUCT"),
    ("JSON", "JSON"),
    ("JSONB", "JSONB"),
    ("UUID", "UUID"),

    # DDL
    ("TABLE", "TABLE"),
    ("VIEW", "VIEW"),
    ("INDEX", "INDEX"),
    ("SCHEMA", "SCHEMA"),
    ("DATABASE", "DATABASE"),
    ("CATALOG", "CATALOG"),
    ("COLUMN", "COLUMN"),
    ("CONSTRAINT", "CONSTRAINT"),
    ("PRIMARY", "PRIMARY"),
    ("FOREIGN", "FOREIGN"),
    ("KEY", "KEY"),
    ("REFERENCES", "REFERENCES"),
    ("UNIQUE", "UNIQUE"),
    ("CHECK", "CHECK"),
    ("TEMPORARY", "TEMPORARY"),
    ("TEMP", "TEMP"),
    ("RENAME", "RENAME"),
    ("ADD", "ADD"),
    ("MODIFY", "MODIFY"),
    ("CHANGE", "CHANGE"),

    # Functions - Common
    ("COUNT", "COUNT"),
    ("SUM", "SUM"),
    ("AVG", "AVG"),
    ("MIN", "MIN"),
    ("MAX", "MAX"),
    ("COALESCE", "COALESCE"),
    ("NULLIF", "NULLIF"),
    ("IFNULL", "IFNULL"),
    ("NVL", "NVL"),
    ("CAST", "CAST"),
    ("TRY_CAST", "TRY_CAST"),
    ("SAFE_CAST", "SAFE_CAST"),
    ("CONVERT", "CONVERT"),
    ("EXTRACT", "EXTRACT"),
    ("DATE_ADD", "DATE_ADD"),
    ("DATE_SUB", "DATE_SUB"),
    ("DATE_DIFF", "DATE_DIFF"),
    ("DATE_TRUNC", "DATE_TRUNC"),
    ("SUBSTRING", "SUBSTRING"),
    ("SUBSTR", "SUBSTR"),
    ("CONCAT", "CONCAT_KW"),
    ("CONCAT_WS", "CONCAT_WS"),
    ("LENGTH", "LENGTH"),
    ("TRIM", "TRIM"),
    ("UPPER", "UPPER"),
    ("LOWER", "LOWER"),
    ("REPLACE", "REPLACE_KW"),
    ("SPLIT", "SPLIT"),
    ("ROUND", "ROUND"),
    ("FLOOR", "FLOOR"),
    ("CEIL", "CEIL"),
    ("ABS", "ABS"),
    ("POWER", "POWER"),
    ("SQRT", "SQRT"),

    # Window functions
    ("OVER", "OVER"),
    ("PARTITION", "PARTITION"),
    ("BY", "BY"),
    ("ROWS", "ROWS"),
    ("RANGE", "RANGE"),
    ("PRECEDING", "PRECEDING"),
    ("FOLLOWING", "FOLLOWING"),
    ("UNBOUNDED", "UNBOUNDED"),
    ("CURRENT", "CURRENT"),
    ("ROW", "ROW"),
    ("RANK", "RANK"),
    ("DENSE_RANK", "DENSE_RANK"),
    ("ROW_NUMBER", "ROW_NUMBER"),
    ("NTILE", "NTILE"),
    ("LEAD", "LEAD"),
    ("LAG", "LAG"),
    ("FIRST_VALUE", "FIRST_VALUE"),
    ("LAST_VALUE", "LAST_VALUE"),
    ("NTH_VALUE", "NTH_VALUE"),

    # Set operations & clauses
    ("LATERAL", "LATERAL"),
    ("APPLY", "APPLY"),
    ("PIVOT", "PIVOT"),
    ("UNPIVOT", "UNPIVOT"),
    ("QUALIFY", "QUALIFY"),
    ("TABLESAMPLE", "TABLESAMPLE"),
    ("FETCH", "FETCH"),
    ("NEXT", "NEXT"),
    ("ONLY", "ONLY"),
    ("FOR", "FOR"),
    ("SHARE", "SHARE"),
    ("NOWAIT", "NOWAIT"),
    ("SKIP", "SKIP"),
    ("LOCKED", "LOCKED"),

    # DML modifiers
    ("INTO", "INTO"),
    ("OVERWRITE", "OVERWRITE"),
    ("IGNORE", "IGNORE"),

    # Transaction control
    ("BEGIN", "BEGIN"),
    ("COMMIT", "COMMIT"),
    ("ROLLBACK", "ROLLBACK"),
    ("SAVEPOINT", "SAVEPOINT"),
    ("TRANSACTION", "TRANSACTION"),
    ("WORK", "WORK"),
    ("ISOLATION", "ISOLATION"),
    ("LEVEL", "LEVEL"),
    ("READ", "READ"),
    ("WRITE", "WRITE"),
    ("COMMITTED", "COMMITTED"),
    ("UNCOMMITTED", "UNCOMMITTED"),
    ("REPEATABLE", "REPEATABLE"),
    ("SERIALIZABLE", "SERIALIZABLE"),

    # Misc SQL
    ("EXPLAIN", "EXPLAIN"),
    ("ANALYZE", "ANALYZE"),
    ("VERBOSE", "VERBOSE"),
    ("DESCRIBE", "DESCRIBE"),
    ("SHOW", "SHOW"),
    ("USE", "USE"),
    ("GRANT", "GRANT"),
    ("REVOKE", "REVOKE"),
    ("PRIVILEGES", "PRIVILEGES"),
    ("COPY", "COPY"),
    ("LOAD", "LOAD"),
    ("EXPORT", "EXPORT"),
    ("IMPORT", "IMPORT"),
    ("PRAGMA", "PRAGMA"),
    ("VACUUM", "VACUUM"),
    ("REINDEX", "REINDEX"),
    ("REGEXP", "REGEXP"),
    ("RLIKE", "RLIKE"),
    ("SIMILAR", "SIMILAR"),
    ("MATCHED", "MATCHED"),

    # DuckDB-specific
    ("HUGEINT", "HUGEINT"),
    ("UHUGEINT", "UHUGEINT"),
    ("LIST", "LIST"),
    ("EXCLUDE", "EXCLUDE"),
    ("COLUMNS", "COLUMNS"),
    ("SAMPLE", "SAMPLE"),
    ("SUMMARIZE", "SUMMARIZE"),

    # BigQuery-specific
    ("SAFE", "SAFE"),
    ("ORDINAL", "ORDINAL"),
    ("SAFE_OFFSET", "SAFE_OFFSET"),
    ("UNNEST", "UNNEST"),
    ("FLATTEN", "FLATTEN"),
    ("OPTIONS", "OPTIONS"),
    ("CLUSTER", "CLUSTER"),
    ("CURRENT_DATE", "CURRENT_DATE"),
    ("CURRENT_TIME", "CURRENT_TIME"),
    ("CURRENT_TIMESTAMP", "CURRENT_TIMESTAMP"),

    # Snowflake-specific
    ("VARIANT", "VARIANT"),
    ("OBJECT", "OBJECT"),
    ("CONNECT", "CONNECT"),
    ("NOCYCLE", "NOCYCLE"),
    ("START_WITH", "START_WITH"),
    ("CONNECT_BY", "CONNECT_BY"),
    ("PRIOR", "PRIOR"),

    # Postgres-specific
    ("DO", "DO"),
    ("LANGUAGE", "LANGUAGE"),
    ("PLPGSQL", "PLPGSQL"),
    ("DECLARE", "DECLARE"),
    ("PERFORM", "PERFORM"),
    ("GENERATE_SERIES", "GENERATE_SERIES"),
    ("DELIMITER", "DELIMITER_KW"),

    # Stored Procedures & Functions
    ("FUNCTION", "FUNCTION"),
    ("PROCEDURE", "PROCEDURE_KW"),
    ("CALL", "CALL"),
    ("RETURN", "RETURN_KW"),
    ("RETURNS", "RETURNS"),
    ("SETOF", "SETOF"),
    ("OUT", "OUT"),
    ("INOUT", "INOUT"),
    ("IF", "IF_KW"),
    ("WHILE", "WHILE"),
    ("LOOP", "LOOP"),
    ("EACH", "EACH"),
    ("ELSEIF", "ELSEIF"),
    ("ENDIF", "ENDIF"),
    ("ENDWHILE", "ENDWHILE"),
    ("ENDLOOP", "ENDLOOP"),
    ("BREAK", "BREAK"),
    ("CONTINUE", "CONTINUE"),
    ("EXIT", "EXIT"),
    ("EXCEPTION", "EXCEPTION"),
    ("WHEN", "WHEN_KW"),
    ("RAISE", "RAISE"),
    ("SIGNAL", "SIGNAL"),
    ("CURSOR", "CURSOR"),
    ("OPEN", "OPEN"),
    ("CLOSE", "CLOSE"),
    ("SCROLL", "SCROLL"),

    # Triggers
    ("TRIGGER", "TRIGGER"),
    ("BEFORE", "BEFORE"),
    ("AFTER", "AFTER"),
    ("INSTEAD", "INSTEAD"),
    ("OF", "OF"),
    ("EACH_ROW", "EACH_ROW"),
    ("EACH_STMT", "EACH_STMT"),
    ("OLD", "OLD"),
    ("NEW", "NEW"),

    # Advanced DDL
    ("TABLESPACE", "TABLESPACE"),
    ("CONCURRENTLY", "CONCURRENTLY"),
    ("HASH", "HASH"),
    ("MAXVALUE", "MAXVALUE"),
    ("MINVALUE", "MINVALUE"),

    # TSQL-specific
    ("TOP", "TOP"),
    ("OUTPUT", "OUTPUT"),
    ("INSERTED", "INSERTED"),
    ("DELETED", "DELETED"),
    ("GO", "GO"),
    ("EXEC", "EXEC"),
    ("EXECUTE", "EXECUTE"),
    ("IDENTITY", "IDENTITY"),
    ("SCOPE_IDENTITY", "SCOPE_IDENTITY"),

    # MySQL-specific
    ("AUTO_INCREMENT", "AUTO_INCREMENT"),
    ("UNSIGNED", "UNSIGNED"),
    ("ZEROFILL", "ZEROFILL"),
    ("ENGINE", "ENGINE"),
    ("CHARSET", "CHARSET"),
    ("COLLATE", "COLLATE"),
    ("STRAIGHT_JOIN", "STRAIGHT_JOIN"),
    ("FORCE", "FORCE"),
    ("USE_INDEX", "USE_INDEX"),

    # Oracle-specific
    ("DUAL", "DUAL"),
    ("ROWNUM", "ROWNUM"),
    ("ROWID", "ROWID"),
    ("CONNECT_BY_ROOT", "CONNECT_BY_ROOT"),
    ("SYS_CONNECT_BY_PATH", "SYS_CONNECT_BY_PATH"),

    # Clickhouse-specific
    ("PARTITION_BY", "PARTITION_BY"),
    ("ORDER_BY", "ORDER_BY"),
    ("FINAL", "FINAL"),
    ("PREWHERE", "PREWHERE"),
    ("SETTINGS", "SETTINGS"),
]

def perfect_hash(keyword):
    """Perfect hash: (first * 31 + last + length) & 127"""
    if not keyword:
        return 0
    return (ord(keyword[0]) * 31 + ord(keyword[-1]) + len(keyword)) & 127

# Build hash table with collision handling
hash_table = [[] for _ in range(128)]

for kw, token_type in keywords:
    h = perfect_hash(kw)
    hash_table[h].append((kw, token_type))

# Find maximum collisions to determine array size
max_collisions = max(len(entries) for entries in hash_table)
if max_collisions > 4:
    print(f"// ERROR: Maximum collisions ({max_collisions}) exceeds capacity (4)", file=__import__('sys').stderr)
    print(f"// Slots with >4 collisions:", file=__import__('sys').stderr)
    for i, entries in enumerate(hash_table):
        if len(entries) > 4:
            kws = ", ".join([kw for kw, _ in entries])
            print(f"//   Slot {i} ({len(entries)} entries): {kws}", file=__import__('sys').stderr)
    print(f"// Using 8-entry slots to accommodate all keywords", file=__import__('sys').stderr)
    SLOT_SIZE = 8
else:
    SLOT_SIZE = 4

# Generate C++ code
print("""#pragma once

#include "tokens.h"
#include <string_view>
#include <cstdint>

namespace libsqlglot {

/// Fast keyword lookup using perfect hash function
class KeywordLookup {
public:
    [[nodiscard]] static TokenType lookup(std::string_view text) noexcept {
        if (text.empty() || text.size() > 16) {
            return TokenType::IDENTIFIER;
        }

        // Convert to uppercase inline (branchless optimization)
        char upper[17];
        size_t len = text.size();
        for (size_t i = 0; i < len; ++i) {
            char c = text[i];
            // Branchless: subtract 32 if lowercase (avoids branch misprediction)
            // (c >= 'a') & (c <= 'z') evaluates to 0 or 1, shift left 5 bits = 0 or 32
            upper[i] = c - (((c >= 'a') & (c <= 'z')) << 5);
        }
        upper[len] = '\\0';

        // Perfect hash: (first * 31 + last + length) & 127
        uint32_t hash = (upper[0] * 31 + upper[len - 1] + len) & 127;
        const KeywordEntry& entry = keyword_table[hash];

        // Linear probing for collisions
        for (int i = 0; i < 8; ++i) {
            if (entry.keywords[i] == nullptr) break;
            if (len == entry.lengths[i]) {
                bool match = true;
                for (size_t j = 0; j < len; ++j) {
                    if (upper[j] != entry.keywords[i][j]) {
                        match = false;
                        break;
                    }
                }
                if (match) return entry.types[i];
            }
        }
        return TokenType::IDENTIFIER;
    }

private:
    struct KeywordEntry {
        const char* keywords[8];
        uint8_t lengths[8];
        TokenType types[8];
    };
""")

print(f"static constexpr KeywordEntry keyword_table[128] = {{")
for i, entries in enumerate(hash_table):
    if not entries:
        nulls = ", ".join(["nullptr"] * SLOT_SIZE)
        zeros = ", ".join(["0"] * SLOT_SIZE)
        idents = ", ".join(["TokenType::IDENTIFIER"] * SLOT_SIZE)
        print(f"    {{{{{nulls}}}, {{{zeros}}}, {{{idents}}}}},")
    else:
        # Take only first SLOT_SIZE entries
        limited_entries = entries[:SLOT_SIZE]
        keywords_str = ", ".join([f'"{kw}"' for kw, _ in limited_entries] + ["nullptr"] * (SLOT_SIZE - len(limited_entries)))
        lengths_str = ", ".join([str(len(kw)) for kw, _ in limited_entries] + ["0"] * (SLOT_SIZE - len(limited_entries)))
        types_str = ", ".join([f"TokenType::{tt}" for _, tt in limited_entries] + ["TokenType::IDENTIFIER"] * (SLOT_SIZE - len(limited_entries)))

        comment = ", ".join([f"{kw} (hash={i})" for kw, _ in limited_entries])
        print(f"    {{{{{keywords_str}}}, {{{lengths_str}}}, {{{types_str}}}}},  // {comment}")

print("};")

# Close the class and namespace
print("""
};

} // namespace libsqlglot""")

# Print hash collision report
print("\n// Hash collision report:")
for i, entries in enumerate(hash_table):
    if len(entries) > 1:
        kws = ", ".join([kw for kw, _ in entries])
        print(f"// Slot {i} ({len(entries)} entries): {kws}")
