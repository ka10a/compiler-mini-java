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

ClassInfo& ClassInfo::AddVariableInfo(VarInfoPtr variable) {
    variables_[variable->GetName()] = std::move(variable);
    return *this;
}

ClassInfo& ClassInfo::AddMethodInfo(MethodInfoPtr method) {
    methods_[method->GetName()] = std::move(method);
    return *this;
}

const VarInfoStorage& ClassInfo::GetVarInfoStorage() const{
    return variables_;
}

const MethodInfoStorage& ClassInfo::GetMethodInfoStorage() const{
    return methods_;
}
