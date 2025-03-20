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

    extern sql::mysql::MySQL_Driver* driver;

    
    namespace Queries {
        namespace Strings {
            /**
             * @return file_id: uint32_t
             * @param file_name(1): varchar(255)
             * @param file_length(2): uint64_t
             */
            extern std::string getFileIDByNameNLength;

            /**
             * @param file_name(1): varchar(255)
             * @param file_length(2): uint64_t
             */
            extern std::string insertFileInfo;




            /**
             * @param chunk_id(1): uint32_t
             * @param file_id(2): uint32_t
             * @param chunk_hash(3): binary(32)
             * @param chunk_begin_pos(4): uint64_t
             * @param chunk_length(5): uint64_t
             */
            extern std::string insertChunkInfo;

            /**
             * @return [chunk_id:uint32_t]
             * @return [file_id:uint32_t]
             * @return [chunk_begin_pos:uint64_t]
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

            /**
             * @return [file_id:uint32_t]
             * @return [file_name:varchar(255)]
             * @return [file_length:uint64_t]
             * @return [chunk_id:uint32_t]
             * @return [chunk_begin_pos:uint64_t]
             * @param chunk_hash(1): binary(32)
             * @param chunk_length(2): uint64_t
             */
            extern std::string getAllByHashNLength;
        }



        /**
         * @return false in failure, true in success
         * @param file_name: __IN__  std::string
         * @param file_length: __IN__  uint64_t
         * @param file_id: __OUT__  uint32_t&
         */
        extern bool getFileIDByNameNLength(
            std::string const &  file_name,
            uint64_t  file_length,
            uint32_t &  file_id
        );

        /**
         * @param file_name: __IN__  std::string
         * @param file_length: __IN__  uint64_t
         */
        extern bool insertFileInfo(
            std::string const &  file_name,
            uint64_t  file_length
        );

        /**
         * @param chunk_id: __IN__  uint32_t
         * @param file_id: __IN__  uint32_t
         * @param chunk_hash: __IN__  std::vector<uint8_t>
         * @param chunk_length: __IN__  uint64_t
         */
        extern bool insertChunkInfo(
            uint32_t  chunk_id,
            uint32_t  file_id,
            std::vector<uint8_t> const &  chunk_hash,
            uint64_t  chunk_length
        );

        /**
         * @param chunk_hash: __IN__  std::vector<uint8_t>
         * @param chunk_length: __IN__  uint64_t
         * @param chunk_id: __OUT__  uint32_t&
         * @param file_id: __OUT__  uint32_t&
         */
        extern bool getChunkInfoByHashNLength(
            std::vector<uint8_t> const &  chunk_hash,
            uint64_t  chunk_length,
            uint32_t &  chunk_id,
            uint32_t &  file_id
        );

        /**
         * @param file_id: __IN__  uint32_t
         * @param file_name: __OUT__  std::string&
         * @param file_length: __OUT__  uint64_t&
         */
        extern bool getFileInfoByFileID(
            uint32_t  file_id,
            std::string &  file_name,
            uint64_t &  file_length
        );
    }
    namespace QueryStr = Queries::Strings;


    extern sql::Connection* getConnection();
} // namespace DataBase
namespace DB = DataBase;
