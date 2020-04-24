#include <ast/var_declaration.hpp>
#include <visitors/visitor.hpp>

VarDeclaration::VarDeclaration(TypePtr type, IdentifierPtr name)
    : type_(std::move(type)), name_(std::move(name)) {
}

void VarDeclaration::Accept(Visitor& visitor) const {
    visitor.Visit(*this);
}

const TypePtr& VarDeclaration::GetType() const {
    return type_;
}

const IdentifierPtr& VarDeclaration::GetName() const {
    return name_;
}
