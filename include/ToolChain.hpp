#pragma once

#include<cstdint>
#include<memory>

#include"StreamGenerator.hpp"
#include"CDChunking.hpp"
#include"ThreadPool.hpp"










namespace ToolChain {
    extern std::unique_ptr<StreamGenerators::StreamGenerator> streamGenerator;
    extern std::unique_ptr<CDChunking::Chunker> chunker;

    extern ThreadPool chunkProcessPool;
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



        // extern uint8_t chunkProcessThreadNum;
        extern CDChunking::MainChunkProcessor::ActionMode chunkProcessorActionMode;



        extern void Build();
    } // namespace Builder

    extern std::mutex _coutMutex;


    extern void StartProcess();
} // namespace ToolChain



