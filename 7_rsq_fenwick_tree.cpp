#include <bits/stdc++.h>

class FenwickTree {
 private:
  uint32_t size;
  std::vector<int64_t> t;

 public:
  std::vector<int64_t> a;

  explicit FenwickTree(const uint32_t& n) : size(n) {
    a.resize(n);
    t.resize(n);
  }

  static int32_t f(const int32_t& i) { return i & (i + 1); }

  void build() {
    for (size_t i = 0; i < size; ++i)
      for (size_t j = f(i); j <= i; ++j) t[i] += a[j];
  }

  void add(const uint32_t& i, const int64_t& value) {
    uint32_t j = i;
    while (j < size) {
      t[j] += value;
      j = j | (j + 1);
    }
  }

  void set(const uint32_t& i, const int64_t& value) {
    int64_t diff = value - a[i];
    a[i] = value;
    add(i, diff);
  }

  int64_t get(int32_t i) const {
    int64_t result = 0;

    while (i >= 0) {
      result += t[i];
      i = f(i) - 1;
    }

    return result;
  }

  int64_t sum(const uint32_t& left, const uint32_t& right) {
    return left > 0 ? get(right) - get(left - 1) : get(right);
  }
};

int main() {
  std::iostream::sync_with_stdio(false);
  std::cin.tie(nullptr);

  uint32_t n;
  std::cin >> n;

  FenwickTree ft(n);
  for (size_t i = 0; i < n; ++i) std::cin >> ft.a[i];
  ft.build();

  uint32_t i, j;
  int64_t x;
  std::string command;
  while (std::cin >> command) {
    if (command == "set") {
      std::cin >> i >> x;
      ft.set(i - 1, x);
    } else if (command == "sum") {
      std::cin >> i >> j;
      std::cout << ft.sum(i - 1, j - 1) << "\n";
    }
  }

  return 0;
}
