#pragma once

#include <ast/class_declaration.hpp>
#include <ast/expressions.hpp>
#include <ast/goal.hpp>
#include <ast/identifier.hpp>
#include <ast/main_class.hpp>
#include <ast/method_declaration.hpp>
#include <ast/statements.hpp>
#include <ast/types.hpp>
#include <ast/var_declaration.hpp>

class Visitor {
public:
    virtual void Visit(const Goal&) = 0;
    virtual void Visit(const MainClass&) = 0;
    virtual void Visit(const ClassDeclaration&) = 0;
    virtual void Visit(const MethodDeclaration&) = 0;
    virtual void Visit(const VarDeclaration&) = 0;

    virtual void Visit(const IntType&) = 0;
    virtual void Visit(const BoolType&) = 0;
    virtual void Visit(const IntArrayType&) = 0;
    virtual void Visit(const IdentifierType&) = 0;

    virtual void Visit(const StatementList&) = 0;
    virtual void Visit(const IfElseStatement&) = 0;
    virtual void Visit(const WhileStatement&) = 0;
    virtual void Visit(const PrintStatement&) = 0;
    virtual void Visit(const AssignmentStatement&) = 0;
    virtual void Visit(const ArrayAssignmentStatement&) = 0;

    virtual void Visit(const AndExpression&) = 0;
    virtual void Visit(const LessExpression&) = 0;
    virtual void Visit(const AddExpression&) = 0;
    virtual void Visit(const SubtractExpression&) = 0;
    virtual void Visit(const MultiplicateExpression&) = 0;

    virtual void Visit(const ArrayExpression&) = 0;
    virtual void Visit(const LengthExpression&) = 0;
    virtual void Visit(const MethodCallExpression&) = 0;

    virtual void Visit(const IntExpression&) = 0;
    virtual void Visit(const BoolExpression&) = 0;
    virtual void Visit(const IdentifierExpression&) = 0;

    virtual void Visit(const ThisExpression&) = 0;
    virtual void Visit(const NewIntArrayExpression&) = 0;
    virtual void Visit(const NewExpression&) = 0;

    virtual void Visit(const NotExpression&) = 0;
    virtual void Visit(const BetweenBracketsExpression&) = 0;

    virtual void Visit(const Identifier&) = 0;
};