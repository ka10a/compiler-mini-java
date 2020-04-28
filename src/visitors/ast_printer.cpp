#include <visitors/ast_printer.hpp>

ASTPrinter::ASTPrinter(const std::string& filename) : out_(filename), node_number_(0) {
}

void ASTPrinter::PrintEdge(size_t curr, size_t node_number) {
    out_ << curr << " -- " << node_number << ";\n";
}

void ASTPrinter::Visit(const Goal& goal) {
    out_ << "graph Grammar{\n";

    size_t curr = node_number_;
    out_ << curr << " [label=\"Goal\"] [color=blue];\n";

    node_number_++;
    PrintEdge(curr, node_number_);
    goal.GetMainClass()->Accept(*this);

    for (const auto& class_decl : goal.GetClassDeclarations()) {
        // TODO: check that class_decl isn't a nullptr and throw logic_exception if it is not (in
        // every function)

        node_number_++;
        PrintEdge(curr, node_number_);
        class_decl->Accept(*this);
    }

    out_ << "}";
}

void ASTPrinter::Visit(const MainClass& main_class) {
    size_t curr = node_number_;
    node_number_++;
    PrintEdge(curr, node_number_);

    node_number_++;
    PrintEdge(curr, node_number_);
    main_class.GetArgsName()->Accept(*this);

    node_number_++;
    PrintEdge(curr, node_number_);
    main_class.GetBody()->Accept(*this);
}

void ASTPrinter::Visit(const ClassDeclaration& class_declaration) {
    size_t curr = node_number_;
    out_ << curr << " [label=\"ClassDeclaration\"];\n";

    node_number_++;
    PrintEdge(curr, node_number_);
    class_declaration.GetClassName()->Accept(*this);

    if (const auto& ext_class_name = class_declaration.GetExtendsClassName(); ext_class_name) {
        node_number_++;
        PrintEdge(curr, node_number_);
        ext_class_name->Accept(*this);
    }

    for (const auto& var : class_declaration.GetVariables()) {
        node_number_++;
        PrintEdge(curr, node_number_);
        var->Accept(*this);
    }

    for (const auto& method : class_declaration.GetMethods()) {
        node_number_++;
        PrintEdge(curr, node_number_);
        method->Accept(*this);
    }
}

void ASTPrinter::Visit(const MethodDeclaration& method_declaration) {
    size_t curr = node_number_;
    out_ << curr << " [label=\"MethodDeclaration\"];\n";

    node_number_++;
    PrintEdge(curr, node_number_);
    method_declaration.GetReturnType()->Accept(*this);

    node_number_++;
    PrintEdge(curr, node_number_);
    method_declaration.GetName()->Accept(*this);

    const auto& args = method_declaration.GetArgs();
    size_t idx = 0;
    for (const auto& arg : args) {
        node_number_++;
        PrintEdge(curr, node_number_);

        size_t argNumber = node_number_;
        out_ << argNumber << " [label=\"Argument\"];\n";
        node_number_++;
        PrintEdge(argNumber, node_number_);
        arg->GetType()->Accept(*this);

        node_number_++;
        PrintEdge(argNumber, node_number_);
        arg->GetName()->Accept(*this);

        if (idx + 1 < args.size()) {
            out_ << ", ";
        }
        idx++;
    }

    for (const auto& var : method_declaration.GetVariables()) {
        node_number_++;
        PrintEdge(curr, node_number_);
        var->Accept(*this);
    }

    for (const auto& statement : method_declaration.GetStatements()) {
        node_number_++;
        PrintEdge(curr, node_number_);
        statement->Accept(*this);
    }

    node_number_++;
    PrintEdge(curr, node_number_);
    out_ << node_number_ << " [label=\"Return\"];\n";

    node_number_++;
    PrintEdge(node_number_ - 1, node_number_);
    method_declaration.GetReturnExpression()->Accept(*this);
}

void ASTPrinter::Visit(const VarDeclaration& var_declaration) {
    size_t curr = node_number_;
    out_ << curr << " [label=\"VarDeclaration\"];\n";

    node_number_++;
    PrintEdge(curr, node_number_);
    var_declaration.GetType()->Accept(*this);

    node_number_++;
    PrintEdge(curr, node_number_);
    var_declaration.GetName()->Accept(*this);
}

void ASTPrinter::Visit(const IntType& /* int_type */) {
    size_t curr = node_number_;
    out_ << curr << " [label=\"IntType\"];\n";

    node_number_++;
    out_ << node_number_ << " [label=\"int\"];\n";
    PrintEdge(curr, node_number_);
}

void ASTPrinter::Visit(const BoolType& /* bool_type */) {
    size_t curr = node_number_;
    out_ << curr << " [label=\"BoolType\"];\n";

    node_number_++;
    out_ << node_number_ << " [label=\"boolean\"];\n";
    PrintEdge(curr, node_number_);
}

void ASTPrinter::Visit(const IntArrayType& /* int_array_type */) {
    size_t curr = node_number_;
    out_ << curr << " [label=\"IntArrayType\"];\n";

    node_number_++;
    out_ << node_number_ << " [label=\"int[]\"];\n";
    PrintEdge(curr, node_number_);
}

void ASTPrinter::Visit(const IdentifierType& identifier_type) {
    size_t curr = node_number_;
    out_ << curr << " [label=\"IdentifierType\"];\n";

    node_number_++;
    PrintEdge(curr, node_number_);
    identifier_type.GetClassName()->Accept(*this);
}

void ASTPrinter::Visit(const StatementList& statement_list) {
    size_t curr = node_number_;
    out_ << curr << "%d [label=\"StatementList\"];\n";

    for (const auto& statement : statement_list.GetStatements()) {
        node_number_++;
        PrintEdge(curr, node_number_);
        statement->Accept(*this);
    }
}

void ASTPrinter::Visit(const IfElseStatement& if_else_statement) {
    size_t curr = node_number_;
    out_ << curr << " [label=\"IfElseStatement\"];\n";
    node_number_++;
    PrintEdge(curr, node_number_);
    if_else_statement.GetClause()->Accept(*this);

    node_number_++;
    PrintEdge(curr, node_number_);
    if_else_statement.GetIfBody()->Accept(*this);

    node_number_++;
    PrintEdge(curr, node_number_);
    if_else_statement.GetElseBody()->Accept(*this);
}

void ASTPrinter::Visit(const WhileStatement& while_statement) {
    size_t curr = node_number_;
    out_ << curr << " [label=\"WhileStatement\"];\n";

    node_number_++;
    PrintEdge(curr, node_number_);
    while_statement.GetClause()->Accept(*this);

    node_number_++;
    PrintEdge(curr, node_number_);
    while_statement.GetBody()->Accept(*this);
}

void ASTPrinter::Visit(const PrintStatement& print_statement) {
    size_t curr = node_number_;
    out_ << curr << " [label=\"PrintStatement\"];\n";

    node_number_++;
    PrintEdge(curr, node_number_);
    print_statement.GetValue()->Accept(*this);
}

void ASTPrinter::Visit(const AssignmentStatement& assignment_statement) {
    size_t curr = node_number_;
    out_ << curr << " [label=\"AssignmentStatement\"];\n";

    node_number_++;
    PrintEdge(curr, node_number_);
    assignment_statement.GetVariable()->Accept(*this);

    node_number_++;
    PrintEdge(curr, node_number_);
    assignment_statement.GetValue()->Accept(*this);
}

void ASTPrinter::Visit(const ArrayAssignmentStatement& array_assignment_statement) {
    size_t curr = node_number_;
    out_ << curr << " [label=\"ArrayAssignmentStatement\"];\n";

    node_number_++;
    PrintEdge(curr, node_number_);
    array_assignment_statement.GetVariable()->Accept(*this);

    node_number_++;
    PrintEdge(curr, node_number_);
    array_assignment_statement.GetSize()->Accept(*this);

    node_number_++;
    PrintEdge(curr, node_number_);
    array_assignment_statement.GetValue()->Accept(*this);
}

void ASTPrinter::Visit(const AndExpression& and_expression) {
    size_t curr = node_number_;
    out_ << curr << " [label=\"AndExpression\"];\n";

    node_number_++;
    PrintEdge(curr, node_number_);
    and_expression.GetLhs()->Accept(*this);

    node_number_++;
    PrintEdge(curr, node_number_);
    and_expression.GetRhs()->Accept(*this);
}

void ASTPrinter::Visit(const LessExpression& less_expression) {
    size_t curr = node_number_;
    out_ << curr << " [label=\"LessExpression\"];\n";

    node_number_++;
    PrintEdge(curr, node_number_);
    less_expression.GetLhs()->Accept(*this);

    node_number_++;
    PrintEdge(curr, node_number_);
    less_expression.GetRhs()->Accept(*this);
}

void ASTPrinter::Visit(const AddExpression& add_expression) {
    size_t curr = node_number_;
    out_ << curr << " [label=\"AddExpression\"];\n";

    node_number_++;
    PrintEdge(curr, node_number_);
    add_expression.GetLhs()->Accept(*this);

    node_number_++;
    PrintEdge(curr, node_number_);
    add_expression.GetRhs()->Accept(*this);
}

void ASTPrinter::Visit(const SubtractExpression& subtract_expression) {
    size_t curr = node_number_;
    out_ << curr << " [label=\"SubtractExpression\"];\n";

    node_number_++;
    PrintEdge(curr, node_number_);
    subtract_expression.GetLhs()->Accept(*this);

    node_number_++;
    PrintEdge(curr, node_number_);
    subtract_expression.GetRhs()->Accept(*this);
}

void ASTPrinter::Visit(const MultiplicateExpression& multiplicate_expression) {
    size_t curr = node_number_;
    out_ << curr << " [label=\"MultiplicateExpression\"];\n";

    node_number_++;
    PrintEdge(curr, node_number_);
    multiplicate_expression.GetLhs()->Accept(*this);

    node_number_++;
    PrintEdge(curr, node_number_);
    multiplicate_expression.GetRhs()->Accept(*this);
}

void ASTPrinter::Visit(const ArrayExpression& array_expression) {
    size_t curr = node_number_;
    out_ << curr << " [label=\"ArrayExpression\"];\n";

    node_number_++;
    PrintEdge(curr, node_number_);
    array_expression.GetArray()->Accept(*this);

    node_number_++;
    PrintEdge(curr, node_number_);
    array_expression.GetIdx()->Accept(*this);
}

void ASTPrinter::Visit(const LengthExpression& length_expression) {
    size_t curr = node_number_;
    out_ << curr << " [label=\"LengthExpression\"];\n";

    node_number_++;
    PrintEdge(curr, node_number_);
    length_expression.GetContainer()->Accept(*this);
}

void ASTPrinter::Visit(const MethodCallExpression& method_call_expression) {
    size_t curr = node_number_;
    out_ << curr << " [label=\"MethodCallExpression\"];\n";

    node_number_++;
    PrintEdge(curr, node_number_);
    method_call_expression.GetClassEntity()->Accept(*this);

    node_number_++;
    PrintEdge(curr, node_number_);
    method_call_expression.GetMethodName()->Accept(*this);

    const auto& params = method_call_expression.GetParams();
    size_t idx = 0;
    for (const auto& param : params) {
        node_number_++;
        PrintEdge(curr, node_number_);
        param->Accept(*this);

        if (idx + 1 < params.size()) {
            out_ << ", ";
        }
        idx++;
    }
}

void ASTPrinter::Visit(const IntExpression& int_expression) {
    size_t curr = node_number_;
    out_ << curr << " [label=\"IntegerExpression\"];\n";

    node_number_++;
    PrintEdge(curr, node_number_);
    out_ << node_number_ << " [label=\"" << int_expression.GetValue() << "\"];\n";
}

void ASTPrinter::Visit(const BoolExpression& bool_expression) {
    size_t curr = node_number_;
    out_ << curr << " [label=\"BoolExpression\"];\n";

    node_number_++;
    PrintEdge(curr, node_number_);
    out_ << node_number_ << " [label=\"" << (bool_expression.IsValue() ? "true" : "false")
         << "\"];\n";
}

void ASTPrinter::Visit(const IdentifierExpression& identifier_expression) {
    size_t curr = node_number_;
    out_ << curr << " [label=\"IdentifierExpression\"];\n";

    node_number_++;
    PrintEdge(curr, node_number_);
    identifier_expression.GetVariableName()->Accept(*this);
}

void ASTPrinter::Visit(const ThisExpression& /* this_expression */) {
    size_t curr = node_number_;
    out_ << curr << " [label=\"ThisExpression\"];\n";

    node_number_++;
    PrintEdge(curr, node_number_);
    out_ << node_number_ << " [label=\"this\"];\n";
}

void ASTPrinter::Visit(const NewIntArrayExpression& new_int_array_expression) {
    size_t curr = node_number_;
    out_ << curr << " [label=\"NewArrExpression\"];\n";

    node_number_++;
    PrintEdge(curr, node_number_);
    new_int_array_expression.GetSize()->Accept(*this);
}

void ASTPrinter::Visit(const NewExpression& new_expression) {
    size_t curr = node_number_;
    out_ << curr << " [label=\"NewExpression\"];\n";

    node_number_++;
    PrintEdge(curr, node_number_);
    new_expression.GetClassName()->Accept(*this);
}

void ASTPrinter::Visit(const NotExpression& not_expression) {
    size_t curr = node_number_;
    out_ << curr << " [label=\"NotExpression\"];\n";

    node_number_++;
    PrintEdge(curr, node_number_);
    not_expression.GetExpression()->Accept(*this);
}

void ASTPrinter::Visit(const BetweenBracketsExpression& between_brackets_expression) {
    size_t curr = node_number_;
    out_ << curr << " [label=\"BetweenBracketsExpression\"];\n";

    node_number_++;
    PrintEdge(curr, node_number_);
    between_brackets_expression.GetExpression()->Accept(*this);
}

void ASTPrinter::Visit(const Identifier& identifier) {
    out_ << node_number_ << " [label=\"" << identifier.GetName() << "\"];\n";
}