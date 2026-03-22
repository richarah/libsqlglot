#!/usr/bin/env bash
# Convenience script for Docker builds
# Usage: ./docker/build.sh [target]

set -euo pipefail

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
PROJECT_ROOT="$(dirname "$SCRIPT_DIR")"

cd "$PROJECT_ROOT"

TARGET="${1:-build}"

case "$TARGET" in
    build)
        echo "🔨 Building libsqlglot with C++26 reflection..."
        docker compose -f docker/docker-compose.yml run --rm build
        ;;
    test)
        echo "🧪 Running tests..."
        docker compose -f docker/docker-compose.yml run --rm test
        ;;
    wheel)
        echo "📦 Building Python wheel..."
        docker compose -f docker/docker-compose.yml run --rm wheel
        ;;
    dev)
        echo "🛠️  Starting development shell..."
        docker compose -f docker/docker-compose.yml run --rm dev
        ;;
    clean)
        echo "🧹 Cleaning build artifacts..."
        docker compose -f docker/docker-compose.yml down -v
        ;;
    clean-build)
        echo "🔥 Clean build (no cache)..."
        docker compose -f docker/docker-compose.yml run --rm clean-build
        ;;
    *)
        echo "Usage: $0 {build|test|wheel|dev|clean|clean-build}"
        echo ""
        echo "Targets:"
        echo "  build        - Build the project"
        echo "  test         - Run tests"
        echo "  wheel        - Build Python wheel"
        echo "  dev          - Interactive development shell"
        echo "  clean        - Remove containers and volumes"
        echo "  clean-build  - Clean build without cache"
        exit 1
        ;;
esac

echo "✓ Done!"
