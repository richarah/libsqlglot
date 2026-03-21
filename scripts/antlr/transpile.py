#!/usr/bin/env python3
"""
ANTLR Grammar Transpiler - Main Orchestrator

This is the main entry point for the Grammar Transpiler System.
Coordinates all phases to generate C++ parser code from ANTLR grammars.

Usage:
    python scripts/antlr/transpile.py --help
    python scripts/antlr/transpile.py --grammar mysql --output parser_mysql.h
    python scripts/antlr/transpile.py --all-dialects --keywords-only
"""

import argparse
from pathlib import Path
import sys

from grammar_parser import parse_grammar_file
from complexity_analyzer import ComplexityAnalyzer, Complexity
from grammar_transformer import GrammarTransformer
from cpp_generator import CppGenerator
from keywords_generator import KeywordsGenerator


class GrammarTranspiler:
    """Main orchestrator for grammar transpilation"""

    def __init__(self, grammars_dir: Path):
        self.grammars_dir = grammars_dir
        self.sql_dir = self._find_sql_dir()

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

    def transpile_dialect(self, dialect: str, output_file: Path,
                         complexity_filter: str = 'all',
                         rules_filter: list = None):
        """Transpile a single dialect"""
        print(f"\n{'='*80}")
        print(f"Transpiling {dialect.upper()} Grammar")
        print(f"{'='*80}")

        # Step 1: Find and parse grammar
        print(f"\n[1/5] Parsing grammar...")
        grammar_file = self.find_grammar_file(dialect)
        print(f"  Using: {grammar_file}")
        grammar = parse_grammar_file(grammar_file)
        print(f"  ✓ Found {len([r for r in grammar.rules.values() if r.type.value == 'parser'])} parser rules")

        # Step 2: Analyze complexity
        print(f"\n[2/5] Analyzing rule complexity...")
        analyzer = ComplexityAnalyzer(grammar)
        analysis = analyzer.analyze_all()

        simple = sum(1 for a in analysis.values() if a.complexity == Complexity.SIMPLE)
        medium = sum(1 for a in analysis.values() if a.complexity == Complexity.MEDIUM)
        complex_count = sum(1 for a in analysis.values() if a.complexity == Complexity.COMPLEX)

        print(f"  ✓ SIMPLE: {simple} ({simple/len(analysis)*100:.1f}%)")
        print(f"  ✓ MEDIUM: {medium} ({medium/len(analysis)*100:.1f}%)")
        print(f"  ✓ COMPLEX: {complex_count} ({complex_count/len(analysis)*100:.1f}%)")

        # Step 3: Transform grammar
        print(f"\n[3/5] Transforming grammar...")
        transformer = GrammarTransformer(grammar)
        transformed = transformer.transform()
        print(f"  ✓ Created {len(transformed.rules) - len(grammar.rules)} helper rules")

        # Step 4: Filter rules
        if complexity_filter != 'all':
            target = Complexity(complexity_filter)
            analysis = {name: a for name, a in analysis.items() if a.complexity == target}
            print(f"  ✓ Filtered to {len(analysis)} {complexity_filter.upper()} rules")

        if rules_filter:
            rule_set = set(rules_filter)
            analysis = {name: a for name, a in analysis.items() if name in rule_set}
            print(f"  ✓ Filtered to {len(analysis)} specified rules")

        # Step 5: Generate C++ code
        print(f"\n[4/5] Generating C++ code...")
        generator = CppGenerator(transformed, analysis)
        generated = generator.generate_all()

        print(f"  ✓ Generated {len(generated)} functions:")
        simple_gen = sum(1 for g in generated if g.complexity == Complexity.SIMPLE)
        medium_gen = sum(1 for g in generated if g.complexity == Complexity.MEDIUM)
        complex_gen = sum(1 for g in generated if g.complexity == Complexity.COMPLEX)

        print(f"    - {simple_gen} fully auto-generated (SIMPLE)")
        print(f"    - {medium_gen} template-assisted (MEDIUM)")
        print(f"    - {complex_gen} manual scaffolds (COMPLEX)")

        # Step 6: Write output
        print(f"\n[5/5] Writing output...")
        header_content = generator.generate_header_file()
        output_file.parent.mkdir(parents=True, exist_ok=True)
        output_file.write_text(header_content, encoding='utf-8')

        print(f"  ✓ Written to: {output_file}")
        print(f"  ✓ Size: {len(header_content)} bytes, {len(header_content.splitlines())} lines")

        print(f"\n{'='*80}")
        print(f"✅ Transpilation complete!")
        print(f"{'='*80}\n")

        return generated

    def generate_keywords(self, output_file: Path):
        """Generate keywords.h from all dialects"""
        print(f"\n{'='*80}")
        print(f"Generating keywords.h from all SQL dialects")
        print(f"{'='*80}")

        generator = KeywordsGenerator()
        generator.scan_all_dialects(self.grammars_dir)

        print(f"\n✅ Extracted {len(generator.keywords)} unique keywords")

        header_content = generator.generate_keywords_h()
        output_file.parent.mkdir(parents=True, exist_ok=True)
        output_file.write_text(header_content, encoding='utf-8')

        print(f"✅ Written to: {output_file}")
        print(f"✅ Size: {len(header_content)} bytes\n")


def main():
    parser = argparse.ArgumentParser(
        description='ANTLR Grammar Transpiler - Generate C++ parser code from SQL grammars',
        formatter_class=argparse.RawDescriptionHelpFormatter,
        epilog="""
Examples:
  # List available dialects
  python transpile.py --list-dialects

  # Generate parser for MySQL
  python transpile.py --grammar mysql --output parser_mysql.h

  # Generate only SIMPLE rules for PostgreSQL
  python transpile.py --grammar postgresql --complexity simple

  # Generate specific rules
  python transpile.py --grammar mysql --rules createTable,dropTable

  # Generate keywords.h from all dialects
  python transpile.py --keywords-only

  # Generate everything for a dialect
  python transpile.py --grammar mysql --output-dir generated/
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
        '--grammar',
        type=str,
        help='SQL dialect to transpile (e.g., mysql, postgresql, tsql)'
    )

    parser.add_argument(
        '--output',
        type=Path,
        help='Output C++ header file (default: include/libsqlglot/parser_<dialect>.h)'
    )

    parser.add_argument(
        '--complexity',
        choices=['simple', 'medium', 'complex', 'all'],
        default='all',
        help='Generate only rules of specified complexity (default: all)'
    )

    parser.add_argument(
        '--rules',
        type=str,
        help='Comma-separated list of specific rules to generate'
    )

    parser.add_argument(
        '--keywords-only',
        action='store_true',
        help='Only generate keywords.h, skip parser code generation'
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

        # Normal transpilation mode
        if not args.grammar:
            print("Error: --grammar is required (or use --keywords-only or --list-dialects)")
            print("Run with --help for usage information")
            return 1

        # Determine output file
        if args.output:
            output_file = args.output
        else:
            output_file = Path(f'include/libsqlglot/parser_{args.grammar}_generated.h')

        # Parse rules filter
        rules_filter = None
        if args.rules:
            rules_filter = [r.strip() for r in args.rules.split(',')]

        # Transpile
        transpiler.transpile_dialect(
            args.grammar,
            output_file,
            complexity_filter=args.complexity,
            rules_filter=rules_filter
        )

        print("💡 Next steps:")
        print(f"  1. Review generated code in {output_file}")
        print(f"  2. Complete TODOs for MEDIUM rules")
        print(f"  3. Manually implement COMPLEX rules")
        print(f"  4. Integrate into include/libsqlglot/parser.h")
        print(f"  5. Build and test: cmake --build build && ./build/tests/libsqlglot_tests")

        return 0

    except Exception as e:
        print(f"\n❌ Error: {e}", file=sys.stderr)
        import traceback
        traceback.print_exc()
        return 1


if __name__ == '__main__':
    sys.exit(main())
