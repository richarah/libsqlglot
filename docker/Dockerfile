# libsqlglot build environment with C++26 reflection support
# Multi-stage build for minimal final image
#
# Builds GCC trunk from source with -freflection support

FROM ubuntu:24.04 AS gcc-builder

# Install GCC build dependencies
RUN apt-get update && \
    DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
        build-essential \
        wget \
        ca-certificates \
        libgmp-dev \
        libmpfr-dev \
        libmpc-dev \
        flex \
        bison \
        git \
    && rm -rf /var/lib/apt/lists/*

# Download and build GCC trunk with reflection support
# This takes ~30-45 minutes but only happens once (Docker layer cache)
WORKDIR /tmp/gcc-build
RUN wget -q https://github.com/gcc-mirror/gcc/archive/refs/heads/master.tar.gz && \
    tar xzf master.tar.gz && \
    cd gcc-master && \
    ./contrib/download_prerequisites && \
    mkdir build && cd build && \
    ../configure \
        --prefix=/opt/gcc-trunk \
        --enable-languages=c,c++ \
        --disable-multilib \
        --disable-bootstrap \
        --enable-checking=release && \
    make -j$(nproc) && \
    make install && \
    cd / && rm -rf /tmp/gcc-build

# Main builder base image
FROM ubuntu:24.04 AS builder-base

# Install build dependencies
RUN apt-get update && \
    DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
        cmake \
        ninja-build \
        python3 \
        python3-pip \
        python3-dev \
        git \
        ccache \
        binutils \
        libgmp10 \
        libmpfr6 \
        libmpc3 \
    && rm -rf /var/lib/apt/lists/*

# Copy GCC trunk from builder
COPY --from=gcc-builder /opt/gcc-trunk /opt/gcc-trunk

# Set GCC trunk as default compiler
ENV CC=/opt/gcc-trunk/bin/gcc \
    CXX=/opt/gcc-trunk/bin/g++ \
    LD_LIBRARY_PATH=/opt/gcc-trunk/lib64:${LD_LIBRARY_PATH} \
    PATH=/opt/gcc-trunk/bin:${PATH} \
    CCACHE_DIR=/cache/ccache

# Verify compiler version and reflection support
RUN g++ --version && \
    g++ -dumpversion && \
    echo "int main() { return 0; }" > /tmp/test.cpp && \
    g++ -std=c++26 -freflection /tmp/test.cpp -o /tmp/test && \
    /tmp/test && \
    rm -f /tmp/test /tmp/test.cpp && \
    echo "✓ GCC trunk with C++26 reflection support verified"

# Set up workspace
WORKDIR /workspace

# Builder stage - for compilation
FROM builder-base AS builder

# Copy only what's needed for build (use .dockerignore to filter)
COPY . .

# Build with all cores
RUN cmake -B build -G Ninja \
    -DCMAKE_BUILD_TYPE=Release \
    -DLIBSQLGLOT_BUILD_PYTHON=ON \
    -DLIBSQLGLOT_BUILD_TESTS=ON \
    && cmake --build build --parallel $(nproc)

# Test stage - run tests
FROM builder AS tester
RUN cd build && ctest --output-on-failure --parallel $(nproc)

# Python wheel builder
FROM builder AS wheel-builder
RUN cd build && \
    pip3 install --no-cache-dir build wheel && \
    python3 -m build --wheel

# Development environment - includes all tools
FROM builder-base AS dev
COPY --from=builder /workspace/build /workspace/build
CMD ["/bin/bash"]

# Minimal runtime (if shipping binaries)
FROM debian:bookworm-slim AS runtime
RUN apt-get update && \
    apt-get install -y --no-install-recommends \
        libstdc++6 \
        python3 \
    && rm -rf /var/lib/apt/lists/*

COPY --from=builder /workspace/build/lib*.so* /usr/local/lib/
RUN ldconfig
