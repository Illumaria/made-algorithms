#include <bits/stdc++.h>

uint16_t roman_to_int(const char& c) {
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

uint16_t roman_to_int(const std::string& s) {
  int value = 0, prev_value = 0;
  // Iterate through string characters in reversed order:
  for (auto chr_ptr = s.rbegin(); chr_ptr != s.rend(); ++chr_ptr) {
    const uint16_t chr_to_int = roman_to_int(*chr_ptr);
    value += chr_to_int < prev_value ? -chr_to_int : chr_to_int;
    prev_value = chr_to_int;
  }
  return value;
}

int main() {
  uint16_t n;
  scanf("%hu", &n);

  // Failed to use scanf() for strings (due to segmentation error)
  // so using the slower std::cin in this solution.
  // Read values:
  std::string name, number;
  std::vector<std::pair<std::string, std::string>> v(n);
  for (uint16_t i = 0; i < n; ++i) {
    std::cin >> name >> number;
    v[i] = make_pair(name, number);
  }

  // Sort values:
  std::sort(v.begin(), v.end(), [](auto& left, auto& right) {
    if (left.first == right.first)
      return roman_to_int(left.second) < roman_to_int(right.second);
    return left.first < right.first;
  });

  // Print values:
  for (const auto& x : v) printf("%s %s\n", x.first.c_str(), x.second.c_str());

  return 0;
}
