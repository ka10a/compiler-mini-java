#include <var_declaration.hpp>
#include <visitor.hpp>

VarDeclaration::VarDeclaration(TypePtr type, IdentifierPtr name)
    : type_(std::move(type)), name_(std::move(name)) {
}

void VarDeclaration::Accept(Visitor& visitor) const {
    visitor.Visit(*this);
}
