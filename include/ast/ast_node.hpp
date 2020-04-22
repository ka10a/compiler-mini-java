#pragma once

class Visitor;

class ASTNode {
public:
    virtual void Accept(const Visitor&) const = 0;
};