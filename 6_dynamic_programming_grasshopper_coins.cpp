#include <bits/stdc++.h>


void solve(const uint16_t& n, const uint16_t& k,
           const std::vector<int16_t>& coins) {
    std::vector<int64_t> dp(n);
    std::vector<uint16_t> ancestors(n);

    uint16_t cur_max_pos;
    int64_t cur_max;
    for (size_t i = 1; i < n; ++i) {
        cur_max_pos = i > k ? i - k : 0;
        cur_max = dp[cur_max_pos];
        for (size_t j = cur_max_pos + 1; j < i; ++j) {
            if (cur_max < dp[j]) {
                cur_max = dp[j];
                cur_max_pos = j;
            }
        }
        dp[i] = cur_max + coins[i];
        ancestors[i] = cur_max_pos;
    }

    std::vector<uint16_t> path;
    ssize_t cur_idx = n - 1;
    while (cur_idx > 0) {
        path.push_back(cur_idx);
        cur_idx = ancestors[cur_idx];
    }
    path.push_back(0);

    std::cout << dp[n - 1] << "\n" << path.size() - 1 << "\n";
    for (ssize_t i = path.size() - 1; i > -1; --i)
        std::cout << path[i] + 1 << " ";
}


int main() {
    std::istream::sync_with_stdio(false);
    std::cin.tie(nullptr);

    uint16_t n, k;
    std::cin >> n >> k;

    std::vector<int16_t> coins(n);
    for (size_t i = 1; i < n - 1; ++i)
        std::cin >> coins[i];

    solve(n, k, coins);

    return 0;
}
