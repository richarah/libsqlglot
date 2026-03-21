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
    {TokenType::STAR, 12, Associativity::LEFT},
    {TokenType::SLASH, 12, Associativity::LEFT},
    {TokenType::PERCENT, 12, Associativity::LEFT},
    {TokenType::MINUS, 11, Associativity::LEFT},
    {TokenType::PLUS, 11, Associativity::LEFT},
    {TokenType::SHIFT_RIGHT, 10, Associativity::LEFT},
    {TokenType::SHIFT_LEFT, 10, Associativity::LEFT},
    {TokenType::AMPERSAND, 9, Associativity::LEFT},
    {TokenType::CARET, 8, Associativity::LEFT},
    {TokenType::NEQ, 6, Associativity::LEFT},
    {TokenType::LTE, 6, Associativity::LEFT},
    {TokenType::GTE, 6, Associativity::LEFT},
    {TokenType::GT, 6, Associativity::LEFT},
    {TokenType::NEQ, 6, Associativity::LEFT},
    {TokenType::LT, 6, Associativity::LEFT},
    {TokenType::EQ, 6, Associativity::LEFT},
    {TokenType::NOT, 5, Associativity::RIGHT},
    {TokenType::AND, 4, Associativity::LEFT}
};

constexpr size_t operator_count = 18;

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
