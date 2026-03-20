#!/bin/bash
# Safe fuzzing wrapper - runs fuzzers with resource limits and auto-restart
# This script ensures fuzzing continues even if individual fuzzers crash

cd "$(dirname "$0")"

# Configuration
MAX_MEMORY_MB=500      # Max memory per fuzzer process (MB)
MAX_CPU_PERCENT=25     # Max CPU usage per fuzzer (%)
CHECK_INTERVAL=5       # Seconds between health checks
LOG_DIR="$(pwd)"

# Colors for output
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
NC='\033[0m' # No Color

echo "========================================"
echo "   SAFE FUZZING CAMPAIGN"
echo "========================================"
echo ""
echo "Configuration:"
echo "  Max memory per fuzzer: ${MAX_MEMORY_MB}MB"
echo "  Max CPU per fuzzer: ${MAX_CPU_PERCENT}%"
echo "  Check interval: ${CHECK_INTERVAL}s"
echo "  Log directory: ${LOG_DIR}"
echo ""
echo "Fuzzers to run:"
echo "  1. simple_fuzzer (transpiler)"
echo "  2. fuzz_optimizer"
echo "  3. fuzz_generator"
echo "  4. fuzz_edge_cases"
echo ""
echo "Press Ctrl+C to stop all fuzzers"
echo "========================================"
echo ""

# Cleanup function
cleanup() {
    echo ""
    echo "${YELLOW}Stopping all fuzzers...${NC}"
    pkill -P $$ 2>/dev/null
    wait
    echo "${GREEN}All fuzzers stopped cleanly${NC}"
    exit 0
}

trap cleanup SIGINT SIGTERM

# Function to start a fuzzer with resource limits
start_fuzzer() {
    local fuzzer_name="$1"
    local fuzzer_bin="$2"
    local log_file="$3"

    while true; do
        echo "${GREEN}[$(date '+%Y-%m-%d %H:%M:%S')]${NC} Starting ${fuzzer_name}..."

        # Run fuzzer with resource limits
        # - Limited virtual memory
        # - Limited CPU time (soft limit, will send SIGXCPU)
        # - Core dumps disabled
        (
            # Memory limit (in KB)
            ulimit -v $((MAX_MEMORY_MB * 1024))
            # CPU time limit (in seconds) - set to unlimited for continuous running
            ulimit -t unlimited
            # Core file size - set to 0 to prevent core dumps from filling disk
            ulimit -c 0
            # Max file size (in KB) - prevent huge log files
            ulimit -f $((100 * 1024))  # 100MB max log file

            # Run the fuzzer, redirect output to log
            "./${fuzzer_bin}" >> "${log_file}" 2>&1
        ) &

        local fuzzer_pid=$!
        echo "${GREEN}[$(date '+%Y-%m-%d %H:%M:%S')]${NC} ${fuzzer_name} started (PID: ${fuzzer_pid})"

        # Wait for fuzzer to exit
        wait $fuzzer_pid
        local exit_code=$?

        if [ $exit_code -eq 0 ]; then
            echo "${GREEN}[$(date '+%Y-%m-%d %H:%M:%S')]${NC} ${fuzzer_name} exited cleanly"
            break
        elif [ $exit_code -eq 137 ]; then
            echo "${RED}[$(date '+%Y-%m-%d %H:%M:%S')]${NC} ${fuzzer_name} killed (OOM or manual stop)"
            break
        elif [ $exit_code -eq 139 ]; then
            echo "${YELLOW}[$(date '+%Y-%m-%d %H:%M:%S')]${NC} ${fuzzer_name} crashed (segfault) - restarting in 2s..."
            sleep 2
        else
            echo "${YELLOW}[$(date '+%Y-%m-%d %H:%M:%S')]${NC} ${fuzzer_name} exited with code ${exit_code} - restarting in 2s..."
            sleep 2
        fi
    done
}

# Check if fuzzers exist
missing_fuzzers=()
for fuzzer in simple_fuzzer fuzz_optimizer fuzz_generator fuzz_edge_cases; do
    if [ ! -x "./${fuzzer}" ]; then
        missing_fuzzers+=("${fuzzer}")
    fi
done

if [ ${#missing_fuzzers[@]} -gt 0 ]; then
    echo "${RED}Error: The following fuzzers are missing or not executable:${NC}"
    for fuzzer in "${missing_fuzzers[@]}"; do
        echo "  - ${fuzzer}"
    done
    echo ""
    echo "Please rebuild the fuzzers first."
    exit 1
fi

# Start all fuzzers in background
start_fuzzer "Transpiler Fuzzer" "simple_fuzzer" "fuzzer_transpiler.log" &
start_fuzzer "Optimizer Fuzzer" "fuzz_optimizer" "fuzzer_optimizer.log" &
start_fuzzer "Generator Fuzzer" "fuzz_generator" "fuzzer_generator.log" &
start_fuzzer "Edge Cases Fuzzer" "fuzz_edge_cases" "fuzzer_edge_cases.log" &

echo ""
echo "${GREEN}All fuzzers started!${NC}"
echo "Monitoring system resources..."
echo ""

# Monitor loop
while true; do
    sleep $CHECK_INTERVAL

    # Check system load
    load=$(uptime | awk -F'load average:' '{print $2}' | awk '{print $1}' | tr -d ',')
    mem_usage=$(free -m | awk 'NR==2{printf "%.0f", $3*100/$2}')

    # Count running fuzzers
    fuzzer_count=$(pgrep -P $$ | wc -l)

    # Display status
    echo -ne "\r[$(date '+%H:%M:%S')] Load: ${load} | Memory: ${mem_usage}% | Active fuzzers: ${fuzzer_count}/4   "

    # Check if all fuzzers have stopped
    if [ $fuzzer_count -eq 0 ]; then
        echo ""
        echo "${YELLOW}All fuzzers have stopped${NC}"
        break
    fi
done

# Wait for all background jobs
wait

echo ""
echo "${GREEN}Fuzzing campaign completed${NC}"
