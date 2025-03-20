#include"DataBaseTools.hpp"





std::string 
DataBase::address = "tcp://127.0.0.1:3306";

std::string 
DataBase::username = "root";

std::string 
DataBase::password = "w20020315";

std::string 
DataBase::dbname = "chunk";

sql::mysql::MySQL_Driver* 
DataBase::driver = nullptr;



// remember to release the connection it returns
sql::Connection* 
DataBase::getConnection() {
    sql::Connection* con = driver->connect(
        address,
        username,
        password
    );

    con->setSchema(dbname);

    return con;
}