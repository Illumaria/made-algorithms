#include <bits/stdc++.h>

#define RADIX 26
#define OFFSET 97

template <typename T>
void counting_sort(std::vector<std::string>& v, T n, T m, T pos) {
  uint32_t cnt[RADIX];
  std::fill(cnt, cnt + RADIX, 0);

  for (uint32_t i = 0; i < v.size(); ++i) ++cnt[v[i][pos] - OFFSET];

  uint32_t p[RADIX];
  std::fill(p, p + RADIX, 0);
  for (uint32_t i = 1; i < RADIX; ++i) p[i] = p[i - 1] + cnt[i - 1];

  std::vector<std::string> u(n);
  for (uint32_t i = 0; i < v.size(); ++i) u[p[v[i][pos] - OFFSET]++] = v[i];

  v = u;
}

template <typename T>
void radix_sort(std::vector<std::string>& v, T n, T m, T k) {
  for (T i = 0; i < k; ++i) counting_sort(v, n, m, (T)(m - i - 1));
}

int main() {
  // n: number of strings (numbers)
  // m: length of strings (numbers)
  // k: number of sorting phases
  uint16_t n, m, k;
  scanf("%u %u %u", &n, &m, &k);

  // Read values:
  std::vector<std::string> v(n);
  for (uint16_t i = 0; i < n; ++i) std::cin >> v[i];

  // Sort values:
  radix_sort(v, n, m, k);

  // Print values:
  for (const auto& x : v) std::cout << x << '\n';

  return 0;
}
