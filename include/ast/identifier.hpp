#pragma once

#include <string>
#include <memory>

#include <ast_node.hpp>

class Identifier : public ASTNode {
public:
    explicit Identifier(std::string name);
    void Accept(const Visitor& visitor) const override;

private:
    std::string name_;
};

using IdentifierPtr = std::shared_ptr<Identifier>;
