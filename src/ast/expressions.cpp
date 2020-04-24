#include <ast/expressions.hpp>
#include <visitors/visitor.hpp>

AndExpression::AndExpression(ExpressionPtr lhs, ExpressionPtr rhs)
    : lhs_(std::move(lhs)), rhs_(std::move(rhs)) {
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

LessExpression::LessExpression(ExpressionPtr lhs, ExpressionPtr rhs)
    : lhs_(std::move(lhs)), rhs_(std::move(rhs)) {
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

AddExpression::AddExpression(ExpressionPtr lhs, ExpressionPtr rhs)
    : lhs_(std::move(lhs)), rhs_(std::move(rhs)) {
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

SubtractExpression::SubtractExpression(ExpressionPtr lhs, ExpressionPtr rhs)
    : lhs_(std::move(lhs)), rhs_(std::move(rhs)) {
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

MultiplicateExpression::MultiplicateExpression(ExpressionPtr lhs, ExpressionPtr rhs)
    : lhs_(std::move(lhs)), rhs_(std::move(rhs)) {
}

void MultiplicateExpression::Accept(Visitor& visitor) const {
    visitor.Visit(*this);
}

const ExpressionPtr& MultiplicateExpression::GetLhs() const {
    return lhs_;
}

const ExpressionPtr& MultiplicateExpression::GetRhs() const {
    return rhs_;
}

ArrayExpression::ArrayExpression(ExpressionPtr array, ExpressionPtr idx)
    : array_(std::move(array)), idx_(std::move(idx)) {
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

LengthExpression::LengthExpression(ExpressionPtr container) : container_(std::move(container)) {
}

void LengthExpression::Accept(Visitor& visitor) const {
    visitor.Visit(*this);
}

const ExpressionPtr& LengthExpression::GetContainer() const {
    return container_;
}

MethodCallExpression::MethodCallExpression(ExpressionPtr class_entity, IdentifierPtr method_name,
                                           Expressions params)
    : class_entity_(std::move(class_entity)),
      method_name_(std::move(method_name)),
      params_(std::move(params)) {
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

IntExpression::IntExpression(int value) : value_(value) {
}

void IntExpression::Accept(Visitor& visitor) const {
    visitor.Visit(*this);
}

int IntExpression::GetValue() const {
    return value_;
}

BoolExpression::BoolExpression(bool value) : value_(value) {
}

void BoolExpression::Accept(Visitor& visitor) const {
    visitor.Visit(*this);
}

bool BoolExpression::IsValue() const {
    return value_;
}

IdentifierExpression::IdentifierExpression(IdentifierPtr variable_name)
    : variable_name_(std::move(variable_name)) {
}

void IdentifierExpression::Accept(Visitor& visitor) const {
    visitor.Visit(*this);
}

const IdentifierPtr& IdentifierExpression::GetVariableName() const {
    return variable_name_;
}

void ThisExpression::Accept(Visitor& visitor) const {
    visitor.Visit(*this);
}

NewIntArrayExpression::NewIntArrayExpression(ExpressionPtr size) : size_(std::move(size)) {
}

void NewIntArrayExpression::Accept(Visitor& visitor) const {
    visitor.Visit(*this);
}

const ExpressionPtr& NewIntArrayExpression::GetSize() const {
    return size_;
}

NewExpression::NewExpression(IdentifierPtr class_name) : class_name_(std::move(class_name)) {
}

void NewExpression::Accept(Visitor& visitor) const {
    visitor.Visit(*this);
}

const IdentifierPtr& NewExpression::GetClassName() const {
    return class_name_;
}

NotExpression::NotExpression(ExpressionPtr expression) : expression_(std::move(expression)) {
}

void NotExpression::Accept(Visitor& visitor) const {
    visitor.Visit(*this);
}

const ExpressionPtr& NotExpression::GetExpression() const {
    return expression_;
}

BetweenBracketsExpression::BetweenBracketsExpression(ExpressionPtr expression)
    : expression_(std ::move(expression)) {
}

void BetweenBracketsExpression::Accept(Visitor& visitor) const {
    visitor.Visit(*this);
}

const ExpressionPtr& BetweenBracketsExpression::GetExpression() const {
    return expression_;
}
