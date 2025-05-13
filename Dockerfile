# Build stage
FROM gcc:12.2.0 AS builder

# Set working directory
WORKDIR /app

# Copy all project files
COPY include/ include/
COPY src/ src/
COPY main.cpp .

# Install any additional dependencies
RUN apt-get update && \
    apt-get install -y cmake && \
    rm -rf /var/lib/apt/lists/*

# Build the application
RUN g++ -std=c++17 -Iinclude src/*.cpp main.cpp -o netflix_app

# Runtime stage
FROM ubuntu:22.04

# Install runtime dependencies
RUN apt-get update && \
    apt-get install -y libstdc++6 && \
    rm -rf /var/lib/apt/lists/*

# Set working directory
WORKDIR /app

# Copy the built binary from builder stage
COPY --from=builder /app/netflix_app .

# Make the binary executable
RUN chmod +x netflix_app

# Set the entry point
ENTRYPOINT ["./netflix_app"]