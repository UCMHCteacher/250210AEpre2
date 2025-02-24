#include"ToolChain.hpp"





ToolChain::Builder::SourceType
ToolChain::Builder::sourceType = ToolChain::Builder::SourceType::File;

std::string
ToolChain::Builder::sourceFileName = "111.txt";

std::unique_ptr<StreamGenerators::StreamGenerator>
ToolChain::streamGenerator = nullptr;



ToolChain::Builder::ChunkerType
ToolChain::Builder::chunkerType = ToolChain::Builder::ChunkerType::AE;

std::unique_ptr<CDChunking::Chunker>
ToolChain::chunker = nullptr;

uint8_t 
ToolChain::Builder::chunkerIntervalLength = 1;
uint16_t 
ToolChain::Builder::chunkerWindowWidth = 256;

uint8_t 
ToolChain::Builder::chunkerThreadnum = 2;



std::mutex _coutMutex{};

// uint8_t
// ToolChain::Builder::chunkProcessThreadNum = 8;

CDChunking::MainChunkProcessor::ActionMode 
ToolChain::Builder::chunkProcessorActionMode = CDChunking::MainChunkProcessor::ActionMode::PrintToConsole;

ThreadPool
ToolChain::chunkProcessPool(8);



void 
ToolChain::Builder::Build() {
    switch (sourceType) 
    {
    case SourceType::File:
        streamGenerator = std::make_unique<StreamGenerators::FileStreamGenerator>(sourceFileName);
        std::cout << "Opening file: " << sourceFileName << '\n';
        break;
    case SourceType::Network:
        // break; // TODO: network Class init
    default:
        // exit(0); // TODO: graceful exit
        break;
    }

    switch (chunkerType)
    {
    case ChunkerType::AE:
        chunker = std::make_unique<CDChunking::AE>(
            chunkerIntervalLength, 
            chunkerWindowWidth
        );
        std::cout << "Built an AE Chunker with interval=" << static_cast<int>(chunkerIntervalLength) << " & windowWidth=" << chunkerWindowWidth << '\n';
        break;
    case ChunkerType::MaxP:
        // break; // TODO: MaxP Class init
    default:
        // exit(0); // TODO: graceful exit
        break;
    }
}