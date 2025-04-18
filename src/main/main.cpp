#include"ArgumentHandler.hpp"
#include"ToolChain.hpp"
#include"BootSequence.hpp"
#include"Summary.hpp"


int main(int argc, char * argv[]) {
    BootSequence();
    ArgumentHandler::Parse(argc, argv);
    ToolChain::Builder::Build();
    ToolChain::StartProcess();
    Summary::Entry();
    return 0;
}