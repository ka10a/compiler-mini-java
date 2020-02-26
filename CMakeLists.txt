cmake_minimum_required(VERSION 3.10)
project(test_flex)

set(CMAKE_CXX_STANDARD 14)

find_package(FLEX REQUIRED)
FLEX_TARGET(MyScanner lexer.l ${CMAKE_CURRENT_BINARY_DIR}/MiniJava.Lexer.h)

include_directories(${CMAKE_CURRENT_BINARY_DIR})
add_executable(test_flex
        main.cpp
        ${FLEX_MyScanner_OUTPUTS}
        )