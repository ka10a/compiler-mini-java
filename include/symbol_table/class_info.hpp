#pragma once

#include <memory>
#include <optional>
#include <string_view>
#include <unordered_map>

#include <ast/method_declaration.hpp>
#include <ast/var_declaration.hpp>
#include <symbol_table/entity_info.hpp>
#include <symbol_table/method_info.hpp>
#include <symbol_table/var_info.hpp>

class ClassInfo;
using ClassInfoPtr = std::shared_ptr<ClassInfo>;
using ClassInfoStorage = std::unordered_map<std::string_view, ClassInfoPtr>;

class ClassInfo : public EntityInfo {
public:
    ClassInfo(std::string_view name, LocationPtr location,
              std::optional<std::string_view> extends_name = std::nullopt);

    std::string_view GetExtendsName() const;
    const VarInfoPtr& GetVariableInfo(std::string_view variable_name) const;
    MethodInfoPtr& GetMethodInfo(std::string_view method_name);
    const MethodInfoPtr& GetMethodInfo(std::string_view method_name) const;

    bool HasExtendsClass() const;
    bool HasVariable(std::string_view variable_name) const;
    bool HasMethod(std::string_view method_name) const;

    ClassInfo& AddVariableInfo(const VarDeclarationPtr& variable);
    ClassInfo& AddMethodInfo(const MethodDeclarationPtr& method);

private:
    std::optional<std::string_view> extends_name_;
    VarInfoStorage variables_;
    MethodInfoStorage methods_;
};
