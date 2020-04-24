#include <goal.hpp>
#include <visitor.hpp>

Goal::Goal(MainClassPtr main_class, ClassDeclarations class_declarations)
    : main_class_(std::move(main_class)), class_declarations_(std::move(class_declarations)) {
}

void Goal::Accept(Visitor& visitor) const {
    visitor.Visit(*this);
}
