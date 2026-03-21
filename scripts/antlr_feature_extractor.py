#!/usr/bin/env python3
"""
ANTLR Feature Extractor - Discover SQL features from ANTLR grammars

This tool parses ANTLR .g4 grammar files and extracts:
1. Parser rules (SQL constructs like CREATE TABLE, SELECT, etc.)
2. Lexer rules (keywords)
3. Feature categories (DDL, DML, procedural, etc.)

Output: Markdown report comparing discovered features vs implemented features
"""

import re
import sys
from pathlib import Path
from collections import defaultdict
from typing import Dict, Set, List, Tuple


class ANTLRGrammarParser:
    """Simple parser for ANTLR .g4 grammar files"""

    # Regex patterns
    PARSER_RULE = re.compile(r'^([a-z][a-zA-Z0-9_]*)\s*:', re.MULTILINE)
    LEXER_RULE = re.compile(r'^([A-Z][A-Z0-9_]*)\s*:', re.MULTILINE)
    KEYWORD_LITERAL = re.compile(r"'([A-Z][A-Z0-9_]*)'")

    def __init__(self, grammar_file: Path):
        self.grammar_file = grammar_file
        self.dialect = self._detect_dialect()
        self.content = grammar_file.read_text(encoding='utf-8', errors='ignore')

    def _detect_dialect(self) -> str:
        """Detect SQL dialect from file path"""
        parts = self.grammar_file.parts
        for i, part in enumerate(parts):
            if part == 'sql' and i + 1 < len(parts):
                return parts[i + 1]
        return 'unknown'

    def extract_parser_rules(self) -> Set[str]:
        """Extract parser rule names (lowercase in ANTLR)"""
        return set(self.PARSER_RULE.findall(self.content))

    def extract_lexer_rules(self) -> Set[str]:
        """Extract lexer rule names (uppercase in ANTLR)"""
        return set(self.LEXER_RULE.findall(self.content))

    def extract_keywords(self) -> Set[str]:
        """Extract keyword literals from grammar"""
        return set(self.KEYWORD_LITERAL.findall(self.content))


class FeatureExtractor:
    """Extract and categorize SQL features from ANTLR grammars"""

    # Feature categories based on parser rule patterns
    FEATURE_PATTERNS = {
        'DDL': [
            r'create.*table', r'drop.*table', r'alter.*table', r'truncate',
            r'create.*index', r'drop.*index',
            r'create.*view', r'drop.*view',
            r'create.*database', r'drop.*database', r'create.*schema',
            r'create.*function', r'create.*procedure',
        ],
        'DML': [
            r'select', r'insert', r'update', r'delete', r'merge', r'upsert',
            r'returning', r'on.*conflict', r'on.*duplicate',
        ],
        'Queries': [
            r'join', r'union', r'intersect', r'except', r'minus',
            r'cte', r'with.*clause', r'subquery',
            r'where.*clause', r'having.*clause', r'group.*by', r'order.*by',
        ],
        'Window Functions': [
            r'window', r'over.*clause', r'partition.*by',
            r'row_number', r'rank', r'dense_rank', r'lag', r'lead',
        ],
        'Procedural': [
            r'begin', r'end', r'if.*statement', r'case.*statement',
            r'while.*loop', r'for.*loop', r'loop.*statement',
            r'declare', r'set.*variable', r'return',
            r'exception', r'try.*catch', r'raise',
        ],
        'Constraints': [
            r'primary.*key', r'foreign.*key', r'unique', r'check.*constraint',
            r'not.*null', r'default',
        ],
        'Advanced': [
            r'pivot', r'unpivot', r'lateral', r'qualify', r'tablesample',
            r'connect.*by', r'recursive', r'materialized',
        ],
    }

    def __init__(self, grammars_dir: Path):
        self.grammars_dir = grammars_dir
        self.dialects: Dict[str, Dict[str, Set[str]]] = defaultdict(lambda: {
            'parser_rules': set(),
            'lexer_rules': set(),
            'keywords': set(),
        })

    def scan_grammars(self):
        """Scan all .g4 files in grammars directory"""
        sql_dir = self.grammars_dir / 'sql'
        if not sql_dir.exists():
            # Try alternative path
            alt_paths = list(self.grammars_dir.rglob('sql'))
            if alt_paths:
                sql_dir = alt_paths[0]
            else:
                print(f"Error: SQL grammars not found in {self.grammars_dir}")
                return

        for g4_file in sql_dir.rglob('*.g4'):
            # Skip test/example directories (not the grammars-v4/examples parent dir)
            file_name = g4_file.name.lower()
            if 'test' in file_name or file_name.startswith('example'):
                continue

            parser = ANTLRGrammarParser(g4_file)
            dialect = parser.dialect

            self.dialects[dialect]['parser_rules'].update(parser.extract_parser_rules())
            self.dialects[dialect]['lexer_rules'].update(parser.extract_lexer_rules())
            self.dialects[dialect]['keywords'].update(parser.extract_keywords())

    def categorize_features(self, parser_rules: Set[str]) -> Dict[str, List[str]]:
        """Categorize parser rules by feature type"""
        categorized = defaultdict(list)
        uncategorized = []

        for rule in sorted(parser_rules):
            matched = False
            for category, patterns in self.FEATURE_PATTERNS.items():
                for pattern in patterns:
                    if re.search(pattern, rule, re.IGNORECASE):
                        categorized[category].append(rule)
                        matched = True
                        break
                if matched:
                    break

            if not matched:
                uncategorized.append(rule)

        if uncategorized:
            categorized['Other'] = uncategorized

        return dict(categorized)

    def generate_report(self) -> str:
        """Generate markdown report of discovered features"""
        lines = [
            "# ANTLR Grammar Feature Discovery Report",
            "",
            f"**Generated from**: {self.grammars_dir}",
            f"**Dialects analyzed**: {len(self.dialects)}",
            "",
            "---",
            "",
        ]

        # Summary table
        lines.extend([
            "## Summary",
            "",
            "| Dialect | Parser Rules | Keywords | Lexer Rules |",
            "|---------|--------------|----------|-------------|",
        ])

        for dialect in sorted(self.dialects.keys()):
            data = self.dialects[dialect]
            lines.append(
                f"| {dialect} | {len(data['parser_rules'])} | "
                f"{len(data['keywords'])} | {len(data['lexer_rules'])} |"
            )

        lines.extend(["", "---", ""])

        # Detailed breakdown by dialect
        for dialect in sorted(self.dialects.keys()):
            data = self.dialects[dialect]
            lines.extend([
                f"## {dialect.upper()}",
                "",
                f"**Parser rules**: {len(data['parser_rules'])}  ",
                f"**Keywords**: {len(data['keywords'])}  ",
                f"**Lexer rules**: {len(data['lexer_rules'])}",
                "",
            ])

            # Categorized features
            categorized = self.categorize_features(data['parser_rules'])

            for category in ['DDL', 'DML', 'Queries', 'Window Functions',
                           'Procedural', 'Constraints', 'Advanced', 'Other']:
                if category in categorized:
                    rules = categorized[category]
                    lines.extend([
                        f"### {category} ({len(rules)} rules)",
                        "",
                    ])

                    # Group by first 30 rules, then show count
                    if len(rules) <= 50:
                        for rule in rules:
                            lines.append(f"- `{rule}`")
                    else:
                        for rule in rules[:30]:
                            lines.append(f"- `{rule}`")
                        lines.append(f"- ... and {len(rules) - 30} more")

                    lines.append("")

            # Top 50 keywords
            keywords = sorted(data['keywords'])
            if keywords:
                lines.extend([
                    f"### Keywords ({len(keywords)} total)",
                    "",
                    "Top 50:",
                    "",
                ])
                for kw in keywords[:50]:
                    lines.append(f"- `{kw}`")
                if len(keywords) > 50:
                    lines.append(f"- ... and {len(keywords) - 50} more")
                lines.append("")

            lines.extend(["---", ""])

        return "\n".join(lines)


def main():
    import argparse

    parser = argparse.ArgumentParser(
        description='Extract SQL features from ANTLR grammars'
    )
    parser.add_argument(
        '--grammars',
        type=Path,
        default=Path('external/grammars-v4/antlr/antlr4/examples/grammars-v4'),
        help='Path to grammars-v4 directory (default: external/grammars-v4/antlr/antlr4/examples/grammars-v4)'
    )
    parser.add_argument(
        '--output',
        type=Path,
        default=Path('ANTLR_FEATURES.md'),
        help='Output markdown file (default: ANTLR_FEATURES.md)'
    )
    parser.add_argument(
        '--dialect',
        type=str,
        help='Extract features for specific dialect only'
    )

    args = parser.parse_args()

    if not args.grammars.exists():
        print(f"Error: Grammars directory not found: {args.grammars}")
        print("Run: git clone https://github.com/antlr/grammars-v4.git external/grammars-v4")
        return 1

    print(f"Scanning ANTLR grammars in {args.grammars}...")

    extractor = FeatureExtractor(args.grammars)
    extractor.scan_grammars()

    if args.dialect and args.dialect in extractor.dialects:
        # Filter to specific dialect
        extractor.dialects = {args.dialect: extractor.dialects[args.dialect]}

    print(f"Found {len(extractor.dialects)} SQL dialects")

    report = extractor.generate_report()
    args.output.write_text(report, encoding='utf-8')

    print(f"✅ Report generated: {args.output}")

    # Print summary
    total_rules = sum(len(d['parser_rules']) for d in extractor.dialects.values())
    total_keywords = sum(len(d['keywords']) for d in extractor.dialects.values())

    print(f"\n📊 Total parser rules: {total_rules}")
    print(f"📊 Total unique keywords: {total_keywords}")

    return 0


if __name__ == '__main__':
    sys.exit(main())
