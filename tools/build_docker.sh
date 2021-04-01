#!/bin/bash

set -e -u -o pipefail

TAG=billiard
docker build . -f tools/Dockerfile -t $TAG && docker run -it --rm $TAG
