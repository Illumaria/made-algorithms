#include <bits/stdc++.h>


template<typename T>
void optimized_bubble_sort(std::vector<T>& v) {
    uint16_t v_size = v.size();
    uint16_t i, new_i = 0;
    while (v_size > 1) {
        new_i = 0;
        for (i = 1; i < v_size; ++i) {
            if (v[i - 1] > v[i]) {
                std::swap(v[i - 1], v[i]);
                new_i = i;
            }
        }
        v_size = new_i;
    }
}


int main() {
    uint16_t n;
    scanf("%hu", &n);

    // Read values:
    std::vector<int64_t> v(n);
    for (uint16_t i = 0; i < n; ++i)
        scanf("%lld", &v[i]);

    // Sort values:
    optimized_bubble_sort(v);

    // Print values:
    for (const auto& x : v)
        printf("%lld ", x);
    printf("\n");

    return 0;
}
