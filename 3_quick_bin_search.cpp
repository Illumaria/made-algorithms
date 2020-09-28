#include <bits/stdc++.h>


template <typename T>
uint32_t lower_bound(const std::vector<T>& v, T target) {
    int64_t left = -1;
    int64_t right = v.size();

    while (left < right - 1) {
        int64_t mid = left + (right - left) / 2;
        if (v[mid] >= target)
            right = mid;
        else
            left = mid;
    }

    return right;
}


template <typename T>
uint32_t upper_bound(const std::vector<T>& v, T target) {
    return lower_bound(v, target + 1);
}


template <typename T>
uint32_t quick_search(const std::vector<T>& v, T left, T right) {
    return upper_bound(v, right) - lower_bound(v, left);
}


int main() {
    uint32_t n;
    scanf("%u", &n);

    // Read values:
    std::vector<int64_t> v(n);
    for (size_t i = 0; i < n; ++i)
        scanf("%lld", &v[i]);

    std::sort(v.begin(), v.end());

    uint32_t k;
    scanf("%u", &k);

    // Read bounds and print results:
    int64_t left, right;
    for (size_t i = 0; i < k; ++i) {
        scanf("%lld %lld", &left, &right);
        printf("%u ", quick_search(v, left, right));
    }

    return 0;
}
