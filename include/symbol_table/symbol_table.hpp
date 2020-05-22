#pragma once

#include <string_view>
#include <unordered_map>

#include <ast/class_declaration.hpp>
#include <ast/main_class.hpp>
#include <symbol_table/class_info.hpp>

class SymbolTable {
public:
    SymbolTable() = default;

    ClassInfoPtr& GetOrdinaryClass(std::string_view class_name);
    const ClassInfoPtr& GetOrdinaryClass(std::string_view class_name) const;
    const ClassInfoPtr& GetMainClass() const;

    const ClassInfoStorage& GetClasses() const;

    bool HasClass(std::string_view class_name) const;

    ClassInfoPtr AddMainClass(const MainClassPtr& main_class);
    ClassInfoPtr AddOrdinaryClass(const ClassDeclarationPtr& class_decl);

private:
    ClassInfoPtr main_class_;
    ClassInfoStorage classes_;
};

using SymbolTablePtr = std::shared_ptr<SymbolTable>;