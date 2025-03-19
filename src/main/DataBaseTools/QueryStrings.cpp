#include"DataBaseTools.hpp"





using namespace DataBase::QueryStrings;




/**
 * @return file_id: uint32_t
 * @param file_name(1): varchar(255)
 * @param file_length(2): uint64_t
 */
std::string getFileID = 
    "SELECT file_id"
    "FROM files"
    "WHERE (file_name, file_length) = (?, ?)";


/**
 * @param file_name(1): varchar(255)
 * @param file_length(2): uint64_t
 */
std::string insertFileInfo = 
    "INSERT INTO files"
    "(file_name, file_length)"
    "VALUES"
    "(?, ?)";





/**
 * @param chunk_id(1): uint32_t
 * @param file_id(1): uint32_t
 * @param chunk_hash(1): binary(32)
 * @param chunk_length(2): uint64_t
 */
std::string insertChunkInfo = 
    "INSERT INTO chunks"
    "(chunk_id, file_id, chunk_hash, chunk_length)"
    "VALUES"
    "(?, ?, ?, ?)";


/**
 * @return [chunk_id:uint32_t]
 * @return [file_id:uint32_t]
 * @param chunk_hash(1): binary(32)
 * @param chunk_length(2): uint64_t
 */
std::string getChunkInfoByHashNLength = 
    "SELECT chunk_id, file_id"
    "FROM chunks"
    "WHERE (chunk_hash, chunk_length) = (?, ?)";


/**
 * @return [file_name:varchar(255)]
 * @return [file_length:uint64_t]
 * @param file_id(1): uint32_t
 */
std::string getFileInfoByFileID = 
    "SELECT file_name, file_length"
    "FROM files"
    "WHERE file_id = ?";