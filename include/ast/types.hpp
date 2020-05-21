#pragma once

#include <memory>

#include <ast/ast_node.hpp>
#include <ast/identifier.hpp>

enum class InnerType {NONE, INT, BOOL, INT_ARRAY, CLASS};

class Type : public ASTNode {
public:
    Type(LocationPtr location);
    virtual InnerType GetInnerType() const = 0;
    virtual const IdentifierPtr& GetClassName() const;
};

using TypePtr = std::shared_ptr<Type>;

class IntType : public Type {
public:
    IntType(LocationPtr location);
    void Accept(Visitor& visitor) const override;
    InnerType GetInnerType () const override;

};

class BoolType : public Type {
public:
    BoolType(LocationPtr location);
    void Accept(Visitor& visitor) const override;
    InnerType GetInnerType () const override;
};

class IntArrayType : public Type {
public:
    IntArrayType(LocationPtr location);
    void Accept(Visitor& visitor) const override;
    InnerType GetInnerType () const override;
};

class ClassType : public Type {
public:
    ClassType(LocationPtr location, IdentifierPtr class_name);
    void Accept(Visitor& visitor) const override;
    const IdentifierPtr& GetClassName() const override;
    InnerType GetInnerType () const override;

private:
    IdentifierPtr class_name_;
};
