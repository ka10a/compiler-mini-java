#pragma once

#include <string_view>
#include <memory>

#include <ast/ast_node.hpp>

class EntityInfo {
public:
    EntityInfo(std::string_view name, LocationPtr location);
    std::string_view GetName() const;
    const LocationPtr& GetLocation() const;

private:
    std::string_view name_;
    LocationPtr location_;
};
