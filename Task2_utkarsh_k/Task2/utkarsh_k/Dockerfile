# Use official GCC compiler image
FROM gcc:latest

# Set working directory
WORKDIR /app

# Copy all source code into the container
COPY . .

# Compile all .cpp files into a single executable named netflix
RUN g++ main.cpp Movie.cpp TVShow.cpp Admin.cpp User.cpp -o netflix

# Command to run the app
CMD ["./netflix"]
