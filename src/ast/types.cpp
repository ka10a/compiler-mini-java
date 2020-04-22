#include <types.hpp>
#include <visitor.hpp>

void IntType::Accept(const Visitor& visitor) const {
    visitor.Visit(*this);
}

void BoolType::Accept(const Visitor& visitor) const {
    visitor.Visit(*this);
}

void IntArrayType::Accept(const Visitor& visitor) const {
    visitor.Visit(*this);
}

IdentifierType::IdentifierType(IdentifierPtr class_name) : class_name_(std::move(class_name)) {
}

void IdentifierType::Accept(const Visitor& visitor) const {
    visitor.Visit(*this);
}
