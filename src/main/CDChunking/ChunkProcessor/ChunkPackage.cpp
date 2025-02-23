#include"CDChunking.hpp"

using CDChunking::ChunkPackage;





ChunkPackage::ChunkPackage(
    uint32_t streamNum, 
    uint32_t chunkNum, 
    std::vector<uint8_t> && chunkData, 
    std::size_t chunkBeginPos,
    std::size_t chunkEndPos,
    std::size_t chunkSize
) :
    _streamNum(streamNum),
    _chunkNum(chunkNum),
    _data(chunkData),
    _beginPos(chunkBeginPos),
    _endPos(chunkEndPos),
    _chunkSize(chunkSize)
{};
ChunkPackage::ChunkPackage(const ChunkPackage & other) :
    _streamNum(other._streamNum),
    _chunkNum(other._chunkNum),
    _data(std::cref(other._data)),
    _beginPos(other._beginPos),
    _endPos(other._endPos),
    _chunkSize(other._chunkSize)
    {};
ChunkPackage::ChunkPackage(ChunkPackage && other) :
    _streamNum(other._streamNum),
    _chunkNum(other._chunkNum),
    _data(std::move(other._data)),
    _beginPos(other._beginPos),
    _endPos(other._endPos),
    _chunkSize(other._chunkSize)
{};