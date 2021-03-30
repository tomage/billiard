#!/bin/bash

set -e
set -u
set -o pipefail

rm -rf build ; mkdir build
./tools/build.sh
