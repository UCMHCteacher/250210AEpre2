#pragma once

#include<filesystem>
#include<map>
#include<mutex>
#include"StreamGenerator.hpp"



namespace Summary {
    extern bool needed;
    extern std::filesystem::path outputPath;
    extern std::filesystem::path terminateSymbol;


    extern void Entry();

    extern void Printer();


    struct EfficiencyRecord {
        uint32_t  _streamNum;
        std::size_t  _streamSize;
        uint32_t  _chunkCount;
        std::chrono::duration<double, std::milli> _duration;
    };
    extern std::vector<EfficiencyRecord> efficiencyData;
    extern std::mutex efficiencyDataMutex;

    using FileID_t = uint32_t;
    using FileTime_t = uint32_t;
    extern std::map<FileID_t,FileTime_t> correctnessData;
    extern std::mutex correctnessDataMutex;
}