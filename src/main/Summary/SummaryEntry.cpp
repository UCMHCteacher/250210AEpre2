#include<filesystem>

#include"Summary.hpp"
#include"ToolChain.hpp"








void 
Summary::Entry() {
    if (!needed)
        return;

    using namespace ToolChain::Builder;
    if (SourceType::Network == sourceType && !std::filesystem::exists(terminateSymbol))
        return;

    Printer();
}