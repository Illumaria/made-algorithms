#include <bits/stdc++.h>

// Elements with indices from left to mid_left
// are smaller than the pivot;
// elements with indices from mid_right to right
// are larger than the pivot.
template <typename T, typename U>
std::tuple<U, U> Split(std::vector<T>& v, U left, U right, T x) {
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
void QuickSort_(std::vector<T>& v, U left, U right) {
  if (left < right) {
    // Random generator works fine
    // but is very time consuming!
    // std::random_device r;
    // std::default_random_engine e(r());
    // std::uniform_int_distribution<U> uniform_dist(left, right);
    // T x = v[uniform_dist(e)];

    // Median of left, mid, and right is used instead:
    U mid = left + (right - left) / 2;
    if (v[mid] < v[left]) std::swap(v[left], v[mid]);
    if (v[right] < v[left]) std::swap(v[left], v[right]);
    if (v[mid] < v[right]) std::swap(v[right], v[mid]);
    T x = v[right];

    U mid_left, mid_right;
    std::tie(mid_left, mid_right) = Split(v, left, right, x);

    QuickSort_(v, left, mid_left);
    QuickSort_(v, mid_right, right);
  }
}

template <typename T>
void QuickSort(std::vector<T>& v) {
  if (!v.empty()) {
    QuickSort_(v, static_cast<uint32_t>(0),
               static_cast<uint32_t>(v.size() - 1));
  }
}

int main() {
  std::iostream::sync_with_stdio(false);
  std::cin.tie(nullptr);

  uint32_t n;
  std::cin >> n;

  // Read values:
  std::vector<int64_t> v(n);
  for (size_t i = 0; i < n; ++i) std::cin >> v[i];

  // Sort values:
  QuickSort(v);

  // Print values:
  for (const auto& x : v) std::cout << x << " ";

  return 0;
}
