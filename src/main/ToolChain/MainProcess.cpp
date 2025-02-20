#include"ToolChain.hpp"
#include"ThreadPool.hpp"




void 
ToolChain::StartProcess() {
    // std::cout << "In StartProcess()\n";
    using chunkerType = std::remove_reference_t<decltype(*chunker)>;

    ThreadPool chunkingPool(Builder::chunkerThreadnum);

    while (streamGenerator->isAlive()) {
        std::shared_ptr<std::istream> streamtoChunk(streamGenerator->getStream());
        chunkingPool.enqueue_void(
            &chunkerType::chunk,
            std::ref(chunker),
            streamtoChunk
        );

    }
    // joins
    // TODO: ToolChain Process
}