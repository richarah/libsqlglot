#!/bin/bash
set -e

# Release script for libsqlglot
# Creates a GitHub release and automatically publishes to PyPI
#
# Usage: ./scripts/release.sh <version>
# Example: ./scripts/release.sh v0.1.3

VERSION="$1"

if [ -z "$VERSION" ]; then
    echo "Usage: $0 <version>"
    echo "Example: $0 v0.1.3"
    exit 1
fi

# Validate version format
if ! [[ "$VERSION" =~ ^v[0-9]+\.[0-9]+\.[0-9]+$ ]]; then
    echo "ERROR: Version must be in format vX.Y.Z (e.g., v0.1.3)"
    exit 1
fi

# Check we're on master branch
CURRENT_BRANCH=$(git rev-parse --abbrev-ref HEAD)
if [ "$CURRENT_BRANCH" != "master" ]; then
    echo "ERROR: Must be on master branch to create release (currently on: $CURRENT_BRANCH)"
    exit 1
fi

# Check working directory is clean
if ! git diff-index --quiet HEAD --; then
    echo "ERROR: Working directory is not clean. Commit or stash changes first."
    git status
    exit 1
fi

echo "========================================="
echo "Creating release: $VERSION"
echo "========================================="
echo ""

# Update version in CMakeLists.txt
VERSION_NO_V="${VERSION#v}"
echo "Updating CMakeLists.txt to version $VERSION_NO_V..."
sed -i "s/^project(libsqlglot VERSION .*/project(libsqlglot VERSION $VERSION_NO_V LANGUAGES CXX)/" CMakeLists.txt

# Update version in pyproject.toml
echo "Updating pyproject.toml to version $VERSION_NO_V..."
sed -i "s/^version = .*/version = \"$VERSION_NO_V\"/" pyproject.toml

# Commit version bumps
git add CMakeLists.txt pyproject.toml
git commit -m "Bump version to $VERSION"

# Create and push tag
echo "Creating tag $VERSION..."
git tag -a "$VERSION" -m "Release $VERSION"

echo "Pushing to origin..."
git push origin master
git push origin "$VERSION"

# Create GitHub release (triggers wheel build and PyPI upload)
echo ""
echo "Creating GitHub release..."
if command -v gh &> /dev/null; then
    # Generate release notes from commits since last tag
    LAST_TAG=$(git describe --tags --abbrev=0 HEAD^ 2>/dev/null || echo "")

    if [ -n "$LAST_TAG" ]; then
        RELEASE_NOTES=$(git log --pretty=format:"- %s" "$LAST_TAG..HEAD")
    else
        RELEASE_NOTES=$(git log --pretty=format:"- %s" HEAD~10..HEAD)
    fi

    gh release create "$VERSION" \
        --title "Release $VERSION" \
        --notes "$RELEASE_NOTES" \
        --generate-notes

    echo ""
    echo "========================================="
    echo "✓ Release $VERSION created successfully!"
    echo "========================================="
    echo ""
    echo "GitHub Actions will now:"
    echo "  1. Build Docker image with GCC trunk + reflection"
    echo "  2. Build manylinux wheels in Docker"
    echo "  3. Upload wheels to GitHub release"
    echo "  4. Publish wheels to PyPI"
    echo ""
    echo "Monitor progress at:"
    echo "  https://github.com/$(git config --get remote.origin.url | sed 's/.*github.com[:/]\(.*\)\.git/\1/')/actions"
    echo ""
    echo "To build wheels locally:"
    echo "  docker compose -f docker/docker-compose.yml run --rm wheel"
    echo ""
else
    echo "WARNING: 'gh' CLI not found. Please install it to auto-create releases."
    echo "         Or manually create release at: https://github.com/$(git config --get remote.origin.url | sed 's/.*github.com[:/]\(.*\)\.git/\1/')/releases/new"
    echo ""
    echo "Tag $VERSION has been pushed. Create the release manually to trigger PyPI publish."
fi
