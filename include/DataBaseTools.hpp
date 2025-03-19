#pragma once

#include<string>
#include<memory>

#include<jdbc/mysql_driver.h>
#include<jdbc/mysql_connection.h>
#include<jdbc/cppconn/prepared_statement.h>
#include<jdbc/cppconn/resultset.h>




namespace DataBase {
    extern std::string address;

    extern std::string username;

    extern std::string password;

    extern std::string dbname;

    sql::mysql::MySQL_Driver* driver;


    namespace QueryStrings {
        /**
         * @return file_id: uint32_t
         * @param file_name(1): varchar(255)
         * @param file_length(2): uint64_t
         */
        extern std::string getFileID;

        /**
         * @param file_name(1): varchar(255)
         * @param file_length(2): uint64_t
         */
        extern std::string insertFileInfo;




        /**
         * @param chunk_id(1): uint32_t
         * @param file_id(1): uint32_t
         * @param chunk_hash(1): binary(32)
         * @param chunk_length(2): uint64_t
         */
        extern std::string insertChunkInfo;

        /**
         * @return [chunk_id:uint32_t]
         * @return [file_id:uint32_t]
         * @param chunk_hash(1): binary(32)
         * @param chunk_length(2): uint64_t
         */
        extern std::string getChunkInfoByHashNLength;

        /**
         * @return [file_name:varchar(255)]
         * @return [file_length:uint64_t]
         * @param file_id(1): uint32_t
         */
        extern std::string getFileInfoByFileID;
        // extern std::string ;
    }
    namespace QueryStr = QueryStrings;


    extern sql::Connection* getConnection();
} // namespace DataBase
namespace DB = DataBase;
