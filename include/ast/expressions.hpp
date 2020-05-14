#pragma once

#include <deque>
#include <memory>

#include <ast/ast_node.hpp>
#include <ast/identifier.hpp>

class Expression : public ASTNode {
public:
    Expression(int first_line, int first_column);
};

using ExpressionPtr = std::shared_ptr<Expression>;
using Expressions = std::deque<ExpressionPtr>;

class AndExpression : public Expression {
public:
    AndExpression(int first_line, int first_column, ExpressionPtr lhs, ExpressionPtr rhs);
    void Accept(Visitor& visitor) const override;
    const ExpressionPtr& GetLhs() const;
    const ExpressionPtr& GetRhs() const;

private:
    ExpressionPtr lhs_;
    ExpressionPtr rhs_;
};

class LessExpression : public Expression {
public:
    LessExpression(int first_line, int first_column, ExpressionPtr lhs, ExpressionPtr rhs);
    void Accept(Visitor& visitor) const override;
    const ExpressionPtr& GetLhs() const;
    const ExpressionPtr& GetRhs() const;

private:
    ExpressionPtr lhs_;
    ExpressionPtr rhs_;
};

class AddExpression : public Expression {
public:
    AddExpression(int first_line, int first_column, ExpressionPtr lhs, ExpressionPtr rhs);
    void Accept(Visitor& visitor) const override;
    const ExpressionPtr& GetLhs() const;
    const ExpressionPtr& GetRhs() const;

private:
    ExpressionPtr lhs_;
    ExpressionPtr rhs_;
};

class SubtractExpression : public Expression {
public:
    SubtractExpression(int first_line, int first_column, ExpressionPtr lhs, ExpressionPtr rhs);
    void Accept(Visitor& visitor) const override;
    const ExpressionPtr& GetLhs() const;
    const ExpressionPtr& GetRhs() const;

private:
    ExpressionPtr lhs_;
    ExpressionPtr rhs_;
};

class MultiplicateExpression : public Expression {
public:
    MultiplicateExpression(int first_line, int first_column, ExpressionPtr lhs, ExpressionPtr rhs);
    void Accept(Visitor& visitor) const override;
    const ExpressionPtr& GetLhs() const;
    const ExpressionPtr& GetRhs() const;

private:
    ExpressionPtr lhs_;
    ExpressionPtr rhs_;
};

class ArrayExpression : public Expression {
public:
    ArrayExpression(int first_line, int first_column, ExpressionPtr array, ExpressionPtr idx);
    void Accept(Visitor& visitor) const override;
    const ExpressionPtr& GetArray() const;
    const ExpressionPtr& GetIdx() const;

private:
    ExpressionPtr array_;
    ExpressionPtr idx_;
};

class LengthExpression : public Expression {
public:
    LengthExpression(int first_line, int first_column, ExpressionPtr container);
    void Accept(Visitor& visitor) const override;
    const ExpressionPtr& GetContainer() const;

private:
    ExpressionPtr container_;
};

class MethodCallExpression : public Expression {
public:
    MethodCallExpression(int first_line, int first_column, ExpressionPtr class_entity,
                         IdentifierPtr method_name, Expressions params);
    void Accept(Visitor& visitor) const override;
    const ExpressionPtr& GetClassEntity() const;
    const IdentifierPtr& GetMethodName() const;
    const Expressions& GetParams() const;

private:
    ExpressionPtr class_entity_;
    IdentifierPtr method_name_;
    Expressions params_;
};

class IntExpression : public Expression {
public:
    IntExpression(int first_line, int first_column, int value);
    void Accept(Visitor& visitor) const override;
    int GetValue() const;

private:
    int value_;
};

class BoolExpression : public Expression {
public:
    BoolExpression(int first_line, int first_column, bool value);
    void Accept(Visitor& visitor) const override;
    bool IsValue() const;

private:
    bool value_;
};

class IdentifierExpression : public Expression {
public:
    IdentifierExpression(int first_line, int first_column, IdentifierPtr variable_name);
    void Accept(Visitor& visitor) const override;
    const IdentifierPtr& GetVariableName() const;

private:
    IdentifierPtr variable_name_;
};

class ThisExpression : public Expression {
public:
    ThisExpression(int first_line, int first_column);
    void Accept(Visitor& visitor) const override;
};

class NewIntArrayExpression : public Expression {
public:
    NewIntArrayExpression(int first_line, int first_column, ExpressionPtr size);
    void Accept(Visitor& visitor) const override;
    const ExpressionPtr& GetSize() const;

private:
    ExpressionPtr size_;
};

class NewExpression : public Expression {
public:
    NewExpression(int first_line, int first_column, IdentifierPtr class_name);
    void Accept(Visitor& visitor) const override;
    const IdentifierPtr& GetClassName() const;

private:
    IdentifierPtr class_name_;
};

class NotExpression : public Expression {
public:
    NotExpression(int first_line, int first_column, ExpressionPtr expression);
    void Accept(Visitor& visitor) const override;
    const ExpressionPtr& GetExpression() const;

private:
    ExpressionPtr expression_;
};
