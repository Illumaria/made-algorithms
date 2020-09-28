#include <bits/stdc++.h>


template <typename T>
T approx_bin_search(const std::vector<T>& v, T target) {
    uint32_t left = 0;
    uint32_t right = v.size() - 1;

    uint32_t mid;
    while (left < right - 1) {
        mid = left + (right - left) / 2;
        if (v[mid] == target)
            return target;
        if (target < v[mid])
            right = mid;
        else
            left = mid;
    }

    return (target - v[left] <= v[right]  - target) ? v[left] : v[right];
}


int main() {
    uint32_t n, k;
    scanf("%u %u", &n, &k);

    // Read values:
    std::vector<int64_t> v_sorted(n), queries(k);
    for (size_t i = 0; i < n; ++i)
        scanf("%lld", &v_sorted[i]);

    for (size_t i = 0; i < k; ++i)
        scanf("%lld", &queries[i]);

    // Print results:
    for (size_t i = 0; i < k; ++i)
        printf("%lld\n", approx_bin_search(v_sorted, queries[i]));

    return 0;
}
