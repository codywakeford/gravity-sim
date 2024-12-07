FROM mcr.microsoft.com/devcontainers/cpp:1-ubuntu-24.04

# Optional: Argument for custom CMake version
ARG REINSTALL_CMAKE_VERSION_FROM_SOURCE="3.22.2"

# Set the working directory
WORKDIR /app

# Copy files into the container
COPY . /app

# Optional: Reinstall CMake if needed
RUN if [ "${REINSTALL_CMAKE_VERSION_FROM_SOURCE}" != "none" ]; then \
        chmod +x /app/reinstall-cmake.sh && /app/reinstall-cmake.sh ${REINSTALL_CMAKE_VERSION_FROM_SOURCE}; \
    fi \
    && rm -f /tmp/reinstall-cmake.sh

# Install dependencies
RUN apt-get update && apt-get install -y \
    make \
    cmake \
    libsfml-dev \
    && rm -rf /var/lib/apt/lists/*

# Configure and build the project
# RUN cmake . && make

# Default command to run
CMD ["make", "rerun"]
