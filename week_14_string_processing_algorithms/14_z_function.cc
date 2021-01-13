#include <bits/stdc++.h>

void zfunction(const std::string& s, std::vector<int32_t>& z) {
  int32_t left = 0, right = 0;

  for (int32_t i = 1; i < s.size(); ++i) {
    z[i] = std::max(0, std::min(right - i, z[i - left]));

    while (z[i] + i < s.size() && s[z[i]] == s[z[i] + i]) ++z[i];

    if (z[i] + i > right) {
      left = i;
      right = z[i] + i;
    }
  }
}

int main() {
  std::iostream::sync_with_stdio(false);
  std::cin.tie(nullptr);

  std::string s;
  std::cin >> s;

  std::vector<int32_t> z(s.size());
  zfunction(s, z);

  for (size_t i = 1; i < s.size(); ++i) std::cout << z[i] << " ";
  std::cout << "\n";

  return 0;
}
