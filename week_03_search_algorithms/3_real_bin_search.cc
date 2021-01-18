#include <bits/stdc++.h>

// The difference between two real numbers
// at which they are considered equal.
const double kEps = 1e-12;

double Func(const double& x) { return (x * x) + std::sqrt(x); }

double RealBinSearch(const double& c) {
  double left = 1e0;
  double right = 1e10;

  uint64_t iter_num = std::log2((right - left) / kEps);

  double mid;
  for (size_t i = 0; i < iter_num; ++i) {
    mid = left + (right - left) / 2.;

    if (Func(mid) < c)
      left = mid;
    else
      right = mid;
  }

  return right;
}

int main() {
  std::iostream::sync_with_stdio(false);
  std::cin.tie(nullptr);

  double c;
  std::cin >> c;

  std::cout << std::setprecision(10) << RealBinSearch(c) << "\n";

  return 0;
}
