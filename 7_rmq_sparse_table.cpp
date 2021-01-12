#include <bits/stdc++.h>

uint32_t update_val(const uint32_t& val) {
  return (23 * val + 21563) % 16714589;
}

void update_u(uint32_t& u, const uint32_t& result, const size_t& i,
              const uint32_t& n) {
  u = (17 * u + 751 + result + 2 * i) % n + 1;
}

void update_v(uint32_t& v, const uint32_t& result, const size_t& i,
              const uint32_t& n) {
  v = (13 * v + 593 + result + 5 * i) % n + 1;
}

class SparseTable {
 private:
  std::vector<std::vector<uint32_t>> min_table;
  uint32_t rows, cols;

 public:
  std::vector<uint32_t> val_vec;

  explicit SparseTable(const uint32_t& n) : rows(n) {
    val_vec.resize(rows);

    cols = 1;
    while (1 << cols < rows) ++cols;

    min_table.resize(rows);
    for (size_t i = 0; i < rows; ++i) min_table[i].resize(cols);
  }

  void build() {
    for (size_t i = 1; i < rows; ++i) val_vec[i] = update_val(val_vec[i - 1]);

    for (size_t i = 0; i < rows; ++i) min_table[i][0] = val_vec[i];

    for (size_t j = 1; j < cols; ++j)
      for (size_t i = 0; i + (1 << j) - 1 < rows; ++i)
        min_table[i][j] =
            std::min(min_table[i][j - 1], min_table[i + (1 << (j - 1))][j - 1]);
  }

  uint32_t get_min(const uint32_t& left, const uint32_t& right,
                   const uint32_t& min_pow) {
    return std::min(min_table[left][min_pow],
                    min_table[right - (1 << min_pow) + 1][min_pow]);
  }
};

int main() {
  std::iostream::sync_with_stdio(false);
  std::cin.tie(nullptr);

  uint32_t n, m;
  std::cin >> n >> m;

  SparseTable st(n);
  std::cin >> st.val_vec[0];
  st.build();

  uint32_t u, v;
  std::cin >> u >> v;

  uint32_t result, left, right;
  for (size_t i = 1; i <= m; ++i) {
    left = std::min(u - 1, v - 1);
    right = std::max(u - 1, v - 1);

    uint32_t min_pow = 0;
    while (1 << min_pow <= right - left + 1) {
      if (1 << (min_pow + 1) > right - left + 1) break;
      ++min_pow;
    }

    result = st.get_min(left, right, min_pow);

    if (i < m) {
      update_u(u, result, i, n);
      update_v(v, result, i, n);
    }
  }

  std::cout << u << " " << v << " " << result << "\n";

  return 0;
}
