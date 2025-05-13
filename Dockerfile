# Base image with g++ and build tools
FROM ubuntu:22.04

# Prevent prompts from tzdata
ENV DEBIAN_FRONTEND=noninteractive

# Install dependencies
RUN apt-get update && apt-get install -y \
    g++ \
    make \
    build-essential \
    nano \
    cmake \
    git \
    && rm -rf /var/lib/apt/lists/*

# Create app directory
WORKDIR /app

# Copy all project files to /app in container
COPY . .

# Compile the code
RUN make

# Set the default command to run the compiled app
CMD ["./Netflix"]

# Build Docker Image
docker build -t netflix-app .

# Run Docker Image
docker run -it netflix-app
