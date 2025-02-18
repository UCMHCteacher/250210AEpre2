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

void 
ToolChain::Builder::Build() {
    switch (sourceType) 
    {
    case SourceType::File:
        streamGenerator = std::make_unique<StreamGenerators::FileStreamGenerator>(sourceFileName);
    case SourceType::Network:
        // break; // TODO: network Class init
    default:
        // exit(0); // TODO: graceful exit
        break;
    }

    switch (chunkerType)
    {
    case ChunkerType::AE:
        chunker = std::make_unique<CDChunking::AE>(); // TODO: init of AE object
        break;
    case ChunkerType::MaxP:
        // break; // TODO: MaxP Class init
    default:
        // exit(0); // TODO: graceful exit
        break;
    }
}