cmake_minimum_required(VERSION 2.8)
project("Linear Partitioning")

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
add_subdirectory(linear_partitioning)

add_executable(main main.cpp)
target_link_libraries(main linear_partitioning)
