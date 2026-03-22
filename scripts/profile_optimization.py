#!/usr/bin/env python3
"""
Profile-Guided Optimization (PGO) Training Script
==================================================
This script runs representative workloads to generate profile data for PGO.

Usage:
    1. Build with profiling: cmake -DLIBSQLGLOT_PGO_GENERATE=ON
    2. Run this script: python3 scripts/profile_optimization.py
    3. Rebuild with PGO: cmake -DLIBSQLGLOT_PGO_USE=ON
"""

import sys
import time
import subprocess
from pathlib import Path

# Add parent directory to path
sys.path.insert(0, str(Path(__file__).parent.parent / "src" / "python"))

try:
    import libsqlglot
except ImportError:
    print("ERROR: libsqlglot not built. Build with LIBSQLGLOT_PGO_GENERATE=ON first.")
    sys.exit(1)


def benchmark(name: str, func, iterations: int = 1000):
    """Benchmark a function and print results."""
    print(f"\n{name}:")
    print(f"  Running {iterations} iterations...", end=" ", flush=True)

    start = time.perf_counter()
    for _ in range(iterations):
        func()
    elapsed = time.perf_counter() - start

    per_op = (elapsed / iterations) * 1_000_000  # microseconds
    ops_per_sec = iterations / elapsed

    print(f"✓")
    print(f"  Total: {elapsed:.3f}s")
    print(f"  Per operation: {per_op:.2f}µs")
    print(f"  Throughput: {ops_per_sec:,.0f} ops/sec")


def training_workload_simple():
    """Simple SELECT queries - most common case."""
    queries = [
        "SELECT * FROM users",
        "SELECT id, name FROM users WHERE age > 18",
        "SELECT COUNT(*) FROM orders",
        "SELECT * FROM users WHERE id = 1",
        "SELECT name FROM products WHERE price < 100",
    ]

    for query in queries:
        libsqlglot.transpile(query)


def training_workload_joins():
    """JOIN queries - moderate complexity."""
    queries = [
        "SELECT * FROM users u JOIN orders o ON u.id = o.user_id",
        "SELECT u.name, COUNT(*) FROM users u JOIN orders o ON u.id = o.user_id GROUP BY u.name",
        "SELECT * FROM users u LEFT JOIN orders o ON u.id = o.user_id",
        "SELECT * FROM a JOIN b ON a.id = b.id JOIN c ON b.id = c.id",
    ]

    for query in queries:
        libsqlglot.transpile(query)


def training_workload_complex():
    """Complex queries - CTEs, subqueries, window functions."""
    queries = [
        """
        WITH ranked AS (
            SELECT *, ROW_NUMBER() OVER (PARTITION BY category ORDER BY price DESC) as rank
            FROM products
        )
        SELECT * FROM ranked WHERE rank <= 10
        """,
        """
        SELECT *
        FROM users
        WHERE id IN (SELECT user_id FROM orders WHERE total > 1000)
        """,
        """
        SELECT
            category,
            product,
            price,
            AVG(price) OVER (PARTITION BY category) as avg_price
        FROM products
        """,
    ]

    for query in queries:
        libsqlglot.transpile(query)


def training_workload_transpilation():
    """Cross-dialect transpilation - key use case."""
    query = "SELECT * FROM users WHERE age > 18 LIMIT 10"

    # Test common transpilation paths
    pairs = [
        (libsqlglot.Dialect.MySQL, libsqlglot.Dialect.PostgreSQL),
        (libsqlglot.Dialect.PostgreSQL, libsqlglot.Dialect.MySQL),
        (libsqlglot.Dialect.BigQuery, libsqlglot.Dialect.Snowflake),
        (libsqlglot.Dialect.Oracle, libsqlglot.Dialect.SQLServer),
        (libsqlglot.Dialect.MySQL, libsqlglot.Dialect.BigQuery),
    ]

    for read_dialect, write_dialect in pairs:
        libsqlglot.transpile(query, read=read_dialect, write=write_dialect)


def training_workload_procedural():
    """Procedural SQL - stored procedures, control flow."""
    queries = [
        """
        BEGIN
            SELECT * FROM users;
            UPDATE users SET last_login = NOW();
        END
        """,
        """
        IF @count > 10 THEN
            SELECT 'many' AS result;
        ELSE
            SELECT 'few' AS result;
        END IF
        """,
        """
        FOR i IN 1..10 LOOP
            INSERT INTO numbers VALUES (i);
        END LOOP
        """,
    ]

    for query in queries:
        libsqlglot.transpile(query)


def training_workload_dml():
    """DML statements - INSERT, UPDATE, DELETE."""
    queries = [
        "INSERT INTO users (id, name) VALUES (1, 'Alice')",
        "UPDATE users SET name = 'Bob' WHERE id = 1",
        "DELETE FROM users WHERE age < 18",
        "INSERT INTO users SELECT * FROM temp_users",
    ]

    for query in queries:
        libsqlglot.transpile(query)


def main():
    print("=" * 70)
    print("Profile-Guided Optimization (PGO) Training Workload")
    print("=" * 70)
    print("\nGenerating profile data for optimization...")
    print("This will take several minutes and exercise all hot paths.\n")

    # Run comprehensive workload to generate profile data
    workloads = [
        ("Simple SELECT queries", training_workload_simple, 10000),
        ("JOIN queries", training_workload_joins, 5000),
        ("Complex queries (CTEs, subqueries)", training_workload_complex, 2000),
        ("Cross-dialect transpilation", training_workload_transpilation, 5000),
        ("Procedural SQL", training_workload_procedural, 2000),
        ("DML statements", training_workload_dml, 5000),
    ]

    total_start = time.perf_counter()

    for name, func, iterations in workloads:
        benchmark(name, func, iterations)

    total_elapsed = time.perf_counter() - total_start

    print("\n" + "=" * 70)
    print(f"Total training time: {total_elapsed:.2f}s")
    print("=" * 70)
    print("\n✓ Profile data generated successfully!")
    print("\nNext steps:")
    print("  1. Rebuild with PGO: cmake -B build -DLIBSQLGLOT_PGO_USE=ON")
    print("  2. cmake --build build -j8")
    print("  3. Run benchmarks to verify improvements")


if __name__ == "__main__":
    main()
