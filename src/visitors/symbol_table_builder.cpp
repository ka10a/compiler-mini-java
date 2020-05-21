#include <visitors/symbol_table_builder.hpp>

SymbolTableBuilder::SymbolTableBuilder()
    : symbol_table_(std::make_shared<SymbolTable>())
    , current_class_(nullptr)
    , current_method_(nullptr)
    , current_var_(nullptr)
    , current_type_(InnerType::NONE)
    , is_valid_expr_(true) {
}

SymbolTablePtr SymbolTableBuilder::Build(const Goal& goal) {
    Visit(goal);
    PrintErrors();
    return std::move(symbol_table_);
}

void SymbolTableBuilder::Visit(const Goal& goal) {
    for (const auto& class_decl : goal.GetClassDeclarations()) {
        class_decl->Accept(*this);
    }
    goal.GetMainClass()->Accept(*this);

    for (const auto& class_decl : goal.GetClassDeclarations()) {
        const auto& name = class_decl->GetClassName()->GetName();
        current_class_ = symbol_table_->GetOrdinaryClass(name);
        for (const auto& [cl_name, cl] : symbol_table_->GetClasses()) {
            if (cl && cl->HasExtendsClass() && cl->GetExtendsName() == current_class_->GetName()) {
                for (const auto& [var_name, var] : cl->GetVarInfoStorage()) {
                    if (current_class_->HasVariable(var->GetName())) {
                        errors_ << "Error at line: " << var->GetLocation()->begin.line
                                << " column: " << var->GetLocation()->begin.column
                                << ". Message: variable " << var_name << " already was declared.\n";
                    }
                }

                for (const auto& [met_name, met] : cl->GetMethodInfoStorage()) {
                    if (current_class_->HasMethod(met->GetName())) {
                        const auto& method = current_class_->GetMethodInfo(met->GetName());
                        if (method->GetReturnType() != met->GetReturnType() ||
                            method->GetArgInfoStorageSize() != met->GetArgInfoStorageSize()) {
                            errors_ << "Error at line: " << met->GetLocation()->begin.line
                                    << " column: " << met->GetLocation()->begin.column
                                    << ". Message: method " << met_name
                                    << " already was declared.\n";
                        } else {
                            for (auto arg1 = method->GetArgInfoStorage().begin(),
                                      arg2 = met->GetArgInfoStorage().begin();
                                 arg1 != method->GetArgInfoStorage().end(); arg1++, arg2++) {
                                if (arg1->second->GetType() != arg2->second->GetType()) {
                                    errors_ << "Error at line: " << met->GetLocation()->begin.line
                                            << " column: " << met->GetLocation()->begin.column
                                            << ". Message: method " << met_name
                                            << " already was declared.\n";
                                    break;
                                }
                            }
                        }
                    }

                    for (const auto& [arg_name, arg] : met->GetArgInfoStorage()) {
                        const auto& class_val = arg->GetType();
                        if (class_val->GetInnerType() == InnerType::CLASS &&
                            !symbol_table_->HasClass(class_val->GetClassName()->GetName())) {
                            errors_ << "Error at line: " << arg->GetLocation()->begin.line
                                    << " column: " << arg->GetLocation()->begin.column
                                    << ". Message: type of argument " << arg_name
                                    << " was not declared yet.\n";
                        }
                    }

                    auto class_val = met->GetReturnType();
                    if (met->GetReturnType()->GetInnerType() == InnerType::CLASS &&
                        !symbol_table_->HasClass(met->GetReturnType()->GetClassName()->GetName())) {
                        errors_ << "Error at line: " << met->GetLocation()->begin.line
                                << " column: " << met->GetLocation()->begin.column
                                << ". Message: type of method " << met_name
                                << " was not declared yet.\n";
                    }
                }
            }
        }
    }

    current_class_ = nullptr;
}

void SymbolTableBuilder::Visit(const MainClass& main_class) {
    const auto& name = main_class.GetClassName()->GetName();
    current_class_ = std::make_shared<ClassInfo>(name, main_class.GetLocation());

    if (symbol_table_->HasClass(current_class_->GetName())) {
        errors_ << "Error at line: " << main_class.GetLocation()->begin.line
                << " column: " << main_class.GetLocation()->begin.column << ". Message: class "
                << name << " was already declared.\n";
    }

    symbol_table_->AddMainClass(current_class_);
    main_class.GetBody()->Accept(*this);

    current_class_ = nullptr;
}

void SymbolTableBuilder::Visit(const ClassDeclaration& class_declaration) {
    const auto& name = class_declaration.GetClassName()->GetName();
    current_class_ =
        class_declaration.GetExtendsClassName()
            ? std::make_shared<ClassInfo>(name, class_declaration.GetLocation(),
                                          class_declaration.GetExtendsClassName()->GetName())
            : std::make_shared<ClassInfo>(name, class_declaration.GetLocation());

    if (symbol_table_->HasClass(current_class_->GetName())) {
        errors_ << "Error at line: " << class_declaration.GetLocation()->begin.line
                << " column: " << class_declaration.GetLocation()->begin.column
                << ". Message: class " << name << " was already declared.\n";
    }

    symbol_table_->AddOrdinaryClass(current_class_);

    for (const auto& var_declaration : class_declaration.GetVariables()) {
        var_declaration->Accept(*this);
    }

    for (const auto& method_declaration : class_declaration.GetMethods()) {
        method_declaration->Accept(*this);
    }

    current_class_ = nullptr;
}

void SymbolTableBuilder::Visit(const MethodDeclaration& method_declaration) {
    const auto& name = method_declaration.GetMethodName()->GetName();
    current_method_ = std::make_shared<MethodInfo>(name, method_declaration.GetLocation(),
                                                   method_declaration.GetReturnType());

    for (const auto& var : method_declaration.GetVariables()) {
        var->Accept(*this);
    }

    for (const auto& arg : method_declaration.GetArgs()) {
        current_var_ = std::make_shared<VarInfo>(arg->GetVarName()->GetName(), arg->GetLocation(),
                                                 arg->GetType());

        if (current_method_->HasArg(current_var_->GetName())) {
            errors_ << "Error at line: " << method_declaration.GetLocation()->begin.line
                    << " column: " << method_declaration.GetLocation()->begin.column
                    << ". Message: argument " << arg->GetVarName() << " was already declared.\n";
        }
        current_method_->AddArgInfo(current_var_);
    }

    if (current_class_->HasMethod(current_method_->GetName())) {
        auto method = current_class_->GetMethodInfo(current_method_->GetName());
        if (method->GetArgInfoStorageSize() != current_method_->GetArgInfoStorageSize()) {
            errors_ << "Error at line: " << method_declaration.GetLocation()->begin.line
                    << " column: " << method_declaration.GetLocation()->begin.column
                    << ". Message: method " << name << " was called with wrong number of args.\n";
        } else {
            for (auto arg1 = method->GetArgInfoStorage().begin(),
                      arg2 = current_method_->GetArgInfoStorage().begin();
                 arg1 != method->GetArgInfoStorage().end(); arg1++, arg2++) {
                if (arg1->second->GetType() != arg2->second->GetType()) {
                    errors_ << "Error at line: " << method_declaration.GetLocation()->begin.line
                            << " column: " << method_declaration.GetLocation()->begin.column
                            << ". Message: method " << name
                            << " doesn't match function signature.\n";
                    break;
                }
            }
        }
    }

    current_class_->AddMethodInfo(current_method_);

    for (const auto& stat : method_declaration.GetStatements()) {
        stat->Accept(*this);
    }

    method_declaration.GetReturnExpression()->Accept(*this);

    if (is_valid_expr_ && current_type_ != current_method_->GetReturnType()->GetInnerType()) {
        errors_ << "Error at line: "
                << method_declaration.GetReturnType()->GetLocation()->begin.line
                << " column: " << method_declaration.GetReturnType()->GetLocation()->begin.column
                << ". Message: returned type doesn't match function signature.\n";
    }

    is_valid_expr_ = true;
    current_type_ = InnerType::NONE;
    current_method_ = nullptr;
}

void SymbolTableBuilder::Visit(const VarDeclaration& var_declaration) {
    const auto& name = var_declaration.GetVarName()->GetName();
    current_var_ =
        std::make_shared<VarInfo>(name, var_declaration.GetLocation(), var_declaration.GetType());

    if (current_method_) {
        if (current_method_->HasVariable(current_var_->GetName())) {
            errors_ << "Error at line: " << var_declaration.GetLocation()->begin.line
                    << " column: " << var_declaration.GetLocation()->begin.column
                    << ". Message: variable " << name << " was already declared as local var.\n";
        }
        current_method_->AddVariableInfo(current_var_);
    } else {
        if (current_class_->HasVariable(current_var_->GetName())) {
            errors_ << "Error at line: " << var_declaration.GetLocation()->begin.line
                    << " column: " << var_declaration.GetLocation()->begin.column
                    << ". Message: variable " << name << " was already declared as class field.\n";
        }
        current_class_->AddVariableInfo(current_var_);
    }
    current_var_ = nullptr;
}

void SymbolTableBuilder::Visit(const StatementList& statement_list) {
    for (const auto& stat : statement_list.GetStatements()) {
        stat->Accept(*this);
    }
}

void SymbolTableBuilder::Visit(const IfElseStatement& if_else_statement) {
    if_else_statement.GetClause()->Accept(*this);
    if (is_valid_expr_ && current_type_ != InnerType::BOOL) {
        errors_ << "Error at line: " << if_else_statement.GetClause()->GetLocation()->begin.line
                << " column: " << if_else_statement.GetClause()->GetLocation()->begin.column
                << ". Message: bool type is required.\n";
    }
    is_valid_expr_ = true;
    current_type_ = InnerType::NONE;
    if_else_statement.GetIfBody()->Accept(*this);
    if_else_statement.GetElseBody()->Accept(*this);
}

void SymbolTableBuilder::Visit(const WhileStatement& while_statement) {
    while_statement.GetClause()->Accept(*this);
    if (is_valid_expr_ && current_type_ != InnerType::BOOL) {
        errors_ << "Error at line: " << while_statement.GetClause()->GetLocation()->begin.line
                << " column: " << while_statement.GetClause()->GetLocation()->begin.column
                << ". Message: bool type is required.\n";
    }
    is_valid_expr_ = true;
    current_type_ = InnerType::NONE;
    while_statement.GetBody()->Accept(*this);
}

void SymbolTableBuilder::Visit(const PrintStatement& print_statement) {
    print_statement.GetValue()->Accept(*this);
    if (is_valid_expr_ && current_type_ != InnerType::INT) {
        errors_ << "Error at line: " << print_statement.GetValue()->GetLocation()->begin.line
                << " column: " << print_statement.GetValue()->GetLocation()->begin.column
                << ". Message: wrong type for printing.\n";
    }
}

void SymbolTableBuilder::Visit(const AssignmentStatement& assignment_statement) {
    assignment_statement.GetValue()->Accept(*this);

    const auto& name = assignment_statement.GetVariable()->GetName();
    if (current_method_->HasVariable(name)) {
        auto var = current_method_->GetVariableInfo(name);
        if (is_valid_expr_ && current_type_ != current_var_->GetType()->GetInnerType()) {
            errors_ << "Error at line: "
                    << assignment_statement.GetValue()->GetLocation()->begin.line
                    << " column: " << assignment_statement.GetValue()->GetLocation()->begin.column
                    << ". Message: type mismatch while assigning.\n";
        }
    } else if (current_class_->HasVariable(name)) {
        auto var = current_class_->GetVariableInfo(name);
        if (is_valid_expr_ && current_type_ != current_var_->GetType()->GetInnerType()) {
            errors_ << "Error at line: "
                    << assignment_statement.GetValue()->GetLocation()->begin.line
                    << " column: " << assignment_statement.GetValue()->GetLocation()->begin.column
                    << ". Message: type mismatch while assigning.\n";
        }
    } else {
        errors_ << "Error at line: " << assignment_statement.GetValue()->GetLocation()->begin.line
                << " column: " << assignment_statement.GetValue()->GetLocation()->begin.column
                << ". Message: variable " << name << " doesn't exist.\n";
    }
    is_valid_expr_ = true;
    current_type_ = InnerType::NONE;
}

void SymbolTableBuilder::Visit(const ArrayAssignmentStatement& array_assignment_statement) {
    array_assignment_statement.GetSize()->Accept(*this);
    if (is_valid_expr_ && current_type_ != InnerType::INT) {
        errors_ << "Error at line: " << array_assignment_statement.GetLocation()->begin.line
                << " column: " << array_assignment_statement.GetLocation()->begin.column
                << ". Message: int array type is required.\n";
    }
    is_valid_expr_ = true;
    current_type_ = InnerType::NONE;

    array_assignment_statement.GetValue()->Accept(*this);
    if (is_valid_expr_ && current_type_ != InnerType::INT) {
        errors_ << "Error at line: "
                << array_assignment_statement.GetValue()->GetLocation()->begin.line
                << " column: " << array_assignment_statement.GetValue()->GetLocation()->begin.column
                << ". Message: int type is required.\n";
    }
    is_valid_expr_ = true;
    current_type_ = InnerType::NONE;

    const auto& name = array_assignment_statement.GetVariable()->GetName();
    if (!current_method_->HasVariable(name) && !current_class_->HasVariable(name)) {
        errors_ << "Error at line: "
                << array_assignment_statement.GetVariable()->GetLocation()->begin.line
                << " column: "
                << array_assignment_statement.GetVariable()->GetLocation()->begin.column
                << ". Message: variable " << name << " doesn't exist.\n";
    }
}

void SymbolTableBuilder::Visit(const AndExpression& and_expression) {
    and_expression.GetLhs()->Accept(*this);
    if (current_type_ != InnerType::BOOL) {
        is_valid_expr_ = false;
        errors_ << "Error at line: " << and_expression.GetLhs()->GetLocation()->begin.line
                << " column: " << and_expression.GetLhs()->GetLocation()->begin.column
                << ". Message: int type is required.\n";
    }
    current_type_ = InnerType::NONE;

    and_expression.GetRhs()->Accept(*this);
    if (current_type_ != InnerType::BOOL) {
        is_valid_expr_ = false;
        errors_ << "Error at line: " << and_expression.GetRhs()->GetLocation()->begin.line
                << " column: " << and_expression.GetRhs()->GetLocation()->begin.column
                << ". Message: int type is required.\n";
    }
    current_type_ = InnerType::BOOL;
}

void SymbolTableBuilder::Visit(const LessExpression& less_expression) {
    less_expression.GetLhs()->Accept(*this);
    if (current_type_ != InnerType::INT) {
        is_valid_expr_ = false;
        errors_ << "Error at line: " << less_expression.GetLhs()->GetLocation()->begin.line
                << " column: " << less_expression.GetLhs()->GetLocation()->begin.column
                << ". Message: int type is required.\n";
    }
    current_type_ = InnerType::NONE;

    less_expression.GetRhs()->Accept(*this);
    if (current_type_ != InnerType::INT) {
        is_valid_expr_ = false;
        errors_ << "Error at line: " << less_expression.GetRhs()->GetLocation()->begin.line
                << " column: " << less_expression.GetRhs()->GetLocation()->begin.column
                << ". Message: int type is required.\n";
    }
    current_type_ = InnerType::BOOL;
}

void SymbolTableBuilder::Visit(const AddExpression& add_expression) {
    add_expression.GetLhs()->Accept(*this);
    if (current_type_ != InnerType::INT) {
        is_valid_expr_ = false;
        errors_ << "Error at line: " << add_expression.GetLhs()->GetLocation()->begin.line
                << " column: " << add_expression.GetLhs()->GetLocation()->begin.column
                << ". Message: int type is required.\n";
    }
    current_type_ = InnerType::NONE;

    add_expression.GetRhs()->Accept(*this);
    if (current_type_ != InnerType::INT) {
        is_valid_expr_ = false;
        errors_ << "Error at line: " << add_expression.GetRhs()->GetLocation()->begin.line
                << " column: " << add_expression.GetRhs()->GetLocation()->begin.column
                << ". Message: int type is required.\n";
    }
    current_type_ = InnerType::INT;
}

void SymbolTableBuilder::Visit(const SubtractExpression& subtract_expression) {
    subtract_expression.GetLhs()->Accept(*this);
    if (current_type_ != InnerType::INT) {
        is_valid_expr_ = false;
        errors_ << "Error at line: " << subtract_expression.GetLhs()->GetLocation()->begin.line
                << " column: " << subtract_expression.GetLhs()->GetLocation()->begin.column
                << ". Message: int type is required.\n";
    }
    current_type_ = InnerType::NONE;

    subtract_expression.GetRhs()->Accept(*this);
    if (current_type_ != InnerType::INT) {
        is_valid_expr_ = false;
        errors_ << "Error at line: " << subtract_expression.GetRhs()->GetLocation()->begin.line
                << " column: " << subtract_expression.GetRhs()->GetLocation()->begin.column
                << ". Message: int type is required.\n";
    }
    current_type_ = InnerType::INT;
}

void SymbolTableBuilder::Visit(const MultiplyExpression& multiply_expression) {
    multiply_expression.GetLhs()->Accept(*this);
    if (current_type_ != InnerType::INT) {
        is_valid_expr_ = false;
        errors_ << "Error at line: " << multiply_expression.GetLhs()->GetLocation()->begin.line
                << " column: " << multiply_expression.GetLhs()->GetLocation()->begin.column
                << ". Message: int type is required.\n";
    }
    current_type_ = InnerType::NONE;

    multiply_expression.GetRhs()->Accept(*this);
    if (current_type_ != InnerType::INT) {
        is_valid_expr_ = false;
        errors_ << "Error at line: " << multiply_expression.GetRhs()->GetLocation()->begin.line
                << " column: " << multiply_expression.GetRhs()->GetLocation()->begin.column
                << ". Message: int type is required.\n";
    }
    current_type_ = InnerType::INT;
}

void SymbolTableBuilder::Visit(const ArrayExpression& array_expression) {
    array_expression.GetArray()->Accept(*this);
    if (current_type_ != InnerType::INT_ARRAY) {
        is_valid_expr_ = false;
        errors_ << "Error at line: " << array_expression.GetArray()->GetLocation()->begin.line
                << " column: " << array_expression.GetArray()->GetLocation()->begin.column
                << ". Message: int array type is required.\n";
    }
    current_type_ = InnerType::NONE;

    array_expression.GetIdx()->Accept(*this);
    if (current_type_ != InnerType::INT) {
        is_valid_expr_ = false;
        errors_ << "Error at line: " << array_expression.GetIdx()->GetLocation()->begin.line
                << " column: " << array_expression.GetIdx()->GetLocation()->begin.column
                << ". Message: int type is required.\n";
    }
    current_type_ = InnerType::INT;
}

void SymbolTableBuilder::Visit(const LengthExpression& length_expression) {
    length_expression.GetContainer()->Accept(*this);
    if (current_type_ != InnerType::INT_ARRAY) {
        is_valid_expr_ = false;
        errors_ << "Error at line: " << length_expression.GetContainer()->GetLocation()->begin.line
                << " column: " << length_expression.GetContainer()->GetLocation()->begin.column
                << ". Message: int array type is required.\n";
    }
    current_type_ = InnerType::INT;
}

void SymbolTableBuilder::Visit(const MethodCallExpression& method_call_expression) {
    method_call_expression.GetClassEntity()->Accept(*this);
    const auto& name = method_call_expression.GetMethodName()->GetName();
    if (current_type_ == InnerType::INT || current_type_ == InnerType::NONE ||
        current_type_ == InnerType::INT_ARRAY || current_type_ == InnerType::BOOL) {
        is_valid_expr_ = false;
        errors_ << "Error at line: "
                << method_call_expression.GetClassEntity()->GetLocation()->begin.line << " column: "
                << method_call_expression.GetClassEntity()->GetLocation()->begin.column
                << ". Message: calling a method " << name << " from a primitive type.\n";
        return;
    }

    if (!current_class_->HasMethod(name)) {
        is_valid_expr_ = false;
        errors_ << "Error at line: "
                << method_call_expression.GetMethodName()->GetLocation()->begin.line << " column: "
                << method_call_expression.GetMethodName()->GetLocation()->begin.column
                << ". Message: method " << name << " doesn't exist.\n";
        return;
    }

    auto met = current_class_->GetMethodInfo(name);
    if (met->GetArgInfoStorageSize() != method_call_expression.GetParams().size()) {
        is_valid_expr_ = false;
        errors_ << "Error at line: " << method_call_expression.GetLocation()->begin.line
                << " column: " << method_call_expression.GetLocation()->begin.column
                << ". Message: method " << name << " was called with wrong number of args\n";
        return;
    }
    current_type_ = InnerType::CLASS;
}

void SymbolTableBuilder::Visit(const IntExpression& /* int_expression */) {
    current_type_ = InnerType::INT;
}

void SymbolTableBuilder::Visit(const BoolExpression& /* bool_expression */) {
    current_type_ = InnerType::BOOL;
}

void SymbolTableBuilder::Visit(const IdentifierExpression& identifier_expression) {
    identifier_expression.GetVariableName()->Accept(*this);
}

void SymbolTableBuilder::Visit(const ThisExpression& /* this_expression */) {
    current_type_ = InnerType::CLASS;
}

void SymbolTableBuilder::Visit(const NewIntArrayExpression& new_int_array_expression) {
    new_int_array_expression.GetSize()->Accept(*this);
    if (current_type_ != InnerType::INT) {
        is_valid_expr_ = false;
        errors_ << "Error at line: " << new_int_array_expression.GetLocation()->begin.line
                << " column: " << new_int_array_expression.GetLocation()->begin.column
                << ". Message: int type is required.\n";
    }
    current_type_ = InnerType::INT_ARRAY;
}

void SymbolTableBuilder::Visit(const NewExpression& new_expression) {
    new_expression.GetClassName()->Accept(*this);
    if (current_type_ != InnerType::CLASS) {
        is_valid_expr_ = false;
    }
}

void SymbolTableBuilder::Visit(const NotExpression& not_expression) {
    not_expression.GetExpression()->Accept(*this);
    if (current_type_ != InnerType::BOOL) {
        is_valid_expr_ = false;
        errors_ << "Error at line: " << not_expression.GetExpression()->GetLocation()->begin.line
                << " column: " << not_expression.GetExpression()->GetLocation()->begin.column
                << ". Message: boolean type is required.\n";
    }
    current_type_ = InnerType::BOOL;
}

void SymbolTableBuilder::Visit(const Identifier& identifier) {
    const auto& name = identifier.GetName();
    if (current_class_->HasVariable(name)) {
        auto var = current_class_->GetVariableInfo(name);
        current_type_ = var->GetType()->GetInnerType();
    } else if (current_method_ && current_method_->HasVariable(name)) {
        auto var = current_method_->GetVariableInfo(name);
        current_type_ = var->GetType()->GetInnerType();
    } else if (current_method_ && current_method_->HasArg(name)) {
        auto var = current_method_->GetArgInfo(name);
        current_type_ = var->GetType()->GetInnerType();
    } else if (symbol_table_->HasClass(name)) {
        auto cl = symbol_table_->GetOrdinaryClass(name);
        current_type_ = InnerType::CLASS;
        current_class_ = cl;
    } else {
        is_valid_expr_ = false;
        errors_ << "Error at line: " << identifier.GetLocation()->begin.line
                << " column: " << identifier.GetLocation()->begin.column << ". Message: name "
                << identifier.GetName() << " wasn't declared.\n";
    }
}

void SymbolTableBuilder::PrintErrors() const {
    std::cerr << errors_.str();
    for (const auto& [cl_name, cl] : symbol_table_->GetClasses()) {
        std::cerr << "class " << cl_name << "\n";
        for (const auto& [m_name, m] : cl->GetMethodInfoStorage()) {
            std::cerr << "method " << m_name << "\n";
            for (const auto& [arg_name, arg] : m->GetArgInfoStorage()) {
                std::cerr << "arg " << arg_name << "\n";
            }
            for (const auto& [var_name, var] : m->GetVarInfoStorage()) {
                std::cerr << "var " << var_name << "\n";
            }
        }
    }

    if (errors_) {
        throw std::logic_error("Errors found. You are so stupid, maaaaan.");
    }
}

void SymbolTableBuilder::Visit(const IntType& /* int_type */) {
    throw std::logic_error("You shouldn't be here.");
}

void SymbolTableBuilder::Visit(const BoolType& /* bool_type */) {
    throw std::logic_error("You shouldn't be here.");
}

void SymbolTableBuilder::Visit(const IntArrayType& /* int_array_type */) {
    throw std::logic_error("You shouldn't be here.");
}

void SymbolTableBuilder::Visit(const ClassType& /* class_type */) {
    throw std::logic_error("You shouldn't be here.");
}
