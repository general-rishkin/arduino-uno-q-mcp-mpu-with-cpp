FROM mdnf1992/cpp-dev AS dev

# Install ino compilation toolchain
RUN curl -fsSL https://raw.githubusercontent.com/arduino/arduino-cli/master/install.sh | BINDIR=/usr/local/bin sh && \
    arduino-cli core update-index && \
    arduino-cli core install arduino:zephyr && \
    arduino-cli lib install "Arduino_RouterBridge"

# Install msgpack for RPC
RUN apt-get update && apt-get install -y libmsgpack-cxx-dev libgpiod-dev docker.io && \
    rm -rf /var/lib/apt/lists/*

FROM dev AS build

COPY . /app
WORKDIR /app

RUN mkdir -p build && cd build && \
    cmake --preset preset .. && \
    cmake --build . --target install

# Ship the build artifacts to a runtime image. Can be more lightweight than below.

FROM debian:trixie-slim AS runtime
COPY --from=build /app/build/install /app

# We're using gcc-16 in the base container
RUN echo "deb http://deb.debian.org/debian sid main" > /etc/apt/sources.list.d/sid.list && \
  apt-get update && \
  apt-get install -y -t sid libstdc++6 && \
  rm /etc/apt/sources.list.d/sid.list && \
  apt-get update 

# Invoke `bridge` app with:
# 
# ```bash
# docker run --init --rm -it -v /var/run/arduino-router.sock:/var/run/arduino-router.sock -p 50051:50051 learning-arduino-q /app/bin/bridge
# ```

# It is worth consideration being able to ship "mcu" firmwares and inside the docker and flash them to the MCU once the 
# container starts.
