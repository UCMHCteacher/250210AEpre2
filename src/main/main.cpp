#include"ArgumentHandler.hpp"
#include"ToolChain.hpp"


int main(int argc, char * argv[]) {
    ArgumentHandler::WholeProcess(argc, argv);
    ToolChainBuilder();
    return 0;
}