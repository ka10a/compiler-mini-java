#include <ast/statements.hpp>
#include <visitors/visitor.hpp>

Statement::Statement(int first_line, int first_column) : ASTNode(first_line, first_column) {
}

StatementList::StatementList(int first_line, int first_column, Statements statements)
    : Statement(first_line, first_column), statements_(std::move(statements)) {
}

void StatementList::Accept(Visitor& visitor) const {
    visitor.Visit(*this);
}

const Statements& StatementList::GetStatements() const {
    return statements_;
}

IfElseStatement::IfElseStatement(int first_line, int first_column, ExpressionPtr clause,
                                 StatementPtr if_body, StatementPtr else_body)
    : Statement(first_line, first_column)
    , clause_(std::move(clause))
    , if_body_(std::move(if_body))
    , else_body_(std::move(else_body)) {
}

void IfElseStatement::Accept(Visitor& visitor) const {
    visitor.Visit(*this);
}

const ExpressionPtr& IfElseStatement::GetClause() const {
    return clause_;
}

const StatementPtr& IfElseStatement::GetIfBody() const {
    return if_body_;
}

const StatementPtr& IfElseStatement::GetElseBody() const {
    return else_body_;
}

WhileStatement::WhileStatement(int first_line, int first_column, ExpressionPtr clause,
                               StatementPtr body)
    : Statement(first_line, first_column), clause_(std::move(clause)), body_(std::move(body)) {
}

void WhileStatement::Accept(Visitor& visitor) const {
    visitor.Visit(*this);
}

const ExpressionPtr& WhileStatement::GetClause() const {
    return clause_;
}

const StatementPtr& WhileStatement::GetBody() const {
    return body_;
}

PrintStatement::PrintStatement(int first_line, int first_column, ExpressionPtr value)
    : Statement(first_line, first_column), value_(std::move(value)) {
}

void PrintStatement::Accept(Visitor& visitor) const {
    visitor.Visit(*this);
}

const ExpressionPtr& PrintStatement::GetValue() const {
    return value_;
}

AssignmentStatement::AssignmentStatement(int first_line, int first_column, IdentifierPtr variable,
                                         ExpressionPtr value)
    : Statement(first_line, first_column)
    , variable_(std::move(variable))
    , value_(std::move(value)) {
}

void AssignmentStatement::Accept(Visitor& visitor) const {
    visitor.Visit(*this);
}

const IdentifierPtr& AssignmentStatement::GetVariable() const {
    return variable_;
}

const ExpressionPtr& AssignmentStatement::GetValue() const {
    return value_;
}

ArrayAssignmentStatement::ArrayAssignmentStatement(int first_line, int first_column,
                                                   IdentifierPtr variable, ExpressionPtr size,
                                                   ExpressionPtr value)
    : Statement(first_line, first_column)
    , variable_(std::move(variable))
    , size_(std::move(size))
    , value_(std::move(value)) {
}

void ArrayAssignmentStatement::Accept(Visitor& visitor) const {
    visitor.Visit(*this);
}

const IdentifierPtr& ArrayAssignmentStatement::GetVariable() const {
    return variable_;
}

const ExpressionPtr& ArrayAssignmentStatement::GetSize() const {
    return size_;
}

const ExpressionPtr& ArrayAssignmentStatement::GetValue() const {
    return value_;
}
