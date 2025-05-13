# Stage 1: compile
FROM gcc:11 AS builder
WORKDIR /app
COPY final.cpp .
RUN g++ -std=c++17 -O2 final.cpp -o ott_app

# Stage 2: runtime
FROM debian:bookworm-slim
RUN useradd --create-home appuser
USER appuser
WORKDIR /home/appuser/app
COPY --from=builder /app/ott_app .
RUN touch user.txt
ENTRYPOINT ["./ott_app"]
