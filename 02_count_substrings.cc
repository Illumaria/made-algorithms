#include <bits/stdc++.h>

// The size of the alphabet.
const uint16_t kRadix = 26;
// The offset of the 'a' character from zero.
const uint16_t kOffset = 97;

// The function counts the number of substrings
// in 's' which can be composed of 't' symbols.
//
// Example:
//     auto result = CountSubstrings("aba", "ab");
//     assert(result == 5)  // true
uint64_t CountSubstrings(const std::string& s, const std::string& t) {
  std::vector<int64_t> t_chars(kRadix, -1);
  for (auto c : t) {
    if (t_chars[c - kOffset] == -1)
      t_chars[c - kOffset] += 2;
    else
      ++t_chars[c - kOffset];
  }

  uint32_t i = 0, j = 0;
  uint64_t result = 0;
  while (j < s.length()) {
    if (t_chars[s[j] - kOffset] > 0) {
      --t_chars[s[j] - kOffset];
      result += j - i + 1;
    } else if (t_chars[s[j] - kOffset] == 0) {
      while (t_chars[s[j] - kOffset] == 0) ++t_chars[s[i++] - kOffset];
      result += j - i + 1;
      --t_chars[s[j] - kOffset];
    } else {
      while (i < j) ++t_chars[s[i++] - kOffset];
      ++i;
    }
    ++j;
  }

  return result;
}

int main() {
  std::iostream::sync_with_stdio(false);
  std::cin.tie(nullptr);

  // Read values:
  uint32_t n, m;
  std::cin >> n >> m;

  std::string s, t;
  std::cin >> s >> t;

  // Count substrings and print the result:
  std::cout << CountSubstrings(s, t) << "\n";

  return 0;
}
