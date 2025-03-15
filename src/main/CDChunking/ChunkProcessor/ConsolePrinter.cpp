#include"ToolChain.hpp"
#include"CDChunking.hpp"

#include<iomanip>




void
CDChunking::ConsolePrinter::operator() (std::shared_ptr<ChunkPackage> chunkPackage) {
    std::lock_guard lk(ToolChain::_coutMutex);
    std::cout   
        << "Stream Number: "        << chunkPackage->_streamNum << " {\n"
        << "\tChunk Number: "       << chunkPackage->_chunkNum  << " {\n"
        << "\t\tBegin Position: "   << chunkPackage->_beginPos  << "\n"
        << "\t\tEnd Posotion: "     << chunkPackage->_endPos    << "\n"
        << "\t\tChunk Length: "     << chunkPackage->_chunkSize << "\n";

    std::cout
        << "\t\tChunk Hash: ";
    for (auto  i : chunkPackage->_datahash) {
        std::cout << std::setw(2) << std::setfill('0') << std::hex << static_cast<int>(i);
    }std::cout << std::resetiosflags(std::ios_base::basefield) << '\n';

    std::cout 
        << "\t}\n"
        << "}\n\n\n";
}