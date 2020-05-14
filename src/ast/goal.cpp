#include <ast/goal.hpp>
#include <visitors/visitor.hpp>

Goal::Goal(int first_line, int first_column, MainClassPtr main_class,
           ClassDeclarations class_declarations)
    : ASTNode(first_line, first_column)
    , main_class_(std::move(main_class))
    , class_declarations_(std::move(class_declarations)) {
}

void Goal::Accept(Visitor& visitor) const {
    visitor.Visit(*this);
}

const MainClassPtr& Goal::GetMainClass() const {
    return main_class_;
}

const ClassDeclarations& Goal::GetClassDeclarations() const {
    return class_declarations_;
}
