#!/bin/bash

set -e
set -u
set -o pipefail

[ ! -d "build" ] && mkdir build
cd build
cmake ..
make
cd ..
