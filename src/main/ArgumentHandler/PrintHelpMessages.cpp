#include<string>
#include<iostream>

#include"NetworkTools.hpp"
#include"PrintHelpMessages.hpp"
#include"ArgumentHandler.hpp"




std::string Indents(uint32_t count) {
    return std::string(count, '\t');
}



void PrintAllHelpMessages() {
    PrintNetworkList(0);
    PrintRTVarParamList(0);
    PrintCtrlFlagParamList(0);
}









void PrintRTVarParamList(int indentCount) {
    std::cout << Indents(indentCount+0) << "RTVarParamList: {\n";

    for (auto const &  RTVarParam : ArgumentHandler::RTVar::Param::list) {
        ArgumentHandler::RTVar::Param::ListItem const &  rtvarItem = RTVarParam.second;
        std::cout 
            << Indents(indentCount+1) << rtvarItem.name << '=' << rtvarItem.acceptableValue << '\n'
            << Indents(indentCount+2) << rtvarItem.description << '\n';
    }

    std::cout << Indents(indentCount+0) << "}\n\n\n";
}



void PrintCtrlFlagParamList(int indentCount) {
    std::cout << Indents(indentCount+0) << "CtrlFlagParamList: {\n";

    for (auto const &  CtrlFlagParam : ArgumentHandler::CtrlFlag::Param::list) {
        for (auto const &  cfParamName : CtrlFlagParam.nameList)
            std::cout << Indents(indentCount+1) << '-' << cfParamName;
        std::cout 
            << '=' << CtrlFlagParam.acceptableValue << '\n'
            << Indents(indentCount+2) << CtrlFlagParam.description << '\n';
    }

    std::cout << Indents(indentCount+0) << "}\n\n\n";
}