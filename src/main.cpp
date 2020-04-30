#include <cstdio>
#include <string>

#include <parser.hpp>
#include <ast/goal.hpp>
#include <visitors/ast_printer.hpp>

void yy::parser::error(const std::string& msg) {
    std::cout << "An error occured: " << msg << '\n';
}

extern FILE* yyin;
extern GoalPtr goal;

int main(int argc, char* argv[]) {
    if (argc == 1) {
        throw std::logic_error("Input and output are not specified");
    }
    if (argc == 2) {
        throw std::logic_error("Output graph filename is not specified");
    }
    if (argc > 3) {
        throw std::logic_error("Only two arguments are allowed");
    }
    const std::string java_filename = argv[1];
    const std::string graph_filename = argv[2];

    FILE* const java_file = fopen(java_filename.c_str(), "r");
    if (!java_file) {
        throw std::runtime_error("File " + java_filename + " does not exist");
    }
    yyin = java_file;

    try {
        yy::parser parser;
        parser.parse();
    } catch (...) {
        std::cerr << "Exception happened while parsing\n";
        fclose(java_file);
        throw;
    }

    try {
        ASTPrinter tree_printer(graph_filename);
        goal->Accept(tree_printer);
    } catch (...) {
        std::cerr << "Exception happened while drawing a tree\n";
        fclose(java_file);
        throw;
    }
    return 0;
}