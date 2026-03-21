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
        # Simple heuristic: if rule definition contains a string literal, it's a keyword
        definition_str = str(rule.definition)

        # Look for patterns like 'SELECT' or "SELECT"
        if "'" in definition_str:
            # Extract string between single quotes
            parts = definition_str.split("'")
            if len(parts) >= 2:
                keyword = parts[1].upper()
                # Filter out non-keywords (operators, etc.)
                if keyword.isalpha() or '_' in keyword:
                    return keyword

        return None

    def _extract_token_sequences(self):
        """Extract token sequences from parser rules"""
        for name, rule in self.grammar.rules.items():
            if rule.type.value == 'parser':
                # Extract sequences from this rule
                sequences = self._extract_sequences_from_rule(name, rule)
                self.token_sequences.extend(sequences)

    def _extract_sequences_from_rule(self, rule_name: str, rule: Rule) -> List[TokenSequence]:
        """Extract token sequences from a single parser rule"""
        sequences = []

        # Convert rule definition to token sequences
        # This is a simplified extraction - real implementation would need full ANTLR parsing
        tokens = self._flatten_elements(rule.definition)

        if tokens:
            sequences.append(TokenSequence(
                name=rule_name,
                tokens=tokens,
                optional_flags=[False] * len(tokens),  # Simplified - would need real optionality detection
                pattern_type=self._categorize_rule(rule_name)
            ))

        return sequences

    def _flatten_elements(self, element: Element) -> List[str]:
        """Flatten element tree into list of token names"""
        tokens = []

        if hasattr(element, 'text'):
            # Terminal - add as token
            token_name = str(element.text).strip("'\"")
            if token_name:
                tokens.append(token_name)

        if hasattr(element, 'elements') and element.elements:
            # Non-terminal with children
            for child in element.elements:
                tokens.extend(self._flatten_elements(child))

        return tokens

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
        """Extract operator precedence information"""
        # This is a heuristic - ANTLR doesn't always explicitly specify precedence
        # We use common SQL operator precedence rules

        operator_precedence_map = {
            # Arithmetic
            'STAR': (10, 'left'),
            'DIVIDE': (10, 'left'),
            'MOD': (10, 'left'),
            'PLUS': (9, 'left'),
            'MINUS': (9, 'left'),

            # Comparison
            'EQ': (7, 'left'),
            'NEQ': (7, 'left'),
            'LT': (7, 'left'),
            'LTE': (7, 'left'),
            'GT': (7, 'left'),
            'GTE': (7, 'left'),

            # Logical
            'NOT': (5, 'right'),
            'AND': (4, 'left'),
            'OR': (3, 'left'),
        }

        # Check which operators exist in this grammar
        for token_name in self.lexer_tokens:
            token_upper = token_name.upper()
            if token_upper in operator_precedence_map:
                prec, assoc = operator_precedence_map[token_upper]
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
