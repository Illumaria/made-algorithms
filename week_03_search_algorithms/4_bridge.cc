#include <bits/stdc++.h>

template <typename T, typename U>
bool Func(const std::vector<T>& v, U k, U length) {
  for (const auto& x : v) {
    if (k <= x / length) return true;
    k -= x / length;
  }

  return false;
}

template <typename T, typename U>
T BridgeWidth(const std::vector<T>& v, U k) {
  U left = 0;
  U right = v.back();
  U mid;

  while (left < right - 1) {
    mid = left + (right - left) / 2;
    if (Func(v, k, mid))
      left = mid;
    else
      right = mid;
  }

  return Func(v, k, right) ? right : left;
}

int main() {
  std::iostream::sync_with_stdio(false);
  std::cin.tie(nullptr);

  uint32_t n, k;
  std::cin >> n >> k;

  // Read values:
  std::vector<uint64_t> v(n);
  for (size_t i = 0; i < n; ++i) std::cin >> v[i];

  // Sort values:
  std::sort(v.begin(), v.end());

  // Print result:
  std::cout << BridgeWidth(v, k) << "\n";

  return 0;
}
