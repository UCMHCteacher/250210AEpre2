#pragma once

#include<filesystem>




namespace Summary {
    extern bool needed;
    extern std::filesystem::path outputPath;
    extern std::filesystem::path terminateSymbol;


    extern void Entry();

    extern void Printer();
}