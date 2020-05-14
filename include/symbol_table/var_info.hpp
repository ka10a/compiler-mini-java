#pragma once

#include <memory>
#include <string_view>
#include <unordered_map>

#include <ast/types.hpp>
#include <symbol_table/entity_info.hpp>

class VarInfo : public EntityInfo {
public:
    VarInfo(std::string_view name, LocationPtr location, TypePtr type);

    const TypePtr& GetType() const;

private:
    TypePtr type_;
};

using VarInfoPtr = std::shared_ptr<VarInfo>;
using VarInfoStorage = std::unordered_map<std::string_view, VarInfoPtr>;
