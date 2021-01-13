#include <bits/stdc++.h>

uint16_t RomanToInt(const char& c) {
  switch (c) {
    case 'I':
      return 1;
    case 'V':
      return 5;
    case 'X':
      return 10;
    case 'L':
      return 50;
    case 'C':
      return 100;
    case 'D':
      return 500;
    case 'M':
      return 1000;
    default:
      return 0;
  }
}

uint16_t RomanToInt(const std::string& s) {
  int value = 0, prev_value = 0;
  // Iterate through string characters in reversed order:
  for (auto chr_ptr = s.rbegin(); chr_ptr != s.rend(); ++chr_ptr) {
    auto chr_to_int = RomanToInt(*chr_ptr);
    value += chr_to_int < prev_value ? -chr_to_int : chr_to_int;
    prev_value = chr_to_int;
  }
  return value;
}

int main() {
  std::iostream::sync_with_stdio(false);
  std::cin.tie(nullptr);

  uint16_t n;
  std::cin >> n;

  // Read values:
  std::string name, number;
  std::vector<std::pair<std::string, std::string>> v(n);
  for (size_t i = 0; i < n; ++i) {
    std::cin >> name >> number;
    v[i] = std::make_pair(name, number);
  }

  // Sort values:
  std::sort(v.begin(), v.end(), [](auto& left, auto& right) {
    if (left.first == right.first)
      return RomanToInt(left.second) < RomanToInt(right.second);
    return left.first < right.first;
  });

  // Print values:
  for (const auto& x : v) std::cout << x.first << " " << x.second << "\n";

  return 0;
}
