#include <types.hpp>
#include <visitor.hpp>

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
