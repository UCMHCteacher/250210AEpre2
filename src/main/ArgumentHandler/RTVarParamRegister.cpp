#include<iostream>

#include"ArgumentHandler.hpp"





void
ArgumentHandler::RTVar::Param::Register(
    std::string name,
    SetValueFunction setValue,
    std::string acceptableValue,
    std::string description
) {
    auto emplaceResult = ArgumentHandler::RTVar::Param::list.try_emplace(
        ArgStringHash(name),
        ListItem({
            name,
            setValue,
            acceptableValue,
            description
        })
    );
    if (!emplaceResult.second) {
        std::cout << "Failed in inserting \"" << name << "\" into RTVar::Param::list.\n";
    };// TODO: More pretty info and error handle
}