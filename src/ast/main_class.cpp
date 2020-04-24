#include <main_class.hpp>
#include <visitor.hpp>

MainClass::MainClass(IdentifierPtr class_name, IdentifierPtr args_name, StatementPtr body)
    : class_name_(std::move(class_name)), args_name_(std::move(args_name)), body_(std::move(body)) {
}

void MainClass::Accept(Visitor& visitor) const {
    visitor.Visit(*this);
}

const IdentifierPtr& MainClass::GetClassName() const {
    return class_name_;
}

const IdentifierPtr& MainClass::GetArgsName() const {
    return args_name_;
}

const StatementPtr& MainClass::GetBody() const {
    return body_;
}
