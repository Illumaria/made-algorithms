#include <bits/stdc++.h>

template <typename T, typename U>
void Merge(std::vector<T>& v, std::vector<T>& buf, U left, U mid, U right) {
  U i = left, k = left;
  U j = mid + 1;

  while (i <= mid || j <= right) {
    if (j > right || (i <= mid && v[i] < v[j])) {
      buf[k] = v[i];
      ++i;
    } else {
      buf[k] = v[j];
      ++j;
    }
    ++k;
  }

  for (U i = left; i <= right; ++i) {
    v[i] = buf[i];
  }
}

template <typename T, typename U>
void MergeSort_(std::vector<T>& v, std::vector<T>& buf, U left, U right) {
  if (left < right) {
    U mid = left + (right - left) / 2;
    MergeSort_(v, buf, left, mid);
    MergeSort_(v, buf, mid + 1, right);
    Merge(v, buf, left, mid, right);
  }
}

template <typename T>
void MergeSort(std::vector<T>& v) {
  if (!v.empty()) {
    std::vector<T> buf(v.size());
    MergeSort_(v, buf, static_cast<uint32_t>(0),
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
  MergeSort(v);

  // Print values:
  for (const auto& x : v) std::cout << x << " ";
  std::cout << "\n";

  return 0;
}
