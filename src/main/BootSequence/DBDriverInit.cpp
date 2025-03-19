// #include"BootSequenceList.hpp"
#include"DataBaseTools.hpp"



void DBDriverInit() {
    DataBase::driver = sql::mysql::get_mysql_driver_instance();
}