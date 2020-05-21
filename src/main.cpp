#include <cstdio>
#include <string>

#include <parser.hpp>
#include <ast/goal.hpp>
#include <visitors/ast_printer.hpp>
#include <visitors/symbol_table_builder.hpp>

extern FILE* yyin;
extern GoalPtr goal;
extern yy::location loc;

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

    // Not const because of yy::location::initialize needs non-const pointer.
    std::string java_filename = argv[1];
    const std::string graph_filename = argv[2];

    FILE* const java_file = fopen(java_filename.c_str(), "r");
    if (!java_file) {
        throw std::runtime_error("File " + java_filename + " does not exist");
    }

    yyin = java_file;
    loc.initialize(&java_filename);

    try {
        yy::parser parser;
        parser.parse();
    } catch (const yy::parser::syntax_error& error) {
        std::cerr << "Exception while parsing " << error.location << ": " << error.what() << '\n';
        fclose(java_file);
        throw;
    } catch (...) {
        std::cerr << "Unknown exception while parsing\n";
        fclose(java_file);
        throw;
    }

    fclose(java_file);

    ASTPrinter tree_printer(graph_filename);
    goal->Accept(tree_printer);

    auto symbol_table = SymbolTableBuilder().Build(*goal);

    return 0;
}