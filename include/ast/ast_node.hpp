#pragma once

class Visitor;

class ASTNode {
public:
    ASTNode(int first_line, int first_column);
    virtual void Accept(Visitor& visitor) const = 0;
    int GetFirstLine() const;
    int GetFirstColumn() const;

private:
    int first_line_;
    int first_column_;
};
