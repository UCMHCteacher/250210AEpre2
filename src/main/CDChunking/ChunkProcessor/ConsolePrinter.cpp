#include"ToolChain.hpp"
#include"CDChunking.hpp"





void
CDChunking::ConsolePrinter::operator() (std::shared_ptr<ChunkPackage> chunkPackage) {
    std::lock_guard lk(ToolChain::_coutMutex);
    std::cout   << "Stream Number: "        << chunkPackage->_streamNum << " {\n"
                << "\tChunk Number: "       << chunkPackage->_chunkNum  << " {\n"
                << "\t\tBegin Position: "   << chunkPackage->_beginPos  << "\n"
                << "\t\tEnd Posotion: "     << chunkPackage->_endPos    << "\n"
                << "\t\tChunk Length: "     << chunkPackage->_chunkSize << "\n"
                << "\t\tChunk Hash: "       << chunkPackage->_datahash  << "\n"
                << "\t}\n"
                << "}\n\n\n";
}