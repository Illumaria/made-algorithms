#include <bits/stdc++.h>

template <typename T, typename U, typename L>
void Merge(std::vector<T>& v, std::vector<T>& buf, U left, U mid, U right,
           L& inv_num) {
  U i = left, k = left;
  U j = mid + 1;

  while (i <= mid || j <= right) {
    if (j > right || (i <= mid && v[i] < v[j])) {
      buf[k] = v[i];
      ++i;
    } else {
      buf[k] = v[j];
      ++j;
      inv_num += mid + 1 - i;
    }
    ++k;
  }

  for (U i = left; i <= right; ++i) {
    v[i] = buf[i];
  }
}

template <typename T, typename U, typename L>
void MergeSort_(std::vector<T>& v, std::vector<T>& buf, U left, U right,
                L& inv_num) {
  if (left < right) {
    U mid = left + (right - left) / 2;
    MergeSort_(v, buf, left, mid, inv_num);
    MergeSort_(v, buf, mid + 1, right, inv_num);
    Merge(v, buf, left, mid, right, inv_num);
  }
}

template <typename T, typename L>
void MergeSort(std::vector<T>& v, L& inv_num) {
  if (!v.empty()) {
    std::vector<T> buf(v.size());
    MergeSort_(v, buf, static_cast<uint32_t>(0),
               static_cast<uint32_t>(v.size() - 1), inv_num);
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

  // Get the number of inversions:
  uint64_t inv_num = 0;
  MergeSort(v, inv_num);

  // Print the number of inversions:
  std::cout << inv_num << "\n";

  return 0;
}
