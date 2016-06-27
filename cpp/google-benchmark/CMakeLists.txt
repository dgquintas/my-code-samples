cmake_minimum_required(VERSION 2.8)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

add_subdirectory(benchmark)
include_directories(benchmark/include)

add_executable(main main.cpp)
target_link_libraries(main benchmark)
