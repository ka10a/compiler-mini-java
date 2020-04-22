#pragma once

#include <memory>
#include <vector>

#include <ast_node.hpp>
#include <identifier.hpp>

class Expression : public ASTNode {};

using ExpressionPtr = std::unique_ptr<Expression>;
using Expressions = std::vector<ExpressionPtr>;

class AndExpression : public Expression {
public:
    AndExpression(ExpressionPtr lhs, ExpressionPtr rhs);
    void Accept(const Visitor& visitor) const override;

private:
    ExpressionPtr lhs_;
    ExpressionPtr rhs_;
};

class LessExpression : public Expression {
public:
    LessExpression(ExpressionPtr lhs, ExpressionPtr rhs);
    void Accept(const Visitor& visitor) const override;

private:
    ExpressionPtr lhs_;
    ExpressionPtr rhs_;
};

class AddExpression : public Expression {
public:
    AddExpression(ExpressionPtr lhs, ExpressionPtr rhs);
    void Accept(const Visitor& visitor) const override;

private:
    ExpressionPtr lhs_;
    ExpressionPtr rhs_;
};

class SubtractExpression : public Expression {
public:
    SubtractExpression(ExpressionPtr lhs, ExpressionPtr rhs);
    void Accept(const Visitor& visitor) const override;

private:
    ExpressionPtr lhs_;
    ExpressionPtr rhs_;
};

class MultiplicateExpression : public Expression {
public:
    MultiplicateExpression(ExpressionPtr lhs, ExpressionPtr rhs);
    void Accept(const Visitor& visitor) const override;

private:
    ExpressionPtr lhs_;
    ExpressionPtr rhs_;
};

class ArrayExpression : public Expression {
public:
    ArrayExpression(ExpressionPtr array, ExpressionPtr idx);
    void Accept(const Visitor& visitor) const override;

private:
    ExpressionPtr array_;
    ExpressionPtr idx_;
};

class LengthExpression : public Expression {
public:
    LengthExpression(ExpressionPtr container);
    void Accept(const Visitor& visitor) const override;

private:
    ExpressionPtr container_;
};

class MethodCallExpression : public Expression {
public:
    MethodCallExpression(ExpressionPtr class_entity, IdentifierPtr method_name, Expressions params);
    void Accept(const Visitor& visitor) const override;

private:
    ExpressionPtr class_entity_;
    IdentifierPtr method_name_;
    Expressions params_;
};

class IntExpression : public Expression {
public:
    IntExpression(int value);
    void Accept(const Visitor& visitor) const override;

private:
    int value_;
};

class BoolExpression : public Expression {
public:
    BoolExpression(bool value);
    void Accept(const Visitor& visitor) const override;

private:
    bool value_;
};

class IdentifierExpression : public Expression {
public:
    IdentifierExpression(IdentifierPtr variable_name);
    void Accept(const Visitor& visitor) const override;

private:
    IdentifierPtr variable_name_;
};

class ThisExpression : public Expression {
public:
    ThisExpression() = default;
    void Accept(const Visitor& visitor) const override;
};

class NewIntArrayExpression : public Expression {
public:
    NewIntArrayExpression(ExpressionPtr size);
    void Accept(const Visitor& visitor) const override;

private:
    ExpressionPtr size_;
};

class NewExpression : public Expression {
public:
    NewExpression(IdentifierPtr class_name);
    void Accept(const Visitor& visitor) const override;

private:
    IdentifierPtr class_name_;
};

class NotExpression : public Expression {
public:
    NotExpression(ExpressionPtr expression);
    void Accept(const Visitor& visitor) const override;

private:
    ExpressionPtr expression_;
};

class BetweenBracketsExpression : public Expression {
public:
    BetweenBracketsExpression(ExpressionPtr expression);
    void Accept(const Visitor& visitor) const override;

private:
    ExpressionPtr expression_;
};
