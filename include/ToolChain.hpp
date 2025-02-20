#pragma once

#include<cstdint>
#include<memory>

#include"StreamGenerator.hpp"
#include"CDChunking.hpp"










namespace ToolChain {
    extern std::unique_ptr<StreamGenerators::StreamGenerator> streamGenerator;
    extern std::unique_ptr<CDChunking::Chunker> chunker;
    // TODO: extern chunkProcessor





    namespace Builder {
        enum class SourceType {
            File,
            Network
        };
        extern SourceType sourceType;

        extern std::string sourceFileName;
        // TODO: extern NetworkRecord

        enum class ChunkerType {
            AE,
            MaxP
        };
        extern ChunkerType chunkerType;
        extern uint8_t chunkerIntervalLength;
        extern uint16_t chunkerWindowWidth;

        extern uint8_t chunkerThreadnum;

        // TODO: infos for chunkProcessor
        // TODO: infos for intervalProcessor

        extern void Build();
    } // namespace Builder



    extern void StartProcess();
} // namespace ToolChain



