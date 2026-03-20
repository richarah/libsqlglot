#!/usr/bin/env python3
"""
sqlglot Compatibility Test Loader

Loads sqlglot's test fixtures and compares parse results between
Python sqlglot and C++ libsqlglot.

Usage:
    python sqlglot_compat.py --sqlglot-path /path/to/sqlglot
"""

import argparse
import json
import sys
from pathlib import Path
from typing import Dict, List, Tuple

try:
    import sqlglot
    import libsqlglot
    HAVE_LIBS = True
except ImportError as e:
    print(f"Missing required library: {e}", file=sys.stderr)
    print("Install with: pip install sqlglot libsqlglot", file=sys.stderr)
    HAVE_LIBS = False


class CompatibilityTester:
    def __init__(self, sqlglot_path: Path):
        self.sqlglot_path = sqlglot_path
        self.passed = 0
        self.failed = 0
        self.errors = []

    def load_test_fixtures(self) -> List[Dict]:
        """Load SQL test fixtures from sqlglot repository"""
        fixtures_path = self.sqlglot_path / "tests" / "fixtures"

        if not fixtures_path.exists():
            print(f"Fixtures not found at {fixtures_path}", file=sys.stderr)
            return []

        fixtures = []
        for file_path in fixtures_path.glob("**/*.sql"):
            with open(file_path) as f:
                for line_num, line in enumerate(f, 1):
                    line = line.strip()
                    if line and not line.startswith("--"):
                        fixtures.append({
                            "sql": line,
                            "file": file_path.name,
                            "line": line_num
                        })

        return fixtures

    def test_parse_compatibility(self, sql: str) -> Tuple[bool, str]:
        """
        Test if libsqlglot can parse the same SQL as sqlglot

        Returns (success, error_message)
        """
        try:
            # Parse with Python sqlglot
            sqlglot_ast = sqlglot.parse_one(sql)
            sqlglot_success = True
        except Exception as e:
            sqlglot_success = False
            sqlglot_error = str(e)

        try:
            # Parse with C++ libsqlglot
            libsqlglot_ast = libsqlglot.parse(sql)
            libsqlglot_success = True
        except Exception as e:
            libsqlglot_success = False
            libsqlglot_error = str(e)

        # Both should succeed or both should fail
        if sqlglot_success == libsqlglot_success:
            return True, ""
        elif sqlglot_success and not libsqlglot_success:
            return False, f"sqlglot parsed, libsqlglot failed: {libsqlglot_error}"
        else:
            return False, f"libsqlglot parsed, sqlglot failed: {sqlglot_error}"

    def run_tests(self, limit: int = None):
        """Run compatibility tests"""
        print("Loading test fixtures...")
        fixtures = self.load_test_fixtures()

        if not fixtures:
            print("No fixtures found", file=sys.stderr)
            return

        if limit:
            fixtures = fixtures[:limit]

        print(f"Testing {len(fixtures)} SQL queries...")
        print()

        for i, fixture in enumerate(fixtures, 1):
            sql = fixture["sql"]
            success, error = self.test_parse_compatibility(sql)

            if success:
                self.passed += 1
                status = "PASS"
            else:
                self.failed += 1
                status = "FAIL"
                self.errors.append({
                    "sql": sql,
                    "file": fixture["file"],
                    "line": fixture["line"],
                    "error": error
                })

            # Progress indicator
            if i % 100 == 0:
                print(f"Progress: {i}/{len(fixtures)} ({self.passed} passed, {self.failed} failed)")

        print()
        print("=" * 80)
        print(f"Results: {self.passed}/{len(fixtures)} passed ({100*self.passed/len(fixtures):.1f}%)")
        print("=" * 80)

        if self.errors:
            print()
            print("Failed queries:")
            for error in self.errors[:10]:  # Show first 10 errors
                print(f"\n{error['file']}:{error['line']}")
                print(f"  SQL: {error['sql'][:80]}...")
                print(f"  Error: {error['error']}")

            if len(self.errors) > 10:
                print(f"\n... and {len(self.errors) - 10} more errors")

    def save_report(self, output_path: Path):
        """Save detailed report to JSON"""
        report = {
            "total": self.passed + self.failed,
            "passed": self.passed,
            "failed": self.failed,
            "pass_rate": 100 * self.passed / (self.passed + self.failed) if (self.passed + self.failed) > 0 else 0,
            "errors": self.errors
        }

        with open(output_path, "w") as f:
            json.dump(report, f, indent=2)

        print(f"\nReport saved to {output_path}")


def main():
    parser = argparse.ArgumentParser(description="Test libsqlglot compatibility with sqlglot")
    parser.add_argument("--sqlglot-path", type=Path, default=Path("../sqlglot"),
                        help="Path to sqlglot repository")
    parser.add_argument("--limit", type=int, help="Limit number of tests")
    parser.add_argument("--output", type=Path, default=Path("compat_report.json"),
                        help="Output report file")

    args = parser.parse_args()

    if not HAVE_LIBS:
        print("\nInstall missing libraries:", file=sys.stderr)
        print("  pip install sqlglot", file=sys.stderr)
        print("  pip install libsqlglot", file=sys.stderr)
        return 1

    tester = CompatibilityTester(args.sqlglot_path)
    tester.run_tests(limit=args.limit)
    tester.save_report(args.output)

    return 0 if tester.failed == 0 else 1


if __name__ == "__main__":
    sys.exit(main())
