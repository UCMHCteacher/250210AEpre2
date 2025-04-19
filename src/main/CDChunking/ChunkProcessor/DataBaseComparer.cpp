#include<sstream>
#include<iomanip>

#include"CDChunking.hpp"
#include"DataBaseTools.hpp"
#include"ToolChain.hpp"
#include"Summary.hpp"




extern std::string Indents(uint32_t count);

struct FitChunkInfo {
    uint32_t file_id;
    std::string file_name;
    uint64_t file_length;
    uint32_t chunk_id;
    uint64_t chunk_begin_pos;
};


void
CDChunking::DatabaseComparer::operator() (std::shared_ptr<ChunkPackage> chunkPackage) {
    sql::Connection *  con = DB::getConnection();

    sql::PreparedStatement *  getChunkInfoStmt = con->prepareStatement(DB::QueryStr::getAllByHashNLength);
    getChunkInfoStmt->setUInt64(2, chunkPackage->_chunkSize);

    std::istringstream _chunkhashStream(
        std::string(
            reinterpret_cast<char*>(chunkPackage->_datahash.data()),
            chunkPackage->_datahash.size()
        )
    );
    getChunkInfoStmt->setBlob(1, &_chunkhashStream);

    sql::ResultSet *  getChunkInfoRes = getChunkInfoStmt->executeQuery();



    std::vector<FitChunkInfo> fitChunkList;
    while (getChunkInfoRes->next()) {
        fitChunkList.emplace_back(
            FitChunkInfo{
                getChunkInfoRes->getUInt("file_id"),
                getChunkInfoRes->getString("file_name"),
                getChunkInfoRes->getUInt64("file_length"),
                getChunkInfoRes->getUInt("chunk_id"),
                getChunkInfoRes->getUInt64("chunk_begin_pos")
            }
        );
    }


    if (fitChunkList.size() > 0) {
        std::lock_guard lkc(ToolChain::_coutMutex);

        std::cout
            << "Chunk with following features were found in database. \n"
            << Indents(1) << "Chunk Length: " << chunkPackage->_chunkSize << '\n'
            << Indents(1) << "Chunk Hash: ";
        for (auto  i : chunkPackage->_datahash) {
            std::cout << std::setw(2) << std::setfill('0') << std::hex << static_cast<int>(i);
        }std::cout << std::resetiosflags(std::ios_base::basefield) << '\n';

        std::cout << "Records in DataBase are as follows:\n";
        for (auto const &  fitChunkInfo : fitChunkList) {
            std::cout 
                << "{\n"
                << Indents(1) << "File ID: " << fitChunkInfo.file_id << '\n'
                << Indents(1) << "File Name: " << fitChunkInfo.file_name << '\n'
                << Indents(1) << "File Length: " << fitChunkInfo.file_length << '\n'
                << Indents(1) << "Chunk ID: " << fitChunkInfo.chunk_id << '\n'
                << Indents(1) << "Chunk Begin Position: " << fitChunkInfo.chunk_begin_pos << '\n'
                << "},\n";
        }

        std::cout << "\n\n";
    }



    if (fitChunkList.size() > 0  &&  Summary::needed) {
        for (auto const &  fitChunkInfo : fitChunkList) {
            std::lock_guard lk{Summary::correctnessDataMutex};

            auto insertIt = Summary::correctnessData.try_emplace(fitChunkInfo.file_id, 1);
            if (!insertIt.second) {
                insertIt.first->second++;
            }
        }
    }


    delete getChunkInfoStmt;
    delete con;
}