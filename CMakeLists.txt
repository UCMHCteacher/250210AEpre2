cmake_minimum_required(VERSION 3.10)

project(AEChunkProgram VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)








# 递归查找所有 .cpp 文件
file(GLOB_RECURSE SRC_FILES ${PROJECT_SOURCE_DIR}/src/*.cpp)

list(APPEND
    ALL_SRC_FILES
    ${SRC_FILES}
)



list(APPEND
    ALL_INCLUDE_DIRS
    "./include"
)





include(Configs.cmake)

find_library(MySQL_LIB mysqlcppconn.lib PATHS ${MySQL_LIB_DIR})
find_library(Packet_LIB Packet.lib PATHS ${Npcap_LIB_DIR})
find_library(wpcap_LIB wpcap.lib PATHS ${Npcap_LIB_DIR})
list(APPEND
    ALL_LIB_FILES
    ${MySQL_LIB}
    ${Packet_LIB}
    ${wpcap_LIB}
    ws2_32.lib
)


list(APPEND
    ALL_INCLUDE_DIRS
    ${MySQL_INCLUDE_DIR}
    ${Npcap_INCLUDE_DIR}
)








# 添加可执行目标
add_executable(${PROJECT_NAME} ${ALL_SRC_FILES})
target_link_libraries(${PROJECT_NAME} PRIVATE ${ALL_LIB_FILES})
include_directories(${ALL_INCLUDE_DIRS})
target_compile_definitions(${PROJECT_NAME} PRIVATE "BPF_MAJOR_VERSION")