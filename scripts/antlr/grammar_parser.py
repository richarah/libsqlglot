#!/usr/bin/env python3
"""
ANTLR Grammar Parser - Phase 1 of Grammar Transpiler

Parses ANTLR .g4 grammar files into a structured AST that can be analyzed and transformed.

Handles:
- Parser rules (lowercase)
- Lexer rules (uppercase)
- Alternatives (|)
- Quantifiers (*, +, ?)
- Grouping ((...))
- Labels
- ANTLR-specific features (fragments, modes, etc.)

Output: Structured Grammar AST
"""

import re
from dataclasses import dataclass, field
from typing import List, Optional, Dict, Set
from pathlib import Path
from enum import Enum


class RuleType(Enum):
    """Type of grammar rule"""
    PARSER = "parser"  # Lowercase rule names
    LEXER = "lexer"    # Uppercase rule names
    FRAGMENT = "fragment"  # Lexer fragment


class Quantifier(Enum):
    """Quantifier types in ANTLR"""
    NONE = ""
    OPTIONAL = "?"    # 0 or 1
    STAR = "*"        # 0 or more
    PLUS = "+"        # 1 or more


@dataclass
class Element:
    """Base class for grammar elements"""
    pass


@dataclass
class Terminal(Element):
    """Terminal symbol (keyword literal or token reference)"""
    value: str
    is_string_literal: bool  # True for 'SELECT', False for SELECT_SYMBOL


@dataclass
class NonTerminal(Element):
    """Non-terminal symbol (rule reference)"""
    name: str


@dataclass
class Sequence(Element):
    """Sequence of elements"""
    elements: List[Element] = field(default_factory=list)


@dataclass
class Alternative(Element):
    """Multiple alternatives (|)"""
    alternatives: List[Element] = field(default_factory=list)


@dataclass
class Quantified(Element):
    """Element with quantifier (*, +, ?)"""
    element: Element
    quantifier: Quantifier


@dataclass
class Group(Element):
    """Grouped elements (...)"""
    content: Element


@dataclass
class Rule:
    """Grammar rule"""
    name: str
    type: RuleType
    definition: Element
    labels: Dict[str, str] = field(default_factory=dict)  # Label assignments
    actions: List[str] = field(default_factory=list)  # Embedded actions


@dataclass
class Grammar:
    """Complete grammar"""
    name: str
    type: str  # 'parser', 'lexer', or 'combined'
    rules: Dict[str, Rule] = field(default_factory=dict)
    options: Dict[str, str] = field(default_factory=dict)
    imports: List[str] = field(default_factory=list)


class GrammarParser:
    """Parser for ANTLR .g4 grammar files"""

    # Regex patterns
    RULE_PATTERN = re.compile(
        r'^([a-zA-Z_][a-zA-Z0-9_]*)\s*:\s*(.+?)\s*;',
        re.MULTILINE | re.DOTALL
    )

    GRAMMAR_HEADER = re.compile(r'^\s*(parser|lexer)?\s*grammar\s+([a-zA-Z_][a-zA-Z0-9_]*)\s*;')
    OPTIONS_PATTERN = re.compile(r'options\s*\{([^}]+)\}', re.DOTALL)
    IMPORT_PATTERN = re.compile(r'import\s+([^;]+);')

    def __init__(self, content: str, filename: str = ""):
        self.content = content
        self.filename = filename
        self.grammar = Grammar(name="", type="combined")

    def parse(self) -> Grammar:
        """Parse the grammar file"""
        # Remove comments
        content = self._remove_comments(self.content)

        # Parse header
        self._parse_header(content)

        # Parse options
        self._parse_options(content)

        # Parse imports
        self._parse_imports(content)

        # Parse rules
        self._parse_rules(content)

        return self.grammar

    def _remove_comments(self, content: str) -> str:
        """Remove single-line and multi-line comments"""
        # Remove multi-line comments
        content = re.sub(r'/\*.*?\*/', '', content, flags=re.DOTALL)
        # Remove single-line comments
        content = re.sub(r'//.*?$', '', content, flags=re.MULTILINE)
        return content

    def _parse_header(self, content: str):
        """Parse grammar header"""
        match = self.GRAMMAR_HEADER.search(content)
        if match:
            grammar_type = match.group(1) or "combined"
            grammar_name = match.group(2)
            self.grammar.name = grammar_name
            self.grammar.type = grammar_type

    def _parse_options(self, content: str):
        """Parse options block"""
        match = self.OPTIONS_PATTERN.search(content)
        if match:
            options_text = match.group(1)
            for line in options_text.split(';'):
                line = line.strip()
                if '=' in line:
                    key, value = line.split('=', 1)
                    self.grammar.options[key.strip()] = value.strip()

    def _parse_imports(self, content: str):
        """Parse import statements"""
        for match in self.IMPORT_PATTERN.finditer(content):
            imports = match.group(1)
            self.grammar.imports.extend([i.strip() for i in imports.split(',')])

    def _parse_rules(self, content: str):
        """Parse all grammar rules"""
        for match in self.RULE_PATTERN.finditer(content):
            rule_name = match.group(1)
            rule_body = match.group(2)

            # Determine rule type
            if rule_name[0].isupper():
                rule_type = RuleType.LEXER
            else:
                rule_type = RuleType.PARSER

            # Check for fragment
            if rule_body.strip().startswith('fragment'):
                rule_type = RuleType.FRAGMENT
                rule_body = rule_body.replace('fragment', '', 1).strip()

            # Parse rule definition
            try:
                definition = self._parse_rule_body(rule_body)
                rule = Rule(name=rule_name, type=rule_type, definition=definition)
                self.grammar.rules[rule_name] = rule
            except Exception as e:
                # Log parsing error but continue
                print(f"Warning: Failed to parse rule '{rule_name}': {e}")

    def _parse_rule_body(self, body: str) -> Element:
        """Parse the body of a rule"""
        body = body.strip()

        # Handle alternatives (|)
        if '|' in body and not self._is_within_parens(body, '|'):
            parts = self._split_alternatives(body)
            alternatives = [self._parse_sequence(part) for part in parts]
            return Alternative(alternatives=alternatives)
        else:
            return self._parse_sequence(body)

    def _parse_sequence(self, text: str) -> Element:
        """Parse a sequence of elements"""
        elements = []
        i = 0
        text = text.strip()

        while i < len(text):
            # Skip whitespace
            while i < len(text) and text[i].isspace():
                i += 1

            if i >= len(text):
                break

            # Parse element
            if text[i] == '(':
                # Grouped expression
                end = self._find_matching_paren(text, i)
                group_content = text[i+1:end]
                element = self._parse_rule_body(group_content)
                element = Group(content=element)
                i = end + 1
            elif text[i] == "'":
                # String literal
                end = text.index("'", i + 1)
                literal = text[i+1:end]
                element = Terminal(value=literal, is_string_literal=True)
                i = end + 1
            elif text[i].isalnum() or text[i] == '_':
                # Rule or token reference
                match = re.match(r'[a-zA-Z_][a-zA-Z0-9_]*', text[i:])
                if match:
                    name = match.group(0)
                    if name[0].isupper():
                        element = Terminal(value=name, is_string_literal=False)
                    else:
                        element = NonTerminal(name=name)
                    i += len(name)
                else:
                    i += 1
                    continue
            else:
                # Unknown character, skip
                i += 1
                continue

            # Check for quantifier
            if i < len(text) and text[i] in '*+?':
                q = Quantifier.STAR if text[i] == '*' else \
                    Quantifier.PLUS if text[i] == '+' else Quantifier.OPTIONAL
                element = Quantified(element=element, quantifier=q)
                i += 1

            elements.append(element)

        if len(elements) == 1:
            return elements[0]
        return Sequence(elements=elements)

    def _is_within_parens(self, text: str, char: str) -> bool:
        """Check if all occurrences of char are within parentheses"""
        depth = 0
        for i, c in enumerate(text):
            if c == '(':
                depth += 1
            elif c == ')':
                depth -= 1
            elif c == char and depth == 0:
                return False
        return True

    def _split_alternatives(self, text: str) -> List[str]:
        """Split by | at depth 0 (not within parentheses)"""
        parts = []
        current = []
        depth = 0

        for char in text:
            if char == '(':
                depth += 1
                current.append(char)
            elif char == ')':
                depth -= 1
                current.append(char)
            elif char == '|' and depth == 0:
                parts.append(''.join(current).strip())
                current = []
            else:
                current.append(char)

        if current:
            parts.append(''.join(current).strip())

        return parts

    def _find_matching_paren(self, text: str, start: int) -> int:
        """Find the matching closing parenthesis"""
        depth = 1
        i = start + 1
        while i < len(text) and depth > 0:
            if text[i] == '(':
                depth += 1
            elif text[i] == ')':
                depth -= 1
            i += 1
        return i - 1


def parse_grammar_file(filepath: Path) -> Grammar:
    """Parse a .g4 grammar file"""
    content = filepath.read_text(encoding='utf-8', errors='ignore')
    parser = GrammarParser(content, str(filepath))
    return parser.parse()


# Testing / CLI interface
if __name__ == '__main__':
    import sys
    import json

    if len(sys.argv) < 2:
        print("Usage: python grammar_parser.py <grammar.g4>")
        sys.exit(1)

    filepath = Path(sys.argv[1])
    grammar = parse_grammar_file(filepath)

    print(f"Grammar: {grammar.name}")
    print(f"Type: {grammar.type}")
    print(f"Rules: {len(grammar.rules)}")
    print(f"Parser rules: {sum(1 for r in grammar.rules.values() if r.type == RuleType.PARSER)}")
    print(f"Lexer rules: {sum(1 for r in grammar.rules.values() if r.type == RuleType.LEXER)}")

    # Show sample rules
    print("\nSample parser rules:")
    for i, (name, rule) in enumerate(grammar.rules.items()):
        if rule.type == RuleType.PARSER and i < 5:
            print(f"  - {name}")
