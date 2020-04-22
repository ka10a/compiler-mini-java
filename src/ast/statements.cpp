#include <statements.hpp>
#include <visitor.hpp>

StatementList::StatementList(Statements statements) : statements_(std::move(statements)) {
}

void StatementList::Accept(const Visitor& visitor) const {
    visitor.Visit(*this);
}

IfElseStatement::IfElseStatement(ExpressionPtr clause, StatementPtr if_body, StatementPtr else_body)
    : clause_(std::move(clause)), if_body_(std::move(if_body)), else_body_(std::move(else_body)) {
}

void IfElseStatement::Accept(const Visitor& visitor) const {
    visitor.Visit(*this);
}

WhileStatement::WhileStatement(ExpressionPtr clause, StatementPtr body)
    : clause_(std::move(clause)), body_(std::move(body)) {
}

void WhileStatement::Accept(const Visitor& visitor) const {
    visitor.Visit(*this);
}

PrintStatement::PrintStatement(ExpressionPtr value) : value_(std::move(value)) {
}

void PrintStatement::Accept(const Visitor& visitor) const {
    visitor.Visit(*this);
}

AssignmentStatement::AssignmentStatement(IdentifierPtr variable, ExpressionPtr value)
    : variable_(std::move(variable)), value_(std::move(value)) {
}

void AssignmentStatement::Accept(const Visitor& visitor) const {
    visitor.Visit(*this);
}

ArrayAssignmentStatement::ArrayAssignmentStatement(IdentifierPtr variable, ExpressionPtr size,
                                                   ExpressionPtr value)
    : variable_(std::move(variable)), size_(std::move(size)), value_(std::move(value)) {
}

void ArrayAssignmentStatement::Accept(const Visitor& visitor) const {
    visitor.Visit(*this);
}
