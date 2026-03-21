#!/usr/bin/env python3
"""
Lemon C++ Wrapper Generator

Generates C++ wrapper code around Lemon-generated C parsers.
Integrates Lemon parsers with libsqlglot's Expression types and Arena allocator.

Usage:
    python lemon_wrapper.py grammar.c --output grammar_wrapper.h
    python lemon_wrapper.py --grammar mysql_expr.c
"""

import argparse
import re
from pathlib import Path
from typing import List, Set, Dict, Tuple, Optional


class LemonWrapperGenerator:
    """Generate C++ wrapper around Lemon parser"""

    def __init__(self, lemon_c_file: Path, lemon_y_file: Optional[Path] = None):
        self.lemon_c_file = lemon_c_file
        self.lemon_y_file = lemon_y_file or lemon_c_file.with_suffix('.y')

        # Extract grammar name from filename
        self.grammar_name = lemon_c_file.stem

        # Extracted information
        self.tokens: Set[str] = set()
        self.nonterminals: Set[str] = set()
        self.start_symbol: str = "program"

    def extract_grammar_info(self):
        """Extract tokens and nonterminals from .y file"""
        if not self.lemon_y_file.exists():
            print(f"Warning: {self.lemon_y_file} not found, using defaults")
            return

        content = self.lemon_y_file.read_text(encoding='utf-8')

        # Extract %token declarations
        token_pattern = r'%token\s+(\w+)'
        self.tokens = set(re.findall(token_pattern, content))

        # Extract %start_symbol
        start_match = re.search(r'%start_symbol\s+(\w+)', content)
        if start_match:
            self.start_symbol = start_match.group(1)

        # Extract nonterminals from LHS of productions
        prod_pattern = r'^(\w+)\([A-Z]\)\s*::='
        nonterminals_found = re.findall(prod_pattern, content, re.MULTILINE)
        self.nonterminals = set(nonterminals_found)

        print(f"Extracted: {len(self.tokens)} tokens, {len(self.nonterminals)} nonterminals")

    def generate_wrapper(self) -> str:
        """Generate complete C++ wrapper header"""
        self.extract_grammar_info()

        lines = []

        # Header guard
        guard = f"{self.grammar_name.upper()}_WRAPPER_H"
        lines.extend([
            f"#pragma once",
            "",
            "// Auto-generated C++ wrapper around Lemon parser",
            f"// Generated from: {self.lemon_c_file.name}",
            "// DO NOT EDIT MANUALLY",
            "",
        ])

        # Includes
        lines.extend([
            "#include <memory>",
            "#include <vector>",
            "#include <string_view>",
            "#include <cstdio>",
            "",
            '#include "expression.h"',
            '#include "arena.h"',
            '#include "tokens.h"',
            "",
        ])

        # Namespace
        lines.extend([
            "namespace libsqlglot {",
            "",
        ])

        # Forward declarations
        lines.extend([
            "// Forward declarations for Lemon parser functions",
            "extern \"C\" {",
            f"    void *{self.grammar_name}Alloc(void *(*mallocProc)(size_t));",
            f"    void {self.grammar_name}Free(void *p, void (*freeProc)(void*));",
            f"    void {self.grammar_name}(void *yyp, int yymajor, void *yyminor);",
            "}",
            "",
        ])

        # Token type enum mapping
        lines.extend(self._generate_token_mapping())

        # Parser class
        lines.extend(self._generate_parser_class())

        # Close namespace
        lines.extend([
            "}  // namespace libsqlglot",
            "",
        ])

        return "\n".join(lines)

    def _generate_token_mapping(self) -> List[str]:
        """Generate token type mapping between libsqlglot and Lemon"""
        lines = [
            "// Token type mapping: libsqlglot::TokenType → Lemon token codes",
            "namespace LemonTokens {",
        ]

        # Include Lemon's token definitions from .h file
        h_file = self.lemon_c_file.with_suffix('.h')
        if h_file.exists():
            # Read token defines from .h file
            h_content = h_file.read_text(encoding='utf-8')
            define_pattern = r'#define\s+(\w+)\s+(\d+)'
            defines = re.findall(define_pattern, h_content)

            for token_name, token_code in defines:
                lines.append(f"    constexpr int {token_name} = {token_code};")
        else:
            # Fallback: generate sequential codes
            for i, token in enumerate(sorted(self.tokens), start=1):
                lines.append(f"    constexpr int {token} = {i};")

        lines.extend([
            "}",
            "",
        ])

        return lines

    def _generate_parser_class(self) -> List[str]:
        """Generate C++ parser wrapper class"""
        lines = [
            f"/// C++ wrapper around Lemon {self.grammar_name} parser",
            f"class {self._to_pascal_case(self.grammar_name)}Parser {{",
            "public:",
            "    /// Constructor",
            f"    {self._to_pascal_case(self.grammar_name)}Parser(Arena& arena)",
            "        : arena_(arena), result_(nullptr) {",
            f"        parser_ = {self.grammar_name}Alloc(malloc);",
            "    }",
            "",
            "    /// Destructor",
            f"    ~{self._to_pascal_case(self.grammar_name)}Parser() {{",
            f"        {self.grammar_name}Free(parser_, free);",
            "    }",
            "",
            "    // Disable copy/move",
            f"    {self._to_pascal_case(self.grammar_name)}Parser(const {self._to_pascal_case(self.grammar_name)}Parser&) = delete;",
            f"    {self._to_pascal_case(self.grammar_name)}Parser& operator=(const {self._to_pascal_case(self.grammar_name)}Parser&) = delete;",
            "",
            "    /// Parse tokens and return AST",
            "    Expression* parse(const std::vector<Token>& tokens) {",
            "        result_ = nullptr;",
            "",
            "        // Feed tokens to Lemon parser",
            "        for (const auto& token : tokens) {",
            "            int lemon_token = convert_token_type(token.type);",
            "            Token* token_copy = new Token(token);  // Lemon takes ownership",
            f"            {self.grammar_name}(parser_, lemon_token, token_copy);",
            "        }",
            "",
            "        // Signal end of input",
            f"        {self.grammar_name}(parser_, 0, nullptr);",
            "",
            "        return result_;",
            "    }",
            "",
            "    /// Set parse result (called from Lemon action code)",
            "    void set_result(Expression* expr) {",
            "        result_ = expr;",
            "    }",
            "",
            "private:",
            "    Arena& arena_;",
            "    void* parser_;",
            "    Expression* result_;",
            "",
            "    /// Convert libsqlglot TokenType to Lemon token code",
            "    int convert_token_type(TokenType type) {",
            "        switch (type) {",
        ]

        # Generate token mapping cases
        for token in sorted(self.tokens):
            # Try to map token name to libsqlglot TokenType
            token_enum = token.upper()
            lines.append(f"            case TokenType::{token_enum}: return LemonTokens::{token};")

        lines.extend([
            "            default:",
            "                fprintf(stderr, \"Unknown token type: %d\\n\", static_cast<int>(type));",
            "                return 0;  // EOF",
            "        }",
            "    }",
            "};",
            "",
        ])

        # Add helper functions for action code
        lines.extend([
            "/// Helper functions for Lemon action code",
            "",
            "/// Create binary expression",
            "inline Expression* create_binary_expr(Arena& arena, TokenType op, Expression* left, Expression* right) {",
            "    return arena.create<BinaryExpr>(op, left, right);",
            "}",
            "",
            "/// Create unary expression",
            "inline Expression* create_unary_expr(Arena& arena, TokenType op, Expression* operand) {",
            "    return arena.create<UnaryExpr>(op, operand);",
            "}",
            "",
            "/// Create list",
            "inline Expression* create_list(Expression* first) {",
            "    // TODO: Implement list creation",
            "    return first;",
            "}",
            "",
            "/// Append to list",
            "inline Expression* append_list(Expression* list, Expression* item) {",
            "    // TODO: Implement list append",
            "    return list;",
            "}",
            "",
        ])

        return lines

    def _to_pascal_case(self, name: str) -> str:
        """Convert name to PascalCase"""
        parts = name.replace('-', '_').replace('.', '_').split('_')
        return ''.join(p.capitalize() for p in parts if p)

    def generate_action_code_patch(self) -> str:
        """Generate patch for .y file to fix action code"""
        lines = [
            "// Suggested action code fixes for .y file",
            "// Replace generic TODOs with proper libsqlglot code",
            "",
        ]

        # Common expression patterns
        patterns = [
            ("Binary expression", "A = create_binary_expr(arena_, TokenType::PLUS, B, D);"),
            ("Unary expression", "A = create_unary_expr(arena_, TokenType::NOT, B);"),
            ("Pass-through", "A = B;"),
            ("List creation", "A = create_list(B);"),
            ("List append", "A = append_list(B, D);"),
        ]

        for desc, code in patterns:
            lines.append(f"// {desc}")
            lines.append(f"{{ {code} }}")
            lines.append("")

        return "\n".join(lines)


# CLI interface
def main():
    parser = argparse.ArgumentParser(
        description='Generate C++ wrapper around Lemon parser',
        formatter_class=argparse.RawDescriptionHelpFormatter,
        epilog="""
Examples:
  # Generate wrapper from Lemon .c file
  python lemon_wrapper.py grammar.c --output grammar_wrapper.h

  # Generate wrapper and action code patch
  python lemon_wrapper.py grammar.c --patch action_code.txt
        """
    )

    parser.add_argument('lemon_c_file', type=Path, help='Path to Lemon-generated .c file')
    parser.add_argument('--output', '-o', type=Path, help='Output C++ wrapper header')
    parser.add_argument('--patch', type=Path, help='Generate action code patch file')
    parser.add_argument('--y-file', type=Path, help='Path to .y grammar file (default: infer from .c)')

    args = parser.parse_args()

    if not args.lemon_c_file.exists():
        print(f"Error: {args.lemon_c_file} not found")
        return 1

    # Generate wrapper
    print(f"Generating C++ wrapper for: {args.lemon_c_file}")
    generator = LemonWrapperGenerator(args.lemon_c_file, args.y_file)

    wrapper_code = generator.generate_wrapper()

    # Write output
    if args.output:
        args.output.parent.mkdir(parents=True, exist_ok=True)
        args.output.write_text(wrapper_code, encoding='utf-8')
        print(f"✅ Wrapper written to: {args.output}")
    else:
        print(wrapper_code)

    # Generate action code patch if requested
    if args.patch:
        patch_code = generator.generate_action_code_patch()
        args.patch.write_text(patch_code, encoding='utf-8')
        print(f"✅ Action code patch written to: {args.patch}")

    # Print summary
    print(f"\n📊 Summary:")
    print(f"  Grammar: {generator.grammar_name}")
    print(f"  Tokens: {len(generator.tokens)}")
    print(f"  Nonterminals: {len(generator.nonterminals)}")
    print(f"  Start symbol: {generator.start_symbol}")

    print(f"\n💡 Next steps:")
    print(f"  1. Review generated wrapper: {args.output or 'stdout'}")
    print(f"  2. Update action code in {generator.lemon_y_file} using patch")
    print(f"  3. Recompile with Lemon: ./external/lemon/lemon {generator.lemon_y_file}")
    print(f"  4. Integrate wrapper into parser.h")

    return 0


if __name__ == '__main__':
    import sys
    sys.exit(main())
