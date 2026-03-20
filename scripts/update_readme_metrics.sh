#!/bin/bash
# Update README.md with current codebase metrics
# Run from project root: ./scripts/update_readme_metrics.sh

set -e

README="README.md"
INCLUDE_DIR="include/libsqlglot"
MAD_QUERIES_DIR="benchmarks/mad_queries"

# Color output
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
NC='\033[0m' # No Color

info() { echo -e "${GREEN}[INFO]${NC} $1"; }
warn() { echo -e "${YELLOW}[WARN]${NC} $1"; }
error() { echo -e "${RED}[ERROR]${NC} $1"; exit 1; }

# Check we're in project root
[[ -f "$README" && -d "$INCLUDE_DIR" ]] || error "Run from project root"

info "Collecting codebase metrics..."

# Count header files
num_files=$(find "$INCLUDE_DIR" -name "*.h" | wc -l)
total_lines=$(find "$INCLUDE_DIR" -name "*.h" -exec cat {} \; | wc -l)
# Format with commas
total_lines_fmt=$(echo "$total_lines" | sed ':a;s/\B[0-9]\{3\}\>/,&/;ta')
num_cpp=$(find "$INCLUDE_DIR" -name "*.cpp" | wc -l)

# Specific file line counts
parser_lines=$(wc -l < "$INCLUDE_DIR/parser.h")
generator_lines=$(wc -l < "$INCLUDE_DIR/generator.h")
expression_lines=$(wc -l < "$INCLUDE_DIR/expression.h")
transpiler_lines=$(wc -l < "$INCLUDE_DIR/transpiler.h")

# Count expression types (enum class ExprType)
expr_types=$(grep -A 200 "enum class ExprType" "$INCLUDE_DIR/expression.h" | grep -c "^    [A-Z]" || true)

# Mad queries metrics
if [[ -d "$MAD_QUERIES_DIR" ]]; then
    mad_lines=$(find "$MAD_QUERIES_DIR" -name "*.sql" -exec cat {} \; | wc -l)
    mad_lines_fmt=$(echo "$mad_lines" | sed ':a;s/\B[0-9]\{3\}\>/,&/;ta')
    mad_bytes=$(find "$MAD_QUERIES_DIR" -name "*.sql" -exec cat {} \; | wc -c)
    mad_kb=$((mad_bytes / 1024))
else
    warn "Mad queries directory not found, skipping"
    mad_lines=0
    mad_lines_fmt="0"
    mad_kb=0
fi

# Test metrics (requires build)
if [[ -f "build/tests/libsqlglot_tests" ]]; then
    test_output=$(build/tests/libsqlglot_tests --reporter compact 2>&1 | tail -1)
    num_assertions=$(echo "$test_output" | grep -oP '\d+(?= assertions)' || echo "0")
    num_tests=$(echo "$test_output" | grep -oP '\d+(?= test cases)' || echo "0")
    num_assertions_fmt=$(echo "$num_assertions" | sed ':a;s/\B[0-9]\{3\}\>/,&/;ta')
    num_tests_fmt=$(echo "$num_tests" | sed ':a;s/\B[0-9]\{3\}\>/,&/;ta')
    has_tests=true
else
    warn "Tests not built, skipping test metrics"
    has_tests=false
fi

info "Metrics collected:"
echo "  Files: $num_files"
echo "  Total lines: $total_lines_fmt"
echo "  parser.h: $parser_lines lines"
echo "  generator.h: $generator_lines lines"
echo "  expression.h: $expression_lines lines"
echo "  transpiler.h: $transpiler_lines lines"
echo "  Expression types: $expr_types"
if [[ "$has_tests" == "true" ]]; then
    echo "  Test cases: $num_tests_fmt"
    echo "  Assertions: $num_assertions_fmt"
else
    echo "  Test cases: (not built)"
    echo "  Assertions: (not built)"
fi
echo "  Mad queries: $mad_lines_fmt lines, ${mad_kb}KB"

# Update README (using sed for in-place editing)
info "Updating README.md..."

# Create backup
cp "$README" "${README}.bak"

# Architecture section
sed -i "s/^[0-9,]* lines of C++ headers, [0-9]* files/${total_lines_fmt} lines of C++ headers, ${num_files} files/" "$README"
sed -i "s/\`parser\.h\` ([0-9,]* lines)/\`parser.h\` (${parser_lines} lines)/" "$README"
sed -i "s/\`generator\.h\` ([0-9,]*)/\`generator.h\` (${generator_lines})/" "$README"
sed -i "s/\`expression\.h\` ([0-9,]*, [0-9]* expression types)/\`expression.h\` (${expression_lines}, ${expr_types} expression types)/" "$README"
sed -i "s/\`transpiler\.h\` ([0-9]* lines)/\`transpiler.h\` (${transpiler_lines} lines)/" "$README"

# Test section (only if tests were built)
if [[ "$has_tests" == "true" ]]; then
    sed -i "s/^[0-9,]* test cases, [0-9,]* assertions/${num_tests_fmt} test cases, ${num_assertions_fmt} assertions/" "$README"
    sed -i "s/^[0-9,]* assertions covering SQL/${num_assertions_fmt} assertions covering SQL/" "$README"
    sed -i "s/Passes [0-9,]* assertions across [0-9,]* test cases/Passes ${num_assertions_fmt} assertions across ${num_tests_fmt} test cases/" "$README"
fi

# Comparison table
sed -i "s/| \*\*Codebase\*\* | [0-9,]* lines C++/| **Codebase** | ${total_lines_fmt} lines C++/" "$README"

# Mad queries
if [[ $mad_lines -gt 0 ]]; then
    sed -i "s/[0-9,]* lines of SQL, [0-9]*KB total/${mad_lines_fmt} lines of SQL, ${mad_kb}KB total/" "$README"
fi

info "README.md updated successfully"
info "Backup saved to ${README}.bak"

# Show diff
if command -v diff &> /dev/null; then
    echo ""
    info "Changes made:"
    diff -u "${README}.bak" "$README" || true
fi
