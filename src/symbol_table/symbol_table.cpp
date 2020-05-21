#include <symbol_table/symbol_table.hpp>

ClassInfoPtr& SymbolTable::GetOrdinaryClass(std::string_view class_name) {
    return classes_[class_name];
}

const ClassInfoPtr& SymbolTable::GetOrdinaryClass(std::string_view class_name) const {
    return classes_.at(class_name);
}

const ClassInfoPtr& SymbolTable::GetMainClass() const {
    return main_class_;
}

const ClassInfoStorage& SymbolTable::GetClasses() const {
    return classes_;
}

bool SymbolTable::HasClass(std::string_view class_name) const {
    return classes_.find(class_name) != classes_.end();
}

ClassInfoPtr SymbolTable::AddMainClass(const MainClassPtr& main_class) {
    std::string_view class_name = main_class->GetClassName()->GetName();
    main_class_ = std::make_shared<ClassInfo>(class_name, main_class->GetLocation());
    return main_class_;
}

ClassInfoPtr SymbolTable::AddOrdinaryClass(const ClassDeclarationPtr& class_decl) {
    std::string_view class_name = class_decl->GetClassName()->GetName();
    classes_[class_name] =
        class_decl->GetExtendsClassName()
            ? std::make_shared<ClassInfo>(class_name, class_decl->GetLocation(),
                                          class_decl->GetExtendsClassName()->GetName())
            : std::make_shared<ClassInfo>(class_name, class_decl->GetLocation());
    return classes_[class_name];
}
