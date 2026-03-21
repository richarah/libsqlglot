#!/usr/bin/env python3
"""
C++ Template Generator - Phase 4 of Grammar Transpiler

Generates C++ parser code from transformed ANTLR grammars:
- SIMPLE rules: Fully auto-generated code
- MEDIUM rules: Template scaffolding with TODOs
- COMPLEX rules: Manual implementation hints

Output integrates with libsqlglot's parser.h structure.
"""

from dataclasses import dataclass
from typing import List, Dict, Set, Optional
from pathlib import Path

from grammar_parser import (
    Grammar, Rule, Element, RuleType,
    Terminal, NonTerminal, Sequence, Alternative, Quantified, Group,
    Quantifier, parse_grammar_file
)
from complexity_analyzer import ComplexityAnalyzer, Complexity, RuleAnalysis


@dataclass
class GeneratedCode:
    """Generated C++ code for a rule"""
    rule_name: str
    complexity: Complexity
    function_signature: str
    function_body: str
    includes_todos: bool = False
    manual_hints: List[str] = None

    def to_cpp(self) -> str:
        """Convert to C++ function"""
        lines = []

        # Add comment header
        lines.append(f"    // Generated from ANTLR rule: {self.rule_name}")
        lines.append(f"    // Complexity: {self.complexity.value.upper()}")

        if self.manual_hints:
            for hint in self.manual_hints:
                lines.append(f"    // {hint}")

        # Add function
        lines.append(f"    {self.function_signature} {{")
        lines.append(self.function_body)
        lines.append("    }")
        lines.append("")

        return "\n".join(lines)


class CppGenerator:
    """Generates C++ parser code from grammar"""

    def __init__(self, grammar: Grammar, analysis: Dict[str, RuleAnalysis]):
        self.grammar = grammar
        self.analysis = analysis
        self.generated_code: List[GeneratedCode] = []

    def generate_all(self) -> List[GeneratedCode]:
        """Generate code for all rules"""
        for name, rule in self.grammar.rules.items():
            if rule.type != RuleType.PARSER:
                continue

            if name not in self.analysis:
                continue

            complexity = self.analysis[name].complexity

            if complexity == Complexity.SIMPLE:
                code = self._generate_simple_rule(rule, self.analysis[name])
            elif complexity == Complexity.MEDIUM:
                code = self._generate_medium_rule(rule, self.analysis[name])
            else:  # COMPLEX
                code = self._generate_complex_rule(rule, self.analysis[name])

            if code:
                self.generated_code.append(code)

        return self.generated_code

    def _generate_simple_rule(self, rule: Rule, analysis: RuleAnalysis) -> GeneratedCode:
        """Generate fully automated code for SIMPLE rules"""
        func_name = self._to_snake_case(rule.name)
        return_type = self._infer_return_type(rule)

        # Generate function signature
        signature = f"{return_type} parse_{func_name}()"

        # Generate body
        body_lines = []
        body_lines.extend(self._generate_element_code(rule.definition, indent=2))

        # Add return statement if needed
        if return_type != "void":
            if "Stmt" in return_type:
                body_lines.append("        auto stmt = arena_.create<{}>()".format(return_type.replace("*", "")))
                body_lines.append("        // TODO: Populate stmt fields")
                body_lines.append("        return stmt;")
            else:
                body_lines.append("        return nullptr;  // TODO: Return appropriate value")

        body = "\n".join(body_lines)

        return GeneratedCode(
            rule_name=rule.name,
            complexity=Complexity.SIMPLE,
            function_signature=signature,
            function_body=body,
            includes_todos=False
        )

    def _generate_medium_rule(self, rule: Rule, analysis: RuleAnalysis) -> GeneratedCode:
        """Generate template scaffolding for MEDIUM rules"""
        func_name = self._to_snake_case(rule.name)
        return_type = self._infer_return_type(rule)

        signature = f"{return_type} parse_{func_name}()"

        # Generate body with TODOs
        body_lines = []
        body_lines.append("        // TODO: Template-assisted implementation")
        body_lines.append(f"        // Reason: {analysis.reason}")
        body_lines.append("")

        body_lines.extend(self._generate_element_code(rule.definition, indent=2, with_todos=True))

        body = "\n".join(body_lines)

        return GeneratedCode(
            rule_name=rule.name,
            complexity=Complexity.MEDIUM,
            function_signature=signature,
            function_body=body,
            includes_todos=True
        )

    def _generate_complex_rule(self, rule: Rule, analysis: RuleAnalysis) -> GeneratedCode:
        """Generate manual implementation scaffold for COMPLEX rules"""
        func_name = self._to_snake_case(rule.name)
        return_type = self._infer_return_type(rule)

        signature = f"{return_type} parse_{func_name}()"

        hints = [
            "MANUAL IMPLEMENTATION REQUIRED",
            f"Reason: {analysis.reason}",
            f"Suggested approach: {analysis.suggested_approach}",
        ]

        body_lines = []
        for hint in hints:
            body_lines.append(f"        // {hint}")
        body_lines.append("")
        body_lines.append("        // TODO: Implement manually")
        body_lines.append("        return nullptr;")

        body = "\n".join(body_lines)

        return GeneratedCode(
            rule_name=rule.name,
            complexity=Complexity.COMPLEX,
            function_signature=signature,
            function_body=body,
            includes_todos=True,
            manual_hints=hints
        )

    def _generate_element_code(self, element: Element, indent: int = 0, with_todos: bool = False) -> List[str]:
        """Generate C++ code for a grammar element"""
        lines = []
        indent_str = "    " * indent

        if isinstance(element, Terminal):
            # expect(TokenType::KEYWORD)
            token_name = element.value.upper()
            if element.is_string_literal:
                # It's a keyword literal like 'SELECT'
                lines.append(f"{indent_str}expect(TokenType::{token_name});")
            else:
                # It's a token reference like SELECT_SYMBOL
                lines.append(f"{indent_str}expect(TokenType::{token_name});")

        elif isinstance(element, NonTerminal):
            # Call to another rule
            func_name = self._to_snake_case(element.name)
            if with_todos:
                lines.append(f"{indent_str}// TODO: Handle {element.name}")
            lines.append(f"{indent_str}parse_{func_name}();")

        elif isinstance(element, Sequence):
            # Sequence of elements
            for e in element.elements:
                lines.extend(self._generate_element_code(e, indent, with_todos))

        elif isinstance(element, Alternative):
            # Switch or if-else based on alternatives
            lines.append(f"{indent_str}// Alternatives:")
            lines.append(f"{indent_str}switch (current().type) {{")

            for i, alt in enumerate(element.alternatives):
                if with_todos:
                    lines.append(f"{indent_str}    // TODO: Add case for alternative {i+1}")
                lines.append(f"{indent_str}    case TokenType::UNKNOWN:")
                alt_lines = self._generate_element_code(alt, indent + 2, with_todos)
                lines.extend(alt_lines)
                lines.append(f"{indent_str}        break;")

            lines.append(f"{indent_str}    default:")
            lines.append(f'{indent_str}        error("Unexpected token");')
            lines.append(f"{indent_str}}}")

        elif isinstance(element, Quantified):
            # while loop for * and +, if statement for ?
            if element.quantifier == Quantifier.STAR:
                lines.append(f"{indent_str}while (/* TODO: Check condition */) {{")
                inner_lines = self._generate_element_code(element.element, indent + 1, with_todos)
                lines.extend(inner_lines)
                lines.append(f"{indent_str}}}")

            elif element.quantifier == Quantifier.PLUS:
                # At least one
                inner_lines = self._generate_element_code(element.element, indent, with_todos)
                lines.extend(inner_lines)
                lines.append(f"{indent_str}while (/* TODO: Check condition */) {{")
                lines.extend(self._generate_element_code(element.element, indent + 1, with_todos))
                lines.append(f"{indent_str}}}")

            elif element.quantifier == Quantifier.OPTIONAL:
                lines.append(f"{indent_str}if (/* TODO: Check condition */) {{")
                inner_lines = self._generate_element_code(element.element, indent + 1, with_todos)
                lines.extend(inner_lines)
                lines.append(f"{indent_str}}}")

        elif isinstance(element, Group):
            # Grouped expression
            lines.append(f"{indent_str}{{  // Grouped")
            inner_lines = self._generate_element_code(element.content, indent + 1, with_todos)
            lines.extend(inner_lines)
            lines.append(f"{indent_str}}}")

        return lines

    def _to_snake_case(self, name: str) -> str:
        """Convert camelCase to snake_case"""
        result = []
        for i, char in enumerate(name):
            if char.isupper() and i > 0:
                result.append('_')
            result.append(char.lower())
        return ''.join(result)

    def _infer_return_type(self, rule: Rule) -> str:
        """Infer C++ return type from rule name"""
        name_lower = rule.name.lower()

        # Common patterns
        if 'statement' in name_lower or 'stmt' in name_lower:
            return "Expression*"
        elif 'create' in name_lower:
            return "Expression*"
        elif 'alter' in name_lower:
            return "Expression*"
        elif 'drop' in name_lower:
            return "Expression*"
        elif 'select' in name_lower:
            return "SelectStmt*"
        elif 'insert' in name_lower:
            return "InsertStmt*"
        elif 'update' in name_lower:
            return "UpdateStmt*"
        elif 'delete' in name_lower:
            return "DeleteStmt*"
        elif 'option' in name_lower or 'clause' in name_lower:
            return "void"
        else:
            return "Expression*"

    def generate_header_file(self) -> str:
        """Generate complete parser_generated.h file"""
        lines = [
            "#pragma once",
            "",
            "// Auto-generated parser code from ANTLR grammars",
            "// DO NOT EDIT MANUALLY - regenerate using scripts/antlr/transpile.py",
            "",
            "#include \"expression.h\"",
            "#include \"arena.h\"",
            "",
            "namespace libsqlglot {",
            "",
            "// Generated parser methods (to be integrated into Parser class)",
            "",
        ]

        # Sort by complexity
        simple = [c for c in self.generated_code if c.complexity == Complexity.SIMPLE]
        medium = [c for c in self.generated_code if c.complexity == Complexity.MEDIUM]
        complex_rules = [c for c in self.generated_code if c.complexity == Complexity.COMPLEX]

        # Add SIMPLE rules
        if simple:
            lines.append("// ============================================================================")
            lines.append("// SIMPLE Rules (Fully Auto-Generated)")
            lines.append(f"// {len(simple)} functions")
            lines.append("// ============================================================================")
            lines.append("")

            for code in simple:
                lines.append(code.to_cpp())

        # Add MEDIUM rules
        if medium:
            lines.append("// ============================================================================")
            lines.append("// MEDIUM Rules (Template-Assisted - Complete TODOs)")
            lines.append(f"// {len(medium)} functions")
            lines.append("// ============================================================================")
            lines.append("")

            for code in medium:
                lines.append(code.to_cpp())

        # Add COMPLEX rules
        if complex_rules:
            lines.append("// ============================================================================")
            lines.append("// COMPLEX Rules (Manual Implementation Required)")
            lines.append(f"// {len(complex_rules)} functions")
            lines.append("// ============================================================================")
            lines.append("")

            for code in complex_rules:
                lines.append(code.to_cpp())

        lines.extend([
            "}  // namespace libsqlglot",
            ""
        ])

        return "\n".join(lines)


# CLI interface
if __name__ == '__main__':
    import argparse

    parser = argparse.ArgumentParser(description='Generate C++ parser code from ANTLR grammar')
    parser.add_argument('grammar_file', type=Path, help='Path to .g4 grammar file')
    parser.add_argument('--output', '-o', type=Path, help='Output C++ header file')
    parser.add_argument('--rules', type=str, help='Comma-separated list of rules to generate (default: all)')
    parser.add_argument('--complexity', type=str, choices=['simple', 'medium', 'complex', 'all'],
                       default='all', help='Generate only rules of specified complexity')

    args = parser.parse_args()

    # Parse grammar
    print(f"Parsing grammar: {args.grammar_file}")
    grammar = parse_grammar_file(args.grammar_file)

    # Analyze complexity
    print("Analyzing rule complexity...")
    analyzer = ComplexityAnalyzer(grammar)
    analysis = analyzer.analyze_all()

    # Filter rules if specified
    if args.rules:
        rule_names = {r.strip() for r in args.rules.split(',')}
        analysis = {name: a for name, a in analysis.items() if name in rule_names}

    if args.complexity != 'all':
        target_complexity = Complexity(args.complexity)
        analysis = {name: a for name, a in analysis.items() if a.complexity == target_complexity}

    # Generate C++ code
    print(f"Generating C++ code for {len(analysis)} rules...")
    generator = CppGenerator(grammar, analysis)
    generated = generator.generate_all()

    # Generate header file
    header_content = generator.generate_header_file()

    if args.output:
        args.output.write_text(header_content, encoding='utf-8')
        print(f"✅ C++ header written to: {args.output}")
    else:
        print(header_content)

    # Print summary
    simple = sum(1 for c in generated if c.complexity == Complexity.SIMPLE)
    medium = sum(1 for c in generated if c.complexity == Complexity.MEDIUM)
    complex_count = sum(1 for c in generated if c.complexity == Complexity.COMPLEX)

    print(f"\n📊 Generation Summary:")
    print(f"  ✅ SIMPLE: {simple} functions (fully auto-generated)")
    print(f"  ⚠️ MEDIUM: {medium} functions (template-assisted)")
    print(f"  ❌ COMPLEX: {complex_count} functions (manual implementation hints)")
    print(f"  Total: {len(generated)} functions")
