#include <bits/stdc++.h>

template <typename T, typename U>
bool func(const std::vector<T>& v, U k, U length) {
  for (size_t i = 0; i < v.size(); ++i) {
    if (k <= v[i] / length) return true;
    k -= v[i] / length;
  }

  return false;
}

template <typename T, typename U>
T clothesline_len(const std::vector<T>& v, U k) {
  U left = 0;
  U right = v.back();
  U mid;

  while (left < right - 1) {
    mid = left + (right - left) / 2;
    if (func(v, k, mid))
      left = mid;
    else
      right = mid;
  }

  return func(v, k, right) ? right : left;
}

int main() {
  uint32_t n, k;
  scanf("%u %u", &n, &k);

  // Read values:
  std::vector<uint64_t> v(n);
  for (size_t i = 0; i < n; ++i) scanf("%llu", &v[i]);

  // Sort values:
  std::sort(v.begin(), v.end());

  // Print result:
  printf("%llu\n", clothesline_len(v, k));

  return 0;
}
