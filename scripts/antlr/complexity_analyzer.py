#!/usr/bin/env python3
"""
Rule Complexity Analyzer - Phase 2 of Grammar Transpiler

Analyzes ANTLR grammar rules and classifies them by implementation complexity:
- SIMPLE (30%): Can be fully auto-generated
- MEDIUM (50%): Template-assisted (needs manual completion)
- COMPLEX (20%): Requires manual implementation

Factors considered:
- Left-recursion (direct or indirect)
- Number of alternatives
- Nesting depth
- Semantic predicates
- Quantifier patterns
- Token vs rule references
"""

import json
from dataclasses import dataclass, asdict
from typing import Dict, List, Set, Tuple
from pathlib import Path
from enum import Enum

from grammar_parser import (
    Grammar, Rule, Element, RuleType,
    Terminal, NonTerminal, Sequence, Alternative, Quantified, Group,
    Quantifier, parse_grammar_file
)


class Complexity(Enum):
    """Rule complexity tiers"""
    SIMPLE = "simple"      # ✅ 30% - Fully auto-generatable
    MEDIUM = "medium"      # ⚠️ 50% - Template-assisted
    COMPLEX = "complex"    # ❌ 20% - Manual implementation


@dataclass
class ComplexityMetrics:
    """Metrics used to determine complexity"""
    has_left_recursion: bool = False
    has_indirect_recursion: bool = False
    num_alternatives: int = 0
    max_nesting_depth: int = 0
    has_semantic_predicates: bool = False
    num_quantifiers: int = 0
    num_terminal_refs: int = 0
    num_nonterminal_refs: int = 0
    has_complex_quantifiers: bool = False  # Nested *, +


@dataclass
class RuleAnalysis:
    """Analysis result for a single rule"""
    name: str
    complexity: Complexity
    metrics: ComplexityMetrics
    reason: str  # Human-readable explanation
    suggested_approach: str  # Implementation hint


class ComplexityAnalyzer:
    """Analyzes grammar rules for complexity"""

    def __init__(self, grammar: Grammar):
        self.grammar = grammar
        self.recursion_graph: Dict[str, Set[str]] = {}
        self._build_recursion_graph()

    def _build_recursion_graph(self):
        """Build call graph for recursion detection"""
        for name, rule in self.grammar.rules.items():
            if rule.type == RuleType.PARSER:
                self.recursion_graph[name] = self._get_called_rules(rule.definition)

    def _get_called_rules(self, element: Element) -> Set[str]:
        """Get all rules called by this element"""
        called = set()

        if isinstance(element, NonTerminal):
            called.add(element.name)
        elif isinstance(element, Sequence):
            for e in element.elements:
                called.update(self._get_called_rules(e))
        elif isinstance(element, Alternative):
            for alt in element.alternatives:
                called.update(self._get_called_rules(alt))
        elif isinstance(element, Quantified):
            called.update(self._get_called_rules(element.element))
        elif isinstance(element, Group):
            called.update(self._get_called_rules(element.content))

        return called

    def _has_left_recursion(self, rule_name: str, element: Element) -> bool:
        """Check for direct left-recursion"""
        if isinstance(element, NonTerminal):
            return element.name == rule_name
        elif isinstance(element, Sequence):
            if element.elements:
                return self._has_left_recursion(rule_name, element.elements[0])
        elif isinstance(element, Alternative):
            return any(self._has_left_recursion(rule_name, alt) for alt in element.alternatives)
        elif isinstance(element, Quantified):
            return self._has_left_recursion(rule_name, element.element)
        elif isinstance(element, Group):
            return self._has_left_recursion(rule_name, element.content)

        return False

    def _has_indirect_recursion(self, rule_name: str, visited: Set[str] = None) -> bool:
        """Check for indirect recursion using call graph"""
        if visited is None:
            visited = set()

        if rule_name in visited:
            return True

        visited.add(rule_name)

        if rule_name in self.recursion_graph:
            for called in self.recursion_graph[rule_name]:
                if called == rule_name:
                    continue  # Direct recursion handled separately
                if self._has_indirect_recursion(called, visited.copy()):
                    return True

        return False

    def _count_alternatives(self, element: Element) -> int:
        """Count number of alternatives at top level"""
        if isinstance(element, Alternative):
            return len(element.alternatives)
        return 1

    def _get_nesting_depth(self, element: Element, current_depth: int = 0) -> int:
        """Calculate maximum nesting depth"""
        if isinstance(element, Group):
            return self._get_nesting_depth(element.content, current_depth + 1)
        elif isinstance(element, Sequence):
            return max((self._get_nesting_depth(e, current_depth) for e in element.elements), default=current_depth)
        elif isinstance(element, Alternative):
            return max((self._get_nesting_depth(alt, current_depth) for alt in element.alternatives), default=current_depth)
        elif isinstance(element, Quantified):
            return self._get_nesting_depth(element.element, current_depth)
        return current_depth

    def _count_quantifiers(self, element: Element) -> int:
        """Count quantifiers in rule"""
        count = 0
        if isinstance(element, Quantified):
            count = 1 + self._count_quantifiers(element.element)
        elif isinstance(element, Sequence):
            count = sum(self._count_quantifiers(e) for e in element.elements)
        elif isinstance(element, Alternative):
            count = sum(self._count_quantifiers(alt) for alt in element.alternatives)
        elif isinstance(element, Group):
            count = self._count_quantifiers(element.content)
        return count

    def _count_references(self, element: Element) -> Tuple[int, int]:
        """Count terminal and non-terminal references"""
        terminals = 0
        nonterminals = 0

        if isinstance(element, Terminal):
            terminals = 1
        elif isinstance(element, NonTerminal):
            nonterminals = 1
        elif isinstance(element, Sequence):
            for e in element.elements:
                t, nt = self._count_references(e)
                terminals += t
                nonterminals += nt
        elif isinstance(element, Alternative):
            for alt in element.alternatives:
                t, nt = self._count_references(alt)
                terminals += t
                nonterminals += nt
        elif isinstance(element, Quantified):
            return self._count_references(element.element)
        elif isinstance(element, Group):
            return self._count_references(element.content)

        return terminals, nonterminals

    def analyze_rule(self, rule: Rule) -> RuleAnalysis:
        """Analyze a single rule"""
        metrics = ComplexityMetrics()

        # Check left recursion
        metrics.has_left_recursion = self._has_left_recursion(rule.name, rule.definition)

        # Check indirect recursion
        metrics.has_indirect_recursion = self._has_indirect_recursion(rule.name)

        # Count alternatives
        metrics.num_alternatives = self._count_alternatives(rule.definition)

        # Get nesting depth
        metrics.max_nesting_depth = self._get_nesting_depth(rule.definition)

        # Count quantifiers
        metrics.num_quantifiers = self._count_quantifiers(rule.definition)

        # Count references
        metrics.num_terminal_refs, metrics.num_nonterminal_refs = \
            self._count_references(rule.definition)

        # Determine complexity
        complexity, reason, approach = self._classify_complexity(rule.name, metrics)

        return RuleAnalysis(
            name=rule.name,
            complexity=complexity,
            metrics=metrics,
            reason=reason,
            suggested_approach=approach
        )

    def _classify_complexity(self, name: str, m: ComplexityMetrics) -> Tuple[Complexity, str, str]:
        """Classify rule complexity based on metrics"""

        # COMPLEX: Left recursion
        if m.has_left_recursion:
            return (
                Complexity.COMPLEX,
                "Has left-recursion",
                "Implement using precedence climbing or Pratt parser"
            )

        # COMPLEX: Indirect recursion
        if m.has_indirect_recursion:
            return (
                Complexity.COMPLEX,
                "Has indirect recursion",
                "Requires careful handling to avoid infinite loops"
            )

        # COMPLEX: Deep nesting (>4 levels)
        if m.max_nesting_depth > 4:
            return (
                Complexity.COMPLEX,
                f"Deep nesting (depth {m.max_nesting_depth})",
                "Break into smaller helper functions"
            )

        # COMPLEX: Many alternatives (>10)
        if m.num_alternatives > 10:
            return (
                Complexity.COMPLEX,
                f"Too many alternatives ({m.num_alternatives})",
                "Consider using dispatch table or redesigning rule structure"
            )

        # SIMPLE: Simple keyword sequence
        if (m.num_alternatives <= 1 and
            m.num_quantifiers == 0 and
            m.num_nonterminal_refs <= 3 and
            m.max_nesting_depth <= 1):
            return (
                Complexity.SIMPLE,
                "Simple keyword sequence with few rule calls",
                "Fully auto-generatable"
            )

        # SIMPLE: Token-only rules (no rule calls)
        if m.num_nonterminal_refs == 0 and m.num_terminal_refs > 0:
            return (
                Complexity.SIMPLE,
                "Token-only rule",
                "Fully auto-generatable"
            )

        # MEDIUM: Everything else
        reason_parts = []
        if m.num_alternatives > 1:
            reason_parts.append(f"{m.num_alternatives} alternatives")
        if m.num_quantifiers > 0:
            reason_parts.append(f"{m.num_quantifiers} quantifiers")
        if m.num_nonterminal_refs > 3:
            reason_parts.append(f"{m.num_nonterminal_refs} rule calls")

        reason = ", ".join(reason_parts) if reason_parts else "Moderate complexity"

        return (
            Complexity.MEDIUM,
            reason,
            "Template-assisted: auto-generate structure, manual implementation for complex parts"
        )

    def analyze_all(self) -> Dict[str, RuleAnalysis]:
        """Analyze all parser rules"""
        results = {}

        for name, rule in self.grammar.rules.items():
            if rule.type == RuleType.PARSER:
                results[name] = self.analyze_rule(rule)

        return results

    def generate_report(self, results: Dict[str, RuleAnalysis]) -> str:
        """Generate markdown report"""
        # Count by complexity
        simple = [r for r in results.values() if r.complexity == Complexity.SIMPLE]
        medium = [r for r in results.values() if r.complexity == Complexity.MEDIUM]
        complex_rules = [r for r in results.values() if r.complexity == Complexity.COMPLEX]

        total = len(results)
        simple_pct = len(simple) / total * 100 if total > 0 else 0
        medium_pct = len(medium) / total * 100 if total > 0 else 0
        complex_pct = len(complex_rules) / total * 100 if total > 0 else 0

        lines = [
            f"# Complexity Analysis: {self.grammar.name}",
            "",
            "## Summary",
            "",
            f"| Complexity | Count | Percentage | Generation Strategy |",
            f"|------------|-------|------------|---------------------|",
            f"| ✅ SIMPLE   | {len(simple)} | {simple_pct:.1f}% | Fully auto-generated |",
            f"| ⚠️ MEDIUM  | {len(medium)} | {medium_pct:.1f}% | Template-assisted |",
            f"| ❌ COMPLEX | {len(complex_rules)} | {complex_pct:.1f}% | Manual implementation |",
            f"| **Total**  | {total} | 100% | |",
            "",
            "---",
            "",
        ]

        # Simple rules
        if simple:
            lines.extend([
                "## ✅ SIMPLE Rules (Auto-generatable)",
                "",
                f"**Count**: {len(simple)}",
                "",
            ])
            for r in simple[:20]:  # Show first 20
                lines.append(f"- `{r.name}`: {r.reason}")
            if len(simple) > 20:
                lines.append(f"- ... and {len(simple) - 20} more")
            lines.extend(["", "---", ""])

        # Medium rules
        if medium:
            lines.extend([
                "## ⚠️ MEDIUM Rules (Template-assisted)",
                "",
                f"**Count**: {len(medium)}",
                "",
            ])
            for r in medium[:30]:
                lines.append(f"- `{r.name}`: {r.reason}")
            if len(medium) > 30:
                lines.append(f"- ... and {len(medium) - 30} more")
            lines.extend(["", "---", ""])

        # Complex rules
        if complex_rules:
            lines.extend([
                "## ❌ COMPLEX Rules (Manual implementation)",
                "",
                f"**Count**: {len(complex_rules)}",
                "",
                "These rules require manual implementation:",
                "",
            ])
            for r in complex_rules:
                lines.append(f"### `{r.name}`")
                lines.append(f"- **Reason**: {r.reason}")
                lines.append(f"- **Approach**: {r.suggested_approach}")
                lines.append("")
            lines.extend(["---", ""])

        return "\n".join(lines)


# CLI interface
if __name__ == '__main__':
    import sys
    import argparse

    parser = argparse.ArgumentParser(description='Analyze ANTLR grammar rule complexity')
    parser.add_argument('grammar_file', type=Path, help='Path to .g4 grammar file')
    parser.add_argument('--output', '-o', type=Path, help='Output markdown file')
    parser.add_argument('--json', type=Path, help='Output JSON file with detailed metrics')

    args = parser.parse_args()

    # Parse grammar
    print(f"Parsing grammar: {args.grammar_file}")
    grammar = parse_grammar_file(args.grammar_file)

    # Analyze
    print(f"Analyzing {len([r for r in grammar.rules.values() if r.type == RuleType.PARSER])} parser rules...")
    analyzer = ComplexityAnalyzer(grammar)
    results = analyzer.analyze_all()

    # Generate report
    report = analyzer.generate_report(results)

    if args.output:
        args.output.write_text(report, encoding='utf-8')
        print(f"✅ Report written to: {args.output}")
    else:
        print(report)

    # Generate JSON if requested
    if args.json:
        json_data = {
            name: asdict(analysis)
            for name, analysis in results.items()
        }
        # Convert enums to strings
        for analysis in json_data.values():
            analysis['complexity'] = analysis['complexity']['value']

        args.json.write_text(json.dumps(json_data, indent=2), encoding='utf-8')
        print(f"✅ JSON data written to: {args.json}")

    # Print summary
    simple = sum(1 for r in results.values() if r.complexity == Complexity.SIMPLE)
    medium = sum(1 for r in results.values() if r.complexity == Complexity.MEDIUM)
    complex_count = sum(1 for r in results.values() if r.complexity == Complexity.COMPLEX)
    total = len(results)

    print(f"\n📊 Summary:")
    print(f"  ✅ SIMPLE: {simple}/{total} ({simple/total*100:.1f}%)")
    print(f"  ⚠️ MEDIUM: {medium}/{total} ({medium/total*100:.1f}%)")
    print(f"  ❌ COMPLEX: {complex_count}/{total} ({complex_count/total*100:.1f}%)")
