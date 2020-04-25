#!/usr/bin/env bash

if [ "$#" -gt 1 ]; then
    echo "Only one argument is allowed (filename.java)"
    exit 1
fi

if [ -z "$1" ]; then
    echo "No filename specified"
    exit 1
fi

PATH_TO_JAVA_FILE=./samples/$1

cmake . -B build
cmake --build build --target compiler-mini-java
./build/compiler-mini-java < "$PATH_TO_JAVA_FILE"
