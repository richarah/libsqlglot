#!/usr/bin/env python3
"""
ANTLR Grammar Transpiler - Main Orchestrator

This is the main entry point for the Grammar Transpiler System.
Extracts grammar data from ANTLR grammars and generates C++ LUT headers
for libsqlglot's hand-written parser.

NEW PIPELINE (Build-time grammar compiler):
    ANTLR grammars → Extract data → Generate C++ LUT headers → libsqlglot uses at runtime

OLD PIPELINE (deprecated):
    ANTLR → Lemon → C runtime parser (SLOW, not used)

Usage:
    python scripts/antlr/transpile.py --extract-all
    python scripts/antlr/transpile.py --grammar mysql --extract-only
"""

import argparse
from pathlib import Path
import sys
import subprocess
import json
from typing import List, Optional

from grammar_parser import parse_grammar_file
from keywords_generator import KeywordsGenerator
from grammar_data_extractor import extract_from_file, save_to_json, GrammarData
from unified_grammar_generator import UnifiedGrammarGenerator


class GrammarTranspiler:
    """Main orchestrator for grammar-to-LUT compilation"""

    def __init__(self, grammars_dir: Path):
        self.grammars_dir = grammars_dir
        self.sql_dir = self._find_sql_dir()
        self.extracted_data: List[Path] = []

    def _find_sql_dir(self) -> Path:
        """Find SQL grammars directory"""
        sql_dir = self.grammars_dir / 'sql'
        if sql_dir.exists():
            return sql_dir

        # Try alternative paths
        alt_paths = list(self.grammars_dir.rglob('sql'))
        if alt_paths:
            return alt_paths[0]

        raise FileNotFoundError(f"SQL grammars not found in {self.grammars_dir}")

    def list_dialects(self) -> list:
        """List available SQL dialects"""
        dialects = []
        for item in self.sql_dir.iterdir():
            if item.is_dir():
                dialects.append(item.name)
        return sorted(dialects)

    def find_grammar_file(self, dialect: str) -> Path:
        """Find parser grammar file for dialect"""
        dialect_dir = self.sql_dir / dialect

        if not dialect_dir.exists():
            raise FileNotFoundError(f"Dialect '{dialect}' not found in {self.sql_dir}")

        # Look for parser grammar
        parser_files = list(dialect_dir.rglob('*Parser.g4'))

        if not parser_files:
            raise FileNotFoundError(f"No parser grammar found for dialect '{dialect}'")

        # Prefer non-test, non-original files
        for pf in parser_files:
            if 'test' not in str(pf).lower() and 'original' not in str(pf).lower():
                return pf

        return parser_files[0]

    def find_lexer_file(self, dialect: str) -> Optional[Path]:
        """Find lexer grammar file for dialect (if exists)"""
        dialect_dir = self.sql_dir / dialect

        if not dialect_dir.exists():
            return None

        # Look for lexer grammar
        lexer_files = list(dialect_dir.rglob('*Lexer.g4'))

        if not lexer_files:
            return None

        # Prefer non-test, non-original files
        for lf in lexer_files:
            if 'test' not in str(lf).lower() and 'original' not in str(lf).lower():
                return lf

        return lexer_files[0]

    def extract_dialect_data(self, dialect: str, output_dir: Path) -> Optional[Path]:
        """Extract grammar data from a single dialect"""
        print(f"\n{'='*80}")
        print(f"Extracting Grammar Data: {dialect.upper()}")
        print(f"Pipeline: ANTLR → Extract patterns/keywords/operators → JSON")
        print(f"{'='*80}")

        try:
            # Find grammar files
            grammar_file = self.find_grammar_file(dialect)
            lexer_file = self.find_lexer_file(dialect)

            print(f"[OK] Using parser grammar: {grammar_file}")
            if lexer_file:
                print(f"[OK] Using lexer grammar: {lexer_file}")

            # Extract data
            data = extract_from_file(grammar_file, dialect, lexer_file)

            # Save to JSON
            output_file = output_dir / f"{dialect}_grammar_data.json"
            save_to_json(data, output_file)

            print(f"[SUCCESS] Extracted {len(data.token_sequences)} patterns, {len(data.keywords)} keywords")
            print(f"{'='*80}\n")

            self.extracted_data.append(output_file)
            return output_file

        except Exception as e:
            print(f"[ERROR] Failed to extract {dialect}: {e}")
            return None

    def extract_all_dialects(self, output_dir: Path) -> List[Path]:
        """Extract grammar data from all available dialects"""
        print(f"\n{'='*80}")
        print(f"Extracting Grammar Data from All Dialects")
        print(f"{'='*80}\n")

        output_dir.mkdir(parents=True, exist_ok=True)
        dialects = self.list_dialects()

        print(f"[OK] Found {len(dialects)} SQL dialects\n")

        extracted_files = []
        for dialect in dialects:
            output_file = self.extract_dialect_data(dialect, output_dir)
            if output_file:
                extracted_files.append(output_file)

        print(f"\n{'='*80}")
        print(f"[SUCCESS] Extracted {len(extracted_files)}/{len(dialects)} dialects")
        print(f"{'='*80}\n")

        return extracted_files

    def generate_unified_headers(self, data_files: List[Path], output_dir: Path):
        """Generate unified C++ headers from extracted data"""
        print(f"\n{'='*80}")
        print(f"Generating Unified C++ Headers")
        print(f"Input: {len(data_files)} dialect data files")
        print(f"Output: {output_dir}")
        print(f"{'='*80}\n")

        generator = UnifiedGrammarGenerator()

        # Load all dialect data
        for data_file in data_files:
            generator.add_dialect_data(data_file)

        # Generate all headers
        generator.generate_all_headers(output_dir)

        print(f"[SUCCESS] Unified headers generated!")
        print(f"[INFO] Headers ready for libsqlglot's hand-written parser")

    def generate_keywords(self, output_file: Path):
        """Generate keywords.h from all dialects"""
        print(f"\n{'='*80}")
        print(f"Generating keywords.h from all SQL dialects")
        print(f"{'='*80}")

        generator = KeywordsGenerator()
        generator.scan_all_dialects(self.grammars_dir)

        print(f"\n[SUCCESS] Extracted {len(generator.keywords)} unique keywords")

        header_content = generator.generate_keywords_h()
        output_file.parent.mkdir(parents=True, exist_ok=True)
        output_file.write_text(header_content, encoding='utf-8')

        print(f"[SUCCESS] Written to: {output_file}")
        print(f"[SUCCESS] Size: {len(header_content)} bytes\n")


def main():
    parser = argparse.ArgumentParser(
        description='ANTLR Grammar-to-LUT Compiler - Extract grammar data and generate C++ headers',
        formatter_class=argparse.RawDescriptionHelpFormatter,
        epilog="""
Examples:
  # List available dialects
  python transpile.py --list-dialects

  # Extract all dialects and generate unified headers (RECOMMENDED)
  python transpile.py --extract-all

  # Extract single dialect only
  python transpile.py --grammar mysql --extract-only

  # Generate keywords.h from all dialects
  python transpile.py --keywords-only
        """
    )

    parser.add_argument(
        '--grammars',
        type=Path,
        default=Path('external/grammars-v4/antlr/antlr4/examples/grammars-v4'),
        help='Path to grammars-v4 directory (default: external/grammars-v4/antlr/antlr4/examples/grammars-v4)'
    )

    parser.add_argument(
        '--list-dialects',
        action='store_true',
        help='List available SQL dialects and exit'
    )

    parser.add_argument(
        '--extract-all',
        action='store_true',
        help='Extract grammar data from all dialects and generate unified C++ headers (RECOMMENDED)'
    )

    parser.add_argument(
        '--grammar',
        type=str,
        help='SQL dialect to extract (e.g., mysql, postgresql, tsql)'
    )

    parser.add_argument(
        '--extract-only',
        action='store_true',
        help='Only extract grammar data, do not generate headers'
    )

    parser.add_argument(
        '--keywords-only',
        action='store_true',
        help='Only generate keywords.h, skip grammar extraction'
    )

    parser.add_argument(
        '--data-output-dir',
        type=Path,
        default=Path('generated/grammar_data'),
        help='Output directory for extracted JSON data (default: generated/grammar_data)'
    )

    parser.add_argument(
        '--header-output-dir',
        type=Path,
        default=Path('include/libsqlglot'),
        help='Output directory for generated C++ headers (default: include/libsqlglot)'
    )

    parser.add_argument(
        '--keywords-output',
        type=Path,
        default=Path('include/libsqlglot/keywords_generated.h'),
        help='Output file for keywords.h (default: include/libsqlglot/keywords_generated.h)'
    )

    args = parser.parse_args()

    try:
        transpiler = GrammarTranspiler(args.grammars)

        # List dialects mode
        if args.list_dialects:
            print("Available SQL dialects:")
            for dialect in transpiler.list_dialects():
                print(f"  - {dialect}")
            return 0

        # Keywords-only mode
        if args.keywords_only:
            transpiler.generate_keywords(args.keywords_output)
            return 0

        # Extract all dialects mode (RECOMMENDED)
        if args.extract_all:
            # Extract all dialects
            data_files = transpiler.extract_all_dialects(args.data_output_dir)

            if not data_files:
                print("[ERROR] No dialect data extracted")
                return 1

            # Generate unified headers
            transpiler.generate_unified_headers(data_files, args.header_output_dir)

            print("\n[INFO] Next steps:")
            print(f"  1. Review generated headers in {args.header_output_dir}")
            print(f"  2. Include headers in libsqlglot parser")
            print(f"  3. Build and test: cmake --build build && ./build/tests/libsqlglot_tests")

            return 0

        # Single dialect extraction mode
        if args.grammar:
            output_file = transpiler.extract_dialect_data(args.grammar, args.data_output_dir)

            if not output_file:
                print(f"[ERROR] Failed to extract {args.grammar}")
                return 1

            # Generate headers if not extract-only
            if not args.extract_only:
                transpiler.generate_unified_headers([output_file], args.header_output_dir)

            return 0

        # No mode specified
        print("Error: Please specify an action:")
        print("  --extract-all        (extract all dialects and generate headers)")
        print("  --grammar DIALECT    (extract single dialect)")
        print("  --keywords-only      (generate keywords.h)")
        print("  --list-dialects      (list available dialects)")
        print("\nRun with --help for usage information")
        return 1

    except Exception as e:
        print(f"\n[ERROR] Error: {e}", file=sys.stderr)
        import traceback
        traceback.print_exc()
        return 1


if __name__ == '__main__':
    sys.exit(main())
