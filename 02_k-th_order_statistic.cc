#include <bits/stdc++.h>

template <typename T, typename U>
std::tuple<U, U> split(std::vector<T>& v, U left, U right, T pivot) {
  U mid_left = left, mid_right = left, k = right;

  while (mid_right <= k) {
    if (v[mid_right] < pivot) {
      std::swap(v[mid_left], v[mid_right]);
      ++mid_left;
      ++mid_right;
    } else if (v[mid_right] > pivot) {
      std::swap(v[mid_right], v[k]);
      --k;
    } else {
      ++mid_right;
    }
  }

  return std::tie(mid_left, mid_right);
}

template <typename T, typename U>
T _kth_order_statistic(std::vector<T>& v, U left, U right, U target) {
  if (left < right) {
    // Median of left, mid, and right:
    U mid = left + (right - left) / 2;
    if (v[mid] < v[left]) std::swap(v[left], v[mid]);
    if (v[right] < v[left]) std::swap(v[left], v[right]);
    if (v[mid] < v[right]) std::swap(v[right], v[mid]);
    T pivot = v[right];

    U mid_left, mid_right;
    std::tie(mid_left, mid_right) = split(v, left, right, pivot);

    if (target < mid_left)
      return _kth_order_statistic(v, left, mid_left - 1, target);
    else if (target >= mid_right)
      return _kth_order_statistic(v, mid_right, right, target);
    else
      return pivot;
  } else {
    return v[target];
  }
}

template <typename T, typename U>
T kth_order_statistic(std::vector<T>& v, U left, U right, U target) {
  if (!v.empty()) {
    std::vector<T> u(v.begin() + left, v.begin() + right + 1);
    return _kth_order_statistic(u, 0, right - left, target);
  }

  return 0;
}

int main() {
  uint16_t n;
  scanf("%hu", &n);

  // Read values:
  std::vector<uint64_t> v(n);
  for (uint16_t i = 0; i < n; ++i) scanf("%llu", &v[i]);

  uint32_t m;
  uint16_t left, right, target;
  scanf("%u", &m);

  // Print k-th order statistic:
  for (; m > 0; --m) {
    scanf("%hu %hu %hu", &left, &right, &target);
    printf("%llu\n", kth_order_statistic(v, left - 1, right - 1, target - 1));
  }

  return 0;
}
