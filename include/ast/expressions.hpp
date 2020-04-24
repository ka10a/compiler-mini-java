#pragma once

#include <memory>
#include <vector>

#include <ast/ast_node.hpp>
#include <ast/identifier.hpp>

class Expression : public ASTNode {};

using ExpressionPtr = std::shared_ptr<Expression>;
using Expressions = std::vector<ExpressionPtr>;

class AndExpression : public Expression {
public:
    AndExpression(ExpressionPtr lhs, ExpressionPtr rhs);
    void Accept(Visitor& visitor) const override;
    const ExpressionPtr& GetLhs() const;
    const ExpressionPtr& GetRhs() const;

private:
    ExpressionPtr lhs_;
    ExpressionPtr rhs_;
};

class LessExpression : public Expression {
public:
    LessExpression(ExpressionPtr lhs, ExpressionPtr rhs);
    void Accept(Visitor& visitor) const override;
    const ExpressionPtr& GetLhs() const;
    const ExpressionPtr& GetRhs() const;

private:
    ExpressionPtr lhs_;
    ExpressionPtr rhs_;
};

class AddExpression : public Expression {
public:
    AddExpression(ExpressionPtr lhs, ExpressionPtr rhs);
    void Accept(Visitor& visitor) const override;
    const ExpressionPtr& GetLhs() const;
    const ExpressionPtr& GetRhs() const;

private:
    ExpressionPtr lhs_;
    ExpressionPtr rhs_;
};

class SubtractExpression : public Expression {
public:
    SubtractExpression(ExpressionPtr lhs, ExpressionPtr rhs);
    void Accept(Visitor& visitor) const override;
    const ExpressionPtr& GetLhs() const;
    const ExpressionPtr& GetRhs() const;

private:
    ExpressionPtr lhs_;
    ExpressionPtr rhs_;
};

class MultiplicateExpression : public Expression {
public:
    MultiplicateExpression(ExpressionPtr lhs, ExpressionPtr rhs);
    void Accept(Visitor& visitor) const override;
    const ExpressionPtr& GetLhs() const;
    const ExpressionPtr& GetRhs() const;

private:
    ExpressionPtr lhs_;
    ExpressionPtr rhs_;
};

class ArrayExpression : public Expression {
public:
    ArrayExpression(ExpressionPtr array, ExpressionPtr idx);
    void Accept(Visitor& visitor) const override;
    const ExpressionPtr& GetArray() const;
    const ExpressionPtr& GetIdx() const;

private:
    ExpressionPtr array_;
    ExpressionPtr idx_;
};

class LengthExpression : public Expression {
public:
    explicit LengthExpression(ExpressionPtr container);
    void Accept(Visitor& visitor) const override;
    const ExpressionPtr& GetContainer() const;

private:
    ExpressionPtr container_;
};

class MethodCallExpression : public Expression {
public:
    MethodCallExpression(ExpressionPtr class_entity, IdentifierPtr method_name, Expressions params);
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
    explicit IntExpression(int value);
    void Accept(Visitor& visitor) const override;
    int GetValue() const;

private:
    int value_;
};

class BoolExpression : public Expression {
public:
    explicit BoolExpression(bool value);
    void Accept(Visitor& visitor) const override;
    bool IsValue() const;

private:
    bool value_;
};

class IdentifierExpression : public Expression {
public:
    explicit IdentifierExpression(IdentifierPtr variable_name);
    void Accept(Visitor& visitor) const override;
    const IdentifierPtr& GetVariableName() const;

private:
    IdentifierPtr variable_name_;
};

class ThisExpression : public Expression {
public:
    ThisExpression() = default;
    void Accept(Visitor& visitor) const override;
};

class NewIntArrayExpression : public Expression {
public:
    explicit NewIntArrayExpression(ExpressionPtr size);
    void Accept(Visitor& visitor) const override;
    const ExpressionPtr& GetSize() const;

private:
    ExpressionPtr size_;
};

class NewExpression : public Expression {
public:
    explicit NewExpression(IdentifierPtr class_name);
    void Accept(Visitor& visitor) const override;
    const IdentifierPtr& GetClassName() const;

private:
    IdentifierPtr class_name_;
};

class NotExpression : public Expression {
public:
    explicit NotExpression(ExpressionPtr expression);
    void Accept(Visitor& visitor) const override;
    const ExpressionPtr& GetExpression() const;

private:
    ExpressionPtr expression_;
};

class BetweenBracketsExpression : public Expression {
public:
    explicit BetweenBracketsExpression(ExpressionPtr expression);
    void Accept(Visitor& visitor) const override;
    const ExpressionPtr& GetExpression() const;

private:
    ExpressionPtr expression_;
};
