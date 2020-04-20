cmake_minimum_required(VERSION 3.10)

bison_target(
    parser
    ${CMAKE_CURRENT_SOURCE_DIR}/parser.y
    ${CMAKE_CURRENT_BINARY_DIR}/parser.cpp
    COMPILE_FLAGS "-dg"
)

flex_target(
    scanner
    ${CMAKE_CURRENT_SOURCE_DIR}/scanner.l
    ${CMAKE_CURRENT_BINARY_DIR}/scanner.cpp
)

add_flex_bison_dependency(scanner parser)

add_executable(
    compiler-mini-java
    main.cpp
    ${BISON_parser_OUTPUTS}
    ${FLEX_scanner_OUTPUTS}
)

target_include_directories(compiler-mini-java PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(compiler-mini-java PUBLIC ${CMAKE_CURRENT_BINARY_DIR})
