#include<iostream>

#include"ArgumentHandler.hpp"





void 
ArgumentHandler::RTVar::HandlingProcess(std::string & arg) {
    std::size_t assignCharPos = arg.find_first_of('=');

    std::string paramStr = arg.substr(0, assignCharPos); // if pos of '=' is npos(aka -1), it still returns [1, size)
    std::string valueStr = 
        assignCharPos != std::string::npos ?
        arg.substr(assignCharPos + 1)  :  "";

    auto listFind = RTVar::Param::list.find(
        ArgStringHash(paramStr)
    );
    if (listFind == RTVar::Param::list.end()) {
        std::cout << "Param name \"" << paramStr << "\" Not Found!\n";
        if (CtrlFlag::argErrorAction == CtrlFlag::ArgErrorAction::OUTPUT) {
            return;
        }
        if (CtrlFlag::argErrorAction == CtrlFlag::ArgErrorAction::EXIT) {
            exit(0);
        }
    }// TODO: Prettier Message

    listFind->second.setValue(valueStr);
}