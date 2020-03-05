cmake_minimum_required(VERSION 3.10)
project(test_flex_bison)

set(CMAKE_CXX_STANDARD 17)

find_package(FLEX REQUIRED)
find_package(BISON REQUIRED)

BISON_TARGET(
    MyParser
    parser.y
    ${CMAKE_CURRENT_BINARY_DIR}/MiniJavaParser.cpp
    DEFINES_FILE ${CMAKE_CURRENT_BINARY_DIR}/MiniJavaParser.hh
)

FLEX_TARGET(
    MyScanner
    lexer.l
    ${CMAKE_CURRENT_BINARY_DIR}/MiniJavaLexer.hh
)

ADD_FLEX_BISON_DEPENDENCY(MyScanner MyParser)

include_directories(${CMAKE_CURRENT_BINARY_DIR})

add_executable(
    test_flex_bison
    main.cpp
    MiniJavaParser.cpp
    ${BISON_MyParser_OUTPUTS}
    ${FLEX_MyScanner_OUTPUTS}
)
