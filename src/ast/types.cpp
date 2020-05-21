#include <ast/types.hpp>
#include <visitors/visitor.hpp>

Type::Type(LocationPtr location) : ASTNode(std::move(location)) {
}
const IdentifierPtr& Type::GetClassName() const {
    throw std::logic_error("This is not a custom class.");
}

IntType::IntType(LocationPtr location) : Type(std::move(location)) {
}

void IntType::Accept(Visitor& visitor) const {
    visitor.Visit(*this);
}

InnerType IntType::GetInnerType() const {
    return InnerType::INT;
}

BoolType::BoolType(LocationPtr location) : Type(std::move(location)) {
}

void BoolType::Accept(Visitor& visitor) const {
    visitor.Visit(*this);
}

InnerType BoolType::GetInnerType() const {
    return InnerType::BOOL;
}

IntArrayType::IntArrayType(LocationPtr location) : Type(std::move(location)) {
}

void IntArrayType::Accept(Visitor& visitor) const {
    visitor.Visit(*this);
}

InnerType IntArrayType::GetInnerType() const {
    return InnerType::INT_ARRAY;
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

InnerType ClassType::GetInnerType() const {
    return InnerType::CLASS;
}
