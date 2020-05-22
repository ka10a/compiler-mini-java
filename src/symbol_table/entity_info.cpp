#include <symbol_table/entity_info.hpp>

EntityInfo::EntityInfo(std::string_view name, LocationPtr location)
    : name_(name), location_(std::move(location)) {
}

std::string_view EntityInfo::GetName() const {
    return name_;
}

const LocationPtr& EntityInfo::GetLocation() const {
    return location_;
}
