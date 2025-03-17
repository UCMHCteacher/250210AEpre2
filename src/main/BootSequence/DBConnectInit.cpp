// #include"BootSequenceList.hpp"
#include"DataBaseTools.hpp"



void DBConnectInit() {
    DataBase::driver = sql::mysql::get_mysql_driver_instance();
}