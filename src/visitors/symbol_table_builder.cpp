#include <visitors/symbol_table_builder.hpp>

SymbolTablePtr SymbolTableBuilder::Build(const Goal& goal) {
    Visit(goal);
    PrintErrors();
    return std::move(symbol_table_);
}

void SymbolTableBuilder::NoteError(const LocationPtr& location, EntityType entity_type,
                                   ErrorType error_type, std::string name = "") {
    std::string entity_descr;
    std::string error_descr;

    if (name.length()) {
        switch (entity_type) {
            case EntityType::METHOD:
                entity_descr = "method ";
                break;
            case EntityType::VARIABLE:
                entity_descr = "variable ";
                break;
            case EntityType::ENTITY_CLASS:
                entity_descr = "class ";
                break;
            case EntityType::ARGUMENT:
                entity_descr = "argument ";
                break;
            case EntityType::CALLING_METHOD:
                entity_descr = "calling a method ";
                break;
            case EntityType::NOTHING:
                entity_descr = "";
                break;
        }
    }

    switch (error_type) {
        case ErrorType::ALREADY_DECL:
            error_descr = " was already declared";
            break;
        case ErrorType::MISSED_DECL:
            error_descr = " wasn't declared";
            break;
        case ErrorType::WRONG_SIGN:
            error_descr = " returned type doesn't match function signature";
            break;
        case ErrorType::BOOL_REQUIR:
            error_descr = " bool type is required";
            break;
        case ErrorType::WRONG_TYPE_PRINT:
            error_descr = " wrong type for printing";
            break;
        case ErrorType::TYPE_MISMATCH:
            error_descr = " type mismatch while assigning";
            break;
        case ErrorType::NOT_EXIST:
            error_descr = " doesn't exist";
            break;
        case ErrorType::INT_ARRAY_REQUIR:
            error_descr = " int array type is required";
            break;
        case ErrorType::INT_REQUIR:
            error_descr = " int type is required";
            break;
        case ErrorType::FROM_PRIM_TYPE:
            error_descr = " from a primitive type";
            break;
    }

    errors_ << "Error at line: " << location->begin.line << " column: " << location->begin.column
            << ". Message: " << entity_descr << name << error_descr << ".\n";
}

void SymbolTableBuilder::Visit(const Goal& goal) {
    const auto& class_declarations = goal.GetClassDeclarations();
    for (const auto& class_decl : class_declarations) {
        const auto& class_name = class_decl->GetClassName()->GetName();
        if (symbol_table_->HasClass(class_name)) {
            NoteError(class_decl->GetLocation(), EntityType::ENTITY_CLASS, ErrorType::ALREADY_DECL,
                      class_name);
            continue;
        }
        auto new_class = symbol_table_->AddOrdinaryClass(class_decl);

        for (const auto& var : class_decl->GetVariables()) {
            const auto& var_name = var->GetVarName()->GetName();
            if (new_class->HasVariable(var_name)) {
                NoteError(var->GetLocation(), EntityType::VARIABLE, ErrorType::ALREADY_DECL,
                          var_name);
                continue;
            }
            new_class->AddVariableInfo(var);
        }

        for (const auto& method : class_decl->GetMethods()) {
            const auto& method_name = method->GetMethodName()->GetName();
            // TODO: Check here number and order of arguments in a method.
            if (new_class->HasMethod(method_name)) {
                NoteError(method->GetLocation(), EntityType::METHOD, ErrorType::ALREADY_DECL,
                          method_name);
                continue;
            }
            new_class->AddMethodInfo(method);
        }
    }

    const auto& main_class = goal.GetMainClass();
    if (const auto& main_class_name = main_class->GetClassName()->GetName();
        !symbol_table_->HasClass(main_class_name)) {
        symbol_table_->AddMainClass(main_class);
    } else {
        NoteError(main_class->GetLocation(), EntityType::ENTITY_CLASS, ErrorType::ALREADY_DECL,
                  main_class_name);
    }

    for (const auto& class_decl : class_declarations) {
        class_decl->Accept(*this);
    }

    main_class->Accept(*this);

    current_class_ = nullptr;
}

void SymbolTableBuilder::Visit(const MainClass& main_class) {
    current_class_ = symbol_table_->GetMainClass();
    main_class.GetBody()->Accept(*this);
    current_class_ = nullptr;
}

void SymbolTableBuilder::Visit(const ClassDeclaration& class_declaration) {
    const auto& class_name = class_declaration.GetClassName()->GetName();
    current_class_ = symbol_table_->GetOrdinaryClass(class_name);

    for (const auto& method : class_declaration.GetMethods()) {
        method->Accept(*this);
    }
    current_class_ = nullptr;
}

void SymbolTableBuilder::Visit(const MethodDeclaration& method_declaration) {
    const auto& method_name = method_declaration.GetMethodName()->GetName();
    current_method_ = current_class_->GetMethodInfo(method_name);

    for (const auto& arg : method_declaration.GetArgs()) {
        const auto& arg_name = arg->GetVarName()->GetName();
        if (current_method_->HasArg(arg_name)) {
            NoteError(method_declaration.GetLocation(), EntityType::ARGUMENT,
                      ErrorType::ALREADY_DECL, arg_name);
            continue;
        }
        current_method_->AddArgInfo(
            std::make_shared<VarInfo>(arg_name, arg->GetLocation(), arg->GetType()));
    }

    for (const auto& var : method_declaration.GetVariables()) {
        const auto& var_name = var->GetVarName()->GetName();
        if (current_method_->HasVariable(var_name)) {
            NoteError(var->GetLocation(), EntityType::VARIABLE, ErrorType::ALREADY_DECL, var_name);
            continue;
        }
        current_method_->AddVariableInfo(
            std::make_shared<VarInfo>(var_name, var->GetLocation(), var->GetType()));
    }

    const auto& method_return_type = current_method_->GetReturnType();
    for (const auto& stat : method_declaration.GetStatements()) {
        stat->Accept(*this);
    }

    method_declaration.GetReturnExpression()->Accept(*this);
    if (is_valid_expr_ && current_type_->GetInnerType() != method_return_type->GetInnerType()) {
        NoteError(method_return_type->GetLocation(), EntityType::NOTHING, ErrorType::WRONG_SIGN);
    }

    is_valid_expr_ = true;
    current_type_ = nullptr;
    current_method_ = nullptr;
}

void SymbolTableBuilder::Visit(const VarDeclaration& /* var_declaration */) {
    throw std::logic_error("You should not be here.");
}

void SymbolTableBuilder::Visit(const StatementList& statement_list) {
    for (const auto& stat : statement_list.GetStatements()) {
        stat->Accept(*this);
    }
}

void SymbolTableBuilder::Visit(const IfElseStatement& if_else_statement) {
    if_else_statement.GetClause()->Accept(*this);
    if (is_valid_expr_ && current_type_->GetInnerType() != InnerType::BOOL) {
        NoteError(if_else_statement.GetClause()->GetLocation(), EntityType::NOTHING,
                  ErrorType::BOOL_REQUIR);
    }
    is_valid_expr_ = true;
    current_type_ = nullptr;
    if_else_statement.GetIfBody()->Accept(*this);
    if_else_statement.GetElseBody()->Accept(*this);
}

void SymbolTableBuilder::Visit(const WhileStatement& while_statement) {
    while_statement.GetClause()->Accept(*this);
    if (is_valid_expr_ && current_type_->GetInnerType() != InnerType::BOOL) {
        NoteError(while_statement.GetLocation(), EntityType::NOTHING, ErrorType::BOOL_REQUIR);
    }
    is_valid_expr_ = true;
    current_type_ = nullptr;
    while_statement.GetBody()->Accept(*this);
}

void SymbolTableBuilder::Visit(const PrintStatement& print_statement) {
    print_statement.GetValue()->Accept(*this);
    if (is_valid_expr_ && current_type_->GetInnerType() != InnerType::INT) {
        NoteError(print_statement.GetValue()->GetLocation(), EntityType::NOTHING,
                  ErrorType::WRONG_TYPE_PRINT);
    }
}

void SymbolTableBuilder::Visit(const AssignmentStatement& assignment_statement) {
    assignment_statement.GetValue()->Accept(*this);

    const auto& name = assignment_statement.GetVariable()->GetName();
    if (current_method_->HasVariable(name)) {
        auto var = current_method_->GetVariableInfo(name);
        if (is_valid_expr_ && current_type_->GetInnerType() != var->GetType()->GetInnerType()) {
            NoteError(assignment_statement.GetValue()->GetLocation(), EntityType::NOTHING,
                      ErrorType::TYPE_MISMATCH);
        }
    } else if (current_method_->HasArg(name)) {
        auto arg = current_method_->GetArgInfo(name);
        if (is_valid_expr_ && current_type_->GetInnerType() != arg->GetType()->GetInnerType()) {
            NoteError(assignment_statement.GetValue()->GetLocation(), EntityType::NOTHING,
                      ErrorType::TYPE_MISMATCH);
        }
    } else if (current_class_->HasVariable(name)) {
        auto var = current_class_->GetVariableInfo(name);
        if (is_valid_expr_ && current_type_->GetInnerType() != var->GetType()->GetInnerType()) {
            NoteError(assignment_statement.GetValue()->GetLocation(), EntityType::NOTHING,
                      ErrorType::TYPE_MISMATCH);
        }
    } else if (current_class_->HasExtendsClass()) {
        const auto& extends_class =
            symbol_table_->GetOrdinaryClass(current_class_->GetExtendsName());
        if (extends_class->HasVariable(name)) {
            auto var = extends_class->GetVariableInfo(name);
            if (is_valid_expr_ && current_type_->GetInnerType() != var->GetType()->GetInnerType()) {
                NoteError(assignment_statement.GetValue()->GetLocation(), EntityType::NOTHING,
                          ErrorType::TYPE_MISMATCH);
            }
        }
    } else {
        NoteError(assignment_statement.GetVariable()->GetLocation(), EntityType::VARIABLE,
                  ErrorType::NOT_EXIST, name);
    }
    is_valid_expr_ = true;
    current_type_ = nullptr;
}

void SymbolTableBuilder::Visit(const ArrayAssignmentStatement& array_assignment_statement) {
    array_assignment_statement.GetSize()->Accept(*this);
    if (is_valid_expr_ && current_type_->GetInnerType() != InnerType::INT) {
        NoteError(array_assignment_statement.GetLocation(), EntityType::NOTHING,
                  ErrorType::INT_ARRAY_REQUIR);
    }
    is_valid_expr_ = true;
    current_type_ = nullptr;

    array_assignment_statement.GetValue()->Accept(*this);
    if (is_valid_expr_ && current_type_->GetInnerType() != InnerType::INT) {
        NoteError(array_assignment_statement.GetValue()->GetLocation(), EntityType::NOTHING,
                  ErrorType::INT_REQUIR);
    }
    is_valid_expr_ = true;
    current_type_ = nullptr;

    const auto& name = array_assignment_statement.GetVariable()->GetName();
    if (!current_method_->HasVariable(name) && !current_class_->HasVariable(name)) {
        NoteError(array_assignment_statement.GetVariable()->GetLocation(), EntityType::VARIABLE,
                  ErrorType::NOT_EXIST, name);
    }
}

void SymbolTableBuilder::Visit(const AndExpression& and_expression) {
    and_expression.GetLhs()->Accept(*this);
    if (current_type_->GetInnerType() != InnerType::BOOL) {
        is_valid_expr_ = false;
        NoteError(and_expression.GetLhs()->GetLocation(), EntityType::NOTHING,
                  ErrorType::INT_REQUIR);
    }
    current_type_ = nullptr;

    and_expression.GetRhs()->Accept(*this);
    if (current_type_->GetInnerType() != InnerType::BOOL) {
        is_valid_expr_ = false;
        NoteError(and_expression.GetRhs()->GetLocation(), EntityType::NOTHING,
                  ErrorType::INT_REQUIR);
    }
    current_type_ = std::make_shared<BoolType>(and_expression.GetLocation());
}

void SymbolTableBuilder::Visit(const LessExpression& less_expression) {
    less_expression.GetLhs()->Accept(*this);
    if (current_type_->GetInnerType() != InnerType::INT) {
        is_valid_expr_ = false;
        NoteError(less_expression.GetLhs()->GetLocation(), EntityType::NOTHING,
                  ErrorType::INT_REQUIR);
    }
    current_type_ = nullptr;

    less_expression.GetRhs()->Accept(*this);
    if (current_type_->GetInnerType() != InnerType::INT) {
        is_valid_expr_ = false;
        NoteError(less_expression.GetRhs()->GetLocation(), EntityType::NOTHING,
                  ErrorType::INT_REQUIR);
    }
    current_type_ = std::make_shared<BoolType>(less_expression.GetLocation());
}

void SymbolTableBuilder::Visit(const AddExpression& add_expression) {
    add_expression.GetLhs()->Accept(*this);
    if (current_type_->GetInnerType() != InnerType::INT) {
        is_valid_expr_ = false;
        NoteError(add_expression.GetLhs()->GetLocation(), EntityType::NOTHING,
                  ErrorType::INT_REQUIR);
    }
    current_type_ = nullptr;

    add_expression.GetRhs()->Accept(*this);
    if (current_type_->GetInnerType() != InnerType::INT) {
        is_valid_expr_ = false;
        NoteError(add_expression.GetRhs()->GetLocation(), EntityType::NOTHING,
                  ErrorType::INT_REQUIR);
    }
    current_type_ = std::make_shared<IntType>(add_expression.GetLocation());
}

void SymbolTableBuilder::Visit(const SubtractExpression& subtract_expression) {
    subtract_expression.GetLhs()->Accept(*this);
    if (current_type_->GetInnerType() != InnerType::INT) {
        is_valid_expr_ = false;
        NoteError(subtract_expression.GetLhs()->GetLocation(), EntityType::NOTHING,
                  ErrorType::INT_REQUIR);
    }
    current_type_ = nullptr;

    subtract_expression.GetRhs()->Accept(*this);
    if (current_type_->GetInnerType() != InnerType::INT) {
        is_valid_expr_ = false;
        NoteError(subtract_expression.GetRhs()->GetLocation(), EntityType::NOTHING,
                  ErrorType::INT_REQUIR);
    }
    current_type_ = std::make_shared<IntType>(subtract_expression.GetLocation());
}

void SymbolTableBuilder::Visit(const MultiplyExpression& multiply_expression) {
    multiply_expression.GetLhs()->Accept(*this);
    if (current_type_->GetInnerType() != InnerType::INT) {
        is_valid_expr_ = false;
        NoteError(multiply_expression.GetLhs()->GetLocation(), EntityType::NOTHING,
                  ErrorType::INT_REQUIR);
    }
    current_type_ = nullptr;

    multiply_expression.GetRhs()->Accept(*this);
    if (current_type_->GetInnerType() != InnerType::INT) {
        is_valid_expr_ = false;
        NoteError(multiply_expression.GetRhs()->GetLocation(), EntityType::NOTHING,
                  ErrorType::INT_REQUIR);
    }
    current_type_ = std::make_shared<IntType>(multiply_expression.GetLocation());
}

void SymbolTableBuilder::Visit(const ArrayExpression& array_expression) {
    array_expression.GetArray()->Accept(*this);
    if (current_type_->GetInnerType() != InnerType::INT_ARRAY) {
        is_valid_expr_ = false;
        NoteError(array_expression.GetArray()->GetLocation(), EntityType::NOTHING,
                  ErrorType::INT_ARRAY_REQUIR);
    }
    current_type_ = nullptr;

    array_expression.GetIdx()->Accept(*this);
    if (current_type_->GetInnerType() != InnerType::INT) {
        is_valid_expr_ = false;
        NoteError(array_expression.GetIdx()->GetLocation(), EntityType::NOTHING,
                  ErrorType::INT_REQUIR);
    }
    current_type_ = std::make_shared<IntType>(array_expression.GetLocation());
}

void SymbolTableBuilder::Visit(const LengthExpression& length_expression) {
    length_expression.GetContainer()->Accept(*this);
    if (current_type_->GetInnerType() != InnerType::INT_ARRAY) {
        is_valid_expr_ = false;
        NoteError(length_expression.GetContainer()->GetLocation(), EntityType::NOTHING,
                  ErrorType::INT_ARRAY_REQUIR);
    }
    current_type_ = std::make_shared<IntType>(length_expression.GetLocation());
}

void SymbolTableBuilder::Visit(const MethodCallExpression& method_call_expression) {
    method_call_expression.GetClassEntity()->Accept(*this);
    const auto& method_name = method_call_expression.GetMethodName()->GetName();
    if (!current_type_ || current_type_->GetInnerType() == InnerType::INT ||
        current_type_->GetInnerType() == InnerType::INT_ARRAY ||
        current_type_->GetInnerType() == InnerType::BOOL) {
        is_valid_expr_ = false;
        NoteError(method_call_expression.GetClassEntity()->GetLocation(),
                  EntityType::CALLING_METHOD, ErrorType::FROM_PRIM_TYPE, method_name);
        return;
    }

    const auto& calling_class =
        symbol_table_->GetOrdinaryClass(current_type_->GetClassName()->GetName());
    if (!calling_class->HasMethod(method_name)) {
        is_valid_expr_ = false;
        NoteError(method_call_expression.GetMethodName()->GetLocation(), EntityType::METHOD,
                  ErrorType::NOT_EXIST, method_name);
        return;
    }

    current_type_ = calling_class->GetMethodInfo(method_name)->GetReturnType();
}

void SymbolTableBuilder::Visit(const IntExpression& int_expression) {
    current_type_ = std::make_shared<IntType>(int_expression.GetLocation());
}

void SymbolTableBuilder::Visit(const BoolExpression& bool_expression) {
    current_type_ = std::make_shared<BoolType>(bool_expression.GetLocation());
}

void SymbolTableBuilder::Visit(const IdentifierExpression& identifier_expression) {
    identifier_expression.GetVariableName()->Accept(*this);
}

void SymbolTableBuilder::Visit(const ThisExpression& /* this_expression */) {
    current_type_ = std::make_shared<ClassType>(
        current_class_->GetLocation(),
        std::make_shared<Identifier>(current_class_->GetLocation(),
                                     std::string(current_class_->GetName())));
}

void SymbolTableBuilder::Visit(const NewIntArrayExpression& new_int_array_expression) {
    new_int_array_expression.GetSize()->Accept(*this);
    if (current_type_->GetInnerType() != InnerType::INT) {
        is_valid_expr_ = false;
        NoteError(new_int_array_expression.GetLocation(), EntityType::NOTHING,
                  ErrorType::INT_REQUIR);
    }
    current_type_ = std::make_shared<IntArrayType>(nullptr);
}

void SymbolTableBuilder::Visit(const NewExpression& new_expression) {
    new_expression.GetClassName()->Accept(*this);
    if (current_type_->GetInnerType() != InnerType::CUSTOM_CLASS) {
        is_valid_expr_ = false;
    }
}

void SymbolTableBuilder::Visit(const NotExpression& not_expression) {
    not_expression.GetExpression()->Accept(*this);
    if (current_type_->GetInnerType() != InnerType::BOOL) {
        is_valid_expr_ = false;
        NoteError(not_expression.GetExpression()->GetLocation(), EntityType::NOTHING,
                  ErrorType::BOOL_REQUIR);
    }
    current_type_ = std::make_shared<BoolType>(not_expression.GetLocation());
}

void SymbolTableBuilder::Visit(const Identifier& identifier) {
    const auto& name = identifier.GetName();
    if (current_class_->HasVariable(name)) {
        auto var = current_class_->GetVariableInfo(name);
        current_type_ = var->GetType();
    } else if (current_method_ && current_method_->HasVariable(name)) {
        auto var = current_method_->GetVariableInfo(name);
        current_type_ = var->GetType();
    } else if (current_method_ && current_method_->HasArg(name)) {
        auto var = current_method_->GetArgInfo(name);
        current_type_ = var->GetType();
    } else if (symbol_table_->HasClass(name)) {
        auto cl = symbol_table_->GetOrdinaryClass(name);
        current_type_ = std::make_shared<ClassType>(
            cl->GetLocation(),
            std::make_shared<Identifier>(cl->GetLocation(), std::string(cl->GetName())));
        current_class_ = cl;
    } else if (current_class_->HasExtendsClass()) {
        const auto& extends_class =
            symbol_table_->GetOrdinaryClass(current_class_->GetExtendsName());
        if (extends_class->HasVariable(name)) {
            auto var = extends_class->GetVariableInfo(name);
            current_type_ = var->GetType();
        }
    } else {
        is_valid_expr_ = false;
        NoteError(identifier.GetLocation(), EntityType::VARIABLE, ErrorType::MISSED_DECL,
                  identifier.GetName());
    }
}

void SymbolTableBuilder::PrintErrors() const {
    std::string errors = errors_.str();
    std::cerr << errors;
    //    for (const auto& [cl_name, cl] : symbol_table_->GetClasses()) {
    //        std::cerr << "class " << cl_name << "\n";
    //        for (const auto& [m_name, m] : cl->GetMethodInfoStorage()) {
    //            std::cerr << "method " << m_name << " "
    //                      << static_cast<size_t>(m->GetReturnType()->GetInnerType()) << "\n";
    //            for (const auto& [arg_name, arg] : m->GetArgInfoStorage()) {
    //                std::cerr << "arg " << arg_name << " "
    //                          << static_cast<size_t>(arg->GetType()->GetInnerType()) << "\n";
    //            }
    //            for (const auto& [var_name, var] : m->GetVarInfoStorage()) {
    //                std::cerr << "var " << var_name << " "
    //                          << static_cast<size_t>(var->GetType()->GetInnerType()) << "\n";
    //            }
    //        }
    //    }

    if (!errors.empty()) {
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
