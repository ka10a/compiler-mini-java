#include <ast/var_declaration.hpp>
#include <visitors/visitor.hpp>

VarDeclaration::VarDeclaration(LocationPtr location, TypePtr type, IdentifierPtr var_name)
    : ASTNode(std::move(location)), type_(std::move(type)), var_name_(std::move(var_name)) {
}

void VarDeclaration::Accept(Visitor& visitor) const {
    visitor.Visit(*this);
}

const TypePtr& VarDeclaration::GetType() const {
    return type_;
}

const IdentifierPtr& VarDeclaration::GetVarName() const {
    return var_name_;
}
