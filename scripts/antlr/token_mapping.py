#!/usr/bin/env python3
"""
Token Mapping: ANTLR ↔ libsqlglot TokenType

Maps ANTLR lexer token names to libsqlglot's TokenType enum.

ANTLR conventions:
- Keyword tokens: SELECT_SYMBOL, INSERT_SYMBOL
- Operator tokens: PLUS_OPERATOR, MULT_OPERATOR
- Delimiter tokens: LPAREN_SYMBOL, OPEN_PAR_SYMBOL

libsqlglot conventions:
- Keywords: TokenType::SELECT, TokenType::INSERT
- Operators: TokenType::PLUS, TokenType::STAR
- Delimiters: TokenType::LPAREN, TokenType::COMMA
"""

from typing import Optional, Set, Dict
from pathlib import Path
import re


class TokenMapper:
    """Maps ANTLR token names to libsqlglot TokenType enum values"""

    def __init__(self):
        self.known_tokens: Set[str] = set()
        self.antlr_to_libsqlglot: Dict[str, str] = {}
        self._build_mapping()

    def _build_mapping(self):
        """Build comprehensive ANTLR → libsqlglot mapping"""

        # Explicit mappings for common patterns
        explicit_mappings = {
            # Common keywords
            'SELECT_SYMBOL': 'SELECT',
            'INSERT_SYMBOL': 'INSERT',
            'UPDATE_SYMBOL': 'UPDATE',
            'DELETE_SYMBOL': 'DELETE',
            'CREATE_SYMBOL': 'CREATE',
            'DROP_SYMBOL': 'DROP',
            'ALTER_SYMBOL': 'ALTER',
            'FROM_SYMBOL': 'FROM',
            'WHERE_SYMBOL': 'WHERE',
            'GROUP_SYMBOL': 'GROUP',
            'ORDER_SYMBOL': 'ORDER',
            'BY_SYMBOL': 'BY',
            'HAVING_SYMBOL': 'HAVING',
            'LIMIT_SYMBOL': 'LIMIT',
            'OFFSET_SYMBOL': 'OFFSET',
            'JOIN_SYMBOL': 'JOIN',
            'INNER_SYMBOL': 'INNER',
            'LEFT_SYMBOL': 'LEFT',
            'RIGHT_SYMBOL': 'RIGHT',
            'FULL_SYMBOL': 'FULL',
            'CROSS_SYMBOL': 'CROSS',
            'OUTER_SYMBOL': 'OUTER',
            'ON_SYMBOL': 'ON',
            'USING_SYMBOL': 'USING',
            'AS_SYMBOL': 'AS',
            'DISTINCT_SYMBOL': 'DISTINCT',
            'ALL_SYMBOL': 'ALL',
            'AND_SYMBOL': 'AND',
            'OR_SYMBOL': 'OR',
            'NOT_SYMBOL': 'NOT',
            'IN_SYMBOL': 'IN',
            'IS_SYMBOL': 'IS',
            'NULL_SYMBOL': 'NULL_KW',
            'TRUE_SYMBOL': 'TRUE',
            'FALSE_SYMBOL': 'FALSE',
            'CASE_SYMBOL': 'CASE',
            'WHEN_SYMBOL': 'WHEN',
            'THEN_SYMBOL': 'THEN',
            'ELSE_SYMBOL': 'ELSE',
            'END_SYMBOL': 'END',
            'WITH_SYMBOL': 'WITH',
            'VALUES_SYMBOL': 'VALUES',
            'SET_SYMBOL': 'SET',
            'TABLE_SYMBOL': 'TABLE',
            'VIEW_SYMBOL': 'VIEW',
            'INDEX_SYMBOL': 'INDEX',
            'PRIMARY_SYMBOL': 'PRIMARY',
            'FOREIGN_SYMBOL': 'FOREIGN',
            'KEY_SYMBOL': 'KEY',
            'REFERENCES_SYMBOL': 'REFERENCES',
            'CONSTRAINT_SYMBOL': 'CONSTRAINT',
            'UNIQUE_SYMBOL': 'UNIQUE',
            'CHECK_SYMBOL': 'CHECK',
            'DEFAULT_SYMBOL': 'DEFAULT',

            # Operators
            'PLUS_OPERATOR': 'PLUS',
            'MINUS_OPERATOR': 'MINUS',
            'MULT_OPERATOR': 'STAR',
            'DIV_OPERATOR': 'SLASH',
            'MOD_OPERATOR': 'PERCENT',
            'EQUAL_OPERATOR': 'EQ',
            'NOT_EQUAL_OPERATOR': 'NEQ',
            'NOT_EQUAL2_OPERATOR': 'NEQ',
            'LESS_THAN_OPERATOR': 'LT',
            'LESS_OR_EQUAL_OPERATOR': 'LTE',
            'GREATER_THAN_OPERATOR': 'GT',
            'GREATER_OR_EQUAL_OPERATOR': 'GTE',
            'BITWISE_AND_OPERATOR': 'AMPERSAND',
            'BITWISE_OR_OPERATOR': 'PIPE',
            'BITWISE_XOR_OPERATOR': 'CARET',
            'BITWISE_NOT_OPERATOR': 'TILDE',
            'LOGICAL_AND_OPERATOR': 'AND',
            'LOGICAL_OR_OPERATOR': 'OR',
            'LOGICAL_NOT_OPERATOR': 'NOT',
            'CONCAT_OPERATOR': 'CONCAT',
            'ASSIGN_OPERATOR': 'EQ',
            'COLON_EQUALS': 'COLON_EQUALS',

            # Delimiters
            'LPAREN': 'LPAREN',
            'RPAREN': 'RPAREN',
            'OPEN_PAR_SYMBOL': 'LPAREN',
            'CLOSE_PAR_SYMBOL': 'RPAREN',
            'LBRACKET': 'LBRACKET',
            'RBRACKET': 'RBRACKET',
            'LBRACE': 'LBRACE',
            'RBRACE': 'RBRACE',
            'OPEN_CURLY_SYMBOL': 'LBRACE',
            'CLOSE_CURLY_SYMBOL': 'RBRACE',
            'COMMA': 'COMMA',
            'COMMA_SYMBOL': 'COMMA',
            'SEMICOLON': 'SEMICOLON',
            'SEMICOLON_SYMBOL': 'SEMICOLON',
            'DOT': 'DOT',
            'DOT_SYMBOL': 'DOT',
            'COLON_SYMBOL': 'COLON',

            # Data types
            'INT_SYMBOL': 'INT',
            'INTEGER_SYMBOL': 'INTEGER',
            'BIGINT_SYMBOL': 'BIGINT',
            'SMALLINT_SYMBOL': 'SMALLINT',
            'TINYINT_SYMBOL': 'TINYINT',
            'FLOAT_SYMBOL': 'FLOAT',
            'DOUBLE_SYMBOL': 'DOUBLE',
            'REAL_SYMBOL': 'REAL',
            'DECIMAL_SYMBOL': 'DECIMAL',
            'NUMERIC_SYMBOL': 'NUMERIC',
            'CHAR_SYMBOL': 'CHAR',
            'VARCHAR_SYMBOL': 'VARCHAR',
            'TEXT_SYMBOL': 'TEXT',
            'BLOB_SYMBOL': 'BLOB',
            'BOOLEAN_SYMBOL': 'BOOLEAN',
            'BOOL_SYMBOL': 'BOOL',
            'DATE_SYMBOL': 'DATE',
            'TIME_SYMBOL': 'TIME',
            'TIMESTAMP_SYMBOL': 'TIMESTAMP',
            'INTERVAL_SYMBOL': 'INTERVAL',
            'ARRAY_SYMBOL': 'ARRAY',
            'JSON_SYMBOL': 'JSON',

            # Functions
            'COUNT_SYMBOL': 'COUNT',
            'SUM_SYMBOL': 'SUM',
            'AVG_SYMBOL': 'AVG',
            'MIN_SYMBOL': 'MIN',
            'MAX_SYMBOL': 'MAX',
            'CAST_SYMBOL': 'CAST',
            'EXTRACT_SYMBOL': 'EXTRACT',
            'SUBSTRING_SYMBOL': 'SUBSTRING',
            'SUBSTR_SYMBOL': 'SUBSTR',
            'CONCAT_SYMBOL': 'CONCAT_KW',
            'COALESCE_SYMBOL': 'COALESCE',
            'NULLIF_SYMBOL': 'NULLIF',
            'UPPER_SYMBOL': 'UPPER',
            'LOWER_SYMBOL': 'LOWER',
            'TRIM_SYMBOL': 'TRIM',

            # Window functions
            'OVER_SYMBOL': 'OVER',
            'PARTITION_SYMBOL': 'PARTITION',
            'ROWS_SYMBOL': 'ROWS',
            'RANGE_SYMBOL': 'RANGE',
            'RANK_SYMBOL': 'RANK',
            'DENSE_RANK_SYMBOL': 'DENSE_RANK',
            'ROW_NUMBER_SYMBOL': 'ROW_NUMBER',
            'LEAD_SYMBOL': 'LEAD',
            'LAG_SYMBOL': 'LAG',

            # Transaction
            'BEGIN_SYMBOL': 'BEGIN',
            'COMMIT_SYMBOL': 'COMMIT',
            'ROLLBACK_SYMBOL': 'ROLLBACK',
            'TRANSACTION_SYMBOL': 'TRANSACTION',

            # Literals
            'INT_NUMBER': 'NUMBER',
            'FLOAT_NUMBER': 'NUMBER',
            'DECIMAL_NUMBER': 'NUMBER',
            'HEX_NUMBER': 'NUMBER',
            'BIN_NUMBER': 'NUMBER',
            'IDENTIFIER': 'IDENTIFIER',
            'SINGLE_QUOTED_TEXT': 'STRING',
            'DOUBLE_QUOTED_TEXT': 'STRING',
            'BACK_TICK_QUOTED_ID': 'IDENTIFIER',

            # Special
            'EOF': 'EOF_TOKEN',
            'WHITESPACE': 'WHITESPACE',
            'COMMENT': 'COMMENT',
            'BLOCK_COMMENT': 'COMMENT',
            'LINE_COMMENT': 'COMMENT',
        }

        self.antlr_to_libsqlglot = explicit_mappings
        self.known_tokens = set(explicit_mappings.values())

    def map_token(self, antlr_name: str) -> Optional[str]:
        """Map ANTLR token name to libsqlglot TokenType"""

        # Direct mapping
        if antlr_name in self.antlr_to_libsqlglot:
            return self.antlr_to_libsqlglot[antlr_name]

        # Pattern-based mapping
        # Remove common ANTLR suffixes
        clean = antlr_name
        for suffix in ['_SYMBOL', '_OPERATOR', '_KW', '_KEYWORD']:
            if clean.endswith(suffix):
                clean = clean[:-len(suffix)]
                break

        # Check if cleaned name is a known token
        if clean in self.known_tokens:
            return clean

        # Special cases
        if 'STAR' in clean or 'MULT' in clean:
            return 'STAR'
        if 'DIV' in clean and 'DIVIDE' not in clean:
            return 'SLASH'

        # Return cleaned name (might not exist in libsqlglot, but that's ok)
        return clean

    def map_keyword(self, keyword: str) -> Optional[str]:
        """Map extracted keyword to libsqlglot TokenType"""
        # Keywords are simpler - just uppercase the keyword
        # Special cases
        keyword_map = {
            'NULL': 'NULL_KW',
            'DEFAULT': 'DEFAULT_KW',
            'MINUS': 'MINUS_KW',
            'STRING': 'STRING_TYPE',
            'CONCAT': 'CONCAT_KW',
            'IF': 'IF_KW',
            'EXISTS': 'EXISTS_KW',
            'PROCEDURE': 'PROCEDURE_KW',
            'RETURN': 'RETURN_KW',
            'WHEN': 'WHEN_KW',
            'DESC': 'DESC_KW',
            'FLATTEN': 'FLATTEN_KW',
            'RANGE': 'RANGE_KW',
            'LIST': 'LIST_KW',
            'STRUCT': 'STRUCT_KW',
            'REPLACE': 'REPLACE_KW',
        }

        return keyword_map.get(keyword.upper(), keyword.upper())


# Global instance
_mapper = None

def get_mapper() -> TokenMapper:
    """Get global TokenMapper instance"""
    global _mapper
    if _mapper is None:
        _mapper = TokenMapper()
    return _mapper


def map_antlr_token(antlr_name: str) -> Optional[str]:
    """Map ANTLR token to libsqlglot TokenType"""
    return get_mapper().map_token(antlr_name)


def map_keyword(keyword: str) -> str:
    """Map keyword to libsqlglot TokenType"""
    return get_mapper().map_keyword(keyword)


# CLI for testing
if __name__ == '__main__':
    mapper = TokenMapper()

    # Test cases
    test_cases = [
        'SELECT_SYMBOL',
        'PLUS_OPERATOR',
        'OPEN_PAR_SYMBOL',
        'INT_NUMBER',
        'IDENTIFIER',
        'MULT_OPERATOR',
    ]

    print("Token Mapping Tests:")
    for test in test_cases:
        mapped = mapper.map_token(test)
        print(f"  {test:30} → {mapped}")

    print("\nKeyword Mapping Tests:")
    keywords = ['SELECT', 'NULL', 'DEFAULT', 'MINUS']
    for kw in keywords:
        mapped = mapper.map_keyword(kw)
        print(f"  {kw:30} → {mapped}")
