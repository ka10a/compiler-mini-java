#include <ast/ast_node.hpp>

ASTNode::ASTNode(int first_line, int first_column)
    : first_line_(first_line), first_column_(first_column) {
}

int ASTNode::GetFirstLine() const {
    return first_line_;
}

int ASTNode::GetFirstColumn() const {
    return first_column_;
}
