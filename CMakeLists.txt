cmake_minimum_required(VERSION 3.16)
project(sorting_strategies CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(${CMAKE_SOURCE_DIR}/src)

add_executable(sorting main.cpp)
