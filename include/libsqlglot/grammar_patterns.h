#pragma once

// Auto-generated grammar patterns from ANTLR grammars
// DO NOT EDIT MANUALLY
//
// This file contains token sequence patterns extracted from SQL dialect grammars.
// These patterns are used by libsqlglot's hand-written parser for validation
// and syntax checking.

#include "tokens.h"
#include "dialects.h"
#include <array>
#include <cstdint>

namespace libsqlglot {
namespace grammar {

/// Grammar pattern: a sequence of tokens representing a valid construct
struct Pattern {
    const char* name;
    Dialect dialect;
    const TokenType* tokens;
    uint8_t length;
    const char* pattern_type;
};

// Unified pattern table
constexpr Pattern all_patterns[] = {

};

constexpr size_t pattern_count = 0;

}  // namespace grammar
}  // namespace libsqlglot
