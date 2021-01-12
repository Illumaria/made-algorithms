#include <bits/stdc++.h>

#define MAX_N 100

template <typename T>
void counting_sort(std::vector<T>& v) {
  uint32_t cnt[MAX_N + 1];
  std::fill(cnt, cnt + MAX_N + 1, 0);

  for (auto x : v) ++cnt[x];

  uint32_t j = 0;
  for (size_t i = 0; i <= MAX_N; ++i) {
    while (cnt[i] > 0) {
      v[j++] = i;
      --cnt[i];
    }
  }
}

int main() {
  std::ios::sync_with_stdio(0);
  std::cin.tie(0);

  // Read values:
  std::string s;
  std::getline(std::cin, s);
  std::istringstream iss(s);

  std::vector<uint8_t> v;
  int x;
  while (iss >> x) v.push_back(x);

  // Sort values:
  counting_sort(v);

  // Print values:
  for (const auto& x : v) printf("%hu ", x);
  printf("\n");

  return 0;
}
