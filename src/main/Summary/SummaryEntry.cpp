#include<filesystem>

#include"Summary.hpp"








void 
Summary::Entry() {
    if (!needed)
        return;

    if (!std::filesystem::exists(terminateSymbol))
        return;

    Printer();
}