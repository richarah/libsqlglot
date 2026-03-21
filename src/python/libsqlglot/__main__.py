#!/usr/bin/env python3
"""
libsqlglot CLI tool - SQL transpiler with pipe support

Usage:
    echo "SELECT * FROM users" | libsqlglot --read mysql --write postgres
    libsqlglot --read mysql --write spark < input.sql > output.sql
    libsqlglot -r mysql -w bigquery --pretty < query.sql
"""

import sys
import argparse
import libsqlglot

def main():
    parser = argparse.ArgumentParser(
        description='SQL transpiler - convert SQL between dialects',
        formatter_class=argparse.RawDescriptionHelpFormatter,
        epilog="""
Examples:
  # Pipe from stdin to stdout
  echo "SELECT * FROM users" | libsqlglot -r mysql -w postgres

  # Read from file, write to stdout
  libsqlglot -r mysql -w spark < input.sql

  # Pretty-print output
  libsqlglot -r mysql -w bigquery --pretty < query.sql

Supported dialects:
  ansi, mysql, postgresql (postgres), sqlite, bigquery, snowflake,
  redshift, oracle, sqlserver (tsql), duckdb, clickhouse, presto,
  trino, hive, spark, athena, databricks
        """)

    parser.add_argument('-r', '--read', '--from', dest='read',
                        default='ansi',
                        help='Source SQL dialect (default: ansi)')
    parser.add_argument('-w', '--write', '--to', dest='write',
                        default='ansi',
                        help='Target SQL dialect (default: ansi)')
    parser.add_argument('--pretty', action='store_true',
                        help='Pretty-print output SQL')
    parser.add_argument('-v', '--version', action='version',
                        version=f'libsqlglot {libsqlglot.__version__}')
    parser.add_argument('input', nargs='?', type=argparse.FileType('r'), default=sys.stdin,
                        help='Input SQL file (default: stdin)')
    parser.add_argument('output', nargs='?', type=argparse.FileType('w'), default=sys.stdout,
                        help='Output SQL file (default: stdout)')

    args = parser.parse_args()

    try:
        # Read SQL from input
        sql = args.input.read()

        if not sql.strip():
            print("Error: No SQL input provided", file=sys.stderr)
            sys.exit(1)

        # Transpile
        result = libsqlglot.transpile(
            sql,
            read=args.read.lower(),
            write=args.write.lower()
        )

        # Write to output
        args.output.write(result)
        if args.output == sys.stdout and not result.endswith('\n'):
            args.output.write('\n')

    except Exception as e:
        print(f"Error: {e}", file=sys.stderr)
        sys.exit(1)

if __name__ == '__main__':
    main()
