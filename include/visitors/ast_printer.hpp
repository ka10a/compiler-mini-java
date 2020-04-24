#pragma once

#include <fstream>

#include <visitor.hpp>

class ASTPrinter : public Visitor {
public:
    explicit ASTPrinter(const std::string& filename);

    void Visit(const Goal& goal) override;
    void Visit(const MainClass& main_class) override;
    void Visit(const ClassDeclaration& class_declaration) override;
    void Visit(const MethodDeclaration& method_declaration) override;
    void Visit(const VarDeclaration& var_declaration) override;

    void Visit(const IntType& int_type) override;
    void Visit(const BoolType& bool_type) override;
    void Visit(const IntArrayType& int_array_type) override;
    void Visit(const IdentifierType& identifier_type) override;

    void Visit(const StatementList& statement_list) override;
    void Visit(const IfElseStatement& if_else_statement) override;
    void Visit(const WhileStatement& while_statement) override;
    void Visit(const PrintStatement& print_statement) override;
    void Visit(const AssignmentStatement& assignment_statement) override;
    void Visit(const ArrayAssignmentStatement& array_assignment_statement) override;

    void Visit(const AndExpression& and_expression) override;
    void Visit(const LessExpression& less_expression) override;
    void Visit(const AddExpression& add_expression) override;
    void Visit(const SubtractExpression& subtract_expression) override;
    void Visit(const MultiplicateExpression& multiplicate_expression) override;

    void Visit(const ArrayExpression& array_expression) override;
    void Visit(const LengthExpression& length_expression) override;
    void Visit(const MethodCallExpression& method_call_expression) override;

    void Visit(const IntExpression& int_expression) override;
    void Visit(const BoolExpression& bool_expression) override;
    void Visit(const IdentifierExpression& identifier_expression) override;

    void Visit(const ThisExpression& this_expression) override;
    void Visit(const NewIntArrayExpression& new_int_array_expression) override;
    void Visit(const NewExpression& new_expression) override;

    void Visit(const NotExpression& not_expression) override;
    void Visit(const BetweenBracketsExpression& between_brackets_expression) override;

    void Visit(const Identifier& identifier) override;

private:
    std::ofstream out_;
};
