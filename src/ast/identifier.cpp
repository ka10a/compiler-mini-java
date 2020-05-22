#include <ast/identifier.hpp>
#include <visitors/visitor.hpp>

Identifier::Identifier(LocationPtr location, std::string name)
    : ASTNode(std::move(location)), name_(std::move(name)) {
}

void Identifier::Accept(Visitor& visitor) const {
    visitor.Visit(*this);
}

const std::string& Identifier::GetName() const {
    return name_;
}
