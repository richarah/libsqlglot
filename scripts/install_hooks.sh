#!/bin/bash
# Install git hooks

set -e

if [[ ! -d .git ]]; then
    echo "ERROR: Not a git repository. Run from project root."
    exit 1
fi

echo "Installing git hooks..."

# Create symlink for pre-commit hook
ln -sf ../../.githooks/pre-commit .git/hooks/pre-commit
chmod +x .git/hooks/pre-commit

echo "✓ pre-commit hook installed"
echo ""
echo "The hook will auto-update README metrics when you commit changes to:"
echo "  - README.md"
echo "  - include/**/*.h"
echo "  - tests/**"
echo ""
echo "To uninstall: rm .git/hooks/pre-commit"
