#include <bits/stdc++.h>

template <typename T>
void OptimizedBubbleSort(std::vector<T>& v) {
  uint16_t v_size = v.size();
  uint16_t i, new_i = 0;
  while (v_size > 1) {
    new_i = 0;
    for (i = 1; i < v_size; ++i) {
      if (v[i - 1] > v[i]) {
        std::swap(v[i - 1], v[i]);
        new_i = i;
      }
    }
    v_size = new_i;
  }
}

int main() {
  std::iostream::sync_with_stdio(false);
  std::cin.tie(nullptr);

  uint16_t n;
  std::cin >> n;

  // Read values:
  std::vector<int64_t> v(n);
  for (size_t i = 0; i < n; ++i) std::cin >> v[i];

  // Sort values:
  OptimizedBubbleSort(v);

  // Print values:
  for (const auto& x : v) std::cout << x << " ";
  std::cout << "\n";

  return 0;
}
