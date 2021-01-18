#include <bits/stdc++.h>

template <typename T>
uint32_t LowerBound(const std::vector<T>& v, T target) {
  int64_t left = -1;
  int64_t right = v.size();

  while (left < right - 1) {
    int64_t mid = left + (right - left) / 2;
    if (v[mid] >= target)
      right = mid;
    else
      left = mid;
  }

  return right;
}

template <typename T>
uint32_t UpperBound(const std::vector<T>& v, T target) {
  return LowerBound(v, target + 1);
}

template <typename T>
uint32_t QuickSearch(const std::vector<T>& v, T left, T right) {
  return UpperBound(v, right) - LowerBound(v, left);
}

int main() {
  std::iostream::sync_with_stdio(false);
  std::cin.tie(nullptr);

  uint32_t n;
  std::cin >> n;

  // Read values:
  std::vector<int64_t> v(n);
  for (size_t i = 0; i < n; ++i) std::cin >> v[i];

  std::sort(v.begin(), v.end());

  uint32_t k;
  std::cin >> k;

  // Read bounds and print results:
  int64_t left, right;
  for (size_t i = 0; i < k; ++i) {
    std::cin >> left >> right;
    std::cout << QuickSearch(v, left, right) << " ";
  }

  return 0;
}
