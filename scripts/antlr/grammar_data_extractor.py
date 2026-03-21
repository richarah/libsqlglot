#!/usr/bin/env python3
"""
Grammar Data Extractor

Extracts structured data from parsed ANTLR grammars for generating C++ LUT headers.
This is the first stage of the grammar-to-LUT compiler pipeline.

Output: Dictionary with:
- Token sequences for each rule
- Operator precedence/associativity
- Keywords
- Syntax patterns
"""

import json
from pathlib import Path
from typing import Dict, List, Any, Optional, Set
from dataclasses import dataclass, asdict

from grammar_parser import parse_grammar_file, Grammar, Rule, Element


@dataclass
class TokenSequence:
    """A sequence of tokens representing a grammar production"""
    name: str
    tokens: List[str]
    optional_flags: List[bool]
    pattern_type: str  # e.g., "select_statement", "binary_expr"


@dataclass
class OperatorInfo:
    """Operator metadata"""
    token: str
    precedence: int
    associativity: str  # "left", "right", "none"


@dataclass
class GrammarData:
    """Extracted grammar data for a single dialect"""
    dialect: str
    grammar_name: str
    token_sequences: List[TokenSequence]
    operators: List[OperatorInfo]
    keywords: List[str]
    lexer_tokens: List[str]


class GrammarDataExtractor:
    """Extract structured data from ANTLR grammars"""

    def __init__(self, grammar: Grammar, dialect: str):
        self.grammar = grammar
        self.dialect = dialect
        self.keywords: Set[str] = set()
        self.lexer_tokens: Set[str] = set()
        self.token_sequences: List[TokenSequence] = []
        self.operators: List[OperatorInfo] = []

    def extract(self) -> GrammarData:
        """Extract all data from grammar"""
        print(f"[OK] Extracting data from {self.grammar.name} grammar...")

        # Extract keywords and lexer tokens
        self._extract_keywords()

        # Extract token sequences from parser rules
        self._extract_token_sequences()

        # Extract operator precedence
        self._extract_operators()

        print(f"[OK] Extracted {len(self.token_sequences)} token sequences")
        print(f"[OK] Extracted {len(self.keywords)} keywords")
        print(f"[OK] Extracted {len(self.operators)} operators")

        return GrammarData(
            dialect=self.dialect,
            grammar_name=self.grammar.name,
            token_sequences=self.token_sequences,
            operators=self.operators,
            keywords=sorted(self.keywords),
            lexer_tokens=sorted(self.lexer_tokens)
        )

    def _extract_keywords(self):
        """Extract keywords and lexer tokens"""
        for name, rule in self.grammar.rules.items():
            if rule.type.value == 'lexer':
                # Lexer rule
                self.lexer_tokens.add(name)

                # Check if it's a keyword (literal string)
                keyword = self._extract_keyword_from_rule(rule)
                if keyword:
                    self.keywords.add(keyword)

    def _extract_keyword_from_rule(self, rule: Rule) -> Optional[str]:
        """Extract keyword literal from lexer rule"""
        # ANTLR lexer keywords can be defined in multiple ways:
        # 1. Direct string: 'SELECT'
        # 2. Character sequence: S E L E C T (using fragment references)
        # 3. Both: 'SELECT' | S E L E C T

        keyword = self._try_extract_from_ast(rule.definition)

        if keyword and len(keyword) > 1:  # Filter out single-character fragments
            # Filter out non-keywords (operators, special symbols)
            if keyword.isalpha() or '_' in keyword:
                return keyword.upper()

        return None

    def _try_extract_from_ast(self, element: Element) -> Optional[str]:
        """Try to extract keyword string from parsed AST"""
        from grammar_parser import Terminal, Sequence, Alternative, NonTerminal

        if isinstance(element, Terminal):
            # Direct string literal like 'SELECT'
            if element.is_string_literal:
                return element.value
            # Single character reference like S, E, L, E, C, T
            # These get concatenated in Sequence
            return element.value

        elif isinstance(element, Sequence):
            # Sequence of characters: S E L E C T → "SELECT"
            parts = []
            for child in element.elements:
                part = self._try_extract_from_ast(child)
                if part:
                    parts.append(part)

            # If all parts are single characters, concatenate them
            if parts and all(len(p) <= 1 for p in parts):
                return ''.join(parts)
            # If we have a string literal in the sequence, use it
            elif parts:
                for p in parts:
                    if len(p) > 1:
                        return p

        elif isinstance(element, Alternative):
            # Try first alternative (usually the canonical form)
            if element.alternatives:
                return self._try_extract_from_ast(element.alternatives[0])

        return None

    def _extract_token_sequences(self):
        """Extract token sequences from parser rules"""
        for name, rule in self.grammar.rules.items():
            if rule.type.value == 'parser':
                # Extract sequences from this rule
                sequences = self._extract_sequences_from_rule(name, rule)
                self.token_sequences.extend(sequences)

    def _extract_sequences_from_rule(self, rule_name: str, rule: Rule) -> List[TokenSequence]:
        """Extract token sequences from a single parser rule using recursive AST walker"""
        from grammar_parser import Alternative

        sequences = []
        pattern_type = self._categorize_rule(rule_name)

        # Walk the AST to extract all possible token sequences
        all_sequences = self._walk_ast_for_sequences(rule.definition)

        # Convert each sequence to TokenSequence
        for seq_info in all_sequences:
            if seq_info['tokens']:  # Only add non-empty sequences
                sequences.append(TokenSequence(
                    name=rule_name,
                    tokens=seq_info['tokens'],
                    optional_flags=seq_info['optional'],
                    pattern_type=pattern_type
                ))

        return sequences

    def _walk_ast_for_sequences(self, element: Element) -> List[Dict[str, List]]:
        """
        Recursively walk AST to extract token sequences.
        Returns list of dicts with 'tokens' and 'optional' lists.
        """
        from grammar_parser import (
            Terminal, NonTerminal, Sequence, Alternative,
            Quantified, Group, Quantifier
        )

        if isinstance(element, Terminal):
            # Base case: single terminal
            token_name = element.value
            return [{'tokens': [token_name], 'optional': [False]}]

        elif isinstance(element, NonTerminal):
            # Non-terminal reference - could inline or just reference name
            # For now, treat as a token
            return [{'tokens': [element.name], 'optional': [False]}]

        elif isinstance(element, Sequence):
            # Sequence: concatenate all children
            if not element.elements:
                return [{'tokens': [], 'optional': []}]

            # Start with first element's sequences
            result_sequences = self._walk_ast_for_sequences(element.elements[0])

            # Concatenate remaining elements
            for child in element.elements[1:]:
                child_sequences = self._walk_ast_for_sequences(child)
                new_results = []

                # Cartesian product of existing and new sequences
                for existing in result_sequences:
                    for child_seq in child_sequences:
                        combined = {
                            'tokens': existing['tokens'] + child_seq['tokens'],
                            'optional': existing['optional'] + child_seq['optional']
                        }
                        new_results.append(combined)

                result_sequences = new_results

            return result_sequences

        elif isinstance(element, Alternative):
            # Alternative: return separate sequence for each alternative
            all_seqs = []
            for alt in element.alternatives:
                seqs = self._walk_ast_for_sequences(alt)
                all_seqs.extend(seqs)
            return all_seqs

        elif isinstance(element, Quantified):
            # Quantified: mark as optional or repeated
            child_seqs = self._walk_ast_for_sequences(element.element)

            if element.quantifier in (Quantifier.OPTIONAL, Quantifier.STAR):
                # Mark all tokens as optional
                for seq in child_seqs:
                    seq['optional'] = [True] * len(seq['tokens'])

            # For STAR and PLUS, tokens can repeat, but we just mark once
            return child_seqs

        elif isinstance(element, Group):
            # Group: just unwrap
            return self._walk_ast_for_sequences(element.content)

        else:
            # Unknown element type
            return [{'tokens': [], 'optional': []}]

    def _categorize_rule(self, rule_name: str) -> str:
        """Categorize rule by type (for organization)"""
        name_lower = rule_name.lower()

        if 'select' in name_lower:
            return 'select_statement'
        elif 'insert' in name_lower:
            return 'insert_statement'
        elif 'update' in name_lower:
            return 'update_statement'
        elif 'delete' in name_lower:
            return 'delete_statement'
        elif 'create' in name_lower:
            return 'create_statement'
        elif 'drop' in name_lower:
            return 'drop_statement'
        elif 'expr' in name_lower or 'expression' in name_lower:
            return 'expression'
        else:
            return 'other'

    def _extract_operators(self):
        """Extract operator precedence information from lexer rules"""
        # Standard SQL operator precedence (higher number = higher precedence)
        operator_precedence_map = {
            # Arithmetic (highest)
            'STAR': (12, 'left'),
            'MULT_OPERATOR': (12, 'left'),
            'SLASH': (12, 'left'),
            'DIV_OPERATOR': (12, 'left'),
            'PERCENT': (12, 'left'),
            'MOD_OPERATOR': (12, 'left'),
            'DIVIDE': (12, 'left'),

            'PLUS': (11, 'left'),
            'PLUS_OPERATOR': (11, 'left'),
            'MINUS': (11, 'left'),
            'MINUS_OPERATOR': (11, 'left'),

            # Bitwise
            'SHIFT_LEFT': (10, 'left'),
            'SHIFT_RIGHT': (10, 'left'),
            'AMPERSAND': (9, 'left'),
            'BITWISE_AND_OPERATOR': (9, 'left'),
            'CARET': (8, 'left'),
            'BITWISE_XOR_OPERATOR': (8, 'left'),
            'PIPE': (7, 'left'),
            'BITWISE_OR_OPERATOR': (7, 'left'),

            # Comparison
            'EQ': (6, 'left'),
            'EQUAL_OPERATOR': (6, 'left'),
            'NEQ': (6, 'left'),
            'NOT_EQUAL_OPERATOR': (6, 'left'),
            'NOT_EQUAL2_OPERATOR': (6, 'left'),
            'LT': (6, 'left'),
            'LESS_THAN_OPERATOR': (6, 'left'),
            'LTE': (6, 'left'),
            'LESS_OR_EQUAL_OPERATOR': (6, 'left'),
            'GT': (6, 'left'),
            'GREATER_THAN_OPERATOR': (6, 'left'),
            'GTE': (6, 'left'),
            'GREATER_OR_EQUAL_OPERATOR': (6, 'left'),

            # Logical (lowest)
            'NOT': (5, 'right'),
            'LOGICAL_NOT_OPERATOR': (5, 'right'),
            'AND': (4, 'left'),
            'LOGICAL_AND_OPERATOR': (4, 'left'),
            'OR': (3, 'left'),
            'LOGICAL_OR_OPERATOR': (3, 'left'),

            # String concatenation
            'CONCAT': (10, 'left'),
            'CONCAT_OPERATOR': (10, 'left'),
        }

        # Scan lexer tokens for operators
        for token_name in self.lexer_tokens:
            # Check if it's in our map (case-insensitive)
            token_upper = token_name.upper()

            # Check exact match
            if token_upper in operator_precedence_map:
                prec, assoc = operator_precedence_map[token_upper]
                self.operators.append(OperatorInfo(
                    token=token_name,
                    precedence=prec,
                    associativity=assoc
                ))
            # Check if it ends with _OPERATOR
            elif token_upper.endswith('_OPERATOR'):
                # Try to infer from name
                base_name = token_upper.replace('_OPERATOR', '')
                if base_name in operator_precedence_map:
                    prec, assoc = operator_precedence_map[base_name]
                    self.operators.append(OperatorInfo(
                        token=token_name,
                        precedence=prec,
                        associativity=assoc
                    ))


def extract_from_file(grammar_file: Path, dialect: str, lexer_file: Optional[Path] = None) -> GrammarData:
    """Extract grammar data from ANTLR grammar file(s)"""
    print(f"\n[OK] Loading grammar from {grammar_file}")
    grammar = parse_grammar_file(grammar_file)

    # Also load lexer grammar if provided
    if lexer_file and lexer_file.exists():
        print(f"[OK] Loading lexer grammar from {lexer_file}")
        lexer_grammar = parse_grammar_file(lexer_file)
        # Merge lexer rules into main grammar
        grammar.rules.update(lexer_grammar.rules)

    extractor = GrammarDataExtractor(grammar, dialect)
    return extractor.extract()


def save_to_json(data: GrammarData, output_file: Path):
    """Save extracted data to JSON file"""
    output_file.parent.mkdir(parents=True, exist_ok=True)

    # Convert dataclass to dict
    data_dict = asdict(data)

    with open(output_file, 'w', encoding='utf-8') as f:
        json.dump(data_dict, f, indent=2)

    print(f"[OK] Saved grammar data to {output_file}")


def main():
    import argparse

    parser = argparse.ArgumentParser(description='Extract grammar data from ANTLR grammar')
    parser.add_argument('grammar_file', type=Path, help='Path to ANTLR .g4 file')
    parser.add_argument('--dialect', required=True, help='SQL dialect name')
    parser.add_argument('--output', type=Path, help='Output JSON file')

    args = parser.parse_args()

    # Extract data
    data = extract_from_file(args.grammar_file, args.dialect)

    # Save to JSON
    if args.output:
        save_to_json(data, args.output)
    else:
        # Print to stdout
        import json
        print(json.dumps(asdict(data), indent=2))


if __name__ == '__main__':
    main()
