#include"ToolChain.hpp"
#include"ThreadPool.hpp"




void 
ToolChain::StartProcess() {
    // std::cout << "In StartProcess()\n";
    using chunkerType = std::remove_reference_t<decltype(*chunker)>;

    ThreadPool chunkingPool(Builder::chunkerThreadnum);

    std::shared_ptr<StreamPackage> streamPackagetoChunk = nullptr;
    while (streamPackagetoChunk = streamGenerator->getStream()) {
        streamPackagetoChunk->_start = std::chrono::steady_clock::now();
        chunkingPool.enqueue_void(
            [_chunker = std::ref(chunker), streamPackagetoChunk]() {
                _chunker.get()->chunk(streamPackagetoChunk);
            }
        );

    }
    // joins
    // TODO: ToolChain Process
}