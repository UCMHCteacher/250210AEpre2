#include<filesystem>
#include<sstream>
#include<fstream>

#include"CDChunking.hpp"
#include"ToolChain.hpp"



void
CDChunking::ChunkFileGenerator::operator() (std::shared_ptr<ChunkPackage> chunkPackage) {
    namespace stdfs = std::filesystem;

    std::stringstream _chunkNumStr{};
    _chunkNumStr << chunkPackage->_chunkNum;

    stdfs::path _chunkFilePath = ToolChain::Builder::chunkDataDir / _chunkNumStr.str();

    std::ofstream _chunkFile{_chunkFilePath, std::ios::out|std::ios::binary};

    // _chunkFile << chunkPackage->_data;
    std::ostreambuf_iterator outputIt{_chunkFile};
    for (auto &  _dataIt : chunkPackage->_data) {
        *outputIt = _dataIt;
        outputIt++;
    }
}