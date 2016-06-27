#include <utility>
#include <vector>

typedef std::pair<int, int> IndexRange;

// Return a collection of ranges (both ends inclusive) partitioning input
// vector "v" into "k" parts so as to minimize the maximum sum over all the
// partitions. That is to say, we aim to partition such that each will contain
// as closely weight as posible.
std::vector<IndexRange> LinearPartition(const std::vector<int>& v, const int k);
