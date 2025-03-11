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






void PrintNetworkList(int indentCount) {
    std::cout << Indents(indentCount) << "NetworkList: {\n";
    
    
    for (int i = 0; i < networkList.size(); i++) {
        std::cout 
            << Indents(indentCount+1) << "Network" << i << ": {\n"
            << Indents(indentCount+2) << "Network Address: \"" << inet_ntoa(networkList[i].networkAddr) << "\"\n"
            << Indents(indentCount+2) << "Network Mask: \"" << inet_ntoa(networkList[i].networkMask) << "\"\n"
            << Indents(indentCount+2) << "Device IP Address: \"" << inet_ntoa(networkList[i].deviceIPAddr) << "\"\n"
            << Indents(indentCount+2) << "Device MAC Address: \"" << macAddrtoString(networkList[i].deviceMACAddr) << "\"\n"
            << Indents(indentCount+2) << "Device Name: \"" << networkList[i].deviceName << "\"\n"
            << Indents(indentCount+2) << "Device Description: \"" << networkList[i].deviceDescription << "\"\n"
            << Indents(indentCount+1) << "},\n";
    }

    std::cout << Indents(indentCount) << "}\n";
	std::cout << Indents(indentCount) << "There are " << networkList.size() << " networks in total.\n\n\n";
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