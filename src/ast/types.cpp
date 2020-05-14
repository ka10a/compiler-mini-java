#include <ast/types.hpp>
#include <visitors/visitor.hpp>

Type::Type(int first_line, int first_column) : ASTNode(first_line, first_column) {
}

IntType::IntType(int first_line, int first_column) : Type(first_line, first_column) {
}

void IntType::Accept(Visitor& visitor) const {
    visitor.Visit(*this);
}

BoolType::BoolType(int first_line, int first_column) : Type(first_line, first_column) {
}

void BoolType::Accept(Visitor& visitor) const {
    visitor.Visit(*this);
}

IntArrayType::IntArrayType(int first_line, int first_column) : Type(first_line, first_column) {
}

void IntArrayType::Accept(Visitor& visitor) const {
    visitor.Visit(*this);
}

ClassType::ClassType(int first_line, int first_column, IdentifierPtr class_name)
    : Type(first_line, first_column), class_name_(std::move(class_name)) {
}

void ClassType::Accept(Visitor& visitor) const {
    visitor.Visit(*this);
}

const IdentifierPtr& ClassType::GetClassName() const {
    return class_name_;
}
