#include <bits/stdc++.h>

template <typename T>
T ApproxBinSearch(const std::vector<T>& v, T target) {
  uint32_t left = 0;
  uint32_t right = v.size() - 1;

  uint32_t mid;
  while (left < right - 1) {
    mid = left + (right - left) / 2;
    if (v[mid] == target) return target;
    if (target < v[mid])
      right = mid;
    else
      left = mid;
  }

  return (target - v[left] <= v[right] - target) ? v[left] : v[right];
}

int main() {
  std::iostream::sync_with_stdio(false);
  std::cin.tie(nullptr);

  uint32_t n, k;
  std::cin >> n >> k;

  // Read values:
  std::vector<int64_t> v_sorted(n), queries(k);
  for (size_t i = 0; i < n; ++i) std::cin >> v_sorted[i];

  for (size_t i = 0; i < k; ++i) std::cin >> queries[i];

  // Print results:
  for (size_t i = 0; i < k; ++i)
    std::cout << ApproxBinSearch(v_sorted, queries[i]) << "\n";

  return 0;
}
