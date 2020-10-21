#include <bits/stdc++.h>


void solve(const size_t& n, const size_t& m,
           const std::vector<int16_t>& coins) {
    std::vector<int16_t> dp(n * m);
    dp[0] = coins[0];
    std::vector<size_t> ancestors(n * m);

    for (size_t i = 0; i < n; ++i)
        for (size_t j = 0; j < m; ++j) {
            if (i == 0 && j > 0) {
                dp[j] = dp[j - 1] + coins[j];
                ancestors[j] = j - 1;
            } else if (i > 0 && j == 0) {
                dp[m * i] = dp[m * (i - 1)] + coins[m * i];
                ancestors[m * i] = m * (i - 1);
            } else  if (i > 0 && j > 0) {
                dp[m * i + j] = std::max(dp[m * (i - 1) + j],
                                         dp[m * i + j - 1])
                                + coins[m * i + j];
                if (dp[m * (i - 1) + j] > dp[m * i + j - 1])
                    ancestors[m * i + j] = m * (i - 1) + j;
                else
                    ancestors[m * i + j] = m * i + j - 1;
            }
        }

    size_t cur_idx = n * m - 1;
    size_t next_idx = ancestors[cur_idx];
    std::string path;
    while (cur_idx > 0) {
        if (cur_idx - next_idx == 1)
            path += "R";
        else
            path += "D";
        cur_idx = next_idx;
        next_idx = ancestors[next_idx];
    }

    std::cout << dp[m * n - 1] << "\n";
    for (ssize_t i = path.size() - 1; i > -1; --i)
        std::cout << path[i];
}


int main() {
    std::istream::sync_with_stdio(false);
    std::cin.tie(nullptr);

    size_t n, m;
    std::cin >> n >> m;

    std::vector<int16_t> coins(n * m);
    for (size_t i = 0; i < n; ++i)
        for (size_t j = 0; j < m; ++j)
            std::cin >> coins[m * i + j];

    solve(n, m, coins);

    return 0;
}
