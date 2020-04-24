#pragma once

#include <memory>

#include <ast/ast_node.hpp>
#include <ast/identifier.hpp>
#include <ast/statements.hpp>

class MainClass : public ASTNode {
public:
    MainClass(IdentifierPtr class_name, IdentifierPtr args_name, StatementPtr body);
    void Accept(Visitor& visitor) const override;
    const IdentifierPtr& GetClassName() const;
    const IdentifierPtr& GetArgsName() const;
    const StatementPtr& GetBody() const;

private:
    IdentifierPtr class_name_;
    IdentifierPtr args_name_;
    StatementPtr body_;
};

using MainClassPtr = std::shared_ptr<MainClass>;