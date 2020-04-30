#pragma once

#include <deque>
#include <memory>

#include <ast/ast_node.hpp>
#include <ast/identifier.hpp>
#include <ast/method_declaration.hpp>
#include <ast/var_declaration.hpp>

class ClassDeclaration : public ASTNode {
public:
    ClassDeclaration(IdentifierPtr class_name, IdentifierPtr extends_class_name,
                     VarDeclarations variables, MethodDeclarations methods);
    void Accept(Visitor& visitor) const override;
    const IdentifierPtr& GetClassName() const;
    const IdentifierPtr& GetExtendsClassName() const;
    const VarDeclarations& GetVariables() const;
    const MethodDeclarations& GetMethods() const;

private:
    IdentifierPtr class_name_;
    IdentifierPtr extends_class_name_;
    VarDeclarations variables_;
    MethodDeclarations methods_;
};

using ClassDeclarationPtr = std::shared_ptr<ClassDeclaration>;
using ClassDeclarations = std::deque<ClassDeclarationPtr>;