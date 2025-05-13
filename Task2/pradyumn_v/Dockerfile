FROM gcc:latest
WORKDIR /usr/src/app
COPY . .
RUN g++ *.cpp -o media_rental_system
VOLUME ["/app/user", "/app/admin", "/app/catalogues"]
CMD ["./media_rental_system"]
