#include <class_declaration.hpp>
#include <visitor.hpp>

ClassDeclaration::ClassDeclaration(IdentifierPtr class_name, IdentifierPtr extends_class_name,
                                   VarDeclarations variables, MethodDeclarations methods)
    : class_name_(std::move(class_name)),
      extends_class_name_(std::move(extends_class_name)),
      variables_(std::move(variables)),
      methods_(std::move(methods)) {
}

void ClassDeclaration::Accept(const Visitor& visitor) const {
    visitor.Visit(*this);
}