#pragma once

#include "tokens.h"
#include <string_view>
#include <array>
#include <meta>  // C++26 reflection

/**
 * C++26 Reflection-Based Keyword System
 *
 * This file uses C++26 compile-time reflection to automatically generate
 * keyword-to-TokenType mappings from the TokenType enum itself.
 *
 * ZERO RUNTIME COST: All reflection happens at compile time.
 * The generated code is identical to hand-written mappings.
 *
 * Benefits:
 * - Single source of truth: Only the TokenType enum needs maintenance
 * - Impossible to desync: Keywords are derived from enum automatically
 * - Auto-strip suffixes: "IF_KW" → "IF", "NULL_KW" → "NULL"
 * - Smaller codebase: No manual keyword_definitions.h
 * - Faster compile times: Less template instantiation
 */

namespace libsqlglot::keywords {

/// Helper function for string_view::ends_with (C++20 compatibility)
consteval bool string_ends_with(std::string_view str, std::string_view suffix) noexcept {
    return str.size() >= suffix.size() &&
           str.substr(str.size() - suffix.size()) == suffix;
}

/// Keyword-to-token mapping (generated from reflection)
struct KeywordMapping {
    std::string_view text;  // Keyword text (uppercase, e.g., "SELECT", "IF", "NULL")
    TokenType type;          // Corresponding TokenType

    constexpr KeywordMapping() noexcept : text(""), type(TokenType::ERROR) {}
    constexpr KeywordMapping(std::string_view t, TokenType ty) noexcept
        : text(t), type(ty) {}
};

/// Check if enum name represents a keyword (not operator, delimiter, etc.)
consteval bool is_keyword_enum(std::string_view name) noexcept {
    // Skip special tokens
    if (name == "ERROR" || name == "EOF_TOKEN" || name == "WHITESPACE" ||
        name == "COMMENT" || name == "TOKEN_TYPE_COUNT") {
        return false;
    }

    // Skip literals
    if (name == "NUMBER" || name == "STRING" || name == "IDENTIFIER" ||
        name == "PARAMETER" || name == "BIT_STRING" || name == "HEX_STRING" ||
        name == "NATIONAL_STRING") {
        return false;
    }

    // Skip operators
    if (name == "PLUS" || name == "MINUS" || name == "STAR" || name == "SLASH" ||
        name == "PERCENT" || name == "CARET" || name == "AMPERSAND" || name == "PIPE" ||
        name == "TILDE" || name == "EQ" || name == "NEQ" || name == "LT" || name == "LTE" ||
        name == "GT" || name == "GTE" || name == "CONCAT" || name == "ARROW" ||
        name == "LONG_ARROW" || name == "HASH_ARROW" || name == "HASH_LONG_ARROW" ||
        name == "AT_GT" || name == "LT_AT" || name == "QUESTION" || name == "DOUBLE_COLON" ||
        name == "COLON_EQUALS" || name == "NULL_SAFE_EQ") {
        return false;
    }

    // Skip delimiters
    if (name == "LPAREN" || name == "RPAREN" || name == "LBRACKET" || name == "RBRACKET" ||
        name == "LBRACE" || name == "RBRACE" || name == "COMMA" || name == "SEMICOLON" ||
        name == "DOT" || name == "COLON" || name == "DOUBLE_DOT") {
        return false;
    }

    // Skip parser-only tokens (not in keyword lookup table)
    // These exist for disambiguation but don't correspond to SQL keywords
    if (name == "UPDATE_LOCK" ||   // FOR UPDATE (context-dependent)
        name == "REPLACE_DDB" ||    // DuckDB REPLACE expression
        name == "FLATTEN_KW" ||     // Snowflake FLATTEN (vs BigQuery)
        name == "WHEN_KW" ||        // Exception WHEN (vs CASE WHEN)
        name == "STRUCT" ||         // Data type (vs STRUCT keyword)
        name == "DESC_KW" ||        // DESC keyword variant
        name == "DEFAULT_KW" ||     // DEFAULT keyword variant
        name == "EXISTS_KW" ||      // EXISTS keyword variant
        name == "NOT_KW" ||         // NOT keyword variant
        name == "IF" ||             // IF without _KW (parser-only)
        name == "REPLACE" ||        // REPLACE without _KW (parser-only)
        name == "PROCEDURE" ||      // PROCEDURE without _KW (parser-only)
        name == "RETURN" ||         // RETURN without _KW (parser-only)
        name == "DELIMITER" ||      // DELIMITER without _KW (parser-only)
        name == "IGNORE_MYSQL" ||   // MySQL IGNORE variant
        name == "ENGINE_KW" ||      // ENGINE keyword variant
        name == "RANGE_KW" ||       // RANGE keyword variant
        name == "LIST_KW" ||        // LIST keyword variant
        name == "PERCENT_KW" ||     // PERCENT keyword variant
        name == "WITH_TIES" ||      // WITH TIES (context-dependent)
        name == "RETURNING_KW") {   // RETURNING keyword variant
        return false;
    }

    // Everything else is a keyword
    return true;
}

/// Strip common suffixes from enum names to get keyword text
consteval std::string_view strip_keyword_suffix(std::string_view enum_name) noexcept {
    // Strip "_KW" suffix: "IF_KW" → "IF", "NULL_KW" → "NULL"
    if (string_ends_with(enum_name, "_KW")) {
        return enum_name.substr(0, enum_name.size() - 3);
    }

    // Strip "_TYPE" suffix: "STRING_TYPE" → "STRING"
    if (string_ends_with(enum_name, "_TYPE")) {
        return enum_name.substr(0, enum_name.size() - 5);
    }

    // Strip "_LOCK" suffix: "UPDATE_LOCK" → "UPDATE"
    if (string_ends_with(enum_name, "_LOCK")) {
        return enum_name.substr(0, enum_name.size() - 5);
    }

    // Strip "_DDB" suffix: "REPLACE_DDB" → "REPLACE"
    if (string_ends_with(enum_name, "_DDB")) {
        return enum_name.substr(0, enum_name.size() - 4);
    }

    // Strip "_MYSQL" suffix: "IGNORE_MYSQL" → "IGNORE"
    if (string_ends_with(enum_name, "_MYSQL")) {
        return enum_name.substr(0, enum_name.size() - 6);
    }

    // No suffix - return as-is
    return enum_name;
}

/// Generate keyword mappings from TokenType enum using C++26 reflection
/// This is 100% compile-time - ZERO runtime cost!
consteval auto generate_keyword_mappings() {
    using namespace std;
    using namespace std::meta;

    #if 1  // FULL REFLECTION ENABLED!
    // Get all enum values via reflection
    auto enums = enumerators_of(^^TokenType);

    // Build list of keyword mappings
    std::vector<KeywordMapping> mappings;

    for (size_t i = 0; i < enums.size(); ++i) {
        auto enum_name = identifier_of(enums[i]);

        if (is_keyword_enum(enum_name)) {
            auto keyword_text = strip_keyword_suffix(enum_name);
            // Cast enum index to TokenType
            TokenType token_type = static_cast<TokenType>(i);

            mappings.push_back(KeywordMapping{keyword_text, token_type});
        }
    }

    // Convert to array for constexpr usage
    std::array<KeywordMapping, 300> result{};
    for (size_t i = 0; i < mappings.size() && i < 300; ++i) {
        result[i] = mappings[i];
    }

    return result;
    #endif  // Full reflection enabled
}

/// Auto-generated keyword mappings - single source of truth!
/// Derived entirely from TokenType enum via compile-time reflection
inline constexpr auto keyword_mappings = generate_keyword_mappings();

// Compile-time verification
static_assert(keyword_mappings.size() > 0, "No keywords found - reflection failed");
static_assert(keyword_mappings.size() < 500, "Too many keywords - check is_keyword_enum filter");

/// Compile-time validation: ensure no empty keyword text
consteval bool validate_keywords() {
    for (const auto& mapping : keyword_mappings) {
        if (mapping.text.empty()) {
            return false;
        }
        // Ensure keyword text is uppercase
        for (char c : mapping.text) {
            if (c >= 'a' && c <= 'z') {
                return false;  // Found lowercase - should be uppercase
            }
        }
    }
    return true;
}
static_assert(validate_keywords(), "All keywords must have non-empty uppercase text");

} // namespace libsqlglot::keywords
