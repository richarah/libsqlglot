#pragma once

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
        upper[len] = '\0';

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

    
static constexpr KeywordEntry keyword_table[128] = {
    {{"TEMP", "PRECEDING", "CONNECT_BY", "CONNECT_BY_ROOT", nullptr, nullptr, nullptr, nullptr}, {4, 9, 10, 15, 0, 0, 0, 0}, {TokenType::TEMP, TokenType::PRECEDING, TokenType::CONNECT_BY, TokenType::CONNECT_BY_ROOT, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER}},  // TEMP (hash=0), PRECEDING (hash=0), CONNECT_BY (hash=0), CONNECT_BY_ROOT (hash=0)
    {{"LANGUAGE", nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr}, {8, 0, 0, 0, 0, 0, 0, 0}, {TokenType::LANGUAGE, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER}},  // LANGUAGE (hash=1)
    {{"LENGTH", "CONCURRENTLY", nullptr, nullptr, nullptr, nullptr, nullptr, nullptr}, {6, 12, 0, 0, 0, 0, 0, 0}, {TokenType::LENGTH, TokenType::CONCURRENTLY, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER}},  // LENGTH (hash=2), CONCURRENTLY (hash=2)
    {{"DESC", "LAST_VALUE", "PLPGSQL", nullptr, nullptr, nullptr, nullptr, nullptr}, {4, 10, 7, 0, 0, 0, 0, 0}, {TokenType::DESC, TokenType::LAST_VALUE, TokenType::PLPGSQL, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER}},  // DESC (hash=3), LAST_VALUE (hash=3), PLPGSQL (hash=3)
    {{"TEXT", "PERFORM", "HASH", nullptr, nullptr, nullptr, nullptr, nullptr}, {4, 7, 4, 0, 0, 0, 0, 0}, {TokenType::TEXT, TokenType::PERFORM, TokenType::HASH, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER}},  // TEXT (hash=4), PERFORM (hash=4), HASH (hash=4)
    {{"HAVING", "DATE", "TIMESTAMP", "TRANSACTION", "LEVEL", "TRIGGER", nullptr, nullptr}, {6, 4, 9, 11, 5, 7, 0, 0}, {TokenType::HAVING, TokenType::DATE, TokenType::TIMESTAMP, TokenType::TRANSACTION, TokenType::LEVEL, TokenType::TRIGGER, TokenType::IDENTIFIER, TokenType::IDENTIFIER}},  // HAVING (hash=5), DATE (hash=5), TIMESTAMP (hash=5), TRANSACTION (hash=5), LEVEL (hash=5), TRIGGER (hash=5)
    {{"DATE_SUB", nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr}, {8, 0, 0, 0, 0, 0, 0, 0}, {TokenType::DATE_SUB, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER}},  // DATE_SUB (hash=6)
    {{"DELETE", "TINYINT", "DOUBLE", "POWER", "PARTITION", "LATERAL", "PRIOR", "DELETED"}, {6, 7, 6, 5, 9, 7, 5, 7}, {TokenType::DELETE, TokenType::TINYINT, TokenType::DOUBLE, TokenType::POWER, TokenType::PARTITION, TokenType::LATERAL, TokenType::PRIOR, TokenType::DELETED}},  // DELETE (hash=7), TINYINT (hash=7), DOUBLE (hash=7), POWER (hash=7), PARTITION (hash=7), LATERAL (hash=7), PRIOR (hash=7), DELETED (hash=7)
    {{"TRY_CAST", "DATE_ADD", "DECLARE", "LOOP", nullptr, nullptr, nullptr, nullptr}, {8, 8, 7, 4, 0, 0, 0, 0}, {TokenType::TRY_CAST, TokenType::DATE_ADD, TokenType::DECLARE, TokenType::LOOP, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER}},  // TRY_CAST (hash=8), DATE_ADD (hash=8), DECLARE (hash=8), LOOP (hash=8)
    {{"DATABASE", "DATE_TRUNC", "PIVOT", "DESCRIBE", nullptr, nullptr, nullptr, nullptr}, {8, 10, 5, 8, 0, 0, 0, 0}, {TokenType::DATABASE, TokenType::DATE_TRUNC, TokenType::PIVOT, TokenType::DESCRIBE, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER}},  // DATABASE (hash=9), DATE_TRUNC (hash=9), PIVOT (hash=9), DESCRIBE (hash=9)
    {{nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr}, {0, 0, 0, 0, 0, 0, 0, 0}, {TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER}},
    {{"DATE_DIFF", "LOWER", nullptr, nullptr, nullptr, nullptr, nullptr, nullptr}, {9, 5, 0, 0, 0, 0, 0, 0}, {TokenType::DATE_DIFF, TokenType::LOWER, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER}},  // DATE_DIFF (hash=11), LOWER (hash=11)
    {{"LEFT", "LAST", "LIST", "DUAL", nullptr, nullptr, nullptr, nullptr}, {4, 4, 4, 4, 0, 0, 0, 0}, {TokenType::LEFT, TokenType::LAST, TokenType::LIST, TokenType::DUAL, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER}},  // LEFT (hash=12), LAST (hash=12), LIST (hash=12), DUAL (hash=12)
    {{"LIMIT", "PRIVILEGES", "DO", nullptr, nullptr, nullptr, nullptr, nullptr}, {5, 10, 2, 0, 0, 0, 0, 0}, {TokenType::LIMIT, TokenType::PRIVILEGES, TokenType::DO, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER}},  // LIMIT (hash=13), PRIVILEGES (hash=13), DO (hash=13)
    {{"TEMPORARY", nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr}, {9, 0, 0, 0, 0, 0, 0, 0}, {TokenType::TEMPORARY, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER}},  // TEMPORARY (hash=14)
    {{"DECIMAL", nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr}, {7, 0, 0, 0, 0, 0, 0, 0}, {TokenType::DECIMAL, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER}},  // DECIMAL (hash=15)
    {{"DROP", "PRIMARY", nullptr, nullptr, nullptr, nullptr, nullptr, nullptr}, {4, 7, 0, 0, 0, 0, 0, 0}, {TokenType::DROP, TokenType::PRIMARY, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER}},  // DROP (hash=16), PRIMARY (hash=16)
    {{"TIMESTAMPTZ", "DENSE_RANK", nullptr, nullptr, nullptr, nullptr, nullptr, nullptr}, {11, 10, 0, 0, 0, 0, 0, 0}, {TokenType::TIMESTAMPTZ, TokenType::DENSE_RANK, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER}},  // TIMESTAMPTZ (hash=17), DENSE_RANK (hash=17)
    {{nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr}, {0, 0, 0, 0, 0, 0, 0, 0}, {TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER}},
    {{"UUID", "USE", "HUGEINT", nullptr, nullptr, nullptr, nullptr, nullptr}, {4, 3, 7, 0, 0, 0, 0, 0}, {TokenType::UUID, TokenType::USE, TokenType::HUGEINT, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER}},  // UUID (hash=19), USE (hash=19), HUGEINT (hash=19)
    {{nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr}, {0, 0, 0, 0, 0, 0, 0, 0}, {TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER}},
    {{"PARTITION_BY", nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr}, {12, 0, 0, 0, 0, 0, 0, 0}, {TokenType::PARTITION_BY, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER}},  // PARTITION_BY (hash=21)
    {{"UPDATE", "UNIQUE", nullptr, nullptr, nullptr, nullptr, nullptr, nullptr}, {6, 6, 0, 0, 0, 0, 0, 0}, {TokenType::UPDATE, TokenType::UNIQUE, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER}},  // UPDATE (hash=22), UNIQUE (hash=22)
    {{"USING", "DEFAULT", "DELIMITER", "UNSIGNED", nullptr, nullptr, nullptr, nullptr}, {5, 7, 9, 8, 0, 0, 0, 0}, {TokenType::USING, TokenType::DEFAULT, TokenType::DELIMITER_KW, TokenType::UNSIGNED, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER}},  // USING (hash=23), DEFAULT (hash=23), DELIMITER (hash=23), UNSIGNED (hash=23)
    {{"DISTINCT", "UNBOUNDED", nullptr, nullptr, nullptr, nullptr, nullptr, nullptr}, {8, 9, 0, 0, 0, 0, 0, 0}, {TokenType::DISTINCT, TokenType::UNBOUNDED, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER}},  // DISTINCT (hash=24), UNBOUNDED (hash=24)
    {{nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr}, {0, 0, 0, 0, 0, 0, 0, 0}, {TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER}},
    {{"UNCOMMITTED", nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr}, {11, 0, 0, 0, 0, 0, 0, 0}, {TokenType::UNCOMMITTED, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER}},  // UNCOMMITTED (hash=26)
    {{nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr}, {0, 0, 0, 0, 0, 0, 0, 0}, {TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER}},
    {{nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr}, {0, 0, 0, 0, 0, 0, 0, 0}, {TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER}},
    {{"MERGE", nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr}, {5, 0, 0, 0, 0, 0, 0, 0}, {TokenType::MERGE, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER}},  // MERGE (hash=29)
    {{"UNION", "MATCHED", nullptr, nullptr, nullptr, nullptr, nullptr, nullptr}, {5, 7, 0, 0, 0, 0, 0, 0}, {TokenType::UNION, TokenType::MATCHED, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER}},  // UNION (hash=30), MATCHED (hash=30)
    {{"IF", nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr}, {2, 0, 0, 0, 0, 0, 0, 0}, {TokenType::IF_KW, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER}},  // IF (hash=31)
    {{"MAXVALUE", "MINVALUE", nullptr, nullptr, nullptr, nullptr, nullptr, nullptr}, {8, 8, 0, 0, 0, 0, 0, 0}, {TokenType::MAXVALUE, TokenType::MINVALUE, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER}},  // MAXVALUE (hash=32), MINVALUE (hash=32)
    {{"ILIKE", nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr}, {5, 0, 0, 0, 0, 0, 0, 0}, {TokenType::ILIKE, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER}},  // ILIKE (hash=33)
    {{"END", "UPPER", "IGNORE", "INSTEAD", "EXEC", nullptr, nullptr, nullptr}, {3, 5, 6, 7, 4, 0, 0, 0}, {TokenType::END, TokenType::UPPER, TokenType::IGNORE, TokenType::INSTEAD, TokenType::EXEC, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER}},  // END (hash=34), UPPER (hash=34), IGNORE (hash=34), INSTEAD (hash=34), EXEC (hash=34)
    {{"INSERTED", nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr}, {8, 0, 0, 0, 0, 0, 0, 0}, {TokenType::INSERTED, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER}},  // INSERTED (hash=35)
    {{"ELSE", "MIN", nullptr, nullptr, nullptr, nullptr, nullptr, nullptr}, {4, 3, 0, 0, 0, 0, 0, 0}, {TokenType::ELSE, TokenType::MIN, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER}},  // ELSE (hash=36), MIN (hash=36)
    {{"ASC", "UNNEST", nullptr, nullptr, nullptr, nullptr, nullptr, nullptr}, {3, 6, 0, 0, 0, 0, 0, 0}, {TokenType::ASC, TokenType::UNNEST, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER}},  // ASC (hash=37), UNNEST (hash=37)
    {{"AND", "MAP", "ADD", "UNPIVOT", "ENDIF", "ENGINE", nullptr, nullptr}, {3, 3, 3, 7, 5, 6, 0, 0}, {TokenType::AND, TokenType::MAP, TokenType::ADD, TokenType::UNPIVOT, TokenType::ENDIF, TokenType::ENGINE, TokenType::IDENTIFIER, TokenType::IDENTIFIER}},  // AND (hash=38), MAP (hash=38), ADD (hash=38), UNPIVOT (hash=38), ENDIF (hash=38), ENGINE (hash=38)
    {{"IN", "UHUGEINT", "EXCLUDE", "EACH", "ELSEIF", "EXECUTE", nullptr, nullptr}, {2, 8, 7, 4, 6, 7, 0, 0}, {TokenType::IN, TokenType::UHUGEINT, TokenType::EXCLUDE, TokenType::EACH, TokenType::ELSEIF, TokenType::EXECUTE, TokenType::IDENTIFIER, TokenType::IDENTIFIER}},  // IN (hash=39), UHUGEINT (hash=39), EXCLUDE (hash=39), EACH (hash=39), ELSEIF (hash=39), EXECUTE (hash=39)
    {{"ENDWHILE", nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr}, {8, 0, 0, 0, 0, 0, 0, 0}, {TokenType::ENDWHILE, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER}},  // ENDWHILE (hash=40)
    {{"AVG", "IFNULL", nullptr, nullptr, nullptr, nullptr, nullptr, nullptr}, {3, 6, 0, 0, 0, 0, 0, 0}, {TokenType::AVG, TokenType::IFNULL, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER}},  // AVG (hash=41), IFNULL (hash=41)
    {{"INTO", nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr}, {4, 0, 0, 0, 0, 0, 0, 0}, {TokenType::INTO, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER}},  // INTO (hash=42)
    {{"MINUS", "INTERVAL", "ANALYZE", nullptr, nullptr, nullptr, nullptr, nullptr}, {5, 8, 7, 0, 0, 0, 0, 0}, {TokenType::MINUS_KW, TokenType::INTERVAL, TokenType::ANALYZE, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER}},  // MINUS (hash=43), INTERVAL (hash=43), ANALYZE (hash=43)
    {{"IS", "USE_INDEX", nullptr, nullptr, nullptr, nullptr, nullptr, nullptr}, {2, 9, 0, 0, 0, 0, 0, 0}, {TokenType::IS, TokenType::USE_INDEX, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER}},  // IS (hash=44), USE_INDEX (hash=44)
    {{nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr}, {0, 0, 0, 0, 0, 0, 0, 0}, {TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER}},
    {{"INNER", "ALL", "INT", "MAX", "ISOLATION", nullptr, nullptr, nullptr}, {5, 3, 3, 3, 9, 0, 0, 0}, {TokenType::INNER, TokenType::ALL, TokenType::INT, TokenType::MAX, TokenType::ISOLATION, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER}},  // INNER (hash=46), ALL (hash=46), INT (hash=46), MAX (hash=46), ISOLATION (hash=46)
    {{"QUALIFY", nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr}, {7, 0, 0, 0, 0, 0, 0, 0}, {TokenType::QUALIFY, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER}},  // QUALIFY (hash=47)
    {{"INTEGER", "EXPLAIN", "INOUT", nullptr, nullptr, nullptr, nullptr, nullptr}, {7, 7, 5, 0, 0, 0, 0, 0}, {TokenType::INTEGER, TokenType::EXPLAIN, TokenType::INOUT, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER}},  // INTEGER (hash=48), EXPLAIN (hash=48), INOUT (hash=48)
    {{"INSERT", "IMPORT", nullptr, nullptr, nullptr, nullptr, nullptr, nullptr}, {6, 6, 0, 0, 0, 0, 0, 0}, {TokenType::INSERT, TokenType::IMPORT, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER}},  // INSERT (hash=49), IMPORT (hash=49)
    {{"MODIFY", "ENDLOOP", "EXCEPTION", nullptr, nullptr, nullptr, nullptr, nullptr}, {6, 7, 9, 0, 0, 0, 0, 0}, {TokenType::MODIFY, TokenType::ENDLOOP, TokenType::EXCEPTION, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER}},  // MODIFY (hash=50), ENDLOOP (hash=50), EXCEPTION (hash=50)
    {{nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr}, {0, 0, 0, 0, 0, 0, 0, 0}, {TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER}},
    {{"INTERSECT", "AS", "EXISTS", "INDEX", nullptr, nullptr, nullptr, nullptr}, {9, 2, 6, 5, 0, 0, 0, 0}, {TokenType::INTERSECT, TokenType::AS, TokenType::EXISTS, TokenType::INDEX, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER}},  // INTERSECT (hash=52), AS (hash=52), EXISTS (hash=52), INDEX (hash=52)
    {{"EXCEPT", "ABS", "EXPORT", nullptr, nullptr, nullptr, nullptr, nullptr}, {6, 3, 6, 0, 0, 0, 0, 0}, {TokenType::EXCEPT, TokenType::ABS, TokenType::EXPORT, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER}},  // EXCEPT (hash=53), ABS (hash=53), EXPORT (hash=53)
    {{"ALTER", "EXTRACT", "READ", "VERBOSE", "AFTER", nullptr, nullptr, nullptr}, {5, 7, 4, 7, 5, 0, 0, 0}, {TokenType::ALTER, TokenType::EXTRACT, TokenType::READ, TokenType::VERBOSE, TokenType::AFTER, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER}},  // ALTER (hash=54), EXTRACT (hash=54), READ (hash=54), VERBOSE (hash=54), AFTER (hash=54)
    {{"ROUND", "ROWID", nullptr, nullptr, nullptr, nullptr, nullptr, nullptr}, {5, 5, 0, 0, 0, 0, 0, 0}, {TokenType::ROUND, TokenType::ROWID, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER}},  // ROUND (hash=55), ROWID (hash=55)
    {{"RANGE", "RLIKE", "RAISE", "EACH_STMT", "IDENTITY", nullptr, nullptr, nullptr}, {5, 5, 5, 9, 8, 0, 0, 0}, {TokenType::RANGE, TokenType::RLIKE, TokenType::RAISE, TokenType::EACH_STMT, TokenType::IDENTITY, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER}},  // RANGE (hash=56), RLIKE (hash=56), RAISE (hash=56), EACH_STMT (hash=56), IDENTITY (hash=56)
    {{"RENAME", "REVOKE", nullptr, nullptr, nullptr, nullptr, nullptr, nullptr}, {6, 6, 0, 0, 0, 0, 0, 0}, {TokenType::RENAME, TokenType::REVOKE, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER}},  // RENAME (hash=57), REVOKE (hash=57)
    {{"REPLACE", "EACH_ROW", "ZEROFILL", nullptr, nullptr, nullptr, nullptr, nullptr}, {7, 8, 8, 0, 0, 0, 0, 0}, {TokenType::REPLACE_KW, TokenType::EACH_ROW, TokenType::ZEROFILL, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER}},  // REPLACE (hash=58), EACH_ROW (hash=58), ZEROFILL (hash=58)
    {{"ANY", nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr}, {3, 0, 0, 0, 0, 0, 0, 0}, {TokenType::ANY, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER}},  // ANY (hash=59)
    {{"RECURSIVE", "NUMERIC", "NTILE", nullptr, nullptr, nullptr, nullptr, nullptr}, {9, 7, 5, 0, 0, 0, 0, 0}, {TokenType::RECURSIVE, TokenType::NUMERIC, TokenType::NTILE, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER}},  // RECURSIVE (hash=60), NUMERIC (hash=60), NTILE (hash=60)
    {{"ARRAY", "JSONB", "RANK", "APPLY", "REPEATABLE", "VACUUM", nullptr, nullptr}, {5, 5, 4, 5, 10, 6, 0, 0}, {TokenType::ARRAY, TokenType::JSONB, TokenType::RANK, TokenType::APPLY, TokenType::REPEATABLE, TokenType::VACUUM, TokenType::IDENTIFIER, TokenType::IDENTIFIER}},  // ARRAY (hash=61), JSONB (hash=61), RANK (hash=61), APPLY (hash=61), REPEATABLE (hash=61), VACUUM (hash=61)
    {{"RETURNING", "REAL", "NULLIF", "NOCYCLE", nullptr, nullptr, nullptr, nullptr}, {9, 4, 6, 7, 0, 0, 0, 0}, {TokenType::RETURNING, TokenType::REAL, TokenType::NULLIF, TokenType::NOCYCLE, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER}},  // RETURNING (hash=62), REAL (hash=62), NULLIF (hash=62), NOCYCLE (hash=62)
    {{nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr}, {0, 0, 0, 0, 0, 0, 0, 0}, {TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER}},
    {{"NTH_VALUE", nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr}, {9, 0, 0, 0, 0, 0, 0, 0}, {TokenType::NTH_VALUE, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER}},  // NTH_VALUE (hash=64)
    {{"NVL", "ROLLBACK", "AUTO_INCREMENT", "ROWNUM", nullptr, nullptr, nullptr, nullptr}, {3, 8, 14, 6, 0, 0, 0, 0}, {TokenType::NVL, TokenType::ROLLBACK, TokenType::AUTO_INCREMENT, TokenType::ROWNUM, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER}},  // NVL (hash=65), ROLLBACK (hash=65), AUTO_INCREMENT (hash=65), ROWNUM (hash=65)
    {{"NULL", "RETURN", nullptr, nullptr, nullptr, nullptr, nullptr, nullptr}, {4, 6, 0, 0, 0, 0, 0, 0}, {TokenType::NULL_KW, TokenType::RETURN_KW, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER}},  // NULL (hash=66), RETURN (hash=66)
    {{"VALUES", "VARCHAR", nullptr, nullptr, nullptr, nullptr, nullptr, nullptr}, {6, 7, 0, 0, 0, 0, 0, 0}, {TokenType::VALUES, TokenType::VARCHAR, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER}},  // VALUES (hash=67), VARCHAR (hash=67)
    {{"FALSE", "BLOB", "REGEXP", "FORCE", nullptr, nullptr, nullptr, nullptr}, {5, 4, 6, 5, 0, 0, 0, 0}, {TokenType::FALSE, TokenType::BLOB, TokenType::REGEXP, TokenType::FORCE, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER}},  // FALSE (hash=68), BLOB (hash=68), REGEXP (hash=68), FORCE (hash=68)
    {{"NATURAL", "VIEW", "ROWS", "VARIANT", nullptr, nullptr, nullptr, nullptr}, {7, 4, 4, 7, 0, 0, 0, 0}, {TokenType::NATURAL, TokenType::VIEW, TokenType::ROWS, TokenType::VARIANT, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER}},  // NATURAL (hash=69), VIEW (hash=69), ROWS (hash=69), VARIANT (hash=69)
    {{nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr}, {0, 0, 0, 0, 0, 0, 0, 0}, {TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER}},
    {{"RIGHT", "FETCH", nullptr, nullptr, nullptr, nullptr, nullptr, nullptr}, {5, 5, 0, 0, 0, 0, 0, 0}, {TokenType::RIGHT, TokenType::FETCH, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER}},  // RIGHT (hash=71), FETCH (hash=71)
    {{"JOIN", "JSON", "ROW", "RETURNS", nullptr, nullptr, nullptr, nullptr}, {4, 4, 3, 7, 0, 0, 0, 0}, {TokenType::JOIN, TokenType::JSON, TokenType::ROW, TokenType::RETURNS, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER}},  // JOIN (hash=72), JSON (hash=72), ROW (hash=72), RETURNS (hash=72)
    {{"NOT", "BEFORE", nullptr, nullptr, nullptr, nullptr, nullptr, nullptr}, {3, 6, 0, 0, 0, 0, 0, 0}, {TokenType::NOT, TokenType::BEFORE, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER}},  // NOT (hash=73), BEFORE (hash=73)
    {{"FULL", "NULLS", "FOLLOWING", "ROW_NUMBER", "FIRST_VALUE", "NEXT", nullptr, nullptr}, {4, 5, 9, 10, 11, 4, 0, 0}, {TokenType::FULL, TokenType::NULLS, TokenType::FOLLOWING, TokenType::ROW_NUMBER, TokenType::FIRST_VALUE, TokenType::NEXT, TokenType::IDENTIFIER, TokenType::IDENTIFIER}},  // FULL (hash=74), NULLS (hash=74), FOLLOWING (hash=74), ROW_NUMBER (hash=74), FIRST_VALUE (hash=74), NEXT (hash=74)
    {{"FROM", "REFERENCES", "FINAL", nullptr, nullptr, nullptr, nullptr, nullptr}, {4, 10, 5, 0, 0, 0, 0, 0}, {TokenType::FROM, TokenType::REFERENCES, TokenType::FINAL, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER}},  // FROM (hash=75), REFERENCES (hash=75), FINAL (hash=75)
    {{"VARBINARY", "NOWAIT", "NEW", nullptr, nullptr, nullptr, nullptr, nullptr}, {9, 6, 3, 0, 0, 0, 0, 0}, {TokenType::VARBINARY, TokenType::NOWAIT, TokenType::NEW, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER}},  // VARBINARY (hash=76), NOWAIT (hash=76), NEW (hash=76)
    {{"REINDEX", nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr}, {7, 0, 0, 0, 0, 0, 0, 0}, {TokenType::REINDEX, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER}},  // REINDEX (hash=77)
    {{"BOOL", nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr}, {4, 0, 0, 0, 0, 0, 0, 0}, {TokenType::BOOL, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER}},  // BOOL (hash=78)
    {{"FOREIGN", "FOR", "FLATTEN", nullptr, nullptr, nullptr, nullptr, nullptr}, {7, 3, 7, 0, 0, 0, 0, 0}, {TokenType::FOREIGN, TokenType::FOR, TokenType::FLATTEN, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER}},  // FOREIGN (hash=79), FOR (hash=79), FLATTEN (hash=79)
    {{"FUNCTION", nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr}, {8, 0, 0, 0, 0, 0, 0, 0}, {TokenType::FUNCTION, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER}},  // FUNCTION (hash=80)
    {{"FLOOR", "BEGIN", nullptr, nullptr, nullptr, nullptr, nullptr, nullptr}, {5, 5, 0, 0, 0, 0, 0, 0}, {TokenType::FLOOR, TokenType::BEGIN, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER}},  // FLOOR (hash=81), BEGIN (hash=81)
    {{nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr}, {0, 0, 0, 0, 0, 0, 0, 0}, {TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER}},
    {{"WHERE", "BETWEEN", "FIRST", "FLOAT", "BOOLEAN", "WRITE", "WHILE", nullptr}, {5, 7, 5, 5, 7, 5, 5, 0}, {TokenType::WHERE, TokenType::BETWEEN, TokenType::FIRST, TokenType::FLOAT, TokenType::BOOLEAN, TokenType::WRITE, TokenType::WHILE, TokenType::IDENTIFIER}},  // WHERE (hash=83), BETWEEN (hash=83), FIRST (hash=83), FLOAT (hash=83), BOOLEAN (hash=83), WRITE (hash=83), WHILE (hash=83)
    {{"SCHEMA", nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr}, {6, 0, 0, 0, 0, 0, 0, 0}, {TokenType::SCHEMA, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER}},  // SCHEMA (hash=84)
    {{"WITH", nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr}, {4, 0, 0, 0, 0, 0, 0, 0}, {TokenType::WITH, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER}},  // WITH (hash=85)
    {{"SOME", "SAFE", nullptr, nullptr, nullptr, nullptr, nullptr, nullptr}, {4, 4, 0, 0, 0, 0, 0, 0}, {TokenType::SOME, TokenType::SAFE, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER}},  // SOME (hash=86), SAFE (hash=86)
    {{"SHARE", nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr}, {5, 0, 0, 0, 0, 0, 0, 0}, {TokenType::SHARE, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER}},  // SHARE (hash=87)
    {{"BIGINT", "WORK", "SAMPLE", "OLD", nullptr, nullptr, nullptr, nullptr}, {6, 4, 6, 3, 0, 0, 0, 0}, {TokenType::BIGINT, TokenType::WORK, TokenType::SAMPLE, TokenType::OLD, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER}},  // BIGINT (hash=88), WORK (hash=88), SAMPLE (hash=88), OLD (hash=88)
    {{"BY", "OF", nullptr, nullptr, nullptr, nullptr, nullptr, nullptr}, {2, 2, 0, 0, 0, 0, 0, 0}, {TokenType::BY, TokenType::OF, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER}},  // BY (hash=89), OF (hash=89)
    {{"STRING", nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr}, {6, 0, 0, 0, 0, 0, 0, 0}, {TokenType::STRING_TYPE, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER}},  // STRING (hash=90)
    {{"WHEN", "SUMMARIZE", "WHEN", nullptr, nullptr, nullptr, nullptr, nullptr}, {4, 9, 4, 0, 0, 0, 0, 0}, {TokenType::WHEN, TokenType::SUMMARIZE, TokenType::WHEN_KW, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER}},  // WHEN (hash=91), SUMMARIZE (hash=91), WHEN (hash=91)
    {{nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr}, {0, 0, 0, 0, 0, 0, 0, 0}, {TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER}},
    {{"BINARY", "SUM", "SUBSTRING", nullptr, nullptr, nullptr, nullptr, nullptr}, {6, 3, 9, 0, 0, 0, 0, 0}, {TokenType::BINARY, TokenType::SUM, TokenType::SUBSTRING, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER}},  // BINARY (hash=93), SUM (hash=93), SUBSTRING (hash=93)
    {{"SERIALIZABLE", nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr}, {12, 0, 0, 0, 0, 0, 0, 0}, {TokenType::SERIALIZABLE, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER}},  // SERIALIZABLE (hash=94)
    {{"OVERWRITE", "START_WITH", "SIGNAL", "SCROLL", nullptr, nullptr, nullptr, nullptr}, {9, 10, 6, 6, 0, 0, 0, 0}, {TokenType::OVERWRITE, TokenType::START_WITH, TokenType::SIGNAL, TokenType::SCROLL, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER}},  // OVERWRITE (hash=95), START_WITH (hash=95), SIGNAL (hash=95), SCROLL (hash=95)
    {{nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr}, {0, 0, 0, 0, 0, 0, 0, 0}, {TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER}},
    {{"ON", "SKIP", nullptr, nullptr, nullptr, nullptr, nullptr, nullptr}, {2, 4, 0, 0, 0, 0, 0, 0}, {TokenType::ON, TokenType::SKIP, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER}},  // ON (hash=97), SKIP (hash=97)
    {{nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr}, {0, 0, 0, 0, 0, 0, 0, 0}, {TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER}},
    {{"OPEN", nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr}, {4, 0, 0, 0, 0, 0, 0, 0}, {TokenType::OPEN, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER}},  // OPEN (hash=99)
    {{"SET", "ORDINAL", nullptr, nullptr, nullptr, nullptr, nullptr, nullptr}, {3, 7, 0, 0, 0, 0, 0, 0}, {TokenType::SET, TokenType::ORDINAL, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER}},  // SET (hash=100), ORDINAL (hash=100)
    {{"OR", "SUBSTR", "SQRT", nullptr, nullptr, nullptr, nullptr, nullptr}, {2, 6, 4, 0, 0, 0, 0, 0}, {TokenType::OR, TokenType::SUBSTR, TokenType::SQRT, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER}},  // OR (hash=101), SUBSTR (hash=101), SQRT (hash=101)
    {{"CASE", "SPLIT", "SIMILAR", nullptr, nullptr, nullptr, nullptr, nullptr}, {4, 5, 7, 0, 0, 0, 0, 0}, {TokenType::CASE, TokenType::SPLIT, TokenType::SIMILAR, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER}},  // CASE (hash=102), SPLIT (hash=102), SIMILAR (hash=102)
    {{"SELECT", "STRUCT", "OVER", "CLOSE", nullptr, nullptr, nullptr, nullptr}, {6, 6, 4, 5, 0, 0, 0, 0}, {TokenType::SELECT, TokenType::STRUCT, TokenType::OVER, TokenType::CLOSE, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER}},  // SELECT (hash=103), STRUCT (hash=103), OVER (hash=103), CLOSE (hash=103)
    {{"CREATE", "ORDER", "OUTER", "CHANGE", "SHOW", "OUT", "STRAIGHT_JOIN", "SYS_CONNECT_BY_PATH"}, {6, 5, 5, 6, 4, 3, 13, 19}, {TokenType::CREATE, TokenType::ORDER, TokenType::OUTER, TokenType::CHANGE, TokenType::SHOW, TokenType::OUT, TokenType::STRAIGHT_JOIN, TokenType::SYS_CONNECT_BY_PATH}},  // CREATE (hash=104), ORDER (hash=104), OUTER (hash=104), CHANGE (hash=104), SHOW (hash=104), OUT (hash=104), STRAIGHT_JOIN (hash=104), SYS_CONNECT_BY_PATH (hash=104)
    {{"SMALLINT", "COLLATE", nullptr, nullptr, nullptr, nullptr, nullptr, nullptr}, {8, 7, 0, 0, 0, 0, 0, 0}, {TokenType::SMALLINT, TokenType::COLLATE, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER}},  // SMALLINT (hash=105), COLLATE (hash=105)
    {{"COALESCE", "SAFE_CAST", "SAVEPOINT", "COMMITTED", "GO", nullptr, nullptr, nullptr}, {8, 9, 9, 9, 2, 0, 0, 0}, {TokenType::COALESCE, TokenType::SAFE_CAST, TokenType::SAVEPOINT, TokenType::COMMITTED, TokenType::GO, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER}},  // COALESCE (hash=106), SAFE_CAST (hash=106), SAVEPOINT (hash=106), COMMITTED (hash=106), GO (hash=106)
    {{"OFFSET", "CATALOG", "OPTIONS", "OBJECT", "OUTPUT", nullptr, nullptr, nullptr}, {6, 7, 7, 6, 6, 0, 0, 0}, {TokenType::OFFSET, TokenType::CATALOG, TokenType::OPTIONS, TokenType::OBJECT, TokenType::OUTPUT, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER}},  // OFFSET (hash=107), CATALOG (hash=107), OPTIONS (hash=107), OBJECT (hash=107), OUTPUT (hash=107)
    {{"SAFE_OFFSET", nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr}, {11, 0, 0, 0, 0, 0, 0, 0}, {TokenType::SAFE_OFFSET, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER}},  // SAFE_OFFSET (hash=108)
    {{"CHECK", "CEIL", "CALL", nullptr, nullptr, nullptr, nullptr, nullptr}, {5, 4, 4, 0, 0, 0, 0, 0}, {TokenType::CHECK, TokenType::CEIL, TokenType::CALL, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER}},  // CHECK (hash=109), CEIL (hash=109), CALL (hash=109)
    {{"GROUP", "ONLY", "CURRENT_DATE", "CURRENT_TIME", nullptr, nullptr, nullptr, nullptr}, {5, 4, 12, 12, 0, 0, 0, 0}, {TokenType::GROUP, TokenType::ONLY, TokenType::CURRENT_DATE, TokenType::CURRENT_TIME, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER}},  // GROUP (hash=110), ONLY (hash=110), CURRENT_DATE (hash=110), CURRENT_TIME (hash=110)
    {{nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr}, {0, 0, 0, 0, 0, 0, 0, 0}, {TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER}},
    {{nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr}, {0, 0, 0, 0, 0, 0, 0, 0}, {TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER}},
    {{"COLUMN", "KEY", nullptr, nullptr, nullptr, nullptr, nullptr, nullptr}, {6, 3, 0, 0, 0, 0, 0, 0}, {TokenType::COLUMN, TokenType::KEY, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER}},  // COLUMN (hash=113), KEY (hash=113)
    {{"GRANT", "ORDER_BY", nullptr, nullptr, nullptr, nullptr, nullptr, nullptr}, {5, 8, 0, 0, 0, 0, 0, 0}, {TokenType::GRANT, TokenType::ORDER_BY, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER}},  // GRANT (hash=114), ORDER_BY (hash=114)
    {{"CHAR", nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr}, {4, 0, 0, 0, 0, 0, 0, 0}, {TokenType::CHAR, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER}},  // CHAR (hash=115)
    {{"SCOPE_IDENTITY", nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr}, {14, 0, 0, 0, 0, 0, 0, 0}, {TokenType::SCOPE_IDENTITY, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER}},  // SCOPE_IDENTITY (hash=116)
    {{"CROSS", "TRUE", "TIME", "CAST", "CURSOR", nullptr, nullptr, nullptr}, {5, 4, 4, 4, 6, 0, 0, 0}, {TokenType::CROSS, TokenType::TRUE, TokenType::TIME, TokenType::CAST, TokenType::CURSOR, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER}},  // CROSS (hash=117), TRUE (hash=117), TIME (hash=117), CAST (hash=117), CURSOR (hash=117)
    {{"TABLE", "COUNT", "CLUSTER", nullptr, nullptr, nullptr, nullptr, nullptr}, {5, 5, 7, 0, 0, 0, 0, 0}, {TokenType::TABLE, TokenType::COUNT, TokenType::CLUSTER, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER}},  // TABLE (hash=118), COUNT (hash=118), CLUSTER (hash=118)
    {{"CONCAT", "COMMIT", "PRAGMA", "COLUMNS", nullptr, nullptr, nullptr, nullptr}, {6, 6, 6, 7, 0, 0, 0, 0}, {TokenType::CONCAT_KW, TokenType::COMMIT, TokenType::PRAGMA, TokenType::COLUMNS, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER}},  // CONCAT (hash=119), COMMIT (hash=119), PRAGMA (hash=119), COLUMNS (hash=119)
    {{"CONVERT", "CURRENT", "CONNECT", "CHARSET", nullptr, nullptr, nullptr, nullptr}, {7, 7, 7, 7, 0, 0, 0, 0}, {TokenType::CONVERT, TokenType::CURRENT, TokenType::CONNECT, TokenType::CHARSET, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER}},  // CONVERT (hash=120), CURRENT (hash=120), CONNECT (hash=120), CHARSET (hash=120)
    {{"TRUNCATE", "CONCAT_WS", nullptr, nullptr, nullptr, nullptr, nullptr, nullptr}, {8, 9, 0, 0, 0, 0, 0, 0}, {TokenType::TRUNCATE, TokenType::CONCAT_WS, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER}},  // TRUNCATE (hash=121), CONCAT_WS (hash=121)
    {{"COPY", nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr}, {4, 0, 0, 0, 0, 0, 0, 0}, {TokenType::COPY, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER}},  // COPY (hash=122)
    {{"CONSTRAINT", "GENERATE_SERIES", "TABLESPACE", nullptr, nullptr, nullptr, nullptr, nullptr}, {10, 15, 10, 0, 0, 0, 0, 0}, {TokenType::CONSTRAINT, TokenType::GENERATE_SERIES, TokenType::TABLESPACE, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER}},  // CONSTRAINT (hash=123), GENERATE_SERIES (hash=123), TABLESPACE (hash=123)
    {{"LEAD", "TABLESAMPLE", "LOAD", nullptr, nullptr, nullptr, nullptr, nullptr}, {4, 11, 4, 0, 0, 0, 0, 0}, {TokenType::LEAD, TokenType::TABLESAMPLE, TokenType::LOAD, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER}},  // LEAD (hash=124), TABLESAMPLE (hash=124), LOAD (hash=124)
    {{"LIKE", "TRIM", "PREWHERE", nullptr, nullptr, nullptr, nullptr, nullptr}, {4, 4, 8, 0, 0, 0, 0, 0}, {TokenType::LIKE, TokenType::TRIM, TokenType::PREWHERE, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER}},  // LIKE (hash=125), TRIM (hash=125), PREWHERE (hash=125)
    {{"THEN", "LAG", "LOCKED", "CURRENT_TIMESTAMP", "PROCEDURE", nullptr, nullptr, nullptr}, {4, 3, 6, 17, 9, 0, 0, 0}, {TokenType::THEN, TokenType::LAG, TokenType::LOCKED, TokenType::CURRENT_TIMESTAMP, TokenType::PROCEDURE_KW, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER}},  // THEN (hash=126), LAG (hash=126), LOCKED (hash=126), CURRENT_TIMESTAMP (hash=126), PROCEDURE (hash=126)
    {{"TOP", nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr}, {3, 0, 0, 0, 0, 0, 0, 0}, {TokenType::TOP, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER}},  // TOP (hash=127)
};

// Hash collision report:
// Slot 0 (4 entries): TEMP, PRECEDING, CONNECT_BY, CONNECT_BY_ROOT
// Slot 2 (2 entries): LENGTH, CONCURRENTLY
// Slot 3 (3 entries): DESC, LAST_VALUE, PLPGSQL
// Slot 4 (3 entries): TEXT, PERFORM, HASH
// Slot 5 (6 entries): HAVING, DATE, TIMESTAMP, TRANSACTION, LEVEL, TRIGGER
// Slot 7 (8 entries): DELETE, TINYINT, DOUBLE, POWER, PARTITION, LATERAL, PRIOR, DELETED
// Slot 8 (4 entries): TRY_CAST, DATE_ADD, DECLARE, LOOP
// Slot 9 (4 entries): DATABASE, DATE_TRUNC, PIVOT, DESCRIBE
// Slot 11 (2 entries): DATE_DIFF, LOWER
// Slot 12 (4 entries): LEFT, LAST, LIST, DUAL
// Slot 13 (3 entries): LIMIT, PRIVILEGES, DO
// Slot 16 (2 entries): DROP, PRIMARY
// Slot 17 (2 entries): TIMESTAMPTZ, DENSE_RANK
// Slot 19 (3 entries): UUID, USE, HUGEINT
// Slot 22 (2 entries): UPDATE, UNIQUE
// Slot 23 (4 entries): USING, DEFAULT, DELIMITER, UNSIGNED
// Slot 24 (2 entries): DISTINCT, UNBOUNDED
// Slot 30 (2 entries): UNION, MATCHED
// Slot 32 (2 entries): MAXVALUE, MINVALUE
// Slot 34 (5 entries): END, UPPER, IGNORE, INSTEAD, EXEC
// Slot 36 (2 entries): ELSE, MIN
// Slot 37 (2 entries): ASC, UNNEST
// Slot 38 (6 entries): AND, MAP, ADD, UNPIVOT, ENDIF, ENGINE
// Slot 39 (6 entries): IN, UHUGEINT, EXCLUDE, EACH, ELSEIF, EXECUTE
// Slot 41 (2 entries): AVG, IFNULL
// Slot 43 (3 entries): MINUS, INTERVAL, ANALYZE
// Slot 44 (2 entries): IS, USE_INDEX
// Slot 46 (5 entries): INNER, ALL, INT, MAX, ISOLATION
// Slot 48 (3 entries): INTEGER, EXPLAIN, INOUT
// Slot 49 (2 entries): INSERT, IMPORT
// Slot 50 (3 entries): MODIFY, ENDLOOP, EXCEPTION
// Slot 52 (4 entries): INTERSECT, AS, EXISTS, INDEX
// Slot 53 (3 entries): EXCEPT, ABS, EXPORT
// Slot 54 (5 entries): ALTER, EXTRACT, READ, VERBOSE, AFTER
// Slot 55 (2 entries): ROUND, ROWID
// Slot 56 (5 entries): RANGE, RLIKE, RAISE, EACH_STMT, IDENTITY
// Slot 57 (2 entries): RENAME, REVOKE
// Slot 58 (3 entries): REPLACE, EACH_ROW, ZEROFILL
// Slot 60 (3 entries): RECURSIVE, NUMERIC, NTILE
// Slot 61 (6 entries): ARRAY, JSONB, RANK, APPLY, REPEATABLE, VACUUM
// Slot 62 (4 entries): RETURNING, REAL, NULLIF, NOCYCLE
// Slot 65 (4 entries): NVL, ROLLBACK, AUTO_INCREMENT, ROWNUM
// Slot 66 (2 entries): NULL, RETURN
// Slot 67 (2 entries): VALUES, VARCHAR
// Slot 68 (4 entries): FALSE, BLOB, REGEXP, FORCE
// Slot 69 (4 entries): NATURAL, VIEW, ROWS, VARIANT
// Slot 71 (2 entries): RIGHT, FETCH
// Slot 72 (4 entries): JOIN, JSON, ROW, RETURNS
// Slot 73 (2 entries): NOT, BEFORE
// Slot 74 (6 entries): FULL, NULLS, FOLLOWING, ROW_NUMBER, FIRST_VALUE, NEXT
// Slot 75 (3 entries): FROM, REFERENCES, FINAL
// Slot 76 (3 entries): VARBINARY, NOWAIT, NEW
// Slot 79 (3 entries): FOREIGN, FOR, FLATTEN
// Slot 81 (2 entries): FLOOR, BEGIN
// Slot 83 (7 entries): WHERE, BETWEEN, FIRST, FLOAT, BOOLEAN, WRITE, WHILE
// Slot 86 (2 entries): SOME, SAFE
// Slot 88 (4 entries): BIGINT, WORK, SAMPLE, OLD
// Slot 89 (2 entries): BY, OF
// Slot 91 (3 entries): WHEN, SUMMARIZE, WHEN
// Slot 93 (3 entries): BINARY, SUM, SUBSTRING
// Slot 95 (4 entries): OVERWRITE, START_WITH, SIGNAL, SCROLL
// Slot 97 (2 entries): ON, SKIP
// Slot 100 (2 entries): SET, ORDINAL
// Slot 101 (3 entries): OR, SUBSTR, SQRT
// Slot 102 (3 entries): CASE, SPLIT, SIMILAR
// Slot 103 (4 entries): SELECT, STRUCT, OVER, CLOSE
// Slot 104 (9 entries): CREATE, ORDER, OUTER, CHANGE, SHOW, OUT, STRAIGHT_JOIN, SYS_CONNECT_BY_PATH, SETTINGS
// Slot 105 (2 entries): SMALLINT, COLLATE
// Slot 106 (5 entries): COALESCE, SAFE_CAST, SAVEPOINT, COMMITTED, GO
// Slot 107 (5 entries): OFFSET, CATALOG, OPTIONS, OBJECT, OUTPUT
// Slot 109 (3 entries): CHECK, CEIL, CALL
// Slot 110 (4 entries): GROUP, ONLY, CURRENT_DATE, CURRENT_TIME
// Slot 113 (2 entries): COLUMN, KEY
// Slot 114 (2 entries): GRANT, ORDER_BY
// Slot 117 (5 entries): CROSS, TRUE, TIME, CAST, CURSOR
// Slot 118 (3 entries): TABLE, COUNT, CLUSTER
// Slot 119 (4 entries): CONCAT, COMMIT, PRAGMA, COLUMNS
// Slot 120 (4 entries): CONVERT, CURRENT, CONNECT, CHARSET
// Slot 121 (2 entries): TRUNCATE, CONCAT_WS
// Slot 123 (3 entries): CONSTRAINT, GENERATE_SERIES, TABLESPACE
// Slot 124 (3 entries): LEAD, TABLESAMPLE, LOAD
// Slot 125 (3 entries): LIKE, TRIM, PREWHERE
// Slot 126 (5 entries): THEN, LAG, LOCKED, CURRENT_TIMESTAMP, PROCEDURE
};

} // namespace libsqlglot
