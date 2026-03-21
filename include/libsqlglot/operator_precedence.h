#pragma once

// Auto-generated operator precedence from ANTLR grammars
// DO NOT EDIT MANUALLY

#include "tokens.h"
#include <cstdint>

namespace libsqlglot {

/// Operator associativity
enum class Associativity : uint8_t {
    LEFT,
    RIGHT,
    NONE
};

/// Operator precedence information
struct OperatorPrecedence {
    TokenType op;
    uint8_t precedence;
    Associativity associativity;
};

/// Operator precedence table (higher number = higher precedence)
constexpr OperatorPrecedence operator_precedence[] = {

};

constexpr size_t operator_count = 0;

/// Get precedence for an operator token
[[nodiscard]] inline int get_precedence(TokenType op) noexcept {
    for (size_t i = 0; i < operator_count; ++i) {
        if (operator_precedence[i].op == op) {
            return operator_precedence[i].precedence;
        }
    }
    return -1;  // Not an operator
}

/// Get associativity for an operator token
[[nodiscard]] inline Associativity get_associativity(TokenType op) noexcept {
    for (size_t i = 0; i < operator_count; ++i) {
        if (operator_precedence[i].op == op) {
            return operator_precedence[i].associativity;
        }
    }
    return Associativity::NONE;
}

}  // namespace libsqlglot
