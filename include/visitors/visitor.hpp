#pragma once

#include <class_declaration.hpp>
#include <expressions.hpp>
#include <goal.hpp>
#include <identifier.hpp>
#include <main_class.hpp>
#include <method_declaration.hpp>
#include <statements.hpp>
#include <types.hpp>
#include <var_declaration.hpp>

class Visitor {
public:
    virtual void Visit(const Goal&) const = 0;
    virtual void Visit(const MainClass&) const = 0;
    virtual void Visit(const ClassDeclaration&) const = 0;
    virtual void Visit(const MethodDeclaration&) const = 0;
    virtual void Visit(const VarDeclaration&) const = 0;

    virtual void Visit(const IntType&) const = 0;
    virtual void Visit(const BoolType&) const = 0;
    virtual void Visit(const IntArrayType&) const = 0;
    virtual void Visit(const IdentifierType&) const = 0;

    virtual void Visit(const StatementList&) const = 0;
    virtual void Visit(const IfElseStatement&) const = 0;
    virtual void Visit(const WhileStatement&) const = 0;
    virtual void Visit(const PrintStatement&) const = 0;
    virtual void Visit(const AssignmentStatement&) const = 0;
    virtual void Visit(const ArrayAssignmentStatement&) const = 0;

    virtual void Visit(const AndExpression&) const = 0;
    virtual void Visit(const LessExpression&) const = 0;
    virtual void Visit(const AddExpression&) const = 0;
    virtual void Visit(const SubtractExpression&) const = 0;
    virtual void Visit(const MultiplicateExpression&) const = 0;

    virtual void Visit(const ArrayExpression&) const = 0;
    virtual void Visit(const LengthExpression&) const = 0;
    virtual void Visit(const MethodCallExpression&) const = 0;

    virtual void Visit(const IntExpression&) const = 0;
    virtual void Visit(const BoolExpression&) const = 0;
    virtual void Visit(const IdentifierExpression&) const = 0;

    virtual void Visit(const ThisExpression&) const = 0;
    virtual void Visit(const NewIntArrayExpression&) const = 0;
    virtual void Visit(const NewExpression&) const = 0;

    virtual void Visit(const NotExpression&) const = 0;
    virtual void Visit(const BetweenBracketsExpression&) const = 0;

    virtual void Visit(const Identifier&) const = 0;
};