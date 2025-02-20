cmake_minimum_required(VERSION 3.10)

project(MyProject VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 递归查找所有 .cpp 和 .h 文件
file(GLOB_RECURSE SRC_FILES ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)
file(GLOB_RECURSE HEADER_FILES ${CMAKE_CURRENT_SOURCE_DIR}/include/*.h)

# 将所有文件设置为源文件列表
set(SOURCE_FILES
    ${SRC_FILES}
    ${HEADER_FILES}
)

# 遍历所有子目录并添加到包含路径中
get_filename_component(ROOT_DIR "${CMAKE_CURRENT_SOURCE_DIR}" ABSOLUTE)
file(GLOB_RECURSE SUB_DIRS LIST_DIRECTORIES true ${ROOT_DIR}/*)

foreach(SUB_DIR ${SUB_DIRS})
    if(IS_DIRECTORY ${SUB_DIR})
        include_directories(${SUB_DIR})
    endif()
endforeach()

# 添加可执行目标
add_executable(${PROJECT_NAME} ${SOURCE_FILES})