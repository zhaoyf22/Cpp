cmake_minimum_required(VERSION 3.21)
project(Cpp)

set(CMAKE_CXX_STANDARD 11)

# 头文件
include_directories(${PROJECT_SOURCE_DIR}/src/PerfTools)
include_directories(${PROJECT_SOURCE_DIR}/src/Base)

add_subdirectory(src/)