#include <numeric>
#include <algorithm>
#include <functional>
#include <limits>

#include "linear_partitioning.h"
#include "matrix.h"

std::vector<IndexRange> LinearPartition(const std::vector<int>& v,
                                        const int k) {
    if (v.size() == 0) {
        return {};
    }
    constexpr const int kUninitialized = -1;
    const int n = v.size();

    // We need the M and D matrices to be of size k x n.
    Matrix<int> M(k, n, kUninitialized);
    Matrix<int> D(k, n, kUninitialized);

    // If the k-th (and last) division happens at index i (inclusive), its cost
    // is the sum v[i] + ... v[n-1].
    // The rest of the vector to the left of that i is a subproblem that can be
    // solved recursively. In general, we want:
    //
    // min_{i} max( M[k-1, i-1], v[i] + ... + v[n-1] )
    //
    // Where M[k, n] is the solution for subproblem. For each k, n we save the
    // partitioning index i in D.
    //
    // The base cases are:
    // - M[k, 0] = v[0] for all k.
    // - M[0, n] = sum of all elements, as there's only one section.

    // Prefix sums.
    std::vector<int> psums(n);
    std::partial_sum(v.begin(), v.end(), psums.begin());

    // Populate the base cases.
    // M[k, 0]. Can't use std::fill_n because elements aren't contiguous.
    for (int k_i = 0; k_i < M.nrows(); ++k_i) {
        M(k_i, 0) = v[0];
    }
    // M[0, n]
    std::copy(psums.begin(), psums.end(), M.data());

    // Recursive lambda, wot!
    std::function<int(const int, const int)> CalculateCostFn =
        [&CalculateCostFn, &M, &D, &psums, &v](const int k, const int n) {

        // Implement min_i max(M[k-1, i-1], v[i] + ... + v[n]).
        // Note that v[i] + ... + v[n] = psum(n) - psum(i-1)
        int minimum = std::numeric_limits<int>::max();
        for (int i = 1; i <= n; ++i) {
            if (M(k-1, n-i) == kUninitialized) {
                M(k-1, n-i) = CalculateCostFn(k-1, n-i);
            }

            const int cost_at_i =
                std::max(M(k-1, i-1), psums[n] - psums[i-1]);

            if (cost_at_i < minimum) {
                minimum = cost_at_i;
                D(k, n) = i-1;
            }
        }
        return minimum;
    };

    // Adjusted indices for 0-indexing.
    M(k-1, n-1) = CalculateCostFn(k-1, n-1);

    // At this point, D should contain the partitioning indices.
    std::vector<int> indices;
    indices.reserve(k+1);
    indices.push_back(n-1);
    for (int k_i = k-1, n_i = n-1; k_i >= 0; --k_i) {
        const int idx = D(k_i, n_i);
        if (idx == kUninitialized) break;
        indices.push_back(idx);
        n_i = idx;
    }
    indices.push_back(-1);

    // Construct the index ranges.
    std::vector<IndexRange> ranges;
    ranges.reserve(indices.size()+1);
    for (int i = indices.size()-1; i >= 1; --i) {
        ranges.push_back(std::make_pair(indices[i]+1, indices[i-1]));
    }

    return ranges;
}
