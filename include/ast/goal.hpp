#pragma once

#include <memory>
#include <vector>

#include <main_class.hpp>
#include <class_declaration.hpp>

class Goal : public ASTNode {
public:
    Goal(MainClassPtr main_class, ClassDeclarations class_declarations);
    void Accept(const Visitor& visitor) const override;

private:
    MainClassPtr main_class_;
    ClassDeclarations class_declarations_;
};

using GoalPtr = std::shared_ptr<Goal>;
