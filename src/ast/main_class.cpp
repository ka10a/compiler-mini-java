#include <ast/main_class.hpp>
#include <visitors/visitor.hpp>

MainClass::MainClass(IdentifierPtr class_name, StatementPtr body)
    : class_name_(std::move(class_name)), body_(std::move(body)) {
}

void MainClass::Accept(Visitor& visitor) const {
    visitor.Visit(*this);
}

const IdentifierPtr& MainClass::GetClassName() const {
    return class_name_;
}

const StatementPtr& MainClass::GetBody() const {
    return body_;
}
