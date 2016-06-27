#include <iostream>
#include <numeric>

#include "linear_partitioning/linear_partitioning.h"

int main() {
    //const std::vector<int> v = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    const std::vector<int> v = {
        32,  48,  72,  96,  120, 144, 168, 184, 216, 240,  272,  304,  320,
        352, 384, 408, 440, 464, 496, 528, 560, 584, 617,  648,  672,  704,
        736, 768, 800, 832, 864, 896, 920, 952, 992, 1024, 1056, 1088, 1080};
    std::vector<IndexRange> ranges = LinearPartition(v, 15);

    for (const auto& range : ranges) {
        const int sum = std::accumulate(v.begin() + range.first,
                                        v.begin() + range.second + 1, 0);
        std::cout << "Sum for range (" << range.first << ", " << range.second
                  << "): " << sum << std::endl;
    }

    return 0;
}
