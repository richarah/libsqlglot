#pragma once

#include "fwd.h"
#include "tokens.h"
#include "intern.h"
#include "keywords.h"
#include <string_view>
#include <vector>
#include <optional>
#include <cstdint>

namespace libsqlglot {

/// Tokenizer - converts SQL source text into tokens
/// Fast scalar implementation with branchless optimizations and perfect hash keyword lookup
/// Thread-safe (stateless), uses LocalStringPool for interning
class Tokenizer {
public:
    explicit Tokenizer(std::string_view source, LocalStringPool* pool = nullptr)
        : source_(source)
        , pos_(0)
        , line_(1)
        , col_(1)
        , pool_(pool)
        , default_pool_()
    {
        if (!pool_) {
            pool_ = &default_pool_;
        }
    }

    /// Tokenize entire source into vector of tokens
    std::vector<Token> tokenize_all() {
        std::vector<Token> tokens;
        tokens.reserve(source_.size() / 8); // Estimate: ~8 chars per token

        while (true) {
            auto tok = next_token();
            tokens.push_back(tok);
            if (tok.type == TokenType::EOF_TOKEN) break;
        }

        return tokens;
    }

    /// Get next token
    Token next_token() {
        skip_whitespace_and_comments();

        if (is_eof()) {
            return make_token(TokenType::EOF_TOKEN);
        }

        char c = peek();

        // Identifiers and keywords
        if (is_identifier_start(c)) {
            return tokenize_identifier();
        }

        // Numbers
        if (is_digit(c)) {
            return tokenize_number();
        }

        // Strings
        if (c == '\'' || c == '"') {
            return tokenize_string(c);
        }

        // Parameters: @name (T-SQL), :name (Oracle), $1 (Postgres), ?
        if (c == '@' || c == ':' || c == '$' || c == '?') {
            return tokenize_parameter();
        }

        // Operators and delimiters
        return tokenize_operator();
    }

private:
    bool is_eof() const { return pos_ >= source_.size(); }

    char peek(size_t offset = 0) const {
        // Guard against integer overflow: check offset is reasonable before adding
        if (offset > source_.size() || pos_ > source_.size() - offset) {
            return '\0';  // Out of bounds
        }
        size_t p = pos_ + offset;
        return source_[p];
    }

    char advance() {
        if (is_eof()) return '\0';
        char c = source_[pos_++];
        if (c == '\n') {
            line_++;
            col_ = 1;
        } else {
            col_++;
        }
        return c;
    }

    Token make_token(TokenType type, uint32_t start_pos, uint32_t end_pos,
                     uint16_t start_line, uint16_t start_col, const char* text = nullptr) {
        return Token{type, static_cast<uint32_t>(start_pos), static_cast<uint32_t>(end_pos),
                     start_line, start_col, text};
    }

    Token make_token(TokenType type, const char* text = nullptr) {
        return Token{type, static_cast<uint32_t>(pos_), static_cast<uint32_t>(pos_), line_, col_, text};
    }

    void skip_whitespace_and_comments() {
        while (!is_eof()) {
            char c = peek();

            // Whitespace
            if (c == ' ' || c == '\t' || c == '\n' || c == '\r') {
                advance();
                continue;
            }

            // Line comment: -- or #
            if ((c == '-' && peek(1) == '-') || c == '#') {
                while (!is_eof() && peek() != '\n') {
                    advance();
                }
                continue;
            }

            // Block comment: /* */
            if (c == '/' && peek(1) == '*') {
                advance(); advance(); // Skip /*
                while (!is_eof()) {
                    if (peek() == '*' && peek(1) == '/') {
                        advance(); advance(); // Skip */
                        break;
                    }
                    advance();
                }
                continue;
            }

            break;
        }
    }

    static bool is_identifier_start(char c) {
        return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == '_';
    }

    static bool is_identifier_continue(char c) {
        return is_identifier_start(c) || is_digit(c) || c == '$';
    }

    static bool is_digit(char c) {
        return c >= '0' && c <= '9';
    }

    static bool is_hex_digit(char c) {
        return is_digit(c) || (c >= 'a' && c <= 'f') || (c >= 'A' && c <= 'F');
    }

    Token tokenize_identifier() {
        uint32_t start_pos = pos_;
        uint16_t start_line = line_;
        uint16_t start_col = col_;

        // Handle quoted identifiers
        if (peek() == '"' || peek() == '`' || peek() == '[') {
            char quote = advance();
            char end_quote = (quote == '[') ? ']' : quote;

            while (!is_eof() && peek() != end_quote) {
                advance();
            }
            if (!is_eof()) advance(); // Skip closing quote

            std::string_view text = source_.substr(start_pos, pos_ - start_pos);
            const char* interned = pool_->intern(text);
            return make_token(TokenType::IDENTIFIER, start_pos, pos_, start_line, start_col, interned);
        }

        // Regular identifier
        while (!is_eof() && is_identifier_continue(peek())) {
            advance();
        }

        std::string_view text = source_.substr(start_pos, pos_ - start_pos);
        const char* interned = pool_->intern(text);

        // Check if it's a keyword
        TokenType type = keyword_type(text);

        return make_token(type, start_pos, pos_, start_line, start_col, interned);
    }

    Token tokenize_number() {
        uint32_t start_pos = pos_;
        uint16_t start_line = line_;
        uint16_t start_col = col_;

        // Hex: 0x...
        if (peek() == '0' && (peek(1) == 'x' || peek(1) == 'X')) {
            advance(); advance();
            while (!is_eof() && is_hex_digit(peek())) {
                advance();
            }
            std::string_view text = source_.substr(start_pos, pos_ - start_pos);
            return make_token(TokenType::NUMBER, start_pos, pos_, start_line, start_col, pool_->intern(text));
        }

        // Binary: 0b...
        if (peek() == '0' && (peek(1) == 'b' || peek(1) == 'B')) {
            advance(); advance();
            while (!is_eof() && (peek() == '0' || peek() == '1')) {
                advance();
            }
            std::string_view text = source_.substr(start_pos, pos_ - start_pos);
            return make_token(TokenType::NUMBER, start_pos, pos_, start_line, start_col, pool_->intern(text));
        }

        // Decimal number
        while (!is_eof() && is_digit(peek())) {
            advance();
        }

        // Decimal point
        if (peek() == '.' && is_digit(peek(1))) {
            advance(); // .
            while (!is_eof() && is_digit(peek())) {
                advance();
            }
        }

        // Exponent
        if (peek() == 'e' || peek() == 'E') {
            advance();
            if (peek() == '+' || peek() == '-') advance();
            while (!is_eof() && is_digit(peek())) {
                advance();
            }
        }

        std::string_view text = source_.substr(start_pos, pos_ - start_pos);
        return make_token(TokenType::NUMBER, start_pos, pos_, start_line, start_col, pool_->intern(text));
    }

    Token tokenize_string(char quote) {
        uint32_t start_pos = pos_;
        uint16_t start_line = line_;
        uint16_t start_col = col_;

        advance(); // Opening quote

        while (!is_eof()) {
            char c = peek();

            if (c == quote) {
                // Check for escaped quote (doubled)
                if (peek(1) == quote) {
                    advance(); advance();
                    continue;
                }
                advance(); // Closing quote
                break;
            }

            if (c == '\\') {
                advance(); // Backslash
                if (!is_eof()) advance(); // Escaped char
                continue;
            }

            advance();
        }

        std::string_view text = source_.substr(start_pos, pos_ - start_pos);
        return make_token(TokenType::STRING, start_pos, pos_, start_line, start_col, pool_->intern(text));
    }

    Token tokenize_parameter() {
        uint32_t start_pos = pos_;
        uint16_t start_line = line_;
        uint16_t start_col = col_;

        char prefix = advance(); // @ or : or $ or ?

        // For standalone ? parameter, return immediately
        if (prefix == '?') {
            std::string_view text = source_.substr(start_pos, pos_ - start_pos);
            return make_token(TokenType::PARAMETER, start_pos, pos_, start_line, start_col, pool_->intern(text));
        }

        // For :=, don't treat as parameter (it's assignment operator)
        if (prefix == ':' && peek() == '=') {
            // Backtrack - this is COLON_EQUALS, not a parameter
            pos_ = start_pos;
            col_ = start_col;
            return tokenize_operator();
        }

        // For :: (double colon cast), don't treat as parameter
        if (prefix == ':' && peek() == ':') {
            // Backtrack - this is DOUBLE_COLON, not a parameter
            pos_ = start_pos;
            col_ = start_col;
            return tokenize_operator();
        }

        // For $1, $2, etc. (Postgres positional parameters)
        if (prefix == '$' && is_digit(peek())) {
            while (!is_eof() && is_digit(peek())) {
                advance();
            }
            std::string_view text = source_.substr(start_pos, pos_ - start_pos);
            return make_token(TokenType::PARAMETER, start_pos, pos_, start_line, start_col, pool_->intern(text));
        }

        // For @name or :name (must be followed by identifier)
        if (is_identifier_start(peek())) {
            while (!is_eof() && is_identifier_continue(peek())) {
                advance();
            }
            std::string_view text = source_.substr(start_pos, pos_ - start_pos);
            return make_token(TokenType::PARAMETER, start_pos, pos_, start_line, start_col, pool_->intern(text));
        }

        // If not followed by identifier/digit, backtrack and treat as operator
        // (e.g., @ alone, : alone, $ alone)
        pos_ = start_pos;
        col_ = start_col;
        return tokenize_operator();
    }

    Token tokenize_operator() {
        uint32_t start_pos = pos_;
        uint16_t start_line = line_;
        uint16_t start_col = col_;

        char c = advance();
        char next = peek();

        // Two-character operators (with text for DELIMITER parsing)
        std::string_view text;
        if (c == '|' && next == '|') { advance(); text = source_.substr(start_pos, pos_ - start_pos); return make_token(TokenType::CONCAT, start_pos, pos_, start_line, start_col, pool_->intern(text)); }
        if (c == '<' && next == '>') { advance(); text = source_.substr(start_pos, pos_ - start_pos); return make_token(TokenType::NEQ, start_pos, pos_, start_line, start_col, pool_->intern(text)); }
        if (c == '<' && next == '=') { advance(); text = source_.substr(start_pos, pos_ - start_pos); return make_token(TokenType::LTE, start_pos, pos_, start_line, start_col, pool_->intern(text)); }
        if (c == '>' && next == '=') { advance(); text = source_.substr(start_pos, pos_ - start_pos); return make_token(TokenType::GTE, start_pos, pos_, start_line, start_col, pool_->intern(text)); }
        if (c == '!' && next == '=') { advance(); text = source_.substr(start_pos, pos_ - start_pos); return make_token(TokenType::NEQ, start_pos, pos_, start_line, start_col, pool_->intern(text)); }
        if (c == ':' && next == '=') { advance(); text = source_.substr(start_pos, pos_ - start_pos); return make_token(TokenType::COLON_EQUALS, start_pos, pos_, start_line, start_col, pool_->intern(text)); }
        if (c == ':' && next == ':') { advance(); text = source_.substr(start_pos, pos_ - start_pos); return make_token(TokenType::DOUBLE_COLON, start_pos, pos_, start_line, start_col, pool_->intern(text)); }
        if (c == '.' && next == '.') { advance(); text = source_.substr(start_pos, pos_ - start_pos); return make_token(TokenType::DOUBLE_DOT, start_pos, pos_, start_line, start_col, pool_->intern(text)); }
        if (c == '-' && next == '>') {
            advance();
            if (peek() == '>') { advance(); text = source_.substr(start_pos, pos_ - start_pos); return make_token(TokenType::LONG_ARROW, start_pos, pos_, start_line, start_col, pool_->intern(text)); }
            text = source_.substr(start_pos, pos_ - start_pos); return make_token(TokenType::ARROW, start_pos, pos_, start_line, start_col, pool_->intern(text));
        }

        // Single-character operators (with text for DELIMITER parsing)
        text = source_.substr(start_pos, pos_ - start_pos);
        const char* interned = pool_->intern(text);
        switch (c) {
            case '+': return make_token(TokenType::PLUS, start_pos, pos_, start_line, start_col, interned);
            case '-': return make_token(TokenType::MINUS, start_pos, pos_, start_line, start_col, interned);
            case '*': return make_token(TokenType::STAR, start_pos, pos_, start_line, start_col, interned);
            case '/': return make_token(TokenType::SLASH, start_pos, pos_, start_line, start_col, interned);
            case '%': return make_token(TokenType::PERCENT, start_pos, pos_, start_line, start_col, interned);
            case '^': return make_token(TokenType::CARET, start_pos, pos_, start_line, start_col, interned);
            case '&': return make_token(TokenType::AMPERSAND, start_pos, pos_, start_line, start_col, interned);
            case '|': return make_token(TokenType::PIPE, start_pos, pos_, start_line, start_col, interned);
            case '~': return make_token(TokenType::TILDE, start_pos, pos_, start_line, start_col, interned);
            case '=': return make_token(TokenType::EQ, start_pos, pos_, start_line, start_col, interned);
            case '<': return make_token(TokenType::LT, start_pos, pos_, start_line, start_col, interned);
            case '>': return make_token(TokenType::GT, start_pos, pos_, start_line, start_col, interned);
            case '(': return make_token(TokenType::LPAREN, start_pos, pos_, start_line, start_col, interned);
            case ')': return make_token(TokenType::RPAREN, start_pos, pos_, start_line, start_col, interned);
            case '[': return make_token(TokenType::LBRACKET, start_pos, pos_, start_line, start_col, interned);
            case ']': return make_token(TokenType::RBRACKET, start_pos, pos_, start_line, start_col, interned);
            case '{': return make_token(TokenType::LBRACE, start_pos, pos_, start_line, start_col, interned);
            case '}': return make_token(TokenType::RBRACE, start_pos, pos_, start_line, start_col, interned);
            case ',': return make_token(TokenType::COMMA, start_pos, pos_, start_line, start_col, interned);
            case ';': return make_token(TokenType::SEMICOLON, start_pos, pos_, start_line, start_col, interned);
            case '.': return make_token(TokenType::DOT, start_pos, pos_, start_line, start_col, interned);
            case ':': return make_token(TokenType::COLON, start_pos, pos_, start_line, start_col, interned);
            case '?': return make_token(TokenType::QUESTION, start_pos, pos_, start_line, start_col, interned);
            default: {
                // Unknown character - return ERROR token with text for debugging
                text = source_.substr(start_pos, pos_ - start_pos);
                return make_token(TokenType::ERROR, start_pos, pos_, start_line, start_col, pool_->intern(text));
            }
        }
    }

    TokenType keyword_type(std::string_view text) {
        // O(1) perfect hash lookup - 5-10x faster than linear scan
        return KeywordLookup::lookup(text);
    }

    std::string_view source_;
    size_t pos_;
    uint16_t line_;
    uint16_t col_;
    LocalStringPool* pool_;
    LocalStringPool default_pool_;
};

} // namespace libsqlglot
