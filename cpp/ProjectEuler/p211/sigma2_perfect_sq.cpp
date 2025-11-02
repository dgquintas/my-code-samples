#include <iostream>
#include <vector>
#include <cmath>
#include <numeric>

// Check if a number is a perfect square
inline bool is_square(long long n) {
    if (n < 0) {
        return false;
    }
    if (n == 0) {
        return true;
    }
    long long root = round(sqrtl(n));
    return root * root == n;
}

int main() {
    constexpr int N = 64000000;
    std::vector<int> spf(N);
    std::iota(spf.begin(), spf.end(), 0);

    for (int i = 2; i * i < N; ++i) {
        if (spf[i] == i) { // i is prime
            for (int j = i * i; j < N; j += i) {
                if (spf[j] == j) {
                    spf[j] = i;
                }
            }
        }
    }

    std::vector<long long> sigma2(N);
    sigma2[1] = 1;

    for (int i = 2; i < N; ++i) {
        int p = spf[i];
        long long p_power_term = (long long)p * p;
        long long sigma_p_power = 1 + p_power_term;
        int n = i / p;
        while (spf[n] == p) {
            sigma_p_power = sigma_p_power * p_power_term + 1;
            n /= p;
        }
        sigma2[i] = sigma_p_power * sigma2[n];
    }

    long long total_sum = 0;
    for (int i = 1; i < N; ++i) {
        if (is_square(sigma2[i])) {
            total_sum += i;
        }
    }

    std::cout << total_sum << std::endl;

    return 0;
}
