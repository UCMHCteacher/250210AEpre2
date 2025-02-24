#include"CDChunking.hpp"

using CDChunking::ChunkPackage;





ChunkPackage::ChunkPackage(
    uint32_t streamNum, 
    uint32_t chunkNum, 
    std::vector<uint8_t> && chunkData, 
    std::size_t chunkBeginPos,
    std::size_t chunkEndPos
) :
    _streamNum(streamNum),
    _chunkNum(chunkNum),

    _data(chunkData),
    _datahash(0),

    _beginPos(chunkBeginPos),
    _endPos(chunkEndPos),
    _chunkSize(chunkData.size())
{};
ChunkPackage::ChunkPackage(const ChunkPackage & other) :
    _streamNum(other._streamNum),
    _chunkNum(other._chunkNum),

    _data(std::cref(other._data)),
    _datahash(other._datahash),

    _beginPos(other._beginPos),
    _endPos(other._endPos),
    _chunkSize(other._chunkSize)
    {};
ChunkPackage::ChunkPackage(ChunkPackage && other) :
    _streamNum(other._streamNum),
    _chunkNum(other._chunkNum),

    _data(std::move(other._data)),
    _datahash(other._datahash),

    _beginPos(other._beginPos),
    _endPos(other._endPos),
    _chunkSize(other._chunkSize)
{};