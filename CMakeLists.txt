cmake_minimum_required(VERSION 3.16)
project(sorting_strategies CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Headers están en la raíz del proyecto
include_directories(${CMAKE_SOURCE_DIR})

add_executable(sorting main.cpp)
