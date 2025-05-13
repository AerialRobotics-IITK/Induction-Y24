
FROM ubuntu:22.04
ENV DEBIAN_FRONTEND=noninteractive
RUN apt-get update && \
    apt-get install -y g++ make build-essential nano vim \
    && apt-get clean
WORKDIR /app
COPY . /app
RUN g++ -std=c++17 -o ott final.cpp
CMD ["./ott"]
