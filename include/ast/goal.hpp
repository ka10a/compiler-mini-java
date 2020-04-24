#pragma once

#include <memory>
#include <vector>

#include <ast/main_class.hpp>
#include <ast/class_declaration.hpp>

class Goal : public ASTNode {
public:
    Goal(MainClassPtr main_class, ClassDeclarations class_declarations);
    void Accept(Visitor& visitor) const override;
    const MainClassPtr& GetMainClass() const;
    const ClassDeclarations& GetClassDeclarations() const;

private:
    MainClassPtr main_class_;
    ClassDeclarations class_declarations_;
};

using GoalPtr = std::shared_ptr<Goal>;
