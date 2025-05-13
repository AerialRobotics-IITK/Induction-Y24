# Use official GCC image as base
FROM gcc:latest

# Set working directory
WORKDIR /app

# Copy all source files
COPY . .

# Install any dependencies (if needed)
RUN apt-get update && apt-get install -y \
    make \
    && rm -rf /var/lib/apt/lists/*

# Compile the application
RUN g++ -std=c++11 -o netflix_app *.cpp

# Run the application
CMD ["./netflix_app"]

VOLUME /app/data


# Run my application with the following command:
#  docker run -it --rm yashraj1729/netflix-app:v1