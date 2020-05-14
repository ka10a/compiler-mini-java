#include <ast/main_class.hpp>
#include <visitors/visitor.hpp>

MainClass::MainClass(int first_line, int first_column, IdentifierPtr class_name, StatementPtr body)
    : ASTNode(first_line, first_column)
    , class_name_(std::move(class_name))
    , body_(std::move(body)) {
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
