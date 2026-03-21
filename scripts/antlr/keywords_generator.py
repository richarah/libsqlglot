#!/usr/bin/env python3
"""
Keywords.h Generator - Phase 6 of Grammar Transpiler

Automatically extracts keywords from ANTLR grammars and generates keywords.h
with perfect hash table. Never manually add keywords again!

Processes all SQL dialect grammars and merges keywords.
"""

import re
from pathlib import Path
from typing import Set, Dict, List
from collections import defaultdict

from grammar_parser import parse_grammar_file, RuleType


class KeywordsGenerator:
    """Generate keywords.h from ANTLR grammars"""

    def __init__(self):
        self.keywords: Set[str] = set()
        self.keyword_to_dialects: Dict[str, Set[str]] = defaultdict(set)

    def extract_from_grammar(self, grammar_file: Path, dialect: str):
        """Extract keywords from a single grammar file"""
        print(f"  Extracting from {grammar_file.name}...")

        try:
            grammar = parse_grammar_file(grammar_file)
        except Exception as e:
            print(f"    Warning: Failed to parse {grammar_file}: {e}")
            return

        # Extract from lexer rules
        for name, rule in grammar.rules.items():
            if rule.type == RuleType.LEXER:
                # Lexer rule names are often keywords
                if self._is_keyword_name(name):
                    keyword = self._normalize_keyword(name)
                    if keyword:
                        self.keywords.add(keyword)
                        self.keyword_to_dialects[keyword].add(dialect)

        # Also extract string literals from grammar
        content = grammar_file.read_text(encoding='utf-8', errors='ignore')
        string_literals = re.findall(r"'([A-Z][A-Z0-9_]*)'", content)

        for literal in string_literals:
            if len(literal) >= 2:  # Ignore single-char literals
                self.keywords.add(literal)
                self.keyword_to_dialects[literal].add(dialect)

    def _is_keyword_name(self, name: str) -> bool:
        """Check if lexer rule name represents a keyword"""
        # Lexer rules for keywords typically end with _SYMBOL or are all caps
        if name.endswith('_SYMBOL') or name.endswith('_KW'):
            return True
        if name.isupper() and len(name) > 1:
            return True
        return False

    def _normalize_keyword(self, name: str) -> str:
        """Normalize keyword name"""
        # Remove common suffixes
        name = name.replace('_SYMBOL', '')
        name = name.replace('_KW', '')
        name = name.replace('_KEYWORD', '')

        # Only return if it looks like a SQL keyword
        if len(name) >= 2 and name.isalpha():
            return name

        return ""

    def scan_all_dialects(self, grammars_dir: Path):
        """Scan all SQL dialect grammars"""
        sql_dir = grammars_dir / 'sql'
        if not sql_dir.exists():
            # Try alternative path
            alt_paths = list(grammars_dir.rglob('sql'))
            if alt_paths:
                sql_dir = alt_paths[0]
            else:
                raise FileNotFoundError(f"SQL grammars not found in {grammars_dir}")

        dialects = {}

        for dialect_dir in sql_dir.iterdir():
            if not dialect_dir.is_dir():
                continue

            dialect_name = dialect_dir.name
            print(f"Processing dialect: {dialect_name}")

            # Find lexer grammar files
            lexer_files = list(dialect_dir.rglob('*Lexer.g4'))

            for lexer_file in lexer_files:
                self.extract_from_grammar(lexer_file, dialect_name)

    def perfect_hash(self, keyword: str) -> int:
        """Perfect hash function: (first * 31 + last + length) & 127"""
        if not keyword:
            return 0
        return (ord(keyword[0]) * 31 + ord(keyword[-1]) + len(keyword)) & 127

    def generate_keywords_h(self) -> str:
        """Generate keywords.h content"""
        # Map keywords to token types
        # For now, use generic naming: keyword -> TOKEN_KEYWORD
        keyword_list = []

        for kw in sorted(self.keywords):
            # Generate token type name
            token_type = kw  # Use keyword as-is for token type

            # Handle conflicts with operators/reserved C++ words
            if token_type in ['NOT', 'OR', 'AND']:
                token_type = token_type + '_KW'

            keyword_list.append((kw, token_type))

        # Build hash table
        hash_table = [[] for _ in range(128)]

        for kw, token_type in keyword_list:
            h = self.perfect_hash(kw)
            hash_table[h].append((kw, token_type))

        # Determine slot size
        max_collisions = max(len(entries) for entries in hash_table)
        slot_size = 8 if max_collisions > 4 else 4

        # Generate C++ code
        lines = [
            "#pragma once",
            "",
            "// Auto-generated from ANTLR SQL grammars",
            f"// Total keywords: {len(keyword_list)}",
            "// DO NOT EDIT MANUALLY - regenerate using scripts/antlr/keywords_generator.py",
            "",
            "#include \"tokens.h\"",
            "#include <string_view>",
            "#include <cstdint>",
            "",
            "namespace libsqlglot {",
            "",
            "/// Fast keyword lookup using perfect hash function",
            "class KeywordLookup {",
            "public:",
            "    [[nodiscard]] static TokenType lookup(std::string_view text) noexcept {",
            "        if (text.empty() || text.size() > 16) {",
            "            return TokenType::IDENTIFIER;",
            "        }",
            "",
            "        // Convert to uppercase inline (branchless optimization)",
            "        char upper[17];",
            "        size_t len = text.size();",
            "        for (size_t i = 0; i < len; ++i) {",
            "            char c = text[i];",
            "            upper[i] = c - (((c >= 'a') & (c <= 'z')) << 5);",
            "        }",
            "        upper[len] = '\\0';",
            "",
            "        // Perfect hash: (first * 31 + last + length) & 127",
            "        uint32_t hash = (upper[0] * 31 + upper[len - 1] + len) & 127;",
            "        const KeywordEntry& entry = keyword_table[hash];",
            "",
            f"        // Linear probing for collisions (max {slot_size} per slot)",
            f"        for (int i = 0; i < {slot_size}; ++i) {{",
            "            if (entry.keywords[i] == nullptr) break;",
            "            if (len == entry.lengths[i]) {",
            "                bool match = true;",
            "                for (size_t j = 0; j < len; ++j) {",
            "                    if (upper[j] != entry.keywords[i][j]) {",
            "                        match = false;",
            "                        break;",
            "                    }",
            "                }",
            "                if (match) return entry.types[i];",
            "            }",
            "        }",
            "        return TokenType::IDENTIFIER;",
            "    }",
            "",
            "private:",
            "    struct KeywordEntry {",
            f"        const char* keywords[{slot_size}];",
            f"        uint8_t lengths[{slot_size}];",
            f"        TokenType types[{slot_size}];",
            "    };",
            "",
            f"    static constexpr KeywordEntry keyword_table[128] = {{",
        ]

        # Generate hash table entries
        for i, entries in enumerate(hash_table):
            if not entries:
                nulls = ", ".join(["nullptr"] * slot_size)
                zeros = ", ".join(["0"] * slot_size)
                idents = ", ".join(["TokenType::IDENTIFIER"] * slot_size)
                lines.append(f"        {{{{{nulls}}}, {{{zeros}}}, {{{idents}}}}},")
            else:
                limited_entries = entries[:slot_size]
                keywords_str = ", ".join([f'"{kw}"' for kw, _ in limited_entries] +
                                        ["nullptr"] * (slot_size - len(limited_entries)))
                lengths_str = ", ".join([str(len(kw)) for kw, _ in limited_entries] +
                                       ["0"] * (slot_size - len(limited_entries)))
                types_str = ", ".join([f"TokenType::{tt}" for _, tt in limited_entries] +
                                     ["TokenType::IDENTIFIER"] * (slot_size - len(limited_entries)))

                comment = ", ".join([f"{kw}" for kw, _ in limited_entries])
                lines.append(f"        {{{{{keywords_str}}}, {{{lengths_str}}}, {{{types_str}}}}},  // {comment}")

        lines.extend([
            "    };",
            "};",
            "",
            "}  // namespace libsqlglot",
            "",
            f"// Collision report: {max_collisions} max collisions, using {slot_size}-entry slots",
            ""
        ])

        return "\n".join(lines)


# CLI interface
if __name__ == '__main__':
    import argparse

    parser = argparse.ArgumentParser(description='Generate keywords.h from ANTLR grammars')
    parser.add_argument(
        '--grammars',
        type=Path,
        default=Path('external/grammars-v4/antlr/antlr4/examples/grammars-v4'),
        help='Path to grammars-v4 directory'
    )
    parser.add_argument(
        '--output',
        type=Path,
        default=Path('include/libsqlglot/keywords_generated.h'),
        help='Output header file'
    )

    args = parser.parse_args()

    # Generate keywords
    print(f"Scanning ANTLR grammars in {args.grammars}")
    generator = KeywordsGenerator()
    generator.scan_all_dialects(args.grammars)

    print(f"\n✅ Extracted {len(generator.keywords)} unique keywords")
    print(f"   Across {len(set().union(*generator.keyword_to_dialects.values()))} dialects")

    # Generate header
    header_content = generator.generate_keywords_h()

    args.output.parent.mkdir(parents=True, exist_ok=True)
    args.output.write_text(header_content, encoding='utf-8')

    print(f"✅ Generated: {args.output}")
    print(f"\n📊 Top 20 keywords:")
    for kw in sorted(generator.keywords)[:20]:
        dialects = ", ".join(sorted(generator.keyword_to_dialects[kw])[:3])
        print(f"  {kw:20} ({dialects})")
