#include"StreamGenerator.hpp"
#include"ToolChain.hpp"
#include"DataBaseTools.hpp"







StreamGenerators::FileStreamGenerator::FileStreamGenerator(std::string fileName) :
    _fileName(fileName),
    _used(false)
{}

StreamGenerators::FileStreamGenerator::~FileStreamGenerator() {}



std::shared_ptr<std::istream>
StreamGenerators::FileStreamGenerator::getStream() {
    if (_used) return nullptr;

    std::shared_ptr<std::istream> stream = std::make_shared<std::ifstream>(_fileName, std::ios::in | std::ios::binary);

    if (!dynamic_cast<std::ifstream*>(stream.get())->is_open()) {
        return nullptr;
    }

    /** Query Order: 
     * 1) check whether the file exist or not
     * 2) insert fileinfo (if file not exist)
     * 3) get file_id
    */
    if (ToolChain::Builder::chunkProcessorActionMode & CDChunking::MainChunkProcessor::ActionMode::RecordToDataBase) {
        uint64_t fileLength = stream->rdbuf()->pubseekoff(0, std::ios::end, std::ios::in);
        stream->rdbuf()->pubseekpos(std::ios::beg, std::ios::in);

        sql::Connection *  con = DB::getConnection();

        // 1)
        sql::PreparedStatement *  getFileIDStmt = con->prepareStatement(DB::QueryStr::getFileIDByNameNLength);
        sql::ResultSet *  getFileIDRes = nullptr;
        getFileIDStmt->setString(1, _fileName);
        getFileIDStmt->setUInt64(2, fileLength);

        getFileIDRes = getFileIDStmt->executeQuery();
        if (getFileIDRes->rowsCount() > 0) {
            std::lock_guard lk(ToolChain::_coutMutex);
            std::cout << "File already exists in DB!\n";
            std::exit(0);
        }


        // 2)
        sql::PreparedStatement *  insertFileInfoStmt = con->prepareStatement(DB::QueryStr::insertFileInfo);
        insertFileInfoStmt->setString(1, _fileName);
        insertFileInfoStmt->setUInt64(2, fileLength);

        insertFileInfoStmt->executeUpdate();


        // 3)
        getFileIDRes = getFileIDStmt->executeQuery();
        while (getFileIDRes->next()) {
            ToolChain::fileID_DB = getFileIDRes->getUInt("file_id");
            std::lock_guard lk(ToolChain::_coutMutex);
            std::cout << "file_id = " << ToolChain::fileID_DB << '\n';
        }


        delete getFileIDRes;
        delete getFileIDStmt;
        delete insertFileInfoStmt;
        delete con;
    }

    _used = true;
    return stream;
}