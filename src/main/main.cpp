#include"ArgumentHandler.hpp"
#include"ToolChain.hpp"
#include"BootSequence.hpp"


int main(int argc, char * argv[]) {
    BootSequence();
    ArgumentHandler::WholeProcess(argc, argv);
    ToolChain::Builder::Start();
    ToolChain::StartProcess();
    return 0;
}