#pragma once

#include <deque>
#include <memory>

#include <ast/ast_node.hpp>
#include <ast/expressions.hpp>
#include <ast/identifier.hpp>

class Statement : public ASTNode {
public:
    Statement(LocationPtr location);
};

using StatementPtr = std::shared_ptr<Statement>;
using Statements = std::deque<StatementPtr>;

class StatementList : public Statement {
public:
    StatementList(LocationPtr location, Statements statements);
    void Accept(Visitor& visitor) const override;
    const Statements& GetStatements() const;

private:
    Statements statements_;
};

class IfElseStatement : public Statement {
public:
    IfElseStatement(LocationPtr location, ExpressionPtr clause, StatementPtr if_body,
                    StatementPtr else_body);
    void Accept(Visitor& visitor) const override;
    const ExpressionPtr& GetClause() const;
    const StatementPtr& GetIfBody() const;
    const StatementPtr& GetElseBody() const;

private:
    ExpressionPtr clause_;
    StatementPtr if_body_;
    StatementPtr else_body_;
};

class WhileStatement : public Statement {
public:
    WhileStatement(LocationPtr location, ExpressionPtr clause, StatementPtr body);
    void Accept(Visitor& visitor) const override;
    const ExpressionPtr& GetClause() const;
    const StatementPtr& GetBody() const;

private:
    ExpressionPtr clause_;
    StatementPtr body_;
};

class PrintStatement : public Statement {
public:
    PrintStatement(LocationPtr location, ExpressionPtr value);
    void Accept(Visitor& visitor) const override;
    const ExpressionPtr& GetValue() const;

private:
    ExpressionPtr value_;
};

class AssignmentStatement : public Statement {
public:
    AssignmentStatement(LocationPtr location, IdentifierPtr variable, ExpressionPtr value);
    void Accept(Visitor& visitor) const override;
    const IdentifierPtr& GetVariable() const;
    const ExpressionPtr& GetValue() const;

private:
    IdentifierPtr variable_;
    ExpressionPtr value_;
};

class ArrayAssignmentStatement : public Statement {
public:
    ArrayAssignmentStatement(LocationPtr location, IdentifierPtr variable, ExpressionPtr size,
                             ExpressionPtr value);
    void Accept(Visitor& visitor) const override;
    const IdentifierPtr& GetVariable() const;
    const ExpressionPtr& GetSize() const;
    const ExpressionPtr& GetValue() const;

private:
    IdentifierPtr variable_;
    ExpressionPtr size_;
    ExpressionPtr value_;
};