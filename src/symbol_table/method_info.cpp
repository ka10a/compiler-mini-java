#include <symbol_table/method_info.hpp>

MethodInfo::MethodInfo(std::string_view name, LocationPtr location, TypePtr return_type)
    : EntityInfo(name, std::move(location)), return_type_(std::move(return_type)) {
}

// const TypePtr& MethodInfo::GetReturnType() const {
//    return return_type_;
//}

const TypePtr& MethodInfo::GetReturnType() const {
    return return_type_;
}

const VarInfoPtr& MethodInfo::GetArgInfo(std::string_view arg_name) const {
    return args_.at(arg_name);
}

const VarInfoPtr& MethodInfo::GetVariableInfo(std::string_view variable_name) const {
    return variables_.at(variable_name);
}

size_t MethodInfo::GetArgInfoStorageSize() const {
    return args_.size();
}

const VarInfoStorage& MethodInfo::GetArgInfoStorage() const {
    return args_;
}

const VarInfoStorage& MethodInfo::GetVarInfoStorage() const {
    return variables_;
}

bool MethodInfo::HasArg(std::string_view arg_name) const {
    return args_.find(arg_name) != args_.end();
}

bool MethodInfo::HasVariable(std::string_view variable_name) const {
    return variables_.find(variable_name) != variables_.end();
}

MethodInfo& MethodInfo::AddArgInfo(VarInfoPtr arg) {
    args_[arg->GetName()] = std::move(arg);
    return *this;
}

MethodInfo& MethodInfo::AddVariableInfo(VarInfoPtr variable) {
    variables_[variable->GetName()] = std::move(variable);
    return *this;
}
