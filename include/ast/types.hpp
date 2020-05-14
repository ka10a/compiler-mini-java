#pragma once

#include <memory>

#include <ast/ast_node.hpp>
#include <ast/identifier.hpp>

class Type : public ASTNode {
public:
    Type(LocationPtr location);
};

using TypePtr = std::shared_ptr<Type>;

class IntType : public Type {
public:
    IntType(LocationPtr location);
    void Accept(Visitor& visitor) const override;
};

class BoolType : public Type {
public:
    BoolType(LocationPtr location);
    void Accept(Visitor& visitor) const override;
};

class IntArrayType : public Type {
public:
    IntArrayType(LocationPtr location);
    void Accept(Visitor& visitor) const override;
};

class ClassType : public Type {
public:
    ClassType(LocationPtr location, IdentifierPtr class_name);
    void Accept(Visitor& visitor) const override;
    const IdentifierPtr& GetClassName() const;

private:
    IdentifierPtr class_name_;
};
