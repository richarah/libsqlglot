#!/usr/bin/env python3
"""
Unified Grammar Generator

Takes extracted grammar data from all SQL dialects and generates unified C++ headers
with static lookup tables and data structures for libsqlglot's hand-written parser.

Output headers:
- grammar_patterns.h - Token sequence patterns per dialect
- operator_precedence.h - Operator precedence tables
- keywords_generated.h - Keyword lookup tables (updated)
"""

import json
from pathlib import Path
from typing import List, Dict, Set, Any
from dataclasses import dataclass
from collections import defaultdict

# Import token mapping
try:
    from token_mapping import map_antlr_token, map_keyword
except ImportError:
    # Fallback if running from different directory
    import sys
    sys.path.insert(0, str(Path(__file__).parent))
    from token_mapping import map_antlr_token, map_keyword


@dataclass
class UnifiedGrammarData:
    """Unified data from all dialects"""
    all_keywords: Set[str]
    dialect_keywords: Dict[str, Set[str]]
    operators: List[Dict[str, Any]]
    token_sequences: List[Dict[str, Any]]
    dialects: List[str]


class UnifiedGrammarGenerator:
    """Generate unified C++ headers from extracted grammar data"""

    def __init__(self):
        self.unified_data = UnifiedGrammarData(
            all_keywords=set(),
            dialect_keywords={},
            operators=[],
            token_sequences=[],
            dialects=[]
        )

    def add_dialect_data(self, data_file: Path):
        """Add data from a dialect JSON file"""
        with open(data_file, 'r', encoding='utf-8') as f:
            data = json.load(f)

        dialect = data['dialect']
        print(f"[OK] Adding data for {dialect} dialect")

        self.unified_data.dialects.append(dialect)

        # Merge keywords
        dialect_keywords = set(data.get('keywords', []))
        self.unified_data.all_keywords.update(dialect_keywords)
        self.unified_data.dialect_keywords[dialect] = dialect_keywords

        # Add operators
        for op in data.get('operators', []):
            op['dialect'] = dialect
            self.unified_data.operators.append(op)

        # Add token sequences
        for seq in data.get('token_sequences', []):
            seq['dialect'] = dialect
            self.unified_data.token_sequences.append(seq)

    def generate_grammar_patterns_h(self, output_file: Path):
        """Generate grammar_patterns.h with token sequence patterns"""
        print(f"\n[OK] Generating grammar_patterns.h...")

        lines = []
        lines.append("#pragma once")
        lines.append("")
        lines.append("// Auto-generated grammar patterns from ANTLR grammars")
        lines.append("// DO NOT EDIT MANUALLY")
        lines.append("//")
        lines.append("// This file contains token sequence patterns extracted from SQL dialect grammars.")
        lines.append("// These patterns are used by libsqlglot's hand-written parser for validation")
        lines.append("// and syntax checking.")
        lines.append("")
        lines.append("#include \"tokens.h\"")
        lines.append("#include \"dialects.h\"")
        lines.append("#include <array>")
        lines.append("#include <cstdint>")
        lines.append("")
        lines.append("namespace libsqlglot {")
        lines.append("namespace grammar {")
        lines.append("")

        # Generate pattern structure
        lines.append("/// Grammar pattern: a sequence of tokens representing a valid construct")
        lines.append("struct Pattern {")
        lines.append("    const char* name;")
        lines.append("    Dialect dialect;")
        lines.append("    const TokenType* tokens;")
        lines.append("    uint8_t length;")
        lines.append("    const char* pattern_type;")
        lines.append("};")
        lines.append("")

        # Generate token sequences by pattern type
        pattern_groups = defaultdict(list)
        for seq in self.unified_data.token_sequences:
            pattern_type = seq.get('pattern_type', 'other')
            pattern_groups[pattern_type].append(seq)

        # Generate constexpr arrays for each pattern group
        for pattern_type, sequences in sorted(pattern_groups.items()):
            lines.append(f"// {pattern_type.upper()} patterns")
            lines.append("")

            for i, seq in enumerate(sequences):
                dialect = seq['dialect']
                name = seq['name']
                tokens = seq['tokens']

                # Generate token array
                array_name = f"{dialect}_{name}_tokens_{i}"
                lines.append(f"constexpr TokenType {array_name}[] = {{")

                token_strs = []
                for token in tokens:
                    # Convert token name to TokenType enum
                    token_enum = self._token_to_enum(token)
                    token_strs.append(f"    TokenType::{token_enum}")

                lines.append(",\n".join(token_strs))
                lines.append("};")
                lines.append("")

        # Generate unified pattern table
        lines.append("// Unified pattern table")
        lines.append("constexpr Pattern all_patterns[] = {")

        pattern_entries = []
        for pattern_type, sequences in sorted(pattern_groups.items()):
            for i, seq in enumerate(sequences):
                dialect = seq['dialect']
                name = seq['name']
                tokens = seq['tokens']
                array_name = f"{dialect}_{name}_tokens_{i}"

                dialect_enum = self._dialect_to_enum(dialect)

                entry = f'    {{"{name}", Dialect::{dialect_enum}, {array_name}, {len(tokens)}, "{pattern_type}"}}'
                pattern_entries.append(entry)

        lines.append(",\n".join(pattern_entries))
        lines.append("};")
        lines.append("")

        lines.append(f"constexpr size_t pattern_count = {len(self.unified_data.token_sequences)};")
        lines.append("")

        lines.append("}  // namespace grammar")
        lines.append("}  // namespace libsqlglot")
        lines.append("")

        # Write to file
        output_file.parent.mkdir(parents=True, exist_ok=True)
        output_file.write_text('\n'.join(lines), encoding='utf-8')

        print(f"[SUCCESS] Generated {output_file}")
        print(f"[INFO] Total patterns: {len(self.unified_data.token_sequences)}")

    def generate_operator_precedence_h(self, output_file: Path):
        """Generate operator_precedence.h with operator precedence tables"""
        print(f"\n[OK] Generating operator_precedence.h...")

        lines = []
        lines.append("#pragma once")
        lines.append("")
        lines.append("// Auto-generated operator precedence from ANTLR grammars")
        lines.append("// DO NOT EDIT MANUALLY")
        lines.append("")
        lines.append("#include \"tokens.h\"")
        lines.append("#include <cstdint>")
        lines.append("")
        lines.append("namespace libsqlglot {")
        lines.append("")

        lines.append("/// Operator associativity")
        lines.append("enum class Associativity : uint8_t {")
        lines.append("    LEFT,")
        lines.append("    RIGHT,")
        lines.append("    NONE")
        lines.append("};")
        lines.append("")

        lines.append("/// Operator precedence information")
        lines.append("struct OperatorPrecedence {")
        lines.append("    TokenType op;")
        lines.append("    uint8_t precedence;")
        lines.append("    Associativity associativity;")
        lines.append("};")
        lines.append("")

        # Deduplicate operators by mapped TokenType enum (not ANTLR token name)
        unique_operators = {}
        for op in self.unified_data.operators:
            token = op['token']
            # Map to TokenType enum to check for duplicates
            token_enum = self._token_to_enum(token)

            # Only add if we haven't seen this TokenType enum before
            # If duplicate, prefer higher precedence
            if token_enum not in unique_operators:
                unique_operators[token_enum] = op
            else:
                # Keep the one with higher precedence
                if op['precedence'] > unique_operators[token_enum]['precedence']:
                    unique_operators[token_enum] = op

        lines.append("/// Operator precedence table (higher number = higher precedence)")
        lines.append("constexpr OperatorPrecedence operator_precedence[] = {")

        op_entries = []
        # Sort by precedence (highest first), then by token name for stability
        for token_enum, op in sorted(unique_operators.items(), key=lambda x: (-x[1]['precedence'], x[0])):
            prec = op['precedence']
            assoc = op['associativity'].upper()

            entry = f"    {{TokenType::{token_enum}, {prec}, Associativity::{assoc}}}"
            op_entries.append(entry)

        lines.append(",\n".join(op_entries))
        lines.append("};")
        lines.append("")

        lines.append(f"constexpr size_t operator_count = {len(unique_operators)};")
        lines.append("")

        lines.append("/// Get precedence for an operator token")
        lines.append("[[nodiscard]] inline int get_precedence(TokenType op) noexcept {")
        lines.append("    for (size_t i = 0; i < operator_count; ++i) {")
        lines.append("        if (operator_precedence[i].op == op) {")
        lines.append("            return operator_precedence[i].precedence;")
        lines.append("        }")
        lines.append("    }")
        lines.append("    return -1;  // Not an operator")
        lines.append("}")
        lines.append("")

        lines.append("/// Get associativity for an operator token")
        lines.append("[[nodiscard]] inline Associativity get_associativity(TokenType op) noexcept {")
        lines.append("    for (size_t i = 0; i < operator_count; ++i) {")
        lines.append("        if (operator_precedence[i].op == op) {")
        lines.append("            return operator_precedence[i].associativity;")
        lines.append("        }")
        lines.append("    }")
        lines.append("    return Associativity::NONE;")
        lines.append("}")
        lines.append("")

        lines.append("}  // namespace libsqlglot")
        lines.append("")

        # Write to file
        output_file.parent.mkdir(parents=True, exist_ok=True)
        output_file.write_text('\n'.join(lines), encoding='utf-8')

        print(f"[SUCCESS] Generated {output_file}")
        print(f"[INFO] Total operators: {len(unique_operators)}")

    def generate_all_headers(self, output_dir: Path):
        """Generate all C++ headers"""
        print(f"\n{'='*80}")
        print(f"Generating Unified Grammar Headers")
        print(f"Total dialects: {len(self.unified_data.dialects)}")
        print(f"Total keywords: {len(self.unified_data.all_keywords)}")
        print(f"Total patterns: {len(self.unified_data.token_sequences)}")
        print(f"{'='*80}")

        output_dir.mkdir(parents=True, exist_ok=True)

        self.generate_grammar_patterns_h(output_dir / 'grammar_patterns.h')
        self.generate_operator_precedence_h(output_dir / 'operator_precedence.h')

        print(f"\n{'='*80}")
        print(f"[SUCCESS] All headers generated in {output_dir}")
        print(f"{'='*80}\n")

    def _token_to_enum(self, token: str) -> str:
        """Convert token name to TokenType enum name using token mapping"""
        # Try ANTLR token mapping first
        mapped = map_antlr_token(token)
        if mapped:
            return mapped

        # Try keyword mapping
        mapped = map_keyword(token)
        if mapped:
            return mapped

        # Fallback: clean up common patterns
        clean = token.upper()
        for suffix in ['_SYMBOL', '_OPERATOR', '_KW']:
            if clean.endswith(suffix):
                clean = clean[:-len(suffix)]
                break

        return clean

    def _dialect_to_enum(self, dialect: str) -> str:
        """Convert dialect name to Dialect enum name"""
        # Capitalize first letter
        dialect_map = {
            'mysql': 'MySQL',
            'postgresql': 'PostgreSQL',
            'sqlite': 'SQLite',
            'tsql': 'SQLServer',
            'plsql': 'Oracle',
            'bigquery': 'BigQuery',
            'snowflake': 'Snowflake',
        }

        return dialect_map.get(dialect.lower(), dialect.capitalize())


def main():
    import argparse

    parser = argparse.ArgumentParser(
        description='Generate unified C++ headers from extracted grammar data'
    )
    parser.add_argument(
        'data_files',
        nargs='+',
        type=Path,
        help='JSON files with extracted grammar data'
    )
    parser.add_argument(
        '--output-dir',
        type=Path,
        default=Path('include/libsqlglot'),
        help='Output directory for generated headers (default: include/libsqlglot)'
    )

    args = parser.parse_args()

    generator = UnifiedGrammarGenerator()

    # Load all dialect data
    for data_file in args.data_files:
        generator.add_dialect_data(data_file)

    # Generate all headers
    generator.generate_all_headers(args.output_dir)


if __name__ == '__main__':
    main()
