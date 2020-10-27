#include <bits/stdc++.h>


typedef std::vector<int16_t> VectorInt16;
typedef std::vector<VectorInt16> MatrixInt16;


typedef std::vector<std::pair<size_t, size_t>> VectorPair;
typedef std::vector<VectorPair> MatrixPair;


void solve(const size_t& n, const size_t& m, const MatrixInt16& coins) {
    MatrixInt16 dp(n, VectorInt16(m));
    dp[0][0] = coins[0][0];
    MatrixPair ancestors(n, VectorPair(m));

    for (size_t i = 0; i < n; ++i)
        for (size_t j = 0; j < m; ++j) {
            if (i == 0 && j > 0) {
                dp[0][j] = dp[0][j - 1] + coins[0][j];
                ancestors[0][j] = {0, j - 1};
            } else if (i > 0 && j == 0) {
                dp[i][0] = dp[i - 1][0] + coins[i][0];
                ancestors[i][0] = {i - 1, 0};
            } else if (i > 0 && j > 0) {
                dp[i][j] = std::max(dp[i - 1][j], dp[i][j - 1]) + coins[i][j];
                if (dp[i - 1][j] > dp[i][j - 1])
                    ancestors[i][j] = {i - 1, j};
                else
                    ancestors[i][j] = {i, j - 1};
            }
        }

    size_t cur_row = n - 1, cur_col = m - 1;
    size_t next_row, next_col;
    std::tie(next_row, next_col) = ancestors[cur_row][cur_col];
    std::string path;
    while (cur_row > 0 || cur_col > 0) {
        if (cur_col > next_col)
            path += "R";
        else
            path += "D";
        std::tie(cur_row, cur_col) = std::tie(next_row, next_col);
        std::tie(next_row, next_col) = ancestors[cur_row][cur_col];
    }

    std::cout << dp[n - 1][m - 1] << "\n";
    for (ssize_t i = path.size() - 1; i > -1; --i)
        std::cout << path[i];
}


int main() {
    std::istream::sync_with_stdio(false);
    std::cin.tie(nullptr);

    size_t n, m;
    std::cin >> n >> m;

    MatrixInt16 coins(n, VectorInt16(m));
    for (size_t i = 0; i < n; ++i)
        for (size_t j = 0; j < m; ++j)
            std::cin >> coins[i][j];

    solve(n, m, coins);

    return 0;
}
