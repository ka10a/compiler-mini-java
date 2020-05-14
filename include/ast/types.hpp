#pragma once

#include <memory>

#include <ast/ast_node.hpp>
#include <ast/identifier.hpp>

class Type : public ASTNode {
public:
    Type(int first_line, int first_column);
};

using TypePtr = std::shared_ptr<Type>;

class IntType : public Type {
public:
    IntType(int first_line, int first_column);
    void Accept(Visitor& visitor) const override;
};

class BoolType : public Type {
public:
    BoolType(int first_line, int first_column);
    void Accept(Visitor& visitor) const override;
};

class IntArrayType : public Type {
public:
    IntArrayType(int first_line, int first_column);
    void Accept(Visitor& visitor) const override;
};

class IdentifierType : public Type {
public:
    IdentifierType(int first_line, int first_column, IdentifierPtr class_name);
    void Accept(Visitor& visitor) const override;
    const IdentifierPtr& GetClassName() const;

private:
    IdentifierPtr class_name_;
};
