#pragma once

#include <vector>
#include <memory>

#include <ast_node.hpp>
#include <expressions.hpp>
#include <identifier.hpp>

class Statement : public ASTNode {};

using StatementPtr = std::shared_ptr<Statement>;
using Statements = std::vector<StatementPtr>;

class StatementList : public Statement {
public:
    explicit StatementList(Statements statements);
    void Accept(const Visitor& visitor) const override;

private:
    Statements statements_;
};

class IfElseStatement : public Statement {
public:
    IfElseStatement(ExpressionPtr clause, StatementPtr if_body, StatementPtr else_body);
    void Accept(const Visitor& visitor) const override;

private:
    ExpressionPtr clause_;
    StatementPtr if_body_;
    StatementPtr else_body_;
};

class WhileStatement : public Statement {
public:
    WhileStatement(ExpressionPtr clause, StatementPtr body);
    void Accept(const Visitor& visitor) const override;

private:
    ExpressionPtr clause_;
    StatementPtr body_;
};

class PrintStatement : public Statement {
public:
    explicit PrintStatement(ExpressionPtr value);
    void Accept(const Visitor& visitor) const override;

private:
    ExpressionPtr value_;
};

class AssignmentStatement : public Statement {
public:
    AssignmentStatement(IdentifierPtr variable, ExpressionPtr value);
    void Accept(const Visitor& visitor) const override;

private:
    IdentifierPtr variable_;
    ExpressionPtr value_;
};

class ArrayAssignmentStatement : public Statement {
public:
    ArrayAssignmentStatement(IdentifierPtr variable, ExpressionPtr size, ExpressionPtr value);
    void Accept(const Visitor& visitor) const override;

private:
    IdentifierPtr variable_;
    ExpressionPtr size_;
    ExpressionPtr value_;
};