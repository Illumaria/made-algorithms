#include <bits/stdc++.h>

int main() {
  std::iostream::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int16_t t;
  std::cin >> t;

  int16_t a, b;
  for (; t > 0; --t) {
    std::cin >> a >> b;
    std::cout << a + b << "\n";
  }

  return 0;
}
