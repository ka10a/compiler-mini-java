#include <method_declaration.hpp>
#include <visitor.hpp>

MethodDeclaration::MethodDeclaration(TypePtr return_type, IdentifierPtr name, VarDeclarations args,
                                     VarDeclarations variables, Statements statements,
                                     ExpressionPtr return_expression)
    : return_type_(std::move(return_type)),
      name_(std::move(name)),
      args_(std::move(args)),
      variables_(std::move(variables)),
      statements_(std::move(statements)),
      return_expression_(std::move(return_expression)) {
}

void MethodDeclaration::Accept(Visitor& visitor) const {
    visitor.Visit(*this);
}
