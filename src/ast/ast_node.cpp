#include <ast/ast_node.hpp>

ASTNode::ASTNode(LocationPtr location) : location_(std::move(location)) {
}

const LocationPtr& ASTNode::GetLocation() const {
    return location_;
}
