cmake_minimum_required(VERSION 3.16)
project(DZ2)

set(CMAKE_CXX_STANDARD 20)
find_library(LIB_TO_INCLUDE openssl /usr/bin /usr/local/bin)
include_directories(${LIB_INCLUDES})

add_executable(DZ2 main.cpp)