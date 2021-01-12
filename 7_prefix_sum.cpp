#include <bits/stdc++.h>

int main() {
  std::iostream::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int32_t n, x, y, a0;
  std::cin >> n >> x >> y >> a0;

  std::vector<int32_t> a(n, a0);
  std::vector<int64_t> pref_sum(n, a0);

  for (size_t i = 1; i < n; ++i) {
    a[i] = (x * a[i - 1] + y) % (1 << 16);
    pref_sum[i] = pref_sum[i - 1] + a[i];
  }

  int32_t m, z, t, b0;
  std::cin >> m >> z >> t >> b0;

  std::vector<int32_t> b(2 * m, b0);

  for (size_t i = 1; i < 2 * m; ++i) {
    b[i] = (z * b[i - 1] + t) % (1 << 30);
    if (b[i] < 0) b[i] += (1 << 30);
  }

  int32_t left, right;
  int64_t result = 0;
  for (size_t i = 0; i < m; ++i) {
    left = std::min(b[2 * i] % n, b[2 * i + 1] % n);
    right = std::max(b[2 * i] % n, b[2 * i + 1] % n);
    result += left > 0 ? pref_sum[right] - pref_sum[left - 1] : pref_sum[right];
  }

  std::cout << result;

  return 0;
}
