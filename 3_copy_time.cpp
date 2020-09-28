#include <bits/stdc++.h>


template <typename T, typename U>
bool func(T n, U x, U y, T time) {
    // Create the first copy to allow for
    // copy machines parallel operation:
    U min_time = x > y ? y : x;
    if (time < min_time)
        return false;
    time -= min_time;
    --n;

    // Check if we can make the required
    // number of copies in the specified time:
    if ((n == 0) || (time / x + time / y >= n))
        return true;
    return false;
}


template <typename T, typename U>
uint64_t copy_time(T n, U x, U y) {
    T left = 1, right = 1;
    // Find the right bound:
    while (!func(n, x, y, right))
        right *= 2;
    T mid;

    while (left < right - 1) {
        mid = left + (right - left) / 2;
        if (func(n, x, y, mid))
            right = mid;
        else
            left = mid;
    }

    return right;
}


int main() {
    uint32_t n;
    uint16_t x, y;
    scanf("%u %hu %hu", &n, &x, &y);

    printf("%llu\n", copy_time(n, x, y));

    return 0;
}
