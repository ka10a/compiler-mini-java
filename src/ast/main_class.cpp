#include <ast/main_class.hpp>
#include <visitors/visitor.hpp>

MainClass::MainClass(LocationPtr location, IdentifierPtr class_name, StatementPtr body)
    : ASTNode(std::move(location)), class_name_(std::move(class_name)), body_(std::move(body)) {
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
