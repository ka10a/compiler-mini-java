#pragma once

#include <memory>

#include <ast_node.hpp>
#include <identifier.hpp>

class Type : public ASTNode {};

using TypePtr = std::shared_ptr<Type>;

class IntType : public Type {
public:
    IntType() = default;
    void Accept(Visitor& visitor) const override;
};

class BoolType : public Type {
public:
    BoolType() = default;
    void Accept(Visitor& visitor) const override;
};

class IntArrayType : public Type {
public:
    IntArrayType() = default;
    void Accept(Visitor& visitor) const override;
};

class IdentifierType : public Type {
public:
    explicit IdentifierType(IdentifierPtr class_name);
    void Accept(Visitor& visitor) const override;
    const IdentifierPtr& GetClassName() const;

private:
    IdentifierPtr class_name_;
};
