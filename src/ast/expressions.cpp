#include <ast/expressions.hpp>
#include <visitors/visitor.hpp>

Expression::Expression(LocationPtr location) : ASTNode(std::move(location)) {
}

AndExpression::AndExpression(LocationPtr location, ExpressionPtr lhs, ExpressionPtr rhs)
    : Expression(std::move(location)), lhs_(std::move(lhs)), rhs_(std::move(rhs)) {
}

void AndExpression::Accept(Visitor& visitor) const {
    visitor.Visit(*this);
}

const ExpressionPtr& AndExpression::GetLhs() const {
    return lhs_;
}

const ExpressionPtr& AndExpression::GetRhs() const {
    return rhs_;
}

LessExpression::LessExpression(LocationPtr location, ExpressionPtr lhs, ExpressionPtr rhs)
    : Expression(std::move(location)), lhs_(std::move(lhs)), rhs_(std::move(rhs)) {
}

void LessExpression::Accept(Visitor& visitor) const {
    visitor.Visit(*this);
}

const ExpressionPtr& LessExpression::GetLhs() const {
    return lhs_;
}

const ExpressionPtr& LessExpression::GetRhs() const {
    return rhs_;
}

AddExpression::AddExpression(LocationPtr location, ExpressionPtr lhs, ExpressionPtr rhs)
    : Expression(std::move(location)), lhs_(std::move(lhs)), rhs_(std::move(rhs)) {
}

void AddExpression::Accept(Visitor& visitor) const {
    visitor.Visit(*this);
}

const ExpressionPtr& AddExpression::GetLhs() const {
    return lhs_;
}

const ExpressionPtr& AddExpression::GetRhs() const {
    return rhs_;
}

SubtractExpression::SubtractExpression(LocationPtr location, ExpressionPtr lhs, ExpressionPtr rhs)
    : Expression(std::move(location)), lhs_(std::move(lhs)), rhs_(std::move(rhs)) {
}

void SubtractExpression::Accept(Visitor& visitor) const {
    visitor.Visit(*this);
}

const ExpressionPtr& SubtractExpression::GetLhs() const {
    return lhs_;
}

const ExpressionPtr& SubtractExpression::GetRhs() const {
    return rhs_;
}

MultiplyExpression::MultiplyExpression(LocationPtr location, ExpressionPtr lhs, ExpressionPtr rhs)
    : Expression(std::move(location)), lhs_(std::move(lhs)), rhs_(std::move(rhs)) {
}

void MultiplyExpression::Accept(Visitor& visitor) const {
    visitor.Visit(*this);
}

const ExpressionPtr& MultiplyExpression::GetLhs() const {
    return lhs_;
}

const ExpressionPtr& MultiplyExpression::GetRhs() const {
    return rhs_;
}

ArrayExpression::ArrayExpression(LocationPtr location, ExpressionPtr array, ExpressionPtr idx)
    : Expression(std::move(location)), array_(std::move(array)), idx_(std::move(idx)) {
}

void ArrayExpression::Accept(Visitor& visitor) const {
    visitor.Visit(*this);
}

const ExpressionPtr& ArrayExpression::GetArray() const {
    return array_;
}

const ExpressionPtr& ArrayExpression::GetIdx() const {
    return idx_;
}

LengthExpression::LengthExpression(LocationPtr location, ExpressionPtr container)
    : Expression(std::move(location)), container_(std::move(container)) {
}

void LengthExpression::Accept(Visitor& visitor) const {
    visitor.Visit(*this);
}

const ExpressionPtr& LengthExpression::GetContainer() const {
    return container_;
}

MethodCallExpression::MethodCallExpression(LocationPtr location, ExpressionPtr class_entity,
                                           IdentifierPtr method_name, Expressions params)
    : Expression(std::move(location))
    , class_entity_(std::move(class_entity))
    , method_name_(std::move(method_name))
    , params_(std::move(params)) {
}

void MethodCallExpression::Accept(Visitor& visitor) const {
    visitor.Visit(*this);
}

const ExpressionPtr& MethodCallExpression::GetClassEntity() const {
    return class_entity_;
}

const IdentifierPtr& MethodCallExpression::GetMethodName() const {
    return method_name_;
}

const Expressions& MethodCallExpression::GetParams() const {
    return params_;
}

IntExpression::IntExpression(LocationPtr location, int value)
    : Expression(std::move(location)), value_(value) {
}

void IntExpression::Accept(Visitor& visitor) const {
    visitor.Visit(*this);
}

int IntExpression::GetValue() const {
    return value_;
}

BoolExpression::BoolExpression(LocationPtr location, bool value)
    : Expression(std::move(location)), value_(value) {
}

void BoolExpression::Accept(Visitor& visitor) const {
    visitor.Visit(*this);
}

bool BoolExpression::IsValue() const {
    return value_;
}

IdentifierExpression::IdentifierExpression(LocationPtr location, IdentifierPtr variable_name)
    : Expression(std::move(location)), variable_name_(std::move(variable_name)) {
}

void IdentifierExpression::Accept(Visitor& visitor) const {
    visitor.Visit(*this);
}

const IdentifierPtr& IdentifierExpression::GetVariableName() const {
    return variable_name_;
}

ThisExpression::ThisExpression(LocationPtr location) : Expression(std::move(location)) {
}

void ThisExpression::Accept(Visitor& visitor) const {
    visitor.Visit(*this);
}

NewIntArrayExpression::NewIntArrayExpression(LocationPtr location, ExpressionPtr size)
    : Expression(std::move(location)), size_(std::move(size)) {
}

void NewIntArrayExpression::Accept(Visitor& visitor) const {
    visitor.Visit(*this);
}

const ExpressionPtr& NewIntArrayExpression::GetSize() const {
    return size_;
}

NewExpression::NewExpression(LocationPtr location, IdentifierPtr class_name)
    : Expression(std::move(location)), class_name_(std::move(class_name)) {
}

void NewExpression::Accept(Visitor& visitor) const {
    visitor.Visit(*this);
}

const IdentifierPtr& NewExpression::GetClassName() const {
    return class_name_;
}

NotExpression::NotExpression(LocationPtr location, ExpressionPtr expression)
    : Expression(std::move(location)), expression_(std::move(expression)) {
}

void NotExpression::Accept(Visitor& visitor) const {
    visitor.Visit(*this);
}

const ExpressionPtr& NotExpression::GetExpression() const {
    return expression_;
}
