# Use Ubuntu 22.04 as the base image for building (it includes g++ and supports C++17)
FROM ubuntu:22.04 AS builder

# Install g++ and other build essentials
RUN apt-get update && apt-get install -y \
    g++ \
    && rm -rf /var/lib/apt/lists/*

# Set the working directory inside the container
WORKDIR /app

# Copy all source files and the data directory into the container
COPY main.cpp movies.cpp tvShows.cpp ./
COPY data/ ./data/

# Compile the C++ program with C++17 standard
RUN g++ -std=c++17 main.cpp -o netflix_clone

# Use a smaller runtime image for the final stage
FROM ubuntu:22.04

# Install runtime dependencies (minimal)
RUN apt-get update && apt-get install -y \
    && rm -rf /var/lib/apt/lists/*

# Set the working directory
WORKDIR /app

# Copy the compiled binary and data directory from the builder stage
COPY --from=builder /app/netflix_clone .
COPY --from=builder /app/data ./data/

# Ensure the data directory is writable
RUN chmod -R 777 /app/data

# Define a volume for the data directory to persist data
VOLUME /app/data

# Set the entrypoint to run the application
CMD ["./netflix_clone"]