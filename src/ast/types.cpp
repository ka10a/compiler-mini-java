#include <ast/types.hpp>
#include <visitors/visitor.hpp>

void IntType::Accept(Visitor& visitor) const {
    visitor.Visit(*this);
}

void BoolType::Accept(Visitor& visitor) const {
    visitor.Visit(*this);
}

void IntArrayType::Accept(Visitor& visitor) const {
    visitor.Visit(*this);
}

IdentifierType::IdentifierType(IdentifierPtr class_name) : class_name_(std::move(class_name)) {
}

void IdentifierType::Accept(Visitor& visitor) const {
    visitor.Visit(*this);
}

const IdentifierPtr& IdentifierType::GetClassName() const {
    return class_name_;
}
