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
    ("STRUCT", "STRUCT_KW"),
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

    # Redshift-specific
    ("DISTKEY", "DISTKEY"),
    ("SORTKEY", "SORTKEY"),
    ("SUPER", "SUPER"),
    ("DISTSTYLE", "DISTSTYLE"),

    # DuckDB/ClickHouse-specific
    ("ASOF", "ASOF"),

    # CockroachDB/SQLite-specific
    ("UPSERT", "UPSERT"),

    # Materialize-specific
    ("TAIL", "TAIL"),

    # Vertica-specific
    ("PROJECTION", "PROJECTION"),
    ("SEGMENTED", "SEGMENTED"),

    # Greenplum/Doris-specific
    ("DISTRIBUTED", "DISTRIBUTED"),

    # SingleStore/PGVector-specific
    ("VECTOR", "VECTOR"),

    # Doris-specific
    ("DUPLICATE", "DUPLICATE"),
    ("BUCKETS", "BUCKETS"),

    # TiDB-specific
    ("AUTO_RANDOM", "AUTO_RANDOM"),

    # MySQL/Spark-specific operators (note: NULL_SAFE_EQ is an operator, not a keyword)
    # ("NULL_SAFE_EQ", "NULL_SAFE_EQ"),  # Handled separately as operator

    # Databricks-specific
    ("OPTIMIZE", "OPTIMIZE"),
    ("ZORDER", "ZORDER"),

    # Hive/Impala-specific
    ("COMPUTE", "COMPUTE"),
    ("STATS", "STATS"),
]

# Configuration constants - eliminates magic numbers
class HashConfig:
    """Configuration for perfect hash table generation"""
    # Hash function parameters
    HASH_MULTIPLIER = 31        # Prime number for better distribution
    HASH_TABLE_SIZE = 256       # Increased from 128 to reduce collisions
    HASH_MASK = HASH_TABLE_SIZE - 1  # Bitmask for fast modulo

    # Slot sizing parameters
    MIN_SLOT_SIZE = 4           # Minimum entries per slot
    MAX_SLOT_SIZE = 8           # Maximum entries per slot
    PREFERRED_MAX_COLLISIONS = 3  # Target maximum collisions per slot

    # Code generation parameters
    MAX_KEYWORD_LENGTH = 19     # Longest keyword: SYS_CONNECT_BY_PATH
    UPPERCASE_OFFSET = 32       # ASCII offset for lowercase to uppercase

    @classmethod
    def validate(cls):
        """Validate configuration parameters"""
        assert cls.HASH_TABLE_SIZE > 0 and (cls.HASH_TABLE_SIZE & (cls.HASH_TABLE_SIZE - 1)) == 0, \
            "HASH_TABLE_SIZE must be a power of 2"
        assert cls.MIN_SLOT_SIZE > 0 and cls.MAX_SLOT_SIZE >= cls.MIN_SLOT_SIZE, \
            "Invalid slot size configuration"

# Validate configuration on startup
HashConfig.validate()

def perfect_hash(keyword: str) -> int:
    """
    Perfect hash function using multiplicative hashing with length component.

    Formula: (first_char * HASH_MULTIPLIER + last_char + length) & HASH_MASK

    Args:
        keyword: Keyword to hash (assumed uppercase)

    Returns:
        Hash value in range [0, HASH_TABLE_SIZE)
    """
    if not keyword:
        return 0

    first_char = ord(keyword[0])
    last_char = ord(keyword[-1])
    length = len(keyword)

    hash_value = (first_char * HashConfig.HASH_MULTIPLIER + last_char + length) & HashConfig.HASH_MASK
    return hash_value

def build_hash_table(keywords_list: list) -> tuple:
    """
    Build hash table with collision tracking.

    Args:
        keywords_list: List of (keyword, token_type) tuples

    Returns:
        Tuple of (hash_table, max_collisions, collision_report)
    """
    hash_table = [[] for _ in range(HashConfig.HASH_TABLE_SIZE)]

    for kw, token_type in keywords_list:
        h = perfect_hash(kw)
        hash_table[h].append((kw, token_type))

    # Analyze collisions
    max_collisions = max(len(entries) for entries in hash_table) if hash_table else 0

    # Generate collision report
    collision_report = []
    for i, entries in enumerate(hash_table):
        if len(entries) > 1:
            kws = ", ".join([kw for kw, _ in entries])
            collision_report.append(f"Slot {i} ({len(entries)} entries): {kws}")

    return hash_table, max_collisions, collision_report

def determine_slot_size(max_collisions: int) -> int:
    """
    Determine optimal slot size based on maximum collisions.

    Args:
        max_collisions: Maximum number of collisions in any slot

    Returns:
        Slot size to use
    """
    if max_collisions <= HashConfig.PREFERRED_MAX_COLLISIONS:
        return HashConfig.MIN_SLOT_SIZE
    elif max_collisions <= HashConfig.MAX_SLOT_SIZE:
        return HashConfig.MAX_SLOT_SIZE
    else:
        raise ValueError(
            f"Maximum collisions ({max_collisions}) exceeds MAX_SLOT_SIZE ({HashConfig.MAX_SLOT_SIZE}). "
            f"Consider increasing HASH_TABLE_SIZE or improving hash function."
        )

# Build hash table
hash_table, max_collisions, collision_report = build_hash_table(keywords)
SLOT_SIZE = determine_slot_size(max_collisions)

def generate_cpp_header(slot_size: int, table_size: int, collision_report: list) -> str:
    """
    Generate C++ header file content.

    Args:
        slot_size: Number of entries per hash table slot
        table_size: Total size of hash table
        collision_report: List of collision information strings

    Returns:
        Complete C++ header file content as string
    """
    # Generate collision report as comments
    collision_comments = "\n".join([f"// {line}" for line in collision_report])
    if collision_report:
        collision_header = f"// Hash collision report ({len(collision_report)} slots with collisions):\n{collision_comments}\n"
    else:
        collision_header = "// No hash collisions - perfect hash achieved!\n"

    buffer_size = HashConfig.MAX_KEYWORD_LENGTH + 1

    header = f"""#pragma once

#include "tokens.h"
#include <string_view>
#include <cstdint>

namespace libsqlglot {{

/// Fast keyword lookup using perfect hash function
///
/// Hash table configuration:
/// - Table size: {table_size}
/// - Slot size: {slot_size}
/// - Max keyword length: {HashConfig.MAX_KEYWORD_LENGTH}
/// - Hash function: (first * {HashConfig.HASH_MULTIPLIER} + last + length) & {HashConfig.HASH_MASK}
///
{collision_header}
class KeywordLookup {{
public:
    [[nodiscard]] static TokenType lookup(std::string_view text) noexcept {{
        if (text.empty() || text.size() > {HashConfig.MAX_KEYWORD_LENGTH}) {{
            return TokenType::IDENTIFIER;
        }}

        // Convert to uppercase inline (branchless optimization)
        char upper[{buffer_size}];
        size_t len = text.size();
        for (size_t i = 0; i < len; ++i) {{
            char c = text[i];
            // Branchless: subtract {HashConfig.UPPERCASE_OFFSET} if lowercase (avoids branch misprediction)
            // (c >= 'a') & (c <= 'z') evaluates to 0 or 1, shift left 5 bits = 0 or {HashConfig.UPPERCASE_OFFSET}
            upper[i] = c - (((c >= 'a') & (c <= 'z')) << 5);
        }}
        upper[len] = '\\0';

        // Perfect hash: (first * {HashConfig.HASH_MULTIPLIER} + last + length) & {HashConfig.HASH_MASK}
        uint32_t hash = (upper[0] * {HashConfig.HASH_MULTIPLIER} + upper[len - 1] + len) & {HashConfig.HASH_MASK};
        const KeywordEntry& entry = keyword_table[hash];

        // Linear probing for collisions
        for (int i = 0; i < {slot_size}; ++i) {{
            if (entry.keywords[i] == nullptr) break;
            if (len == entry.lengths[i]) {{
                bool match = true;
                for (size_t j = 0; j < len; ++j) {{
                    if (upper[j] != entry.keywords[i][j]) {{
                        match = false;
                        break;
                    }}
                }}
                if (match) return entry.types[i];
            }}
        }}
        return TokenType::IDENTIFIER;
    }}

private:
    struct KeywordEntry {{
        const char* keywords[{slot_size}];
        uint8_t lengths[{slot_size}];
        TokenType types[{slot_size}];
    }};
"""
    return header

# Generate C++ code
print(generate_cpp_header(SLOT_SIZE, HashConfig.HASH_TABLE_SIZE, collision_report))

def generate_empty_slot(slot_size: int) -> tuple:
    """Generate arrays for an empty hash table slot."""
    nulls = ", ".join(["nullptr"] * slot_size)
    zeros = ", ".join(["0"] * slot_size)
    idents = ", ".join(["TokenType::IDENTIFIER"] * slot_size)
    return nulls, zeros, idents

def generate_filled_slot(entries: list, slot_size: int, slot_index: int) -> tuple:
    """Generate arrays for a filled hash table slot."""
    # Ensure we don't exceed slot size
    limited_entries = entries[:slot_size]
    padding_count = slot_size - len(limited_entries)

    # Generate keyword strings
    keywords_str = ", ".join(
        [f'"{kw}"' for kw, _ in limited_entries] + ["nullptr"] * padding_count
    )

    # Generate lengths
    lengths_str = ", ".join(
        [str(len(kw)) for kw, _ in limited_entries] + ["0"] * padding_count
    )

    # Generate token types
    types_str = ", ".join(
        [f"TokenType::{tt}" for _, tt in limited_entries] + ["TokenType::IDENTIFIER"] * padding_count
    )

    # Generate comment
    comment = ", ".join([f"{kw} (hash={slot_index})" for kw, _ in limited_entries])

    return keywords_str, lengths_str, types_str, comment

def generate_hash_table_code(hash_table: list, slot_size: int, table_size: int) -> str:
    """
    Generate C++ static hash table initialization code.

    Args:
        hash_table: List of keyword entries per slot
        slot_size: Number of entries per slot
        table_size: Total size of hash table

    Returns:
        C++ code for static hash table
    """
    lines = [f"static constexpr KeywordEntry keyword_table[{table_size}] = {{"]

    for i in range(table_size):
        entries = hash_table[i] if i < len(hash_table) else []

        if not entries:
            nulls, zeros, idents = generate_empty_slot(slot_size)
            lines.append(f"    {{{{{nulls}}}, {{{zeros}}}, {{{idents}}}}},")
        else:
            keywords_str, lengths_str, types_str, comment = generate_filled_slot(entries, slot_size, i)
            lines.append(f"    {{{{{keywords_str}}}, {{{lengths_str}}}, {{{types_str}}}}},  // {comment}")

    lines.append("};")
    return "\n".join(lines)

# Generate hash table
print(generate_hash_table_code(hash_table, SLOT_SIZE, HashConfig.HASH_TABLE_SIZE))

# Close the class and namespace
print("""
};

} // namespace libsqlglot""")
