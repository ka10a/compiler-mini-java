# MiniJava Compiler

To build:

```
./build.sh
```

To draw an AST for a file:
```
./tool.sh path/to/file.java graphname 
```

Check out results in `graphname.gv` and `graphname.png`.

To run tests:

```
cd build/samples
ctest
```

Graphs and images will be saved into the same folder.
