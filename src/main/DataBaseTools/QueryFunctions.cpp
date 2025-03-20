#include"DataBaseTools.hpp"






bool 
DB::Queries::getFileIDByNameNLength(
    std::string const &  file_name,
    uint64_t  file_length,
    uint32_t &  file_id
) {
    return true;
}



bool 
DB::Queries::insertFileInfo(
    std::string const &  file_name,
    uint64_t  file_length
) {
    return true;
}



bool 
DB::Queries::insertChunkInfo(
    uint32_t  chunk_id,
    uint32_t  file_id,
    std::vector<uint8_t> const &  chunk_hash,
    uint64_t  chunk_length
) {
    return true;
}



bool 
DB::Queries::getChunkInfoByHashNLength(
    std::vector<uint8_t> const &  chunk_hash,
    uint64_t  chunk_length,
    uint32_t &  chunk_id,
    uint32_t &  file_id
) {
    return true;
}



bool 
DB::Queries::getFileInfoByFileID(
    uint32_t  file_id,
    std::string &  file_name,
    uint64_t &  file_length
) {
    return true;
}