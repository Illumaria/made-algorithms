#include <bits/stdc++.h>


#define MAX_DAYS 100
#define MAX_DAILY_COST 300
#define MAX_COST MAX_DAYS * MAX_DAILY_COST + 1


template <typename T>
class Matrix {
 public:
    explicit Matrix(const size_t rows, const size_t cols, const T value)
            : rows(rows), cols(cols), ptr(new T*[rows]) {
        for (size_t i = 0; i < rows; ++i) {
            ptr[i] = new T[cols];
            for (size_t j = 0; j < cols; ++j)
                ptr[i][j] = value;
        }
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
    size_t rows, cols;
    T** ptr;
};


void solve(uint16_t n, const std::vector<int16_t>& prices) {
    Matrix<int32_t> dp(n + 1, n + 3, MAX_COST);
    dp[0][1] = 0;
    Matrix<std::pair<uint16_t, uint16_t>> ancestors(n + 1, n + 3, {0, 0});

    for (size_t i = 1; i < n + 1; ++i) {
        for (size_t j = 1; j < n + 2; ++j) {
            if (prices[i] > 100) {
                if (dp[i - 1][j - 1] + prices[i] < dp[i - 1][j + 1]) {
                    dp[i][j] = dp[i - 1][j - 1] + prices[i];
                    ancestors[i][j] = {i - 1, j - 1};
                } else {
                    dp[i][j] = dp[i - 1][j + 1];
                    ancestors[i][j] = {i - 1, j + 1};
                }
            } else {
                if (dp[i - 1][j] + prices[i] < dp[i - 1][j + 1]) {
                    dp[i][j] = dp[i - 1][j] + prices[i];
                    ancestors[i][j] = {i - 1, j};
                } else {
                    dp[i][j] = dp[i - 1][j + 1];
                    ancestors[i][j] = {i - 1, j + 1};
                }
            }
        }
    }

    int32_t min_cost = dp[n][0];
    size_t min_pos = 0;
    for (size_t j = 1; j < n + 2; ++j)
        if (dp[n][j] <= min_cost) {
            min_cost = dp[n][j];
            min_pos = j;
        }

    std::stack<size_t> path;
    size_t cur_row = n, cur_col = min_pos;
    size_t next_row, next_col;
    std::tie(next_row, next_col) = ancestors[cur_row][cur_col];
    while (cur_row > 0 || cur_col > 0) {
        if (next_col > cur_col)
            path.push(cur_row);
        std::tie(cur_row, cur_col) = std::tie(next_row, next_col);
        std::tie(next_row, next_col) = ancestors[cur_row][cur_col];
    }

    std::cout << dp[n][min_pos] << "\n";
    std::cout << min_pos - 1 << " " << path.size() << "\n";

    while (!path.empty()) {
        std::cout << path.top() << "\n";
        path.pop();
    }
}


int main() {
    std::iostream ::sync_with_stdio(false);
    std::cin.tie(nullptr);

    uint16_t n;
    std::cin >> n;

    std::vector<int16_t> prices(n + 1);
    prices[0] = 0;
    for (size_t i = 1; i <= n; ++i)
        std::cin >> prices[i];

    solve(n, prices);

    return 0;
}
