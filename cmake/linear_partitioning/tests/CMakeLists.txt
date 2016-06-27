find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

add_executable(linear_partitioning_tests linear_partitioning_tests.cpp)
target_link_libraries(linear_partitioning_tests linear_partitioning
                                                ${GTEST_BOTH_LIBRARIES})
add_test(AllTests linear_partitioning_tests)
