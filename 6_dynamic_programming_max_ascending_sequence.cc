#include <bits/stdc++.h>

void solve(const size_t& n, const std::vector<int64_t>& a) {
  std::vector<int64_t> dp(n);
  std::vector<int64_t> ancestors(n);

  for (size_t i = 0; i < n; ++i) {
    ancestors[i] = -1;
    dp[i] = 1;
    for (size_t j = 0; j < i; ++j) {
      if (a[j] < a[i])
        if (dp[i] - 1 < dp[j]) {
          ancestors[i] = j;
          dp[i] = dp[j] + 1;
        }
    }
  }

  ssize_t last = 0;
  int64_t len = dp[0];
  for (size_t i = 0; i < n; ++i) {
    if (len < dp[i]) {
      last = i;
      len = dp[i];
    }
  }

  std::vector<int64_t> ans;
  while (last >= 0) {
    int64_t cur = a[last];
    ans.push_back(cur);
    last = ancestors[last];
  }

  std::cout << ans.size() << "\n";
  while (!ans.empty()) {
    std::cout << ans.back() << " ";
    ans.pop_back();
  }
}

int main() {
  std::istream::sync_with_stdio(false);
  std::cin.tie(nullptr);

  uint16_t n;
  std::cin >> n;

  std::vector<int64_t> values(n);
  for (size_t i = 0; i < n; ++i) std::cin >> values[i];

  solve(n, values);

  return 0;
}
