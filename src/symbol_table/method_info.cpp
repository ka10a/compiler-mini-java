#include <symbol_table/method_info.hpp>

MethodInfo::MethodInfo(std::string_view name, LocationPtr location, TypePtr return_type)
    : EntityInfo(name, std::move(location)), return_type_(std::move(return_type)) {
}

const TypePtr& MethodInfo::GetReturnType() const {
    return return_type_;
}

const VarInfoPtr& MethodInfo::GetArgInfo(std::string_view arg_name) const {
    return args_.at(arg_name);
}

const VarInfoPtr& MethodInfo::GetVariableInfo(std::string_view variable_name) const {
    return variables_.at(variable_name);
}

bool MethodInfo::HasArg(std::string_view arg_name) const {
    return args_.find(arg_name) != args_.end();
}

bool MethodInfo::HasVariable(std::string_view variable_name) const {
    return variables_.find(variable_name) != variables_.end();
}

MethodInfo& MethodInfo::AddArgInfo(const VarDeclarationPtr& arg) {
    args_[arg->GetVarName()->GetName()] =
        std::make_shared<VarInfo>(arg->GetVarName()->GetName(), arg->GetLocation(), arg->GetType());
    return *this;
}

MethodInfo& MethodInfo::AddVariableInfo(const VarDeclarationPtr& variable) {
    variables_[variable->GetVarName()->GetName()] = std::make_shared<VarInfo>(
        variable->GetVarName()->GetName(), variable->GetLocation(), variable->GetType());
    return *this;
}
