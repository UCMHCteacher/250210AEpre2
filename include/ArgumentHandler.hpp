#pragma once

#include<string>
#include<map>
#include<cstdint>
#include<vector>
#include<fstream>










namespace ArgumentHandler {

    inline namespace Utils {
        extern std::hash<std::string> ArgStringHash;
        using ParamNameHash = uint64_t;



        using SetValueFunction = void (*)(std::string &);
        using PrintValueFunction = void (*)();
    } // namespace Utils




    namespace RuntimeVariable {

        extern void HandlingProcess(std::string &);



        namespace Parameter {
            extern void Register(
                std::string name,
                SetValueFunction setValue,
                std::string acceptableValue,
                std::string description
            );

            inline namespace Organization {
                struct ListItem {
                    std::string name;
                    SetValueFunction setValue;
                    std::string acceptableValue;
                    std::string description;
                };

                extern std::map<ParamNameHash,ListItem> list;
            } // namespace Organization
        } // namespace Parameter
        namespace Param = Parameter;



    } // namespace RuntimeVariable
    namespace RTVar = RuntimeVariable;





    namespace ControlFlag {

        extern bool willPrintHelpMsg;

        enum class ArgErrorAction {
            NOTHING,
            OUTPUT,
            EXIT
        };
        extern ArgErrorAction argErrorAction;

        enum class ArgChangeAction {
            NOTHING,
            OUTPUT
        };
        extern ArgChangeAction argChangeAction;

        extern std::ifstream fileStream;

        extern bool willEnterConsole;



        namespace Parameter {
            extern void ListInit();
            extern void Register(
                std::vector<std::string> nameList,
                SetValueFunction setValue,
                std::string acceptableValue,
                std::string description
            );

            inline namespace Organization {
                struct ListItem {
                    std::vector<std::string> nameList;
                    SetValueFunction setValue;
                    std::string acceptableValue;
                    std::string description;
                };

                using ListPos = int;
                extern std::vector<ListItem> list;
                extern std::map<ParamNameHash,ListPos> lookupList;
            } // namespace Organization
        } // namespace Parameter
        namespace Param = Parameter;



    } // namespace ControlFlag
    namespace CtrlFlag = ControlFlag;





    extern void Parse(int argc, char * argv[]);
} // namespace ArgumentHandler