#pragma once

#include<cstdint>
#include<memory>
#include<filesystem>

#include"StreamGenerator.hpp"
#include"CDChunking.hpp"
#include"ThreadPool.hpp"










namespace ToolChain {
    extern std::unique_ptr<StreamGenerators::StreamGenerator> streamGenerator;
    extern std::unique_ptr<CDChunking::Chunker> chunker;
    // TODO: extern chunkProcessor

    extern uint32_t fileID_DB;





    namespace Builder {
        enum class SourceType {
            File,
            Network
        };
        extern SourceType sourceType;

        extern std::string sourceFilePath;
        extern std::string sourceFileName;
        extern uint16_t networkNum;



        enum class ChunkerType {
            AE,
            MaxP
        };
        extern ChunkerType chunkerType;
        extern uint8_t chunkerIntervalLength;
        extern uint16_t chunkerWindowWidth;

        extern uint8_t chunkerThreadnum;



        extern uint8_t chunkProcessThreadNum;
        extern CDChunking::MainChunkProcessor::ActionMode chunkProcessorActionMode;
        extern std::filesystem::path chunkDataDir;



        extern void Build();
    } // namespace Builder

    extern std::mutex _coutMutex;


    extern void StartProcess();
} // namespace ToolChain



