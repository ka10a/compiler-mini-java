cmake_minimum_required(VERSION 3.10)

bison_target(
    parser
    parsing/parser.y
    ${CMAKE_CURRENT_BINARY_DIR}/parser.cpp
    COMPILE_FLAGS "-dg"
    VERBOSE
)

flex_target(
    scanner
    parsing/scanner.l
    ${CMAKE_CURRENT_BINARY_DIR}/scanner.cpp
)

add_flex_bison_dependency(scanner parser)

add_executable(
    compiler-mini-java
    main.cpp
    ${BISON_parser_OUTPUTS}
    ${FLEX_scanner_OUTPUTS}
    ast/ast_node.cpp
    ast/class_declaration.cpp
    ast/expressions.cpp
    ast/goal.cpp
    ast/identifier.cpp
    ast/main_class.cpp
    ast/method_declaration.cpp
    ast/statements.cpp
    ast/types.cpp
    ast/var_declaration.cpp
    symbol_table/class_info.cpp
    symbol_table/entity_info.cpp
    symbol_table/method_info.cpp
    symbol_table/symbol_table.cpp
    symbol_table/var_info.cpp
    visitors/ast_printer.cpp
    visitors/symbol_table_builder.cpp
)

target_include_directories(compiler-mini-java PUBLIC ${CMAKE_CURRENT_BINARY_DIR})
target_include_directories(compiler-mini-java PUBLIC ${PROJECT_SOURCE_DIR}/include)
