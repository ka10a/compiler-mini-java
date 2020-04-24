#include <ast/class_declaration.hpp>
#include <visitors/visitor.hpp>

ClassDeclaration::ClassDeclaration(IdentifierPtr class_name, IdentifierPtr extends_class_name,
                                   VarDeclarations variables, MethodDeclarations methods)
    : class_name_(std::move(class_name)),
      extends_class_name_(std::move(extends_class_name)),
      variables_(std::move(variables)),
      methods_(std::move(methods)) {
}

void ClassDeclaration::Accept(Visitor& visitor) const {
    visitor.Visit(*this);
}

const IdentifierPtr& ClassDeclaration::GetClassName() const {
    return class_name_;
}

const IdentifierPtr& ClassDeclaration::GetExtendsClassName() const {
    return extends_class_name_;
}

const VarDeclarations& ClassDeclaration::GetVariables() const {
    return variables_;
}

const MethodDeclarations& ClassDeclaration::GetMethods() const {
    return methods_;
}
