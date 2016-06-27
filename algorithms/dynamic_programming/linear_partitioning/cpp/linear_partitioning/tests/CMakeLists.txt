cmake_minimum_required(VERSION 2.8)

# Google Mock & Test
set(GMOCK_ROOT "${CMAKE_CURRENT_LIST_DIR}/gmock")
add_subdirectory(${GMOCK_ROOT})
include_directories(${GMOCK_ROOT}/include)
include_directories(${GMOCK_ROOT}/gtest/include)

# Unit Tests
add_executable(linear_partitioning_tests linear_partitioning_tests.cpp)
target_link_libraries(linear_partitioning_tests 
                      linear_partitioning
                      gtest
                      gtest_main
                      gmock)
add_test(LinearPartition linear_partitioning_tests)
add_custom_target(build-tests DEPENDS linear_partitioning_tests)
