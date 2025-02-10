#pragma once

#include<iostream>

#include"ArgumentHandler.hpp"





using namespace ArgumentHandler;



std::hash<std::string>
Utils::ArgStringHash = std::hash<std::string>{};

std::map<ParamNameHash,RTVar::Param::ListItem>
RTVar::Param::list{};



bool
CtrlFlag::willPrintHelpMsg = false;

CtrlFlag::ArgErrorAction
CtrlFlag::argErrorAction = CtrlFlag::ArgErrorAction::OUTPUT;

CtrlFlag::ArgChangeAction
CtrlFlag::argChangeAction = CtrlFlag::ArgChangeAction::NOTHING;

std::ifstream
CtrlFlag::fileStream;

bool
CtrlFlag::willEnterConsole = false;

std::vector<CtrlFlag::Param::ListItem>
CtrlFlag::Param::list{};

std::map<ParamNameHash,CtrlFlag::Param::ListPos>
CtrlFlag::Param::lookupList{};



void 
CtrlFlag::Param::Register(
    std::vector<std::string> nameList,
    SetValueFunction setValue,
    std::string acceptableValue,
    std::string description
) {
    ListPos listPos = list.size();

    for (auto &  name : nameList) {
        auto emplaceResult = CtrlFlag::Param::lookupList.try_emplace(
            ArgStringHash(name),
            listPos
        );
        if (!emplaceResult.second) {
            std::cout << "Failed in inserting \"" << name << "\" into CtrlFlag::Param::lookupList.\n";
        };
    }

    CtrlFlag::Param::list.emplace_back(
        std::move(nameList),
        setValue,
        std::move(acceptableValue),
        std::move(description)
    );
}



void
CtrlFlag::Param::ListInit() {

    // -help
    CtrlFlag::Param::Register(
        {"help","h"},
        [](std::string & valueStr){;},
        "",
        "Print help messages"
    );// TODO: help messages with hint word

    // -file=<string>
    CtrlFlag::Param::Register(
        {"file","f"},
        [](std::string & valueStr){
            fileStream.open(valueStr);
        },
        "<filename(string_with_no_spaces)>",
        "Opens the file"
    );

    // -console
    CtrlFlag::Param::Register(
        {"console","c"},
        [](std::string & valueStr){;},
        "",
        "Will enter console interface"
    );

    // -argErrorAction=<>
    CtrlFlag::Param::Register(
        {"argErrorAction"},
        [](std::string & valueStr){
            if (
                ArgStringHash(valueStr) ==
                ArgStringHash("NOTHING")
            ) {
                argErrorAction = ArgErrorAction::NOTHING;
            }
            else if (
                ArgStringHash(valueStr) ==
                ArgStringHash("OUTPUT")
            ) {
                argErrorAction = ArgErrorAction::OUTPUT;
            }
            else if (
                ArgStringHash(valueStr) ==
                ArgStringHash("EXIT")
            ) {
                argErrorAction = ArgErrorAction::EXIT;
            }

            else {
                std::cout << "There's no ArgErrorAction called " << valueStr << "\n";
            }
        },
        "<NOTHING|OUTPUT|EXIT>",
        "Directs what happens when there is an argument error."
    );

    // -argChangeAction=<>
    CtrlFlag::Param::Register(
        {"argChangeAction"},
        [](std::string & valueStr){
            if (
                ArgStringHash(valueStr) ==
                ArgStringHash("NOTHING")
            ) {
                argChangeAction = ArgChangeAction::NOTHING;
            }
            else if (
                ArgStringHash(valueStr) ==
                ArgStringHash("OUTPUT")
            ) {
                argChangeAction = ArgChangeAction::OUTPUT;
            }

            else {
                std::cout << "There's no ArgChangeAction called " << valueStr << "\n";
            }
        },
        "<NOTHING|OUTPUT>",
        "Directs what happens when there is an argument change."
    );

}