#!/usr/bin/env python3
"""
Grammar Merger - Combines base SQL grammar with dialect patches

Usage:
    python merge_grammar.py <base_grammar.json> <patch.json> <output.json>

Example:
    python merge_grammar.py generated/grammar_data/postgresql_grammar_data.json \\
                           dialects/patches/redshift.json \\
                           generated/grammar_data/redshift_grammar_data.json
"""

import json
import sys
from pathlib import Path
from typing import Dict, List, Any, Set


class GrammarMerger:
    """Merges a base grammar with a dialect patch"""

    def __init__(self, base_path: Path, patch_path: Path):
        self.base_path = base_path
        self.patch_path = patch_path

        # Load files
        with open(base_path) as f:
            self.base = json.load(f)
        with open(patch_path) as f:
            self.patch = json.load(f)

        # Validate
        self._validate_patch()

    def _validate_patch(self):
        """Validate patch has required fields"""
        required = ['dialect_name', 'base_dialect']
        for field in required:
            if field not in self.patch:
                raise ValueError(f"Patch missing required field: {field}")

        # Verify base dialect matches
        if self.patch['base_dialect'] != self.base['dialect']:
            raise ValueError(
                f"Patch base_dialect '{self.patch['base_dialect']}' "
                f"does not match base grammar dialect '{self.base['dialect']}'"
            )

    def merge(self) -> Dict[str, Any]:
        """Merge base grammar + patch -> output grammar"""
        # Start with a copy of base
        result = {
            'dialect': self.patch['dialect_name'],
            'grammar_name': f"{self.patch['dialect_name'].title()}Parser",
            'token_sequences': self.base['token_sequences'].copy(),
            'operators': self._merge_operators(),
            'keywords': self._merge_keywords(),
            'lexer_tokens': self._merge_lexer_tokens()
        }

        return result

    def _merge_keywords(self) -> List[str]:
        """Merge keywords: base + add - remove"""
        # Start with base keywords as a set for fast operations
        keywords: Set[str] = set(self.base['keywords'])

        patch_keywords = self.patch.get('keywords', {})

        # Remove keywords
        to_remove = set(patch_keywords.get('remove', []))
        keywords -= to_remove

        # Add new keywords
        to_add = patch_keywords.get('add', [])
        for kw in to_add:
            keywords.add(kw['name'].upper())

        # Add data types as keywords (they're recognized as keyword tokens)
        patch_types = self.patch.get('data_types', {})
        for dt in patch_types.get('add', []):
            keywords.add(dt['name'].upper())

        # Remove data types if specified
        for dt_name in patch_types.get('remove', []):
            keywords.discard(dt_name.upper())

        # Return sorted list
        return sorted(keywords)

    def _merge_operators(self) -> List[Dict[str, Any]]:
        """Merge operators: base + add - remove, with precedence overrides"""
        # Start with base operators
        operators = {op['token']: op.copy() for op in self.base['operators']}

        patch_ops = self.patch.get('operators', {})

        # Remove operators
        to_remove = set(patch_ops.get('remove', []))
        for token in to_remove:
            # Try to find by symbol or token name
            for op_token in list(operators.keys()):
                if op_token == token:
                    del operators[op_token]
                    break

        # Add new operators
        to_add = patch_ops.get('add', [])
        for op in to_add:
            operators[op['token_type']] = {
                'token': op['token_type'],
                'precedence': self._precedence_to_int(op.get('precedence', 'comparison')),
                'associativity': op.get('associativity', 'left')
            }

        # Apply precedence overrides
        precedence_overrides = self.patch.get('precedence_overrides', {})
        for token, precedence in precedence_overrides.items():
            if token in operators:
                operators[token]['precedence'] = precedence

        # Return as list
        return list(operators.values())

    def _precedence_to_int(self, precedence_name: str) -> int:
        """Convert precedence name to integer level"""
        # PostgreSQL-style precedence levels (higher = tighter binding)
        precedence_map = {
            'assignment': 2,
            'or': 3,
            'and': 4,
            'not': 5,
            'comparison': 6,
            'bitwise_or': 8,
            'bitwise_xor': 9,
            'bitwise_and': 10,
            'additive': 11,
            'multiplicative': 12,
            'exponentiation': 13,
            'unary': 14
        }
        return precedence_map.get(precedence_name, 6)  # Default to comparison

    def _merge_lexer_tokens(self) -> List[str]:
        """Merge lexer tokens (all unique tokens from keywords, operators, literals)"""
        # Start with base lexer tokens
        tokens: Set[str] = set(self.base['lexer_tokens'])

        # Add new keywords to lexer tokens
        patch_keywords = self.patch.get('keywords', {})
        for kw in patch_keywords.get('add', []):
            tokens.add(kw['token_type'])

        # Add new operators to lexer tokens
        patch_ops = self.patch.get('operators', {})
        for op in patch_ops.get('add', []):
            tokens.add(op['token_type'])

        # Add new data types to lexer tokens
        patch_types = self.patch.get('data_types', {})
        for dt in patch_types.get('add', []):
            tokens.add(dt['token_type'])

        # Remove tokens
        to_remove_kw = set(patch_keywords.get('remove', []))
        tokens -= to_remove_kw

        to_remove_ops = set(patch_ops.get('remove', []))
        # Need to map operator symbols to token types for removal
        for symbol in to_remove_ops:
            # This is simplistic - in reality we'd need a symbol->token mapping
            tokens.discard(symbol)

        return sorted(tokens)

    def save(self, output_path: Path):
        """Merge and save to output file"""
        result = self.merge()

        # Create parent directory if needed
        output_path.parent.mkdir(parents=True, exist_ok=True)

        with open(output_path, 'w') as f:
            json.dump(result, f, indent=2)

        print(f"✓ Merged {self.patch['dialect_name']} grammar:")
        print(f"  Base: {self.base_path}")
        print(f"  Patch: {self.patch_path}")
        print(f"  Output: {output_path}")
        print(f"  Keywords: {len(result['keywords'])} "
              f"(base: {len(self.base['keywords'])}, "
              f"Δ: {len(result['keywords']) - len(self.base['keywords']):+d})")
        print(f"  Operators: {len(result['operators'])} "
              f"(base: {len(self.base['operators'])}, "
              f"Δ: {len(result['operators']) - len(self.base['operators']):+d})")


def main():
    if len(sys.argv) != 4:
        print(__doc__)
        sys.exit(1)

    base_path = Path(sys.argv[1])
    patch_path = Path(sys.argv[2])
    output_path = Path(sys.argv[3])

    if not base_path.exists():
        print(f"Error: Base grammar not found: {base_path}")
        sys.exit(1)

    if not patch_path.exists():
        print(f"Error: Patch file not found: {patch_path}")
        sys.exit(1)

    try:
        merger = GrammarMerger(base_path, patch_path)
        merger.save(output_path)
    except Exception as e:
        print(f"Error: {e}")
        import traceback
        traceback.print_exc()
        sys.exit(1)


if __name__ == '__main__':
    main()
