#pragma once

#include<string>
#include<memory>

#include<jdbc/mysql_driver.h>
#include<jdbc/mysql_connection.h>
#include<jdbc/cppconn/statement.h>




namespace DataBase {
    extern std::string address;

    extern std::string username;

    extern std::string password;

    extern std::string dbname;

    sql::mysql::MySQL_Driver* driver;
} // namespace DataBase
