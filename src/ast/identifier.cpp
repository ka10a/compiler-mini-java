#include <ast/identifier.hpp>
#include <visitors/visitor.hpp>

Identifier::Identifier(int first_line, int first_column, std::string name)
    : ASTNode(first_line, first_column), name_(std::move(name)) {
}

void Identifier::Accept(Visitor& visitor) const {
    visitor.Visit(*this);
}

const std::string& Identifier::GetName() const {
    return name_;
}
