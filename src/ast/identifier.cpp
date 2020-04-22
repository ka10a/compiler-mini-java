#include <identifier.hpp>
#include <visitor.hpp>

Identifier::Identifier(std::string name) : name_(std::move(name)) {
}

void Identifier::Accept(const Visitor& visitor) const {
    visitor.Visit(*this);
}
