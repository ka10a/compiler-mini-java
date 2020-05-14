#pragma once

#include <memory>
#include <string_view>
#include <unordered_map>

#include <ast/types.hpp>
#include <ast/var_declaration.hpp>
#include <symbol_table/var_info.hpp>

class MethodInfo : public EntityInfo {
public:
    MethodInfo(std::string_view name, LocationPtr location, TypePtr return_type);

    const TypePtr& GetReturnType() const;
    const VarInfoPtr& GetArgInfo(std::string_view arg_name) const;
    const VarInfoPtr& GetVariableInfo(std::string_view variable_name) const;

    bool HasArg(std::string_view arg_name) const;
    bool HasVariable(std::string_view variable_name) const;

    MethodInfo& AddArgInfo(const VarDeclarationPtr& arg);
    MethodInfo& AddVariableInfo(const VarDeclarationPtr& variable);

private:
    TypePtr return_type_;
    VarInfoStorage args_;
    VarInfoStorage variables_;
};

using MethodInfoPtr = std::shared_ptr<MethodInfo>;
using MethodInfoStorage = std::unordered_map<std::string_view, MethodInfoPtr>;
