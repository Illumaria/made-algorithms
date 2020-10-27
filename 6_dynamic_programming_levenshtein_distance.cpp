#include <bits/stdc++.h>


#define DELETE_COST 1
#define INSERT_COST 1
#define REPLACE_COST static_cast<int>(s[i - 1] != t[j - 1])


typedef std::vector<int> VectorInt;
typedef std::vector<VectorInt> MatrixInt;


int min(int a, int b, int c) {
    return std::min(std::min(a, b), c);
}


int levenshtein_distance(const std::string& s, const std::string& t) {
    int n = s.length();
    int m = t.length();
    MatrixInt dp(n + 1, VectorInt(m + 1));
    dp[0][0] = 0;

    for (size_t j = 1; j < m + 1; ++j)
        dp[0][j] = dp[0][j - 1] + INSERT_COST;

    for (size_t i = 1; i < n + 1; ++i) {
        dp[i][0] = dp[i - 1][0] + DELETE_COST;
        for (size_t j = 1; j < m + 1; ++j)
            dp[i][j] = min(dp[i - 1][j] + DELETE_COST,
                           dp[i][j - 1] + INSERT_COST,
                           // REPLACE_COST = 0 if chars are the same,
                           //                1 otherwise
                           dp[i - 1][j - 1] + REPLACE_COST);
    }

    return dp[n][m];
}


int main() {
    std::iostream::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::string s, t;
    std::cin >> s >> t;

    std::cout << levenshtein_distance(s, t) << "\n";

    return 0;
}
