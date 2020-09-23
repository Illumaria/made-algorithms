#include <bits/stdc++.h>


template <typename T, typename U, typename L>
void merge(std::vector<T>& v, std::vector<T>& buf,
           U left, U mid, U right, L& inv_num) {
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
void _merge_sort(std::vector<T>& v, std::vector<T>& buf,
                 U left, U right, L& inv_num) {
    if (left < right) {
        U mid = left + (right - left) / 2;
        _merge_sort(v, buf, left, mid, inv_num);
        _merge_sort(v, buf, mid + 1, right, inv_num);
        merge(v, buf, left, mid, right, inv_num);
    }
}


template <typename T, typename L>
void merge_sort(std::vector<T>& v, L& inv_num) {
    if (!v.empty()) {
        std::vector<T> buf(v.size());
        _merge_sort(v, buf, (uint32_t)0, (uint32_t)(v.size() - 1), inv_num);
    }
}


int main() {
    uint32_t n;
    scanf("%lu", &n);

    // Read values:
    std::vector<int64_t> v(n);
    for (uint32_t i = 0; i < n; i++)
        scanf("%lld", &v[i]);

    // Get the number of inversions:
    uint64_t inv_num = 0;
    merge_sort(v, inv_num);

    // Print the number of inversions:
    printf("%llu\n", inv_num);

    return 0;
}
