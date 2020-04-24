#pragma once

#include <memory>
#include <vector>

#include <ast_node.hpp>
#include <types.hpp>

class VarDeclaration : public ASTNode {
public:
    VarDeclaration(TypePtr type, IdentifierPtr name);
    void Accept(Visitor& visitor) const override;

private:
    TypePtr type_;
    IdentifierPtr name_;
};

using VarDeclarationPtr = std::shared_ptr<VarDeclaration>;
using VarDeclarations = std::vector<VarDeclarationPtr>;
