#!/usr/bin/env python3
"""
ANTLR to Lemon Grammar Converter

Converts ANTLR .g4 grammar files to Lemon .y format for LALR(1) parsing.
Focuses on COMPLEX rules that benefit from Lemon's left-recursion handling.

Usage:
    python antlr_to_lemon.py <grammar.g4> --output <grammar.y>
    python antlr_to_lemon.py --grammar mysql --rules "expression,selectStatement"
"""

import argparse
import re
from pathlib import Path
from typing import Dict, List, Set, Tuple, Optional
from dataclasses import dataclass

from grammar_parser import (
    Grammar, Rule, Element, RuleType,
    Terminal, NonTerminal, Sequence, Alternative, Quantified, Group,
    Quantifier, parse_grammar_file
)
from complexity_analyzer import ComplexityAnalyzer, Complexity, RuleAnalysis


@dataclass
class LemonRule:
    """A single Lemon grammar rule production"""
    lhs: str                    # Left-hand side (rule name)
    rhs: List[str]             # Right-hand side symbols
    action_code: str           # C action code
    precedence: Optional[str]  # Precedence token (for operators)


class AntlrToLemonConverter:
    """Convert ANTLR grammars to Lemon format"""

    def __init__(self, grammar: Grammar, analysis: Dict[str, RuleAnalysis]):
        self.grammar = grammar
        self.analysis = analysis
        self.lemon_rules: List[LemonRule] = []

        # Track tokens and types
        self.tokens: Set[str] = set()
        self.nonterminals: Set[str] = set()

        # Precedence tracking
        self.precedence_levels: List[Tuple[str, List[str]]] = []  # (assoc, tokens)

    def convert_all(self, rules_filter: Optional[List[str]] = None) -> str:
        """Convert all rules to Lemon format"""
        # Filter to COMPLEX rules if specified
        rules_to_convert = []

        for name, rule in self.grammar.rules.items():
            if rule.type != RuleType.PARSER:
                continue

            # Only convert if in filter or if COMPLEX
            if rules_filter and name not in rules_filter:
                continue

            if name in self.analysis:
                analysis = self.analysis[name]
                # Convert COMPLEX and MEDIUM rules
                if analysis.complexity in (Complexity.COMPLEX, Complexity.MEDIUM):
                    rules_to_convert.append((name, rule, analysis))

        # Convert each rule
        for name, rule, analysis in rules_to_convert:
            self._convert_rule(rule)

        # Generate Lemon grammar file
        return self._generate_lemon_grammar()

    def _convert_rule(self, rule: Rule):
        """Convert a single ANTLR rule to Lemon productions"""
        self.nonterminals.add(rule.name)

        # Convert rule definition to Lemon productions
        productions = self._element_to_productions(rule.name, rule.definition)

        for prod in productions:
            self.lemon_rules.append(prod)

    def _element_to_productions(self, lhs: str, element: Element) -> List[LemonRule]:
        """Convert an ANTLR element to Lemon productions"""
        productions = []

        if isinstance(element, Alternative):
            # Each alternative becomes a separate production
            for i, alt in enumerate(element.alternatives):
                alt_prods = self._element_to_productions(lhs, alt)
                productions.extend(alt_prods)

        elif isinstance(element, Sequence):
            # Sequence becomes single production
            rhs = []
            for e in element.elements:
                symbols = self._element_to_symbols(e)
                rhs.extend(symbols)

            action = self._generate_action_code(lhs, rhs)
            productions.append(LemonRule(lhs, rhs, action, None))

        elif isinstance(element, Terminal):
            # Single terminal
            token = self._normalize_token(element.value)
            self.tokens.add(token)
            action = self._generate_action_code(lhs, [token])
            productions.append(LemonRule(lhs, [token], action, None))

        elif isinstance(element, NonTerminal):
            # Single nonterminal
            self.nonterminals.add(element.name)
            action = self._generate_action_code(lhs, [element.name])
            productions.append(LemonRule(lhs, [element.name], action, None))

        elif isinstance(element, Quantified):
            # Quantifiers need special handling
            prods = self._convert_quantified(lhs, element)
            productions.extend(prods)

        elif isinstance(element, Group):
            # Unwrap group
            prods = self._element_to_productions(lhs, element.content)
            productions.extend(prods)

        else:
            # Fallback: empty production
            productions.append(LemonRule(lhs, [], "{ /* TODO */ }", None))

        return productions

    def _element_to_symbols(self, element: Element) -> List[str]:
        """Convert element to list of symbols (for RHS)"""
        if isinstance(element, Terminal):
            token = self._normalize_token(element.value)
            self.tokens.add(token)
            return [token]

        elif isinstance(element, NonTerminal):
            self.nonterminals.add(element.name)
            return [element.name]

        elif isinstance(element, Sequence):
            symbols = []
            for e in element.elements:
                symbols.extend(self._element_to_symbols(e))
            return symbols

        elif isinstance(element, Quantified):
            # For quantified in sequence, create helper rule
            helper_name = self._create_quantified_helper(element)
            return [helper_name]

        elif isinstance(element, Group):
            return self._element_to_symbols(element.content)

        return []

    def _convert_quantified(self, lhs: str, element: Quantified) -> List[LemonRule]:
        """Convert quantified element (*, +, ?) to Lemon rules"""
        productions = []
        inner_symbols = self._element_to_symbols(element.element)

        if element.quantifier == Quantifier.OPTIONAL:
            # A? → A ::= inner. | A ::= . (empty)
            action = self._generate_action_code(lhs, inner_symbols)
            productions.append(LemonRule(lhs, inner_symbols, action, None))
            productions.append(LemonRule(lhs, [], "{ /* empty */ }", None))

        elif element.quantifier == Quantifier.STAR:
            # A* → A ::= A inner. | A ::= . (empty)
            # Right-recursive for LALR efficiency
            action_recursive = self._generate_list_action(lhs, inner_symbols, is_continuation=True)
            productions.append(LemonRule(lhs, [lhs] + inner_symbols, action_recursive, None))
            productions.append(LemonRule(lhs, [], "{ /* empty list */ }", None))

        elif element.quantifier == Quantifier.PLUS:
            # A+ → A ::= inner. | A ::= A inner.
            action_first = self._generate_list_action(lhs, inner_symbols, is_continuation=False)
            action_recursive = self._generate_list_action(lhs, inner_symbols, is_continuation=True)
            productions.append(LemonRule(lhs, inner_symbols, action_first, None))
            productions.append(LemonRule(lhs, [lhs] + inner_symbols, action_recursive, None))

        return productions

    def _create_quantified_helper(self, element: Quantified) -> str:
        """Create helper rule for quantified element in sequence"""
        # Generate unique name based on inner element
        inner_name = self._get_element_name(element.element)

        if element.quantifier == Quantifier.OPTIONAL:
            helper_name = f"{inner_name}_opt"
        elif element.quantifier == Quantifier.STAR:
            helper_name = f"{inner_name}_list"
        elif element.quantifier == Quantifier.PLUS:
            helper_name = f"{inner_name}_list1"
        else:
            helper_name = f"{inner_name}_q"

        # Add helper rule if not exists
        if helper_name not in self.nonterminals:
            self.nonterminals.add(helper_name)
            prods = self._convert_quantified(helper_name, element)
            self.lemon_rules.extend(prods)

        return helper_name

    def _get_element_name(self, element: Element) -> str:
        """Get name representation of element"""
        if isinstance(element, Terminal):
            return self._normalize_token(element.value).lower()
        elif isinstance(element, NonTerminal):
            return element.name
        elif isinstance(element, Sequence) and element.elements:
            return self._get_element_name(element.elements[0])
        elif isinstance(element, Group):
            return self._get_element_name(element.content)
        return "elem"

    def _normalize_token(self, token: str) -> str:
        """Normalize ANTLR token to Lemon token"""
        # Remove _SYMBOL, _KW suffixes
        token = token.replace('_SYMBOL', '')
        token = token.replace('_KW', '')
        token = token.replace('_KEYWORD', '')

        # Uppercase tokens
        return token.upper()

    def _generate_action_code(self, lhs: str, rhs: List[str]) -> str:
        """Generate C action code for production"""
        if not rhs:
            return "{ A = nullptr; }"

        # Infer expression type from lhs
        expr_type = self._infer_expression_type(lhs)

        if len(rhs) == 1:
            # Single symbol: pass through
            return "{ A = B; }"

        # Multiple symbols: create expression
        return f"{{ A = arena_.create<{expr_type}>(); /* TODO: populate fields */ }}"

    def _generate_list_action(self, lhs: str, inner: List[str], is_continuation: bool) -> str:
        """Generate action code for list production"""
        if is_continuation:
            # Append to existing list
            return "{ A = append_list(A, B); }"
        else:
            # Create new list
            return "{ A = create_list(B); }"

    def _infer_expression_type(self, rule_name: str) -> str:
        """Infer C++ Expression type from rule name"""
        name_lower = rule_name.lower()

        # Common patterns
        if 'statement' in name_lower or 'stmt' in name_lower:
            return "Expression"
        elif 'expr' in name_lower:
            return "Expression"
        elif 'select' in name_lower:
            return "SelectStmt"
        elif 'create' in name_lower:
            return "CreateStmt"
        elif 'insert' in name_lower:
            return "InsertStmt"
        elif 'update' in name_lower:
            return "UpdateStmt"
        elif 'delete' in name_lower:
            return "DeleteStmt"
        else:
            return "Expression"

    def _extract_precedence(self):
        """Extract operator precedence from grammar patterns"""
        # Common SQL operator precedence (lowest to highest)
        self.precedence_levels = [
            ('left', ['OR']),
            ('left', ['AND']),
            ('left', ['EQUALS', 'NOT_EQUALS', 'LESS', 'LESS_EQUALS', 'GREATER', 'GREATER_EQUALS']),
            ('left', ['PLUS', 'MINUS']),
            ('left', ['TIMES', 'DIVIDE', 'MODULO']),
            ('right', ['NOT', 'UNARY_MINUS']),
        ]

    def _generate_lemon_grammar(self) -> str:
        """Generate complete Lemon grammar file"""
        lines = []

        # Header comment
        lines.extend([
            "// Auto-generated Lemon grammar from ANTLR",
            f"// Source: {self.grammar.name}",
            "// DO NOT EDIT MANUALLY",
            "",
        ])

        # Include directives
        lines.extend([
            "%include {",
            "    #include <cassert>",
            "    #include <cstdio>",
            '    #include "expression.h"',
            '    #include "arena.h"',
            "}",
            "",
        ])

        # Token type declarations
        lines.extend([
            "%token_type {Token*}",
            "%default_type {Expression*}",
            "",
        ])

        # Declare tokens
        lines.append("// Terminal symbols (tokens)")
        for token in sorted(self.tokens):
            lines.append(f"%token {token}.")
        lines.append("")

        # Precedence declarations
        self._extract_precedence()
        lines.append("// Operator precedence (lowest to highest)")
        for assoc, tokens in self.precedence_levels:
            tokens_str = ' '.join(tokens)
            lines.append(f"%{assoc} {tokens_str}.")
        lines.append("")

        # Syntax error handler
        lines.extend([
            "%syntax_error {",
            '    fprintf(stderr, "Syntax error\\n");',
            "}",
            "",
        ])

        # Grammar rules
        lines.append("// Grammar productions")
        lines.append("")

        # Add start symbol if needed
        if self.lemon_rules:
            # Use first nonterminal as start, or create a wrapper
            first_rule_lhs = self.lemon_rules[0].lhs
            lines.append("// Start symbol")
            lines.append(f"%start_symbol program")
            lines.append("")
            lines.append(f"program(A) ::= {first_rule_lhs}(B). {{ A = B; }}")
            lines.append("")

        for rule in self.lemon_rules:
            # Format: lhs(A) ::= rhs1(B) rhs2(C) rhs3(D). { action }

            # Generate variable names: A, B, C, D, ...
            lhs_var = "A"
            rhs_vars = [chr(ord('B') + i) for i in range(len(rule.rhs))]

            # Build production string
            lhs_str = f"{rule.lhs}({lhs_var})"

            if rule.rhs:
                rhs_parts = [f"{sym}({var})" for sym, var in zip(rule.rhs, rhs_vars)]
                rhs_str = " ".join(rhs_parts)
            else:
                rhs_str = ""

            precedence_str = f" [{rule.precedence}]" if rule.precedence else ""

            # Emit production
            lines.append(f"{lhs_str} ::= {rhs_str}{precedence_str}. {rule.action_code}")

        lines.append("")

        return "\n".join(lines)


# CLI interface
def main():
    parser = argparse.ArgumentParser(
        description='Convert ANTLR grammar to Lemon format',
        formatter_class=argparse.RawDescriptionHelpFormatter,
        epilog="""
Examples:
  # Convert specific rules to Lemon
  python antlr_to_lemon.py grammar.g4 --rules "expression,selectStatement"

  # Convert all COMPLEX rules
  python antlr_to_lemon.py grammar.g4 --complexity complex --output grammar.y

  # Convert specific dialect
  python antlr_to_lemon.py --grammar mysql --output mysql_expr.y
        """
    )

    parser.add_argument('grammar_file', type=Path, nargs='?', help='Path to ANTLR .g4 file')
    parser.add_argument('--grammar', type=str, help='SQL dialect name (alternative to grammar_file)')
    parser.add_argument('--output', '-o', type=Path, help='Output Lemon .y file')
    parser.add_argument('--rules', type=str, help='Comma-separated list of rules to convert')
    parser.add_argument('--complexity', choices=['medium', 'complex', 'all'],
                       default='complex', help='Convert only rules of specified complexity')
    parser.add_argument(
        '--grammars',
        type=Path,
        default=Path('external/grammars-v4/antlr/antlr4/examples/grammars-v4'),
        help='Path to grammars-v4 directory'
    )

    args = parser.parse_args()

    # Determine grammar file
    if args.grammar:
        # Find grammar file for dialect
        from transpile import GrammarTranspiler
        transpiler = GrammarTranspiler(args.grammars)
        grammar_file = transpiler.find_grammar_file(args.grammar)
    elif args.grammar_file:
        grammar_file = args.grammar_file
    else:
        parser.error("Either grammar_file or --grammar must be specified")

    print(f"Converting ANTLR grammar: {grammar_file}")

    # Parse grammar
    grammar = parse_grammar_file(grammar_file)

    # Analyze complexity
    print("Analyzing rule complexity...")
    analyzer = ComplexityAnalyzer(grammar)
    analysis = analyzer.analyze_all()

    # Filter by complexity
    if args.complexity == 'complex':
        analysis = {name: a for name, a in analysis.items() if a.complexity == Complexity.COMPLEX}
    elif args.complexity == 'medium':
        analysis = {name: a for name, a in analysis.items() if a.complexity in (Complexity.MEDIUM, Complexity.COMPLEX)}

    print(f"  Found {len(analysis)} rules to convert")

    # Filter by rules
    rules_filter = None
    if args.rules:
        rules_filter = [r.strip() for r in args.rules.split(',')]
        analysis = {name: a for name, a in analysis.items() if name in rules_filter}
        print(f"  Filtered to {len(analysis)} specified rules")

    # Convert to Lemon
    print("Converting to Lemon format...")
    converter = AntlrToLemonConverter(grammar, analysis)
    lemon_grammar = converter.convert_all(rules_filter)

    # Write output
    if args.output:
        args.output.parent.mkdir(parents=True, exist_ok=True)
        args.output.write_text(lemon_grammar, encoding='utf-8')
        print(f"✅ Lemon grammar written to: {args.output}")
        print(f"   {len(converter.lemon_rules)} productions generated")
        print(f"   {len(converter.tokens)} tokens, {len(converter.nonterminals)} nonterminals")
    else:
        print(lemon_grammar)

    # Next steps
    print("\n💡 Next steps:")
    print(f"  1. Compile with Lemon: ./external/lemon/lemon {args.output or 'grammar.y'}")
    print(f"  2. Review generated .c file")
    print(f"  3. Wrap with C++ adapter (lemon_wrapper.py)")


if __name__ == '__main__':
    main()
