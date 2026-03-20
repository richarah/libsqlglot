#!/usr/bin/env python3
"""Generate perfect hash keyword table for libsqlglot"""

# List of SQL keywords with their token types
keywords = [
    ("SELECT", "SELECT"),
    ("FROM", "FROM"),
    ("WHERE", "WHERE"),
    ("INSERT", "INSERT"),
    ("UPDATE", "UPDATE"),
    ("DELETE", "DELETE"),
    ("CREATE", "CREATE"),
    ("DROP", "DROP"),
    ("TABLE", "TABLE"),
    ("VIEW", "VIEW"),
    ("INDEX", "INDEX"),
    ("ALTER", "ALTER"),
    ("JOIN", "JOIN"),
    ("INNER", "INNER"),
    ("LEFT", "LEFT"),
    ("RIGHT", "RIGHT"),
    ("FULL", "FULL"),
    ("CROSS", "CROSS"),
    ("ON", "ON"),
    ("USING", "USING"),
    ("UNION", "UNION"),
    ("INTERSECT", "INTERSECT"),
    ("EXCEPT", "EXCEPT"),
    ("GROUP", "GROUP"),
    ("HAVING", "HAVING"),
    ("ORDER", "ORDER"),
    ("BY", "BY"),
    ("LIMIT", "LIMIT"),
    ("OFFSET", "OFFSET"),
    ("DISTINCT", "DISTINCT"),
    ("ALL", "ALL"),
    ("AS", "AS"),
    ("AND", "AND"),
    ("OR", "OR"),
    ("NOT", "NOT"),
    ("IN", "IN"),
    ("EXISTS", "EXISTS"),
    ("BETWEEN", "BETWEEN"),
    ("LIKE", "LIKE"),
    ("IS", "IS"),
    ("NULL", "NULL_KW"),
    ("TRUE", "TRUE"),
    ("FALSE", "FALSE"),
    ("CASE", "CASE"),
    ("WHEN", "WHEN"),
    ("THEN", "THEN"),
    ("ELSE", "ELSE"),
    ("END", "END"),
    ("WITH", "WITH"),
    ("RECURSIVE", "RECURSIVE"),
    ("VALUES", "VALUES"),
    ("DEFAULT", "DEFAULT"),
    ("SET", "SET"),
    ("RETURNING", "RETURNING"),
    ("PRIMARY", "PRIMARY"),
    ("FOREIGN", "FOREIGN"),
    ("REFERENCES", "REFERENCES"),
    ("UNIQUE", "UNIQUE"),
    ("CHECK", "CHECK"),
    ("KEY", "KEY"),
    ("BEGIN", "BEGIN"),
    ("COMMIT", "COMMIT"),
    ("ROLLBACK", "ROLLBACK"),
    ("SAVEPOINT", "SAVEPOINT"),
    ("SHOW", "SHOW"),
    ("DESCRIBE", "DESCRIBE"),
    ("DESC", "DESC"),
    ("EXPLAIN", "EXPLAIN"),
    ("ANALYZE", "ANALYZE"),
    ("IF", "IF_KW"),
    ("OVER", "OVER"),
    ("PARTITION", "PARTITION"),
    ("ROWS", "ROWS"),
    ("RANGE", "RANGE"),
    ("ANY", "ANY"),
    ("SOME", "SOME"),
    ("COALESCE", "COALESCE"),
    ("NULLIF", "NULLIF"),
    ("INTO", "INTO"),
    ("MERGE", "MERGE"),
    ("MATCHED", "MATCHED"),
    ("SIMILAR", "SIMILAR"),
    ("REGEXP", "REGEXP"),
    ("LATERAL", "LATERAL"),
    ("PIVOT", "PIVOT"),
    ("UNPIVOT", "UNPIVOT"),
    ("TABLESAMPLE", "TABLESAMPLE"),
    ("QUALIFY", "QUALIFY"),
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

# Generate C++ code
print("static constexpr KeywordEntry keyword_table[128] = {")
for i, entries in enumerate(hash_table):
    if not entries:
        print(f"    {{{{nullptr, nullptr, nullptr, nullptr}}, {{0, 0, 0, 0}}, {{TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER}}}},")
    else:
        keywords_str = ", ".join([f'"{kw}"' if kw else "nullptr" for kw, _ in entries] + ["nullptr"] * (4 - len(entries)))
        lengths_str = ", ".join([str(len(kw)) for kw, _ in entries] + ["0"] * (4 - len(entries)))
        types_str = ", ".join([f"TokenType::{tt}" for _, tt in entries] + ["TokenType::IDENTIFIER"] * (4 - len(entries)))

        comment = ", ".join([f"{kw} (hash={i})" for kw, _ in entries])
        print(f"    {{{{{keywords_str}}}, {{{lengths_str}}}, {{{types_str}}}}},  // {comment}")

print("};")

# Print hash collision report
print("\n// Hash collision report:")
for i, entries in enumerate(hash_table):
    if len(entries) > 1:
        kws = ", ".join([kw for kw, _ in entries])
        print(f"// Slot {i}: {kws}")
