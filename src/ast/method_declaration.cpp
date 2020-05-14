#include <ast/method_declaration.hpp>
#include <visitors/visitor.hpp>

MethodDeclaration::MethodDeclaration(LocationPtr location, TypePtr return_type,
                                     IdentifierPtr method_name, VarDeclarations args,
                                     VarDeclarations variables, Statements statements,
                                     ExpressionPtr return_expression)
    : ASTNode(std::move(location))
    , return_type_(std::move(return_type))
    , method_name_(std::move(method_name))
    , args_(std::move(args))
    , variables_(std::move(variables))
    , statements_(std::move(statements))
    , return_expression_(std::move(return_expression)) {
}

void MethodDeclaration::Accept(Visitor& visitor) const {
    visitor.Visit(*this);
}

const TypePtr& MethodDeclaration::GetReturnType() const {
    return return_type_;
}

const IdentifierPtr& MethodDeclaration::GetMethodName() const {
    return method_name_;
}

const VarDeclarations& MethodDeclaration::GetArgs() const {
    return args_;
}

const VarDeclarations& MethodDeclaration::GetVariables() const {
    return variables_;
}

const Statements& MethodDeclaration::GetStatements() const {
    return statements_;
}

const ExpressionPtr& MethodDeclaration::GetReturnExpression() const {
    return return_expression_;
}
