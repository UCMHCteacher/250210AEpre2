#include<sstream>

#include"CDChunking.hpp"
#include"DataBaseTools.hpp"
#include"ToolChain.hpp"




void
CDChunking::DatabaseRecorder::operator() (std::shared_ptr<ChunkPackage> chunkPackage) {
    // {std::lock_guard lk(ToolChain::_coutMutex);
    //     std::cout << "Here\n";
    // }
    sql::Connection *  con = DB::getConnection();

    sql::PreparedStatement *  insertChunkInfoStmt = con->prepareStatement(DB::QueryStr::insertChunkInfo);
    insertChunkInfoStmt->setUInt(1, chunkPackage->_chunkNum);
    insertChunkInfoStmt->setUInt(2, ToolChain::fileID_DB);
    insertChunkInfoStmt->setUInt64(4, chunkPackage->_beginPos);
    insertChunkInfoStmt->setUInt64(5, chunkPackage->_chunkSize);

    std::istringstream _chunkhashStream(
        std::string(
            reinterpret_cast<char*>(chunkPackage->_datahash.data()),
            chunkPackage->_datahash.size()
        )
    );
    insertChunkInfoStmt->setBlob(3, &_chunkhashStream);

    int affected = insertChunkInfoStmt->executeUpdate();
    // {std::lock_guard lk(ToolChain::_coutMutex);
    //     std::cout << affected << '\n';
    // }


    delete insertChunkInfoStmt;
    delete con;
}