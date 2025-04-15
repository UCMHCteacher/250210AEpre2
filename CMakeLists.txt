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





include(ImportPaths.cmake)

find_library(MySQL_LIB          mysqlcppconn    PATHS ${MySQL_LIB_DIR})
list(APPEND
    ALL_LIB_FILES
    ${MySQL_LIB}
)

if(CMAKE_SYSTEM_NAME STREQUAL "Windows")
    find_library(Packet_LIB Packet  PATHS ${pcap_LIB_DIR})
    find_library(wpcap_LIB  wpcap   PATHS ${pcap_LIB_DIR})

    find_library(OpenSSL_SSL_LIB    libssl      PATHS ${OpenSSL_LIB_DIR})
    find_library(OpenSSL_CRYPTO_LIB libcrypto   PATHS ${OpenSSL_LIB_DIR})

    # find_library(WinSock_LIB ws2_32.lib)

    list(APPEND
        ALL_LIB_FILES
        ${Packet_LIB}
        ${wpcap_LIB}
        ${OpenSSL_SSL_LIB}
        ${OpenSSL_CRYPTO_LIB}
        ws2_32.lib
    )
elseif(CMAKE_SYSTEM_NAME STREQUAL "Linux")
    find_library(pcap_LIB   pcap    PATHS ${pcap_LIB_DIR})

    find_library(OpenSSL_SSL_LIB    ssl     PATHS ${OpenSSL_LIB_DIR})
    find_library(OpenSSL_CRYPTO_LIB crypto  PATHS ${OpenSSL_LIB_DIR})

    find_library(pthread_LIB pthread)

    list(APPEND
        ALL_LIB_FILES
        ${pcap_LIB}
        ${OpenSSL_SSL_LIB}
        ${OpenSSL_CRYPTO_LIB}
        ${pthread_LIB}
    )
endif()





list(APPEND
    ALL_INCLUDE_DIRS
    ${MySQL_INCLUDE_DIR}
    ${pcap_INCLUDE_DIR}
    ${OpenSSL_INCLUDE_DIR}
)








# 添加可执行目标
add_executable(${PROJECT_NAME} ${ALL_SRC_FILES})
target_link_libraries(${PROJECT_NAME} PRIVATE ${ALL_LIB_FILES})
include_directories(${ALL_INCLUDE_DIRS})
target_compile_definitions(${PROJECT_NAME} PRIVATE "BPF_MAJOR_VERSION")
if(CMAKE_SYSTEM_NAME STREQUAL "Linux")
    target_compile_options(${PROJECT_NAME} PRIVATE "-pthread")
endif()