#include <symbol_table/class_info.hpp>

ClassInfo::ClassInfo(std::string_view name, LocationPtr location,
                     std::optional<std::string_view> extends_name)
    : EntityInfo(name, std::move(location)), extends_name_(extends_name) {
}

std::string_view ClassInfo::GetExtendsName() const {
    return *extends_name_;
}

const VarInfoPtr& ClassInfo::GetVariableInfo(std::string_view variable_name) const {
    return variables_.at(variable_name);
}

MethodInfoPtr& ClassInfo::GetMethodInfo(std::string_view method_name) {
    return methods_[method_name];
}

const MethodInfoPtr& ClassInfo::GetMethodInfo(std::string_view method_name) const {
    return methods_.at(method_name);
}

bool ClassInfo::HasExtendsClass() const {
    return extends_name_.has_value();
}

bool ClassInfo::HasVariable(std::string_view variable_name) const {
    return variables_.find(variable_name) != variables_.end();
}

bool ClassInfo::HasMethod(std::string_view method_name) const {
    return methods_.find(method_name) != methods_.end();
}

VarInfoPtr ClassInfo::AddVariableInfo(const VarDeclarationPtr& var) {
    std::string_view var_name = var->GetVarName()->GetName();
    variables_[var_name] = std::make_shared<VarInfo>(var_name, var->GetLocation(), var->GetType());
    return variables_[var_name];
}

MethodInfoPtr ClassInfo::AddMethodInfo(const MethodDeclarationPtr& method) {
    std::string_view method_name = method->GetMethodName()->GetName();
    methods_[method_name] =
        std::make_shared<MethodInfo>(method_name, method->GetLocation(), method->GetReturnType());
    return methods_[method_name];
}

const VarInfoStorage& ClassInfo::GetVarInfoStorage() const {
    return variables_;
}

const MethodInfoStorage& ClassInfo::GetMethodInfoStorage() const {
    return methods_;
}
