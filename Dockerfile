FROM ubuntu:24.04

ENV DEBIAN_FRONTEND=noninteractive

# Install build dependencies - C++23 requires GCC 13+ or Clang 17+
RUN apt-get update && apt-get install -y \
    build-essential \
    cmake \
    git \
    wget \
    python3 \
    python3-pip \
    python3-dev \
    clang-18 \
    libc++-18-dev \
    libc++abi-18-dev \
    && rm -rf /var/lib/apt/lists/*

# Set Clang 18 as default compiler (needed for C++23)
ENV CC=clang-18
ENV CXX=clang++-18

WORKDIR /libsqlglot

# Copy source
COPY . .

# Build
RUN cmake -S . -B build \
    -DCMAKE_BUILD_TYPE=Release \
    -DLIBSQLGLOT_BUILD_TESTS=ON \
    -DLIBSQLGLOT_BUILD_SHARED=ON \
    -DCMAKE_CXX_COMPILER=clang++-18

RUN cmake --build build -j$(nproc)

# Run tests
RUN cd build && ctest --output-on-failure || true

CMD ["/bin/bash"]
