FROM debian:bullseye-slim

WORKDIR /test

# Add 3rd party libs
RUN apt-get update \
    && apt-get install -y \
        g++ \
        cmake \
        libgl1-mesa-dev \
        freeglut3-dev \
        libopenal-dev \
        libalut-dev

# Add the repo
ADD . .

# Build
RUN ./tools/full_build.sh
