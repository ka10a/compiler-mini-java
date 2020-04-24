#!/usr/bin/env bash

if [ "$#" -gt 1 ]; then
    echo "Only one argument is allowed (filename.java)"
    exit 1
fi

if [ -z "$1" ]; then
    echo "No filename specified"
    exit 1
fi

PATH_TO_JAVA_FILE=../samples/$1

mkdir build
cd build
cmake ..
make compiler-mini-java
./compiler-mini-java < "$PATH_TO_JAVA_FILE"
