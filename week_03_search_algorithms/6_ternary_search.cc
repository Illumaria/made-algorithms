#include <bits/stdc++.h>

// The difference between two real numbers
// at which they are considered equal.
const double kEps = 1e-12;

template <typename T>
double Func(const double& x, const double& a, T v_p, T v_f) {
  // Time spent in the field:
  double time_p = std::sqrt(x * x + (1 - a) * (1 - a)) / v_p;
  // Time spent in the forest:
  double time_f = std::sqrt((1 - x) * (1 - x) + a * a) / v_f;

  return time_p + time_f;
}

template <typename T>
double TernarySearch(const double& a, T v_p, T v_f) {
  double left = 0.0;
  double right = 1.0;

  uint64_t iter_num = std::log2((right - left) / kEps);

  double mid_left, mid_right;
  for (size_t i = 0; i < iter_num; ++i) {
    mid_left = left + (right - left) / 3.;
    mid_right = left + 2 * (right - left) / 3.;

    if (Func(mid_left, a, v_p, v_f) < Func(mid_right, a, v_p, v_f))
      right = mid_right;
    else
      left = mid_left;
  }

  return right;
}

int main() {
  std::iostream::sync_with_stdio(false);
  std::cin.tie(nullptr);

  uint32_t v_p, v_f;
  double a;
  std::cin >> v_p >> v_f >> a;

  std::cout << std::setprecision(10) << TernarySearch(a, v_p, v_f) << "\n";

  return 0;
}
