#include<string>
#include<vector>
#include<thread>
#include<iostream>

#include"ArgumentHandler.hpp"










void 
ArgumentHandler::WholeProcess(int _argc, char * _argv[]) {
    CtrlFlag::Param::ListInit();





    std::vector<std::string> argList;
    for (int argi=0; argi<_argc; argi++) {
        argList.emplace_back(_argv[argi]);
    }





    for (decltype(argList)::iterator argListIt = argList.begin(); argListIt != argList.end();) {



        /*  The format of ArgHandlingControlFlag argument:
                -<flag>=<assignValue>
            in which =<assignValue> is optional, depends on what <flag> is.
            The Procedure:
            1. hashes the <flag>
            2. use the hash value to get function setParam(string)
            3. call setParam(<assignValue>)
        */
        if ((*argListIt)[0] == '-') {
            std::size_t assignCharPos = argListIt->find_first_of('=');

            std::string paramStr = argListIt->substr(1, assignCharPos - 1); // if pos of '=' is npos(aka -1), it still returns [1, size)
            std::string valueStr = 
                assignCharPos != std::string::npos ?
                argListIt->substr(assignCharPos + 1)  :  "";

            argList.erase(argListIt);



            CtrlFlag::Param::ListPos listPos;

            // impl.1
            // try {
            //     listPos = 
            //         CtrlFlag::Param::lookupList.at(
            //             ArgStringHash(paramStr)
            //         );
            // }
            // catch(const std::out_of_range& e) {
            //     std::cout << "Param name \"" << paramStr << "\"Not Found!\n";
            //     continue;
            // }

            // impl.2
            auto lookupListFind = CtrlFlag::Param::lookupList.find(
                ArgStringHash(paramStr)
            );
            if (lookupListFind == CtrlFlag::Param::lookupList.end()) {
                std::cout << "Param name \"" << paramStr << "\"Not Found!\n";
                continue;
            }
            listPos = lookupListFind->second;

            CtrlFlag::Param::list[listPos].setValue(valueStr);
        }



        else {
            argListIt++;
        }
    }




    // if help

    // if file...

    for (auto &  argi : argList) {
        RTVar::HandlingProcess(argi);
    }

    // if console...
}