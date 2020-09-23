#include <bits/stdc++.h>


template <typename T, typename U>
void merge(std::vector<T>& v, std::vector<T>& buf, U left, U mid, U right) {
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
void _merge_sort(std::vector<T>& v, std::vector<T>& buf, U left, U right) {
    if (left < right) {
        U mid = left + (right - left) / 2;
        _merge_sort(v, buf, left, mid);
        _merge_sort(v, buf, mid + 1, right);
        merge(v, buf, left, mid, right);
    }
}


template <typename T>
void merge_sort(std::vector<T>& v) {
    if (!v.empty()) {
        std::vector<T> buf(v.size());
        _merge_sort(v, buf, (uint32_t)0, (uint32_t)(v.size() - 1));
    }
}


int main() {
    uint32_t n;
    scanf("%lu", &n);

    // Read values:
    std::vector<int64_t> v(n);
    for (uint32_t i = 0; i < n; i++)
        scanf("%lld", &v[i]);

    // Sort values:
    merge_sort(v);

    // Print values:
    for (const auto& x : v)
        printf("%lld ", x);
    printf("\n");

    return 0;
}
