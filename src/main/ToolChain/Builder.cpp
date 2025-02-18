#include"ToolChain.hpp"





ToolChain::Builder::ChunkerType
ToolChain::Builder::chunkerType = ToolChain::Builder::ChunkerType::AE;

std::unique_ptr<CDChunking::Chunker>
ToolChain::chunker = nullptr;

void 
ToolChain::Builder::Build() {
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