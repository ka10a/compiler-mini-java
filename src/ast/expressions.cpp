#include <ast/expressions.hpp>
#include <visitors/visitor.hpp>

Expression::Expression(int first_line, int first_column) : ASTNode(first_line, first_column) {
}

AndExpression::AndExpression(int first_line, int first_column, ExpressionPtr lhs, ExpressionPtr rhs)
    : Expression(first_line, first_column), lhs_(std::move(lhs)), rhs_(std::move(rhs)) {
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

LessExpression::LessExpression(int first_line, int first_column, ExpressionPtr lhs,
                               ExpressionPtr rhs)
    : Expression(first_line, first_column), lhs_(std::move(lhs)), rhs_(std::move(rhs)) {
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

AddExpression::AddExpression(int first_line, int first_column, ExpressionPtr lhs, ExpressionPtr rhs)
    : Expression(first_line, first_column), lhs_(std::move(lhs)), rhs_(std::move(rhs)) {
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

SubtractExpression::SubtractExpression(int first_line, int first_column, ExpressionPtr lhs,
                                       ExpressionPtr rhs)
    : Expression(first_line, first_column), lhs_(std::move(lhs)), rhs_(std::move(rhs)) {
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

MultiplyExpression::MultiplyExpression(int first_line, int first_column, ExpressionPtr lhs,
                                       ExpressionPtr rhs)
    : Expression(first_line, first_column), lhs_(std::move(lhs)), rhs_(std::move(rhs)) {
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

ArrayExpression::ArrayExpression(int first_line, int first_column, ExpressionPtr array,
                                 ExpressionPtr idx)
    : Expression(first_line, first_column), array_(std::move(array)), idx_(std::move(idx)) {
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

LengthExpression::LengthExpression(int first_line, int first_column, ExpressionPtr container)
    : Expression(first_line, first_column), container_(std::move(container)) {
}

void LengthExpression::Accept(Visitor& visitor) const {
    visitor.Visit(*this);
}

const ExpressionPtr& LengthExpression::GetContainer() const {
    return container_;
}

MethodCallExpression::MethodCallExpression(int first_line, int first_column,
                                           ExpressionPtr class_entity, IdentifierPtr method_name,
                                           Expressions params)
    : Expression(first_line, first_column)
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

IntExpression::IntExpression(int first_line, int first_column, int value)
    : Expression(first_line, first_column), value_(value) {
}

void IntExpression::Accept(Visitor& visitor) const {
    visitor.Visit(*this);
}

int IntExpression::GetValue() const {
    return value_;
}

BoolExpression::BoolExpression(int first_line, int first_column, bool value)
    : Expression(first_line, first_column), value_(value) {
}

void BoolExpression::Accept(Visitor& visitor) const {
    visitor.Visit(*this);
}

bool BoolExpression::IsValue() const {
    return value_;
}

IdentifierExpression::IdentifierExpression(int first_line, int first_column,
                                           IdentifierPtr variable_name)
    : Expression(first_line, first_column), variable_name_(std::move(variable_name)) {
}

void IdentifierExpression::Accept(Visitor& visitor) const {
    visitor.Visit(*this);
}

const IdentifierPtr& IdentifierExpression::GetVariableName() const {
    return variable_name_;
}

ThisExpression::ThisExpression(int first_line, int first_column)
    : Expression(first_line, first_column) {
}

void ThisExpression::Accept(Visitor& visitor) const {
    visitor.Visit(*this);
}

NewIntArrayExpression::NewIntArrayExpression(int first_line, int first_column, ExpressionPtr size)
    : Expression(first_line, first_column), size_(std::move(size)) {
}

void NewIntArrayExpression::Accept(Visitor& visitor) const {
    visitor.Visit(*this);
}

const ExpressionPtr& NewIntArrayExpression::GetSize() const {
    return size_;
}

NewExpression::NewExpression(int first_line, int first_column, IdentifierPtr class_name)
    : Expression(first_line, first_column), class_name_(std::move(class_name)) {
}

void NewExpression::Accept(Visitor& visitor) const {
    visitor.Visit(*this);
}

const IdentifierPtr& NewExpression::GetClassName() const {
    return class_name_;
}

NotExpression::NotExpression(int first_line, int first_column, ExpressionPtr expression)
    : Expression(first_line, first_column), expression_(std::move(expression)) {
}

void NotExpression::Accept(Visitor& visitor) const {
    visitor.Visit(*this);
}

const ExpressionPtr& NotExpression::GetExpression() const {
    return expression_;
}
