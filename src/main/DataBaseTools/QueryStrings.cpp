#include"DataBaseTools.hpp"








std::string 
DB::QueryStr::getFileID = 
    "SELECT file_id"
    "FROM files"
    "WHERE (file_name, file_length) = (?, ?)";



std::string 
DB::QueryStr::insertFileInfo = 
    "INSERT INTO files"
    "(file_name, file_length)"
    "VALUES"
    "(?, ?)";






std::string 
DB::QueryStr::insertChunkInfo = 
    "INSERT INTO chunks"
    "(chunk_id, file_id, chunk_hash, chunk_length)"
    "VALUES"
    "(?, ?, ?, ?)";



std::string 
DB::QueryStr::getChunkInfoByHashNLength = 
    "SELECT chunk_id, file_id"
    "FROM chunks"
    "WHERE (chunk_hash, chunk_length) = (?, ?)";



std::string 
DB::QueryStr::getFileInfoByFileID = 
    "SELECT file_name, file_length"
    "FROM files"
    "WHERE file_id = ?";