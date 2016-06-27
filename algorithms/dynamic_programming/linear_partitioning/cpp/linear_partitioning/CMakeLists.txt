cmake_minimum_required(VERSION 2.8)

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

add_library(linear_partitioning linear_partitioning.cpp)

# include the directory of this CMakeList in the -I
#include_directories(${CMAKE_CURRENT_SOURCE_DIR})

enable_testing()
add_subdirectory(tests EXCLUDE_FROM_ALL)
