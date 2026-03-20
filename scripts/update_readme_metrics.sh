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

# Single find for all headers
mapfile -t header_files < <(find "$INCLUDE_DIR" -name "*.h")
num_files=${#header_files[@]}
num_cpp=$(find "$INCLUDE_DIR" -name "*.cpp" -print -quit | wc -l)

# Count total lines in one wc call
total_lines=$(cat "${header_files[@]}" | wc -l)
total_lines_fmt=$(echo "$total_lines" | sed ':a;s/\B[0-9]\{3\}\>/,&/;ta')

# Specific file line counts (single wc call with all files)
wc_output=$(wc -l "$INCLUDE_DIR/parser.h" "$INCLUDE_DIR/generator.h" \
                 "$INCLUDE_DIR/expression.h" "$INCLUDE_DIR/transpiler.h")
parser_lines=$(echo "$wc_output" | awk 'NR==1 {print $1}')
generator_lines=$(echo "$wc_output" | awk 'NR==2 {print $1}')
expression_lines=$(echo "$wc_output" | awk 'NR==3 {print $1}')
transpiler_lines=$(echo "$wc_output" | awk 'NR==4 {print $1}')

# Count expression types (enum class ExprType)
expr_types=$(awk '/enum class ExprType/,/^};/ {if (/^    [A-Z]/) count++} END {print count}' "$INCLUDE_DIR/expression.h")

# Mad queries metrics (cat once, count lines and bytes)
if [[ -d "$MAD_QUERIES_DIR" ]]; then
    mapfile -t mad_files < <(find "$MAD_QUERIES_DIR" -name "*.sql")
    if [[ ${#mad_files[@]} -gt 0 ]]; then
        mad_content=$(cat "${mad_files[@]}")
        mad_lines=$(echo "$mad_content" | wc -l)
        mad_bytes=$(echo "$mad_content" | wc -c)
        mad_lines_fmt=$(echo "$mad_lines" | sed ':a;s/\B[0-9]\{3\}\>/,&/;ta')
        mad_kb=$((mad_bytes / 1024))
    else
        mad_lines=0; mad_lines_fmt="0"; mad_kb=0
    fi
else
    warn "Mad queries directory not found, skipping"
    mad_lines=0; mad_lines_fmt="0"; mad_kb=0
fi

# Test metrics (requires build)
if [[ -f "build/tests/libsqlglot_tests" ]]; then
    test_output=$(build/tests/libsqlglot_tests --reporter compact 2>&1)
    num_tests=$(echo "$test_output" | grep -oP '\d+(?= test cases)' | head -1 || echo "0")
    num_assertions=$(echo "$test_output" | grep -oP '\d+(?= assertions)' | head -1 || echo "0")
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
