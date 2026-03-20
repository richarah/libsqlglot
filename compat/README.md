# sqlglot Compatibility Testing

Test libsqlglot's compatibility with Python sqlglot by running the same SQL queries through both parsers.

## Setup

```bash
# Install dependencies
pip install sqlglot libsqlglot

# Clone sqlglot repository (if not already available)
git clone https://github.com/tobymao/sqlglot.git ../sqlglot
```

## Run tests

```bash
# Run all compatibility tests
python sqlglot_compat.py --sqlglot-path ../sqlglot

# Run limited test set
python sqlglot_compat.py --sqlglot-path ../sqlglot --limit 1000

# Save detailed report
python sqlglot_compat.py --sqlglot-path ../sqlglot --output compat_report.json
```

## What it tests

The compatibility tester:
1. Loads SQL fixtures from sqlglot's test suite
2. Parses each query with both Python sqlglot and C++ libsqlglot
3. Compares results (both should parse or both should fail)
4. Generates a detailed compatibility report

## Expected results

**Current Compatibility**: ~85-95% expected

Differences are expected due to:
- Feature coverage (libsqlglot implements core SQL, sqlglot has more dialects)
- Edge case handling
- Error message differences

## Compatibility report format

```json
{
  "total": 10000,
  "passed": 9234,
  "failed": 766,
  "pass_rate": 92.34,
  "errors": [
    {
      "sql": "SELECT ...",
      "file": "test_select.sql",
      "line": 42,
      "error": "libsqlglot failed: ..."
    }
  ]
}
```

## CI integration

```yaml
# .github/workflows/compat.yml
name: sqlglot Compatibility
on: [push, pull_request]

jobs:
  compat:
    runs-on: ubuntu-latest
    steps:
      - uses: actions/checkout@v2
      - name: Setup Python
        uses: actions/setup-python@v2
        with:
          python-version: '3.10'
      - name: Install dependencies
        run: |
          pip install sqlglot libsqlglot
          git clone https://github.com/tobymao/sqlglot.git
      - name: Run compatibility tests
        run: python compat/sqlglot_compat.py --limit 1000
```

## Improving compatibility

To improve compatibility:
1. Run: `python sqlglot_compat.py --limit 100 --output report.json`
2. Review errors in `report.json`
3. Fix parser/generator for failed cases
4. Re-run tests to verify improvements
5. Iterate until target compatibility reached
