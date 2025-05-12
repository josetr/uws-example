FROM debian:12.10 as builder
RUN apt-get update && apt-get install -y sudo build-essential git cmake curl

WORKDIR /home
RUN git clone https://github.com/Microsoft/vcpkg.git

WORKDIR /home/vcpkg
RUN ./bootstrap-vcpkg.sh

WORKDIR /app

COPY vcpkg.json .
RUN /home/vcpkg/vcpkg install

COPY . .
RUN mkdir build && cd build && \
    cmake -DCMAKE_TOOLCHAIN_FILE=/home/vcpkg/scripts/buildsystems/vcpkg.cmake .. 

RUN cmake --build build
 
FROM debian:12.10-slim as final

WORKDIR /app

COPY --from=builder /app/build/uWSExample uWSExample

CMD ["./uWSExample"]
