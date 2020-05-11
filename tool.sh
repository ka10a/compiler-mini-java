#!/usr/bin/env bash

if [ "$#" -gt 2 ]; then
    echo "Only two arguments are allowed"
    exit 1
fi

if [ -z "$1" ]; then
    echo "No Java filename specified"
    exit 1
fi

if [ -z "$2" ]; then
    echo "No graph filename specified"
    exit 1
fi

PATH_TO_JAVA_FILE=./$1
PATH_TO_GRAPH_FILE=./$2

./build/compiler-mini-java "$PATH_TO_JAVA_FILE" "$PATH_TO_GRAPH_FILE".gv
dot -Tpng "$PATH_TO_GRAPH_FILE".gv -o "$PATH_TO_GRAPH_FILE".png
