#include <bits/stdc++.h>

// Elements with indices from left to mid_left
// are smaller than the pivot;
// elements with indices from mid_right to right
// are larger than the pivot.
template <typename T, typename U>
std::tuple<U, U> split(std::vector<T>& v, U left, U right, T x) {
  U mid_left = left, mid_right = left;
  U k = right;

  while (mid_right <= k) {
    if (v[mid_right] < x) {
      std::swap(v[mid_left], v[mid_right]);
      ++mid_left;
      ++mid_right;
    } else if (v[mid_right] > x) {
      std::swap(v[mid_right], v[k]);
      --k;
    } else {
      ++mid_right;
    }
  }
  return std::tie(mid_left, mid_right);
}

template <typename T, typename U>
void _quick_sort(std::vector<T>& v, U left, U right) {
  if (left < right) {
    // Random generator works fine
    // but is very time consuming!
    // std::random_device r;
    // std::default_random_engine e(r());
    // std::uniform_int_distribution<U> uniform_dist(left, right);
    // T x = v[uniform_dist(e)];

    // Median of left, mid, and right is used instead.
    U mid = left + (right - left) / 2;
    if (v[mid] < v[left]) std::swap(v[left], v[mid]);
    if (v[right] < v[left]) std::swap(v[left], v[right]);
    if (v[mid] < v[right]) std::swap(v[right], v[mid]);
    T x = v[right];

    U mid_left, mid_right;
    std::tie(mid_left, mid_right) = split(v, left, right, x);

    _quick_sort(v, left, mid_left);
    _quick_sort(v, mid_right, right);
  }
}

template <typename T>
void quick_sort(std::vector<T>& v) {
  if (!v.empty()) {
    _quick_sort(v, (uint32_t)0, (uint32_t)v.size() - 1);
  }
}

int main() {
  uint32_t n;
  scanf("%lu", &n);

  // Read values:
  std::vector<int64_t> v(n);
  for (uint32_t i = 0; i < n; ++i) scanf("%lld", &v[i]);

  // Sort values:
  quick_sort(v);

  // Print values:
  for (const auto& x : v) printf("%lld ", x);
  printf("\n");

  return 0;
}
