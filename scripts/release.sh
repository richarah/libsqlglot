#!/bin/bash
set -e

# Build wheel using Docker and publish to PyPI
# Usage: ./scripts/release.sh [--test-pypi]

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
PROJECT_ROOT="$(cd "$SCRIPT_DIR/.." && pwd)"

TEST_PYPI=false
if [ "$1" = "--test-pypi" ]; then
    TEST_PYPI=true
    shift
fi

cd "$PROJECT_ROOT"

echo "========================================="
echo "Building wheel with Docker"
echo "========================================="
echo ""

# Clean previous builds
echo "Cleaning previous builds..."
rm -rf dist/ build/ *.egg-info
mkdir -p dist

# Build the wheel using Docker
echo "Building wheel in Docker container..."
docker-compose -f docker/docker-compose.yml up wheel

# Check if wheel was created
if [ ! -f dist/*.whl ]; then
    echo "ERROR: No wheel found in dist/"
    echo "Docker build may have failed. Check logs with:"
    echo "  docker-compose -f docker/docker-compose.yml logs wheel"
    exit 1
fi

WHEEL_FILE=$(ls -t dist/*.whl | head -1)
echo ""
echo "✓ Wheel built successfully: $WHEEL_FILE"
echo ""

# Extract version from wheel filename
VERSION=$(basename "$WHEEL_FILE" | sed 's/libsqlglot-\([0-9.]*\)-.*/\1/')
echo "Version: $VERSION"
echo ""

# Verify the wheel
echo "========================================="
echo "Verifying wheel"
echo "========================================="
echo ""

if ! command -v twine &> /dev/null; then
    echo "Installing twine..."
    pip install twine
fi

echo "Running twine check..."
twine check "$WHEEL_FILE"

if [ $? -ne 0 ]; then
    echo "ERROR: Wheel verification failed"
    exit 1
fi

echo ""
echo "✓ Wheel verification passed"
echo ""

# Upload to PyPI
echo "========================================="
echo "Publishing to PyPI"
echo "========================================="
echo ""

if [ "$TEST_PYPI" = true ]; then
    echo "Uploading to TestPyPI..."
    twine upload --repository testpypi "$WHEEL_FILE"

    echo ""
    echo "========================================="
    echo "✓ Published to TestPyPI"
    echo "========================================="
    echo ""
    echo "Test installation with:"
    echo "  pip install --index-url https://test.pypi.org/simple/ libsqlglot==$VERSION"
    echo ""
    echo "If everything works, publish to production PyPI with:"
    echo "  ./scripts/build_and_publish.sh"
else
    echo "Uploading to PyPI..."
    read -p "Are you sure you want to publish libsqlglot $VERSION to PyPI? (y/N) " -n 1 -r
    echo
    if [[ $REPLY =~ ^[Yy]$ ]]; then
        twine upload "$WHEEL_FILE"

        echo ""
        echo "========================================="
        echo "✓ Published to PyPI"
        echo "========================================="
        echo ""
        echo "Install with:"
        echo "  pip install libsqlglot==$VERSION"
        echo ""
        echo "View on PyPI:"
        echo "  https://pypi.org/project/libsqlglot/$VERSION/"
    else
        echo ""
        echo "Upload cancelled."
        echo ""
        echo "To upload to TestPyPI first, run:"
        echo "  ./scripts/build_and_publish.sh --test-pypi"
    fi
fi
