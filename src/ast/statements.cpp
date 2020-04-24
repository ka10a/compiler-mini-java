#include <ast/statements.hpp>
#include <visitors/visitor.hpp>

StatementList::StatementList(Statements statements) : statements_(std::move(statements)) {
}

void StatementList::Accept(Visitor& visitor) const {
    visitor.Visit(*this);
}

const Statements& StatementList::GetStatements() const {
    return statements_;
}

IfElseStatement::IfElseStatement(ExpressionPtr clause, StatementPtr if_body, StatementPtr else_body)
    : clause_(std::move(clause)), if_body_(std::move(if_body)), else_body_(std::move(else_body)) {
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

WhileStatement::WhileStatement(ExpressionPtr clause, StatementPtr body)
    : clause_(std::move(clause)), body_(std::move(body)) {
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

PrintStatement::PrintStatement(ExpressionPtr value) : value_(std::move(value)) {
}

void PrintStatement::Accept(Visitor& visitor) const {
    visitor.Visit(*this);
}

const ExpressionPtr& PrintStatement::GetValue() const {
    return value_;
}

AssignmentStatement::AssignmentStatement(IdentifierPtr variable, ExpressionPtr value)
    : variable_(std::move(variable)), value_(std::move(value)) {
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

ArrayAssignmentStatement::ArrayAssignmentStatement(IdentifierPtr variable, ExpressionPtr size,
                                                   ExpressionPtr value)
    : variable_(std::move(variable)), size_(std::move(size)), value_(std::move(value)) {
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
