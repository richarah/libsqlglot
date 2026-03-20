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
        for (int i = 0; i < 4; ++i) {
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
        const char* keywords[4];
        uint8_t lengths[4];
        TokenType types[4];
    };

    static constexpr KeywordEntry keyword_table[128] = {
        {{"PRECEDING", nullptr, nullptr, nullptr}, {9, 0, 0, 0}, {TokenType::PRECEDING, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER}},  // PRECEDING (hash=0)
        {{nullptr, nullptr, nullptr, nullptr}, {0, 0, 0, 0}, {TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER}},
        {{nullptr, nullptr, nullptr, nullptr}, {0, 0, 0, 0}, {TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER}},
        {{"DESC", nullptr, nullptr, nullptr}, {4, 0, 0, 0}, {TokenType::DESC, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER}},  // DESC (hash=3)
        {{"HASH", nullptr, nullptr, nullptr}, {4, 0, 0, 0}, {TokenType::HASH, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER}},  // HASH (hash=4)
        {{"HAVING", "TIMESTAMP", "DATE", "TRIGGER"}, {6, 9, 4, 7}, {TokenType::HAVING, TokenType::TIMESTAMP, TokenType::DATE, TokenType::TRIGGER}},  // HAVING (hash=5), TIMESTAMP (hash=5), DATE (hash=5), TRIGGER (hash=5)
        {{nullptr, nullptr, nullptr, nullptr}, {0, 0, 0, 0}, {TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER}},
        {{"DELETE", "PARTITION", nullptr, nullptr}, {6, 9, 0, 0}, {TokenType::DELETE, TokenType::PARTITION, TokenType::IDENTIFIER, TokenType::IDENTIFIER}},  // DELETE (hash=7), PARTITION (hash=7)
        {{"DECLARE", "LOOP", nullptr, nullptr}, {7, 4, 0, 0}, {TokenType::DECLARE, TokenType::LOOP, TokenType::IDENTIFIER, TokenType::IDENTIFIER}},  // DECLARE (hash=8), LOOP (hash=8)
        {{"PIVOT", nullptr, nullptr, nullptr}, {5, 0, 0, 0}, {TokenType::PIVOT, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER}},  // PIVOT (hash=9)
        {{nullptr, nullptr, nullptr, nullptr}, {0, 0, 0, 0}, {TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER}},
        {{nullptr, nullptr, nullptr, nullptr}, {0, 0, 0, 0}, {TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER}},
        {{"TABLESAMPLE", "LEFT", nullptr, nullptr}, {11, 4, 0, 0}, {TokenType::TABLESAMPLE, TokenType::LEFT, TokenType::IDENTIFIER, TokenType::IDENTIFIER}},  // TABLESAMPLE (hash=12), LEFT (hash=12)
        {{"LIMIT", "DO", nullptr, nullptr}, {5, 2, 0, 0}, {TokenType::LIMIT, TokenType::DO, TokenType::IDENTIFIER, TokenType::IDENTIFIER}},  // LIMIT (hash=13), DO (hash=13)
        {{nullptr, nullptr, nullptr, nullptr}, {0, 0, 0, 0}, {TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER}},
        {{nullptr, nullptr, nullptr, nullptr}, {0, 0, 0, 0}, {TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER}},
        {{"DROP", "PRIMARY", nullptr, nullptr}, {4, 7, 0, 0}, {TokenType::DROP, TokenType::PRIMARY, TokenType::IDENTIFIER, TokenType::IDENTIFIER}},  // DROP (hash=16), PRIMARY (hash=16)
        {{"ROLLBACK", nullptr, nullptr, nullptr}, {8, 0, 0, 0}, {TokenType::ROLLBACK, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER}},  // ROLLBACK (hash=17)
        {{nullptr, nullptr, nullptr, nullptr}, {0, 0, 0, 0}, {TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER}},
        {{nullptr, nullptr, nullptr, nullptr}, {0, 0, 0, 0}, {TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER}},
        {{"REGEXP", nullptr, nullptr, nullptr}, {6, 0, 0, 0}, {TokenType::REGEXP, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER}},  // REGEXP (hash=20)
        {{nullptr, nullptr, nullptr, nullptr}, {0, 0, 0, 0}, {TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER}},
        {{"UPDATE", "UNIQUE", nullptr, nullptr}, {6, 6, 0, 0}, {TokenType::UPDATE, TokenType::UNIQUE, TokenType::IDENTIFIER, TokenType::IDENTIFIER}},  // UPDATE (hash=22), UNIQUE (hash=22)
        {{"USING", "DEFAULT", "LATERAL", nullptr}, {5, 7, 7, 0}, {TokenType::USING, TokenType::DEFAULT, TokenType::LATERAL, TokenType::IDENTIFIER}},  // USING (hash=23), DEFAULT (hash=23), LATERAL (hash=23)
        {{"DISTINCT", "UNBOUNDED", nullptr, nullptr}, {8, 9, 0, 0}, {TokenType::DISTINCT, TokenType::UNBOUNDED, TokenType::IDENTIFIER, TokenType::IDENTIFIER}},  // DISTINCT (hash=24), UNBOUNDED (hash=24)
        {{"DESCRIBE", nullptr, nullptr, nullptr}, {8, 0, 0, 0}, {TokenType::DESCRIBE, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER}},  // DESCRIBE (hash=25)
        {{nullptr, nullptr, nullptr, nullptr}, {0, 0, 0, 0}, {TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER}},
        {{nullptr, nullptr, nullptr, nullptr}, {0, 0, 0, 0}, {TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER}},
        {{nullptr, nullptr, nullptr, nullptr}, {0, 0, 0, 0}, {TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER}},
        {{nullptr, nullptr, nullptr, nullptr}, {0, 0, 0, 0}, {TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER}},
        {{"UNION", nullptr, nullptr, nullptr}, {5, 0, 0, 0}, {TokenType::UNION, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER}},  // UNION
        {{"IF", nullptr, nullptr, nullptr}, {2, 0, 0, 0}, {TokenType::IF_KW, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER}},  // IF (hash=31)
        {{"EXPLAIN", nullptr, nullptr, nullptr}, {7, 0, 0, 0}, {TokenType::EXPLAIN, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER}},  // EXPLAIN (hash=32)
        {{"ILIKE", nullptr, nullptr, nullptr}, {5, 0, 0, 0}, {TokenType::ILIKE, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER}},  // ILIKE (hash=33)
        {{"END", "CONCURRENTLY", nullptr, nullptr}, {3, 12, 0, 0}, {TokenType::END, TokenType::CONCURRENTLY, TokenType::IDENTIFIER, TokenType::IDENTIFIER}},  // END (hash=34), CONCURRENTLY (hash=34)
        {{nullptr, nullptr, nullptr, nullptr}, {0, 0, 0, 0}, {TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER}},
        {{"ELSE", nullptr, nullptr, nullptr}, {4, 0, 0, 0}, {TokenType::ELSE, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER}},  // ELSE
        {{"ASC", nullptr, nullptr, nullptr}, {3, 0, 0, 0}, {TokenType::ASC, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER}},  // ASC (hash=37)
        {{"AND", "UNPIVOT", "ENDIF", nullptr}, {3, 7, 5, 0}, {TokenType::AND, TokenType::UNPIVOT, TokenType::ENDIF, TokenType::IDENTIFIER}},  // AND (hash=38), UNPIVOT (hash=38), ENDIF (hash=38)
        {{"IN", "ELSEIF", nullptr, nullptr}, {2, 6, 0, 0}, {TokenType::IN, TokenType::ELSEIF, TokenType::IDENTIFIER, TokenType::IDENTIFIER}},  // IN (hash=39), ELSEIF (hash=39)
        {{"ENDWHILE", nullptr, nullptr, nullptr}, {8, 0, 0, 0}, {TokenType::ENDWHILE, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER}},  // ENDWHILE (hash=40)
        {{nullptr, nullptr, nullptr, nullptr}, {0, 0, 0, 0}, {TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER}},
        {{"INTO", "COALESCE", nullptr, nullptr}, {4, 8, 0, 0}, {TokenType::INTO, TokenType::COALESCE, TokenType::IDENTIFIER, TokenType::IDENTIFIER}},  // INTO (hash=42), COALESCE (hash=42)
        {{"INTERVAL", nullptr, nullptr, nullptr}, {8, 0, 0, 0}, {TokenType::INTERVAL, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER}},  // INTERVAL (hash=43)
        {{"IS", nullptr, nullptr, nullptr}, {2, 0, 0, 0}, {TokenType::IS, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER}},  // IS (hash=44)
        {{nullptr, nullptr, nullptr, nullptr}, {0, 0, 0, 0}, {TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER}},
        {{"INNER", "ALL", nullptr, nullptr}, {5, 3, 0, 0}, {TokenType::INNER, TokenType::ALL, TokenType::IDENTIFIER, TokenType::IDENTIFIER}},  // INNER (hash=46), ALL (hash=46)
        {{nullptr, nullptr, nullptr, nullptr}, {0, 0, 0, 0}, {TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER}},
        {{nullptr, nullptr, nullptr, nullptr}, {0, 0, 0, 0}, {TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER}},
        {{"INSERT", nullptr, nullptr, nullptr}, {6, 0, 0, 0}, {TokenType::INSERT, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER}},  // INSERT (hash=49)
        {{"ENDLOOP", nullptr, nullptr, nullptr}, {7, 0, 0, 0}, {TokenType::ENDLOOP, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER}},  // ENDLOOP (hash=50)
        {{nullptr, nullptr, nullptr, nullptr}, {0, 0, 0, 0}, {TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER}},
        {{"INDEX", "INTERSECT", "AS", "EXISTS"}, {5, 9, 2, 6}, {TokenType::INDEX, TokenType::INTERSECT, TokenType::AS, TokenType::EXISTS}},  // INDEX (hash=52), INTERSECT (hash=52), AS (hash=52), EXISTS (hash=52)
        {{"EXCEPT", nullptr, nullptr, nullptr}, {6, 0, 0, 0}, {TokenType::EXCEPT, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER}},  // EXCEPT (hash=53)
        {{"ALTER", "EXTRACT", nullptr, nullptr}, {5, 7, 0, 0}, {TokenType::ALTER, TokenType::EXTRACT, TokenType::IDENTIFIER, TokenType::IDENTIFIER}},  // ALTER (hash=54), EXTRACT (hash=54)
        {{"COMMIT", nullptr, nullptr, nullptr}, {6, 0, 0, 0}, {TokenType::COMMIT, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER}},  // COMMIT (hash=55)
        {{"RANGE", nullptr, nullptr, nullptr}, {5, 0, 0, 0}, {TokenType::RANGE, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER}},  // RANGE (hash=56)
        {{nullptr, nullptr, nullptr, nullptr}, {0, 0, 0, 0}, {TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER}},
        {{nullptr, nullptr, nullptr, nullptr}, {0, 0, 0, 0}, {TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER}},
        {{"ANY", nullptr, nullptr, nullptr}, {3, 0, 0, 0}, {TokenType::ANY, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER}},  // ANY
        {{"RECURSIVE", "QUALIFY", nullptr, nullptr}, {9, 7, 0, 0}, {TokenType::RECURSIVE, TokenType::QUALIFY, TokenType::IDENTIFIER, TokenType::IDENTIFIER}},  // RECURSIVE (hash=60), QUALIFY (hash=60)
        {{nullptr, nullptr, nullptr, nullptr}, {0, 0, 0, 0}, {TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER}},
        {{nullptr, nullptr, nullptr, nullptr}, {0, 0, 0, 0}, {TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER}},
        {{nullptr, nullptr, nullptr, nullptr}, {0, 0, 0, 0}, {TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER}},
        {{nullptr, nullptr, nullptr, nullptr}, {0, 0, 0, 0}, {TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER}},
        {{nullptr, nullptr, nullptr, nullptr}, {0, 0, 0, 0}, {TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER}},
        {{"RETURN", "NULL", nullptr, nullptr}, {6, 4, 0, 0}, {TokenType::RETURN_KW, TokenType::NULL_KW, TokenType::IDENTIFIER, TokenType::IDENTIFIER}},  // RETURN (hash=66), NULL (hash=66)
        {{"VALUES", nullptr, nullptr, nullptr}, {6, 0, 0, 0}, {TokenType::VALUES, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER}},  // VALUES (hash=67)
        {{"FALSE", nullptr, nullptr, nullptr}, {5, 0, 0, 0}, {TokenType::FALSE, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER}},  // FALSE (hash=68)
        {{"ROWS", nullptr, nullptr, nullptr}, {4, 0, 0, 0}, {TokenType::ROWS, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER}},  // ROWS (hash=69)
        {{nullptr, nullptr, nullptr, nullptr}, {0, 0, 0, 0}, {TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER}},
        {{"RIGHT", nullptr, nullptr, nullptr}, {5, 0, 0, 0}, {TokenType::RIGHT, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER}},  // RIGHT (hash=71)
        {{"JOIN", "ROW", nullptr, nullptr}, {4, 3, 0, 0}, {TokenType::JOIN, TokenType::ROW, TokenType::IDENTIFIER, TokenType::IDENTIFIER}},  // JOIN (hash=72), ROW (hash=72)
        {{"NOT", "BEFORE", nullptr, nullptr}, {3, 6, 0, 0}, {TokenType::NOT, TokenType::BEFORE, TokenType::IDENTIFIER, TokenType::IDENTIFIER}},  // NOT (hash=73), BEFORE (hash=73)
        {{"FULL", "FOLLOWING", nullptr, nullptr}, {4, 9, 0, 0}, {TokenType::FULL, TokenType::FOLLOWING, TokenType::IDENTIFIER, TokenType::IDENTIFIER}},  // FULL (hash=74), FOLLOWING (hash=74)
        {{"FROM", "REFERENCES", "LIST", nullptr}, {4, 10, 4, 0}, {TokenType::FROM, TokenType::REFERENCES, TokenType::LIST_KW, TokenType::IDENTIFIER}},  // FROM (hash=75), REFERENCES (hash=75), LIST (hash=76)
        {{nullptr, nullptr, nullptr, nullptr}, {0, 0, 0, 0}, {TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER}},
        {{"MERGE", nullptr, nullptr, nullptr}, {5, 0, 0, 0}, {TokenType::MERGE, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER}},  // MERGE (hash=77)
        {{"MATCHED", nullptr, nullptr, nullptr}, {7, 0, 0, 0}, {TokenType::MATCHED, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER}},  // MATCHED (hash=78)
        {{"FOREIGN", "FOR", nullptr, nullptr}, {7, 3, 0, 0}, {TokenType::FOREIGN, TokenType::FOR, TokenType::IDENTIFIER, TokenType::IDENTIFIER}},  // FOREIGN (hash=79), FOR (hash=79)
        {{nullptr, nullptr, nullptr, nullptr}, {0, 0, 0, 0}, {TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER}},
        {{"BEGIN", nullptr, nullptr, nullptr}, {5, 0, 0, 0}, {TokenType::BEGIN, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER}},  // BEGIN (hash=81)
        {{"SIMILAR", nullptr, nullptr, nullptr}, {7, 0, 0, 0}, {TokenType::SIMILAR, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER}},  // SIMILAR (hash=82)
        {{"WHERE", "BETWEEN", "WHILE", nullptr}, {5, 7, 5, 0}, {TokenType::WHERE, TokenType::BETWEEN, TokenType::WHILE, TokenType::IDENTIFIER}},  // WHERE (hash=83), BETWEEN (hash=83), WHILE (hash=83)
        {{"SHOW", nullptr, nullptr, nullptr}, {4, 0, 0, 0}, {TokenType::SHOW, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER}},  // SHOW (hash=84)
        {{"WITH", nullptr, nullptr, nullptr}, {4, 0, 0, 0}, {TokenType::WITH, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER}},  // WITH
        {{"SOME", nullptr, nullptr, nullptr}, {4, 0, 0, 0}, {TokenType::SOME, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER}},  // SOME
        {{"SAVEPOINT", "AFTER", nullptr, nullptr}, {9, 5, 0, 0}, {TokenType::SAVEPOINT, TokenType::AFTER, TokenType::IDENTIFIER, TokenType::IDENTIFIER}},  // SAVEPOINT (hash=86), AFTER (hash=86)
        {{"EACH", nullptr, nullptr, nullptr}, {4, 0, 0, 0}, {TokenType::EACH, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER}},  // EACH (hash=87)
        {{"BY", "RETURNS", nullptr, nullptr}, {2, 7, 0, 0}, {TokenType::BY, TokenType::RETURNS, TokenType::IDENTIFIER, TokenType::IDENTIFIER}},  // BY (hash=88), RETURNS (hash=88)
        {{nullptr, nullptr, nullptr, nullptr}, {0, 0, 0, 0}, {TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER}},
        {{"WHEN", "TABLESPACE", nullptr, nullptr}, {4, 10, 0, 0}, {TokenType::WHEN, TokenType::TABLESPACE, TokenType::IDENTIFIER, TokenType::IDENTIFIER}},  // WHEN (hash=90), TABLESPACE (hash=91)
        {{"NEW", nullptr, nullptr, nullptr}, {3, 0, 0, 0}, {TokenType::NEW, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER}},  // NEW (hash=92)
        {{nullptr, nullptr, nullptr, nullptr}, {0, 0, 0, 0}, {TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER}},
        {{nullptr, nullptr, nullptr, nullptr}, {0, 0, 0, 0}, {TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER}},
        {{nullptr, nullptr, nullptr, nullptr}, {0, 0, 0, 0}, {TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER}},
        {{"FUNCTION", nullptr, nullptr, nullptr}, {8, 0, 0, 0}, {TokenType::FUNCTION, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER}},  // FUNCTION (hash=96)
        {{"ON", nullptr, nullptr, nullptr}, {2, 0, 0, 0}, {TokenType::ON, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER}},  // ON (hash=97)
        {{"INSTEAD", nullptr, nullptr, nullptr}, {7, 0, 0, 0}, {TokenType::INSTEAD, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER}},  // INSTEAD (hash=98)
        {{nullptr, nullptr, nullptr, nullptr}, {0, 0, 0, 0}, {TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER}},
        {{"SET", nullptr, nullptr, nullptr}, {3, 0, 0, 0}, {TokenType::SET, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER}},  // SET (hash=100)
        {{"OR", nullptr, nullptr, nullptr}, {2, 0, 0, 0}, {TokenType::OR, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER}},  // OR (hash=101)
        {{"CASE", nullptr, nullptr, nullptr}, {4, 0, 0, 0}, {TokenType::CASE, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER}},  // CASE
        {{"SELECT", "OVER", nullptr, nullptr}, {6, 4, 0, 0}, {TokenType::SELECT, TokenType::OVER, TokenType::IDENTIFIER, TokenType::IDENTIFIER}},  // SELECT (hash=103), OVER (hash=103)
        {{"ORDER", "CREATE", "OUT", "OLD"}, {5, 6, 3, 3}, {TokenType::ORDER, TokenType::CREATE, TokenType::OUT, TokenType::OLD}},  // ORDER (hash=104), CREATE (hash=104), OUT (hash=104), OLD (hash=104)
        {{"OF", nullptr, nullptr, nullptr}, {2, 0, 0, 0}, {TokenType::OF, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER}},  // OF (hash=105)
        {{nullptr, nullptr, nullptr, nullptr}, {0, 0, 0, 0}, {TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER}},  // Empty bucket 106
        {{"OFFSET", nullptr, nullptr, nullptr}, {6, 0, 0, 0}, {TokenType::OFFSET, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER}},  // OFFSET
        {{nullptr, nullptr, nullptr, nullptr}, {0, 0, 0, 0}, {TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER}},
        {{"CHECK", "CALL", nullptr, nullptr}, {5, 4, 0, 0}, {TokenType::CHECK, TokenType::CALL, TokenType::IDENTIFIER, TokenType::IDENTIFIER}},  // CHECK (hash=109), CALL (hash=109)
        {{"GROUP", "NULLIF", nullptr, nullptr}, {5, 6, 0, 0}, {TokenType::GROUP, TokenType::NULLIF, TokenType::IDENTIFIER, TokenType::IDENTIFIER}},  // GROUP (hash=110), NULLIF (hash=110)
        {{nullptr, nullptr, nullptr, nullptr}, {0, 0, 0, 0}, {TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER}},
        {{"INOUT", nullptr, nullptr, nullptr}, {5, 0, 0, 0}, {TokenType::INOUT, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER}},  // INOUT (hash=112)
        {{"KEY", nullptr, nullptr, nullptr}, {3, 0, 0, 0}, {TokenType::KEY, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER}},  // KEY (hash=113)
        {{nullptr, nullptr, nullptr, nullptr}, {0, 0, 0, 0}, {TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER}},
        {{nullptr, nullptr, nullptr, nullptr}, {0, 0, 0, 0}, {TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER}},
        {{nullptr, nullptr, nullptr, nullptr}, {0, 0, 0, 0}, {TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER}},  // hash 116 (empty)
        {{"TIME", "CAST", "CROSS", "TRUE"}, {4, 4, 5, 4}, {TokenType::TIME, TokenType::CAST, TokenType::CROSS, TokenType::TRUE}},  // TIME (hash=117), CAST (hash=117), CROSS (hash=117), TRUE (hash=117)
        {{"TABLE", nullptr, nullptr, nullptr}, {5, 0, 0, 0}, {TokenType::TABLE, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER}},  // TABLE
        {{nullptr, nullptr, nullptr, nullptr}, {0, 0, 0, 0}, {TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER}},
        {{"CURRENT", nullptr, nullptr, nullptr}, {7, 0, 0, 0}, {TokenType::CURRENT, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER}},  // CURRENT (hash=120)
        {{nullptr, nullptr, nullptr, nullptr}, {0, 0, 0, 0}, {TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER}},
        {{nullptr, nullptr, nullptr, nullptr}, {0, 0, 0, 0}, {TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER}},
        {{nullptr, nullptr, nullptr, nullptr}, {0, 0, 0, 0}, {TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER}},
        {{nullptr, nullptr, nullptr, nullptr}, {0, 0, 0, 0}, {TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER}},
        {{"LIKE", nullptr, nullptr, nullptr}, {4, 0, 0, 0}, {TokenType::LIKE, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER}},  // LIKE (hash=125)
        {{"THEN", nullptr, nullptr, nullptr}, {4, 0, 0, 0}, {TokenType::THEN, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER}},  // THEN (hash=126)
        {{nullptr, nullptr, nullptr, nullptr}, {0, 0, 0, 0}, {TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER, TokenType::IDENTIFIER}}   // hash 127 (empty)
    };
};

} // namespace libsqlglot
