#include <expressions.hpp>
#include <visitor.hpp>

AndExpression::AndExpression(ExpressionPtr lhs, ExpressionPtr rhs)
    : lhs_(std::move(lhs)), rhs_(std::move(rhs)) {
}

void AndExpression::Accept(const Visitor& visitor) const {
    visitor.Visit(*this);
}

LessExpression::LessExpression(ExpressionPtr lhs, ExpressionPtr rhs)
    : lhs_(std::move(lhs)), rhs_(std::move(rhs)) {
}

void LessExpression::Accept(const Visitor& visitor) const {
    visitor.Visit(*this);
}

AddExpression::AddExpression(ExpressionPtr lhs, ExpressionPtr rhs)
    : lhs_(std::move(lhs)), rhs_(std::move(rhs)) {
}

void AddExpression::Accept(const Visitor& visitor) const {
    visitor.Visit(*this);
}

SubtractExpression::SubtractExpression(ExpressionPtr lhs, ExpressionPtr rhs)
    : lhs_(std::move(lhs)), rhs_(std::move(rhs)) {
}

void SubtractExpression::Accept(const Visitor& visitor) const {
    visitor.Visit(*this);
}

MultiplicateExpression::MultiplicateExpression(ExpressionPtr lhs, ExpressionPtr rhs)
    : lhs_(std::move(lhs)), rhs_(std::move(rhs)) {
}

void MultiplicateExpression::Accept(const Visitor& visitor) const {
    visitor.Visit(*this);
}

ArrayExpression::ArrayExpression(ExpressionPtr array, ExpressionPtr idx)
    : array_(std::move(array)), idx_(std::move(idx)) {
}

void ArrayExpression::Accept(const Visitor& visitor) const {
    visitor.Visit(*this);
}

LengthExpression::LengthExpression(ExpressionPtr container) : container_(std::move(container)) {
}

void LengthExpression::Accept(const Visitor& visitor) const {
    visitor.Visit(*this);
}

MethodCallExpression::MethodCallExpression(ExpressionPtr class_entity, IdentifierPtr method_name,
                                           Expressions params)
    : class_entity_(std::move(class_entity)),
      method_name_(std::move(method_name)),
      params_(std::move(params)) {
}

void MethodCallExpression::Accept(const Visitor& visitor) const {
    visitor.Visit(*this);
}

IntExpression::IntExpression(int value) : value_(value) {
}

void IntExpression::Accept(const Visitor& visitor) const {
    visitor.Visit(*this);
}

BoolExpression::BoolExpression(bool value) : value_(value) {
}

void BoolExpression::Accept(const Visitor& visitor) const {
    visitor.Visit(*this);
}

IdentifierExpression::IdentifierExpression(IdentifierPtr variable_name)
    : variable_name_(std::move(variable_name)) {
}

void IdentifierExpression::Accept(const Visitor& visitor) const {
    visitor.Visit(*this);
}

void ThisExpression::Accept(const Visitor& visitor) const {
    visitor.Visit(*this);
}

NewIntArrayExpression::NewIntArrayExpression(ExpressionPtr size) : size_(std::move(size)) {
}

void NewIntArrayExpression::Accept(const Visitor& visitor) const {
    visitor.Visit(*this);
}

NewExpression::NewExpression(IdentifierPtr class_name) : class_name_(std::move(class_name)) {
}

void NewExpression::Accept(const Visitor& visitor) const {
    visitor.Visit(*this);
}

NotExpression::NotExpression(ExpressionPtr expression) : expression_(std::move(expression)) {
}

void NotExpression::Accept(const Visitor& visitor) const {
    visitor.Visit(*this);
}

BetweenBracketsExpression::BetweenBracketsExpression(ExpressionPtr expression)
    : expression_(std ::move(expression)) {
}

void BetweenBracketsExpression::Accept(const Visitor& visitor) const {
    visitor.Visit(*this);
}