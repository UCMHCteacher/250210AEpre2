#include"ToolChain.hpp"
#include"ThreadPool.hpp"




void 
ToolChain::StartProcess() {
    // std::cout << "In StartProcess()\n";
    using chunkerType = std::remove_reference_t<decltype(*chunker)>;

    ThreadPool chunkingPool(Builder::chunkerThreadnum);

    std::shared_ptr<std::istream> streamtoChunk = nullptr;
    while (streamtoChunk = streamGenerator->getStream()) {
        chunkingPool.enqueue_void(
            [_chunker = std::ref(chunker), streamtoChunk]() {
                _chunker.get()->chunk(streamtoChunk);
            }
        );

    }
    // joins
    // TODO: ToolChain Process
}