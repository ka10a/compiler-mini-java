cmake_minimum_required(VERSION 3.10)

set(valid_samples_dir ${CMAKE_CURRENT_SOURCE_DIR}/valid)

enable_testing()

file(GLOB valid_samples ${valid_samples_dir}/*.java)
foreach(file ${valid_samples})
    get_filename_component(filename ${file} NAME_WE)

    add_test(
        NAME Parse${filename}.java
        COMMAND ${CMAKE_BINARY_DIR}/compiler-mini-java ${file} ${filename}AST
        WORKING_DIRECTORY ${valid_samples_dir}
    )

    add_test(
        NAME Draw${filename}AST
        COMMAND dot -Tpng ${filename}AST.gv -o ${filename}AST.png
        WORKING_DIRECTORY ${valid_samples_dir}
    )
endforeach()