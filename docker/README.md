# Docker Build Environment

This directory contains Docker configurations for building libsqlglot with C++26 reflection support.

## Structure

```
docker/
├── Dockerfile              # Main build environment (GCC 14 + C++26 reflection)
├── docker-compose.yml      # Orchestration for build, test, and wheel generation
├── .dockerignore          # Files to exclude from Docker context
├── build.sh               # Convenience script for common operations
├── Dockerfile.legacy      # Legacy Ubuntu 24.04 with Clang 18
└── grammar-transpiler/    # ANTLR → C++ grammar transpilation
    ├── Dockerfile
    ├── docker-compose.yml
    └── README.md
```

## Requirements

- Docker 20.10+
- Docker Compose 2.0+
- 8GB+ RAM recommended for parallel builds
- 20GB+ disk space for Docker images and build cache

## Quick Start

```bash
# Build the project
docker compose -f docker/docker-compose.yml run --rm build

# Run tests
docker compose -f docker/docker-compose.yml run --rm test

# Build Python wheel
docker compose -f docker/docker-compose.yml run --rm wheel

# Interactive development shell
docker compose -f docker/docker-compose.yml run --rm dev

# Clean build (no cache)
docker compose -f docker/docker-compose.yml run --rm clean-build
```

## Features

### Multi-Stage Build
- **builder-base**: Minimal toolchain with GCC 14 trunk + C++26 reflection
- **builder**: Compiles the project
- **tester**: Runs test suite
- **wheel-builder**: Creates Python wheels
- **dev**: Interactive development environment
- **runtime**: Minimal runtime image for deployment

### Optimizations
- **ccache**: Speeds up rebuilds (persistent volume)
- **Ninja**: Fast parallel builds
- **BuildKit cache**: Docker layer caching
- **Minimal images**: Only essential dependencies

### Security
- No Docker files in project root
- Read-only git config mount
- Minimal runtime dependencies
- Regular base image updates

## Compiler Details

- **Base Image**: Ubuntu 24.04
- **GCC Version**: Trunk (built from source with reflection support)
- **C++ Standard**: C++26
- **Reflection**: `-freflection` flag enabled
- **Build System**: CMake 3.28+ with Ninja
- **Optimization**: ccache for faster rebuilds, LTO enabled in Release mode
- **Build Time**: Initial Docker image build takes ~30-45 minutes (one-time, cached)

## Volume Mounts

- `build-cache`: Persistent build artifacts (bind mount to `build/`)
- `ccache`: Compiler cache for faster rebuilds (Docker volume)
- Project root mounted at `/workspace` with `:cached` for better performance
- Git config mounted read-only in dev container

## Services

### build
Main build service that compiles the C++ library and Python bindings.
- **Target**: `builder` stage
- **Output**: Compiled binaries in `build/`
- **Features**: ccache statistics, parallel builds

### test
Runs the C++ test suite using Catch2.
- **Target**: `tester` stage
- **Command**: `ctest --output-on-failure --parallel`
- **Requires**: `build` service

### test-python
Runs Python binding tests.
- **Target**: `dev` stage
- **Command**: `pytest tests/python/`
- **Environment**: `PYTHONPATH` configured for local imports

### wheel
Builds manylinux-compatible Python wheels for distribution.
- **Target**: `wheel-builder` stage
- **Output**: `dist/*.whl`
- **Uses**: Static linking for portability

### dev
Interactive development shell with all build tools installed.
- **Target**: `dev` stage
- **Features**: ccache, git config, custom PS1 prompt
- **Usage**: Run `docker compose -f docker/docker-compose.yml run --rm dev`

### clean-build
Performs a clean build without using Docker layer cache.
- **Target**: `builder` stage
- **Options**: `no_cache: true`
- **Command**: Removes `build/` and rebuilds from scratch

## Customization

Edit `docker-compose.yml` to adjust:
- Build type (Release/Debug)
- CMake options
- Parallel build jobs
- Environment variables

## CI/CD Integration

```yaml
# Example GitHub Actions
- name: Build with Docker
  run: docker compose -f docker/docker-compose.yml run --rm build

- name: Run tests
  run: docker compose -f docker/docker-compose.yml run --rm test
```

## Cleanup

```bash
# Remove containers
docker compose -f docker/docker-compose.yml down

# Remove volumes (build cache)
docker compose -f docker/docker-compose.yml down -v

# Remove images
docker compose -f docker/docker-compose.yml down --rmi all
```

## Environment Variables

All services use a common environment configuration:

- `CCACHE_DIR=/cache/ccache` - Compiler cache directory
- `CCACHE_MAXSIZE=5G` - Maximum ccache size
- `CMAKE_GENERATOR=Ninja` - Use Ninja for faster builds
- `CMAKE_BUILD_TYPE=Release` - Optimized builds by default

Override in `docker-compose.yml` or via command line:
```bash
docker compose -f docker/docker-compose.yml run --rm -e CMAKE_BUILD_TYPE=Debug build
```

## Performance Tips

1. **ccache**: First build is slow, subsequent builds are 10-50× faster
2. **Parallel builds**: Uses all CPU cores via `$(nproc)`
3. **Volume caching**: `:delegated` and `:cached` flags for macOS/WSL performance
4. **BuildKit**: Enable with `export DOCKER_BUILDKIT=1` for faster image builds

## Troubleshooting

### Out of Memory
Reduce parallel jobs:
```bash
docker compose -f docker/docker-compose.yml run --rm build bash -c "cmake --build build --parallel 4"
```

### Permission Issues (WSL/Linux)
Ensure your user owns the project directory:
```bash
sudo chown -R $USER:$USER build/ dist/
```

### Reflection Not Found
Verify GCC trunk with reflection support:
```bash
docker compose -f docker/docker-compose.yml run --rm dev bash -c "g++ --version && g++ -std=c++26 -freflection -x c++ - <<< 'int main(){}'"
```

### nanobind ABI Issues
The Python bindings use specific compiler flags for ABI compatibility:
- `-fvisibility=hidden` - Symbol visibility control
- `-fno-semantic-interposition` - Better optimization across boundaries
- Static linking of libstdc++ and libgcc for portability

If you encounter crashes in Python tests, rebuild with:
```bash
docker compose -f docker/docker-compose.yml run --rm clean-build
```

### Docker Build Cache Issues
Clear Docker BuildKit cache:
```bash
docker builder prune -a
```
