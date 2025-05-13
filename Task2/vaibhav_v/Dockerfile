# Use the official GCC image with build tools
FROM gcc:latest

# Set working directory inside the container
WORKDIR /app

# Copy all files from the current directory to the working directory inside the container
COPY . .

# Compile the C++ source code
RUN g++ -o app main.cpp

# Run the compiled application
CMD ["./app"]
