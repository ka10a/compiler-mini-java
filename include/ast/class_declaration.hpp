#pragma once

#include <memory>
#include <vector>

#include <ast_node.hpp>
#include <identifier.hpp>
#include <method_declaration.hpp>
#include <var_declaration.hpp>

class ClassDeclaration : public ASTNode {
public:
    ClassDeclaration(IdentifierPtr class_name, IdentifierPtr extends_class_name,
                     VarDeclarations variables, MethodDeclarations methods);
    void Accept(Visitor& visitor) const override;

private:
    IdentifierPtr class_name_;
    IdentifierPtr extends_class_name_;
    VarDeclarations variables_;
    MethodDeclarations methods_;
};

using ClassDeclarationPtr = std::shared_ptr<ClassDeclaration>;
using ClassDeclarations = std::vector<ClassDeclarationPtr>;