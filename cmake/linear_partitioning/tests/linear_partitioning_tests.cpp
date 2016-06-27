#include "../linear_partitioning.h"

#include <gtest/gtest.h>
#include <gmock/gmock.h>

namespace testing {

TEST(LinearPartition, Test1to9) {
    const std::vector<int> v = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    const std::vector<IndexRange> ranges = LinearPartition(v, 3);

    const std::vector<IndexRange> expected =
        std::vector<IndexRange>{{0, 4}, {5, 6}, {7, 8}};

    EXPECT_THAT(ranges, ::testing::Eq(expected));
}

TEST(LinearPartition, TestEmpty) {
    const std::vector<int> v = {};
    const std::vector<IndexRange> ranges = LinearPartition(v, 3);

    EXPECT_EQ(ranges.size(), 0);
}

TEST(LinearPartition, TestSingle) {
    const std::vector<int> v = {1};
    const std::vector<IndexRange> ranges = LinearPartition(v, 3);

    const std::vector<IndexRange> expected = std::vector<IndexRange>{{0, 0}};

    EXPECT_THAT(ranges, ::testing::Eq(expected));
}

}  // namespace testing
