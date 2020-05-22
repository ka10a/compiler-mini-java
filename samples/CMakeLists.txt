cmake_minimum_required(VERSION 3.10)

set(valid_samples_dir ${CMAKE_CURRENT_SOURCE_DIR}/valid)
set(invalid_samples_dir ${CMAKE_CURRENT_SOURCE_DIR}/invalid)

enable_testing()

file(GLOB valid_samples ${valid_samples_dir}/*.java)
file(GLOB invalid_samples ${invalid_samples_dir}/*.java)

foreach(file ${valid_samples})
    get_filename_component(filename ${file} NAME_WE)

    add_test(
        NAME ParseValid${filename}.java
        COMMAND ${CMAKE_BINARY_DIR}/compiler-mini-java ${file} ${filename}AST.gv
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
    )

    add_test(
        NAME Draw${filename}AST
        COMMAND dot -Tpng ${filename}AST.gv -o ${filename}AST.png
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
    )
endforeach()

foreach(file ${invalid_samples})
    get_filename_component(filename ${file} NAME_WE)

    add_test(
        NAME ParseInvalid${filename}.java
        COMMAND ${CMAKE_BINARY_DIR}/compiler-mini-java ${file} ${filename}AST.gv
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
    )

    set_tests_properties(
        ParseInvalid${filename}.java PROPERTIES WILL_FAIL true
    )
endforeach()