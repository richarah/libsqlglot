#!/usr/bin/env python3
"""
Complete benchmark comparison: Standard sqlglot benchmarks + Mad Queries
Calculates blended average speedup
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

def benchmark_query(sql, iterations=100):
    """Benchmark parsing and generation"""
    try:
        # Warmup
        parsed = sqlglot.parse_one(sql, read='postgres')
        if parsed is None:
            raise ValueError("Parse failed")

        # Benchmark parsing
        start = time.perf_counter()
        for _ in range(iterations):
            parsed = sqlglot.parse_one(sql, read='postgres')
        parse_time = (time.perf_counter() - start) / iterations

        # Benchmark generation
        parsed = sqlglot.parse_one(sql, read='postgres')
        start = time.perf_counter()
        for _ in range(iterations):
            output = parsed.sql(dialect='postgres')
        gen_time = (time.perf_counter() - start) / iterations

        return {
            'success': True,
            'parse_time_us': parse_time * 1_000_000,
            'gen_time_us': gen_time * 1_000_000,
            'total_time_us': (parse_time + gen_time) * 1_000_000
        }
    except RecursionError:
        return {'success': False, 'error': 'RecursionError (stack overflow)'}
    except Exception as e:
        return {'success': False, 'error': str(e)[:50]}

def main():
    print("=" * 100)
    print("COMPLETE BENCHMARK: Standard sqlglot Benchmarks + TRULY MAD Queries")
    print("=" * 100)
    print()

    # Standard sqlglot benchmarks (matching README.md table)
    standard_benchmarks = {
        'tpch': """
            SELECT
                l_returnflag,
                l_linestatus,
                SUM(l_quantity) as sum_qty,
                SUM(l_extendedprice) as sum_base_price,
                SUM(l_extendedprice * (1 - l_discount)) as sum_disc_price,
                SUM(l_extendedprice * (1 - l_discount) * (1 + l_tax)) as sum_charge,
                AVG(l_quantity) as avg_qty,
                AVG(l_extendedprice) as avg_price,
                AVG(l_discount) as avg_disc,
                COUNT(*) as count_order
            FROM lineitem
            WHERE l_shipdate <= DATE '1998-12-01'
            GROUP BY l_returnflag, l_linestatus
            ORDER BY l_returnflag, l_linestatus
        """,
        'short': "SELECT a FROM b",
        'deep_arithmetic': "SELECT ((((((1 + 2) * 3) / 4) - 5) + 6) * 7) / 8 as result",
        'large_in': "SELECT * FROM users WHERE id IN (" + ", ".join(str(i) for i in range(1000)) + ")",
        'values': "INSERT INTO users (id, name) VALUES " + ", ".join(f"({i}, 'user{i}')" for i in range(500)),
        'many_joins': """
            SELECT * FROM t1
            JOIN t2 ON t1.id = t2.id
            JOIN t3 ON t2.id = t3.id
            JOIN t4 ON t3.id = t4.id
            JOIN t5 ON t4.id = t5.id
            JOIN t6 ON t5.id = t6.id
            JOIN t7 ON t6.id = t7.id
            JOIN t8 ON t7.id = t8.id
            JOIN t9 ON t8.id = t9.id
            JOIN t10 ON t9.id = t10.id
        """,
        'many_unions': " UNION ".join(f"SELECT {i} as n" for i in range(50)),
        'nested_subqueries': """
            SELECT * FROM (
                SELECT * FROM (
                    SELECT * FROM (
                        SELECT * FROM (
                            SELECT * FROM users
                        ) a
                    ) b
                ) c
            ) d
        """,
        'many_columns': "SELECT " + ", ".join(f"col{i}" for i in range(100)) + " FROM wide_table",
        'large_case': "SELECT CASE " + " ".join(f"WHEN x = {i} THEN {i*10}" for i in range(100)) + " ELSE 0 END as result FROM t",
        'complex_where': """
            SELECT * FROM users
            WHERE (age > 18 AND age < 65)
                AND (status = 'active' OR status = 'pending')
                AND (score > 100 OR (level > 5 AND experience > 1000))
                AND created_at > '2020-01-01'
                AND updated_at < '2025-12-31'
        """,
        'many_ctes': """
            WITH cte1 AS (SELECT * FROM t1),
                 cte2 AS (SELECT * FROM t2),
                 cte3 AS (SELECT * FROM t3),
                 cte4 AS (SELECT * FROM t4),
                 cte5 AS (SELECT * FROM t5),
                 cte6 AS (SELECT * FROM cte1 JOIN cte2 ON cte1.id = cte2.id)
            SELECT * FROM cte6
        """,
        'many_windows': """
            SELECT
                id,
                ROW_NUMBER() OVER (ORDER BY id) as rn1,
                RANK() OVER (ORDER BY score) as rn2,
                DENSE_RANK() OVER (PARTITION BY category ORDER BY score DESC) as rn3,
                LAG(value) OVER (ORDER BY date) as lag_val,
                LEAD(value) OVER (ORDER BY date) as lead_val,
                SUM(amount) OVER (PARTITION BY user_id ORDER BY date) as running_sum
            FROM data
        """,
        'nested_functions': """
            SELECT
                UPPER(LOWER(TRIM(SUBSTRING(CONCAT(COALESCE(name, ''), ' - '), 1, 10)))) as processed,
                ROUND(ABS(SQRT(POWER(x, 2) + POWER(y, 2))), 2) as distance
            FROM points
        """,
        'large_strings': "SELECT '" + ("x" * 1000) + "' as long_string FROM t",
        'many_numbers': "SELECT " + " + ".join(str(i) for i in range(500)) + " as total"
    }

    # libsqlglot times from README.md (in seconds)
    libsqlglot_times = {
        'tpch': 0.000007,
        'short': 0.000002,
        'deep_arithmetic': 0.000003,
        'large_in': 0.000123,
        'values': 0.000159,
        'many_joins': 0.000006,
        'many_unions': 0.000019,
        'nested_subqueries': 0.000003,
        'many_columns': 0.000013,
        'large_case': 0.000037,
        'complex_where': 0.000004,
        'many_ctes': 0.000007,
        'many_windows': 0.000006,
        'nested_functions': 0.000005,
        'large_strings': 0.000004,
        'many_numbers': 0.000068
    }

    # Mad queries
    mad_queries = [
        ("Deep CTE nesting", "query1_deep_ctes_windows.sql"),
        ("Deep CASE nesting", "query2_deep_case.sql"),
        ("Complex subqueries", "query3_multiple_subqueries.sql"),
        ("Multi-table joins", "query4_complex_joins_windows.sql"),
        ("Union chains", "query5_union_extract.sql"),
        ("Complex string functions", "query6_string_concat.sql"),
        ("Correlated subqueries", "query7_correlated_subqueries.sql"),
        ("Complex WHERE clause", "query8_complex_where.sql")
    ]

    # libsqlglot mad query times (in microseconds, from bench_mad_queries output)
    libsqlglot_mad_times = {
        "Deep CTE nesting": 82.36,
        "Deep CASE nesting": 103.10,
        "Complex subqueries": 73.18,
        "Multi-table joins": 141.16,
        "Union chains": 115.77,
        "Complex string functions": 71.42,
        "Correlated subqueries": 60.60,
        "Complex WHERE clause": 81.99
    }

    print("PART 1: Standard sqlglot Benchmarks")
    print("=" * 100)
    print(f"{'Query':<25} {'Size':>8} {'sqlglot (μs)':>15} {'libsqlglot (μs)':>18} {'Speedup':>12}")
    print("-" * 100)

    standard_results = []
    for name, sql in standard_benchmarks.items():
        iterations = 10 if len(sql) > 1000 else 100
        result = benchmark_query(sql, iterations)

        if result['success']:
            sqlglot_time = result['total_time_us']
            libsqlglot_time = libsqlglot_times[name] * 1_000_000  # Convert to μs
            speedup = sqlglot_time / libsqlglot_time if libsqlglot_time > 0 else 0

            print(f"{name:<25} {len(sql):>8} {sqlglot_time:>15.2f} {libsqlglot_time:>18.2f} {speedup:>12.1f}×")
            standard_results.append({
                'name': name,
                'sqlglot_us': sqlglot_time,
                'libsqlglot_us': libsqlglot_time,
                'speedup': speedup
            })
        else:
            print(f"{name:<25} {len(sql):>8} FAILED: {result.get('error', 'Unknown error')}")

    print()
    print("PART 2: TRULY MAD Queries")
    print("=" * 100)
    print(f"{'Query':<25} {'Size':>8} {'sqlglot (μs)':>15} {'libsqlglot (μs)':>18} {'Speedup':>12}")
    print("-" * 100)

    mad_results = []
    base_path = Path("../benchmarks/mad_queries")
    for name, filename in mad_queries:
        try:
            sql = read_file(base_path / filename)
            result = benchmark_query(sql, iterations=10)  # Fewer iterations for complex queries

            if result['success']:
                sqlglot_time = result['total_time_us']
                libsqlglot_time = libsqlglot_mad_times[name]
                speedup = sqlglot_time / libsqlglot_time if libsqlglot_time > 0 else 0

                print(f"{name:<25} {len(sql):>8} {sqlglot_time:>15.2f} {libsqlglot_time:>18.2f} {speedup:>12.1f}×")
                mad_results.append({
                    'name': name,
                    'sqlglot_us': sqlglot_time,
                    'libsqlglot_us': libsqlglot_time,
                    'speedup': speedup
                })
            else:
                print(f"{name:<25} {len(sql):>8} FAILED: {result.get('error', 'Unknown error')}")
        except Exception as e:
            print(f"{name:<25} ERROR: {str(e)[:50]}")

    # Calculate blended average
    print()
    print("=" * 100)
    print("BLENDED AVERAGE CALCULATION")
    print("=" * 100)

    if standard_results and mad_results:
        # Calculate averages for each category
        std_speedups = [r['speedup'] for r in standard_results]
        mad_speedups = [r['speedup'] for r in mad_results]

        avg_std = sum(std_speedups) / len(std_speedups)
        avg_mad = sum(mad_speedups) / len(mad_speedups)

        # Blended average (equal weight)
        blended_equal = (avg_std + avg_mad) / 2

        # Blended average (query count weighted)
        total_queries = len(standard_results) + len(mad_results)
        blended_weighted = (sum(std_speedups) + sum(mad_speedups)) / total_queries

        print()
        print(f"Standard Benchmarks (n={len(standard_results)}):")
        print(f"  Average speedup: {avg_std:.1f}×")
        print(f"  Range: {min(std_speedups):.1f}× to {max(std_speedups):.1f}×")
        print()
        print(f"Mad Queries (n={len(mad_results)}):")
        print(f"  Average speedup: {avg_mad:.1f}×")
        print(f"  Range: {min(mad_speedups):.1f}× to {max(mad_speedups):.1f}×")
        print()
        print("=" * 100)
        print(f"BLENDED AVERAGE (equal category weight): {blended_equal:.1f}×")
        print(f"BLENDED AVERAGE (query count weighted):  {blended_weighted:.1f}×")
        print("=" * 100)
        print()
        print(f"Total queries tested: {total_queries}")
        print(f"  - Standard benchmarks: {len(standard_results)}")
        print(f"  - Mad queries: {len(mad_results)}")
        print()
        print(f"sqlglot version: {sqlglot.__version__}")

if __name__ == '__main__':
    main()
