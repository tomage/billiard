#!/bin/sh

clang-format -i \
    `find . -iname *.cpp -o -iname *.c -o -iname *.cxx -o -iname *.hpp -o -iname *.h -o -iname *.hxx | xargs`
