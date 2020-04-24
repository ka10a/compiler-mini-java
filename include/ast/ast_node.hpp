#pragma once

class Visitor;

class ASTNode {
public:
    virtual void Accept(Visitor& visitor) const = 0;
};