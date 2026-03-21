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
    {TokenType::TILDE, 14, Associativity::RIGHT},
    {TokenType::CARET, 13, Associativity::RIGHT},
    {TokenType::CARET_, 13, Associativity::RIGHT},
    {TokenType::POWER, 13, Associativity::RIGHT},
    {TokenType::DIVIDE, 12, Associativity::LEFT},
    {TokenType::PERCENT, 12, Associativity::LEFT},
    {TokenType::PERCENT_, 12, Associativity::LEFT},
    {TokenType::SLASH, 12, Associativity::LEFT},
    {TokenType::SLASH_, 12, Associativity::LEFT},
    {TokenType::STAR, 12, Associativity::LEFT},
    {TokenType::MINUS, 11, Associativity::LEFT},
    {TokenType::MINUS_, 11, Associativity::LEFT},
    {TokenType::PLUS, 11, Associativity::LEFT},
    {TokenType::PLUS_, 11, Associativity::LEFT},
    {TokenType::CONCAT, 10, Associativity::LEFT},
    {TokenType::SHIFT_LEFT, 10, Associativity::LEFT},
    {TokenType::SHIFT_RIGHT, 10, Associativity::LEFT},
    {TokenType::AMPERSAND, 9, Associativity::LEFT},
    {TokenType::PIPE, 7, Associativity::LEFT},
    {TokenType::ARROW, 6, Associativity::LEFT},
    {TokenType::EQ, 6, Associativity::LEFT},
    {TokenType::EQ_, 6, Associativity::LEFT},
    {TokenType::GT, 6, Associativity::LEFT},
    {TokenType::GTE, 6, Associativity::LEFT},
    {TokenType::GTE_, 6, Associativity::LEFT},
    {TokenType::GT_, 6, Associativity::LEFT},
    {TokenType::LT, 6, Associativity::LEFT},
    {TokenType::LTE, 6, Associativity::LEFT},
    {TokenType::LTE_, 6, Associativity::LEFT},
    {TokenType::LT_, 6, Associativity::LEFT},
    {TokenType::NEQ, 6, Associativity::LEFT},
    {TokenType::NEQ_, 6, Associativity::LEFT},
    {TokenType::NULL_SAFE_EQUAL, 6, Associativity::LEFT},
    {TokenType::OVERLAPS, 6, Associativity::LEFT},
    {TokenType::QUESTION_MARK, 6, Associativity::LEFT},
    {TokenType::QUESTION_MARK_, 6, Associativity::LEFT},
    {TokenType::RANGE, 6, Associativity::LEFT},
    {TokenType::RANGE_, 6, Associativity::LEFT},
    {TokenType::EXCLAMATION, 5, Associativity::RIGHT},
    {TokenType::NOT, 5, Associativity::RIGHT},
    {TokenType::NOT_, 5, Associativity::RIGHT},
    {TokenType::AND, 4, Associativity::LEFT},
    {TokenType::AND_, 4, Associativity::LEFT},
    {TokenType::OR, 3, Associativity::LEFT},
    {TokenType::OR_, 3, Associativity::LEFT},
    {TokenType::ASSIGN, 2, Associativity::RIGHT},
    {TokenType::COLON_EQUALS, 2, Associativity::RIGHT}
};

constexpr size_t operator_count = 47;

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
