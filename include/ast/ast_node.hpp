#pragma once

#include <memory>

#include <location.hh>

using LocationPtr = std::shared_ptr<yy::location>;

class Visitor;

class ASTNode {
public:
    ASTNode(LocationPtr location);
    virtual void Accept(Visitor& visitor) const = 0;
    const LocationPtr& GetLocation() const;

private:
    LocationPtr location_;
};
