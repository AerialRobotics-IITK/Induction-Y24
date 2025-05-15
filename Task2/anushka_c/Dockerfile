FROM gcc:latest

WORKDIR /app

COPY . .

RUN g++ -std=c++17 -o netflix main.cpp

CMD ["./netflix"]

RUN make