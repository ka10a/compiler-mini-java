#include <parser.hpp>
#include <ast/goal.hpp>
#include <visitors/ast_printer.hpp>

void yy::parser::error(const std::string& msg) {
    std::cout << "An error occured: " << msg << std::endl;
}

extern GoalPtr goal;

int main() {
    yy::parser parser;
    parser.parse();
    return 0;
}