# C++ base image C++17 support
FROM gcc:11
RUN apt-get update && apt-get install -y \
    libssl-dev \
    && rm -rf /var/lib/apt/lists/*

WORKDIR /app
COPY paste.txt /app/netflix.cpp
RUN mkdir -p /app/users
RUN touch /app/password_db.txt
RUN touch /app/movies_db.txt
RUN touch /app/tv_show_db.txt

# Compile
RUN g++ -o netflix_app netflix.cpp -lcrypto -std=c++17 -lstdc++fs
RUN chmod +x netflix_app
CMD ["./netflix_app"]
