#include"CDChunking.hpp"

using CDChunking::Chunker;
using CDChunking::ChunkProcessInterface;





void 
Chunker::SetChunkProcessor(const std::shared_ptr<ChunkProcessInterface> & other) {
    this->_chunkProcessor = other;
};
std::shared_ptr<ChunkProcessInterface> Chunker::GetChunkProcessor() {
    return this->_chunkProcessor;
};


uint32_t
Chunker::getStreamCount() {
    return _streamCount;
}