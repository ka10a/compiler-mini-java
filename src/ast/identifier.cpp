#include <identifier.hpp>
#include <visitor.hpp>

Identifier::Identifier(std::string name) : name_(std::move(name)) {
}

void Identifier::Accept(Visitor& visitor) const {
    visitor.Visit(*this);
}

const std::string& Identifier::GetName() const {
    return name_;
}
