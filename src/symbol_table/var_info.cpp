#include <symbol_table/var_info.hpp>

VarInfo::VarInfo(std::string_view name, LocationPtr location, TypePtr type)
    : EntityInfo(name, std::move(location)), type_(std::move(type)) {
}

const TypePtr& VarInfo::GetType() const {
    return type_;
}
