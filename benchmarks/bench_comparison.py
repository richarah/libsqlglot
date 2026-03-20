#!/usr/bin/env python3
"""
Benchmark comparison between libsqlglot (C++) and sqlglot (Python)

Run with: python3 bench_comparison.py
"""

import time
import statistics
from typing import List, Tuple

# Try to import sqlglot Python
try:
    import sqlglot
    HAS_SQLGLOT = True
except ImportError:
    HAS_SQLGLOT = False
    print("Warning: sqlglot not installed. Install with: pip install sqlglot")

# Try to import libsqlglot C++
try:
    import libsqlglot
    HAS_LIBSQLGLOT = True
except ImportError:
    HAS_LIBSQLGLOT = False
    print("Warning: libsqlglot not installed. Build with: pip install -e .")

# Test queries
TEST_QUERIES = [
    ("Simple SELECT", "SELECT * FROM users"),
    ("SELECT with WHERE", "SELECT id, name FROM users WHERE age > 18 AND active = 1"),
    ("Complex JOIN", """
        SELECT u.id, u.name, COUNT(o.id) as order_count
        FROM users u
        LEFT JOIN orders o ON u.id = o.user_id
        WHERE u.active = 1
        GROUP BY u.id, u.name
        HAVING COUNT(o.id) > 5
        ORDER BY order_count DESC
        LIMIT 100
    """),
    ("CTE", """
        WITH active_users AS (
            SELECT id, name FROM users WHERE active = 1
        )
        SELECT * FROM active_users WHERE id > 100
    """),
    ("Window Function", """
        SELECT 
            id,
            name,
            ROW_NUMBER() OVER (ORDER BY score DESC) as rank
        FROM employees
    """),
]

def benchmark_sqlglot(sql: str, iterations: int = 1000) -> Tuple[float, float]:
    """Benchmark sqlglot Python"""
    if not HAS_SQLGLOT:
        return (0.0, 0.0)
    
    times = []
    for _ in range(iterations):
        start = time.perf_counter()
        try:
            parsed = sqlglot.parse_one(sql)
            result = parsed.sql()
        except Exception as e:
            # Skip queries that sqlglot can't handle
            return (0.0, 0.0)
        elapsed = time.perf_counter() - start
        times.append(elapsed)
    
    avg_time = statistics.mean(times)
    std_dev = statistics.stdev(times) if len(times) > 1 else 0.0
    return (avg_time, std_dev)

def benchmark_libsqlglot(sql: str, iterations: int = 1000) -> Tuple[float, float]:
    """Benchmark libsqlglot C++"""
    if not HAS_LIBSQLGLOT:
        return (0.0, 0.0)
    
    times = []
    for _ in range(iterations):
        start = time.perf_counter()
        try:
            result = libsqlglot.transpile(sql)
        except Exception as e:
            # Skip queries that fail
            return (0.0, 0.0)
        elapsed = time.perf_counter() - start
        times.append(elapsed)
    
    avg_time = statistics.mean(times)
    std_dev = statistics.stdev(times) if len(times) > 1 else 0.0
    return (avg_time, std_dev)

def format_time(seconds: float) -> str:
    """Format time in appropriate units"""
    if seconds == 0:
        return "N/A"
    elif seconds < 1e-6:
        return f"{seconds * 1e9:.2f} ns"
    elif seconds < 1e-3:
        return f"{seconds * 1e6:.2f} µs"
    elif seconds < 1:
        return f"{seconds * 1e3:.2f} ms"
    else:
        return f"{seconds:.2f} s"

def format_throughput(avg_time: float) -> str:
    """Format throughput in queries/second"""
    if avg_time == 0:
        return "N/A"
    return f"{1.0 / avg_time:,.0f} q/s"

def main():
    print("=" * 80)
    print("libsqlglot vs sqlglot Performance Comparison")
    print("=" * 80)
    print()
    
    if not HAS_SQLGLOT and not HAS_LIBSQLGLOT:
        print("ERROR: Neither library is available!")
        return
    
    if HAS_LIBSQLGLOT:
        print(f"[OK] libsqlglot C++ version: {libsqlglot.__version__}")
    else:
        print("[MISSING] libsqlglot C++ not available")

    if HAS_SQLGLOT:
        print(f"[OK] sqlglot Python version: {sqlglot.__version__}")
    else:
        print("[MISSING] sqlglot Python not available")
    
    print()
    print("Running benchmarks (1000 iterations each)...")
    print()
    
    # Header
    print(f"{'Query':<20} {'libsqlglot (C++)':<25} {'sqlglot (Python)':<25} {'Speedup':<10}")
    print("-" * 80)
    
    total_speedup = []
    
    for name, sql in TEST_QUERIES:
        # Benchmark both
        cpp_time, cpp_std = benchmark_libsqlglot(sql)
        py_time, py_std = benchmark_sqlglot(sql)
        
        # Calculate speedup
        if cpp_time > 0 and py_time > 0:
            speedup = py_time / cpp_time
            total_speedup.append(speedup)
            speedup_str = f"{speedup:.1f}x"
        else:
            speedup_str = "N/A"
        
        # Format output
        cpp_str = format_time(cpp_time) if cpp_time > 0 else "N/A"
        py_str = format_time(py_time) if py_time > 0 else "N/A"
        
        print(f"{name:<20} {cpp_str:<25} {py_str:<25} {speedup_str:<10}")
    
    print("-" * 80)
    
    # Summary
    if total_speedup:
        avg_speedup = statistics.mean(total_speedup)
        print()
        print(f"Average Speedup: {avg_speedup:.1f}x")
        print()
        
        # Throughput for simple SELECT
        if HAS_LIBSQLGLOT:
            simple_time, _ = benchmark_libsqlglot(TEST_QUERIES[0][1])
            if simple_time > 0:
                print(f"libsqlglot C++ throughput (simple SELECT): {format_throughput(simple_time)}")
        
        if HAS_SQLGLOT:
            simple_time, _ = benchmark_sqlglot(TEST_QUERIES[0][1])
            if simple_time > 0:
                print(f"sqlglot Python throughput (simple SELECT): {format_throughput(simple_time)}")
    
    print()
    print("=" * 80)

if __name__ == "__main__":
    main()
