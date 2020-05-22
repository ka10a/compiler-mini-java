#pragma once

#include <string>
#include <memory>

#include <ast/ast_node.hpp>

class Identifier : public ASTNode {
public:
    Identifier(LocationPtr location, std::string name);
    void Accept(Visitor& visitor) const override;
    const std::string& GetName() const;

private:
    std::string name_;
};

using IdentifierPtr = std::shared_ptr<Identifier>;
