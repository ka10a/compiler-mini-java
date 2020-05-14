#include <ast/types.hpp>
#include <visitors/visitor.hpp>

Type::Type(LocationPtr location) : ASTNode(std::move(location)) {
}

IntType::IntType(LocationPtr location) : Type(std::move(location)) {
}

void IntType::Accept(Visitor& visitor) const {
    visitor.Visit(*this);
}

BoolType::BoolType(LocationPtr location) : Type(std::move(location)) {
}

void BoolType::Accept(Visitor& visitor) const {
    visitor.Visit(*this);
}

IntArrayType::IntArrayType(LocationPtr location) : Type(std::move(location)) {
}

void IntArrayType::Accept(Visitor& visitor) const {
    visitor.Visit(*this);
}

ClassType::ClassType(LocationPtr location, IdentifierPtr class_name)
    : Type(std::move(location)), class_name_(std::move(class_name)) {
}

void ClassType::Accept(Visitor& visitor) const {
    visitor.Visit(*this);
}

const IdentifierPtr& ClassType::GetClassName() const {
    return class_name_;
}
