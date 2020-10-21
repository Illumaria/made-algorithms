#include <bits/stdc++.h>


#define DELETE_COST 1
#define INSERT_COST 1
#define REPLACE_COST static_cast<int>(s[i - 1] != t[j - 1])


template <typename T>
class Matrix {
 public:
    explicit Matrix(const size_t n, const size_t m)
            : rows(n), ptr(new T*[n]) {
        for (size_t i = 0; i < n; ++i)
            ptr[i] = new T[m];
    }

    ~Matrix() {
        for (size_t i = 0; i < rows; ++i)
            delete[] ptr[i];
        delete[] ptr;
    }

    T* operator[](const size_t i) {
        return ptr[i];
    }

    const T* operator[](const size_t i) const {
        return ptr[i];
    }

 private:
    size_t rows;
    T** ptr;
};


int min(int a, int b, int c) {
    return std::min(std::min(a, b), c);
}


int levenshtein_distance(const std::string& s, const std::string& t) {
    int m = s.length();
    int n = t.length();
    Matrix<int> dp(m + 1, n + 1);
    dp[0][0] = 0;

    for (size_t j = 1; j <= n; ++j)
        dp[0][j] = dp[0][j - 1] + INSERT_COST;

    for (size_t i = 1; i <= m; ++i) {
        dp[i][0] = dp[i - 1][0] + DELETE_COST;
        for (size_t j = 1; j <= n; ++j)
            dp[i][j] = min(dp[i - 1][j] + DELETE_COST,
                           dp[i][j - 1] + INSERT_COST,
                           // REPLACE_COST = 0 if chars are the same,
                           //                1 otherwise
                           dp[i - 1][j - 1] + REPLACE_COST);
    }

    return dp[m][n];
}


int main() {
    std::iostream::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::string s, t;
    std::cin >> s >> t;

    std::cout << levenshtein_distance(s, t) << "\n";

    return 0;
}
