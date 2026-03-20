#!/usr/bin/env python3
"""
Benchmark the TRULY MAD queries with Python sqlglot to compare performance
"""
import time
import sys
from pathlib import Path

try:
    import sqlglot
except ImportError:
    print("Error: sqlglot not installed. Install with: pip install sqlglot")
    sys.exit(1)

def read_file(path):
    with open(path, 'r') as f:
        return f.read()

def benchmark_query(name, sql, iterations=100):
    """Benchmark parsing and generation"""
    result = {
        'name': name,
        'size': len(sql),
        'iterations': iterations
    }

    # Benchmark parsing
    try:
        start = time.perf_counter()
        for _ in range(iterations):
            parsed = sqlglot.parse_one(sql, read='postgres')
            if parsed is None:
                raise ValueError("Parse failed")
        parse_time = (time.perf_counter() - start) / iterations
        result['parse_time_ms'] = parse_time * 1000
        result['parse_success'] = True

        # Benchmark generation
        parsed = sqlglot.parse_one(sql, read='postgres')
        start = time.perf_counter()
        for _ in range(iterations):
            output = parsed.sql(dialect='postgres')
        gen_time = (time.perf_counter() - start) / iterations
        result['gen_time_ms'] = gen_time * 1000
        result['gen_success'] = True
        result['total_time_ms'] = result['parse_time_ms'] + result['gen_time_ms']
    except RecursionError:
        result['parse_success'] = False
        result['gen_success'] = False
        result['error'] = 'RecursionError (stack overflow)'
    except Exception as e:
        result['parse_success'] = False
        result['gen_success'] = False
        result['error'] = str(e)[:50]

    return result

def main():
    print("Python sqlglot - TRULY MAD Query Benchmarks")
    print("=" * 85)
    print()

    base_path = Path("../benchmarks/mad_queries")

    queries = [
        ("Deep CTE nesting", "query1_deep_ctes_windows.sql"),
        ("Deep CASE nesting", "query2_deep_case.sql"),
        ("Complex subqueries", "query3_multiple_subqueries.sql"),
        ("Multi-table joins", "query4_complex_joins_windows.sql"),
        ("Union chains", "query5_union_extract.sql"),
        ("Complex string functions", "query6_string_concat.sql"),
        ("Correlated subqueries", "query7_correlated_subqueries.sql"),
        ("Complex WHERE clause", "query8_complex_where.sql")
    ]

    results = []

    print(f"{'Query':<25} {'Size':>10} {'Parse (μs)':>12} {'Gen (μs)':>12} {'Total (μs)':>12} {'Iters':>10}")
    print("-" * 85)

    for name, filename in queries:
        try:
            sql = read_file(base_path / filename)
            # Use fewer iterations for sqlglot as it's much slower
            iterations = 10 if len(sql) > 500 else 100
            result = benchmark_query(name, sql, iterations)
            results.append(result)

            if result.get('parse_success'):
                print(f"{result['name']:<25} {result['size']:>10} "
                      f"{result['parse_time_ms']*1000:>12.2f} "
                      f"{result['gen_time_ms']*1000:>12.2f} "
                      f"{result['total_time_ms']*1000:>12.2f} "
                      f"{result['iterations']:>10}")
            else:
                print(f"{result['name']:<25} {result['size']:>10} "
                      f"FAILED: {result.get('error', 'Unknown error')}")
        except Exception as e:
            print(f"{name:<25} ERROR: {str(e)[:50]}")

    # Summary
    successful = [r for r in results if r.get('parse_success')]
    if successful:
        total_parse = sum(r['parse_time_ms'] for r in successful)
        total_gen = sum(r['gen_time_ms'] for r in successful)
        total_size = sum(r['size'] for r in successful)

        print()
        print("=" * 85)
        print("Summary:")
        print(f"  Queries successful: {len(successful)}/{len(results)}")
        print(f"  Total query size: {int(total_size)} bytes")
        print(f"  Average parse time: {(total_parse / len(successful)) * 1000:.2f} μs")
        print(f"  Average generate time: {(total_gen / len(successful)) * 1000:.2f} μs")
        print(f"  Average total time: {((total_parse + total_gen) / len(successful)) * 1000:.2f} μs")

    print()
    print("Notes:")
    print("  - Python sqlglot (pure Python implementation)")
    print("  - Some queries may fail due to stack overflow (RecursionError)")
    print("  - Times in microseconds (μs = 0.001 milliseconds)")
    print(f"  - sqlglot version: {sqlglot.__version__}")

if __name__ == '__main__':
    main()
