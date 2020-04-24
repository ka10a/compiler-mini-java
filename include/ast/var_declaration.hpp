#pragma once

#include <memory>
#include <vector>

#include <ast/ast_node.hpp>
#include <ast/types.hpp>

class VarDeclaration : public ASTNode {
public:
    VarDeclaration(TypePtr type, IdentifierPtr name);
    void Accept(Visitor& visitor) const override;
    const TypePtr& GetType() const;
    const IdentifierPtr& GetName() const;

private:
    TypePtr type_;
    IdentifierPtr name_;
};

using VarDeclarationPtr = std::shared_ptr<VarDeclaration>;
using VarDeclarations = std::vector<VarDeclarationPtr>;
