#pragma once

#include <memory>

#include <ast_node.hpp>
#include <identifier.hpp>
#include <statements.hpp>

class MainClass : public ASTNode {
public:
    MainClass(IdentifierPtr class_name, IdentifierPtr args_name, StatementPtr body);
    void Accept(const Visitor& visitor) const override;

private:
    IdentifierPtr class_name_;
    IdentifierPtr args_name_;
    StatementPtr body_;
};

using MainClassPtr = std::shared_ptr<MainClass>;