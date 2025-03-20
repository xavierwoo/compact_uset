cmake_minimum_required(VERSION 3.30)
project(compact_uset)

set(CMAKE_CXX_STANDARD 20)

add_library(compact_uset STATIC
        cus/core.cpp
        cus/core.h)

target_include_directories(compact_uset PUBLIC "${CMAKE_CURRENT_LIST_DIR}")