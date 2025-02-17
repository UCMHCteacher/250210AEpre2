#pragma once

#include<cstdint>

#include"CDChunking.hpp"










namespace ToolChain {
    // extern streamGenerator
    extern CDChunking::Chunker *  chunker;
    // extern chunkProcessor





    namespace Builder {
        enum class SourceType {
            File,
            Network
        };
        extern SourceType sourceType;

        extern std::string sourceFileName;
        // extern NetworkRecord

        enum class ChunkerType {
            AE,
            MaxP
        };
        extern ChunkerType chunkerType;
        extern uint8_t chunkerIntervalLength;
        extern uint16_t chunkerWindowWidth;

        // infos for chunkProcessor
        // infos for intervalProcessor

        extern void Start();
    } // namespace Builder



    extern void StartProcess();
} // namespace ToolChain



