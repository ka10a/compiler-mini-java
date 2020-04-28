#!/usr/bin/env bash

if [ "$#" -gt 1 ]; then
    echo "Only one argument is allowed (path/to/file.java)"
    exit 1
fi

if [ -z "$1" ]; then
    echo "No filename specified"
    exit 1
fi

PATH_TO_JAVA_FILE=./$1

cmake . -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build -j 2 -t compiler-mini-java
./build/compiler-mini-java < "$PATH_TO_JAVA_FILE"
dot -Tpng ast.gv -o ast.png
