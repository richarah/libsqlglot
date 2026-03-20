"""
libsqlglot - High-performance C++ SQL parser, transpiler, and optimizer
"""

from ._libsqlglot import (
    # Core classes
    Arena,
    Parser,
    Expression,
    SelectStmt,

    # Enums
    Dialect,
    ExprType,

    # Functions
    parse,
    parse_one,     # sqlglot compatibility
    generate,
    transpile,
    optimize,      # Optimizer
    diff,          # SQL comparison
    select,        # Fluent builder

    # Version & metadata
    __version__,
    __dialect_count__,
)

__all__ = [
    # Core classes
    "Arena",
    "Parser",
    "Expression",
    "SelectStmt",

    # Enums
    "Dialect",
    "ExprType",

    # Functions
    "parse",
    "parse_one",
    "generate",
    "transpile",
    "optimize",
    "diff",
    "select",

    # Version & metadata
    "__version__",
    "__dialect_count__",
]
