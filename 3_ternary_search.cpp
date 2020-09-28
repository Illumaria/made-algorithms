#include <bits/stdc++.h>


#define EPS 1e-12


template <typename T>
double func(const double& x, const double& a, T v_p, T v_f) {
    // Time spent in the field:
    double time_p = sqrt(x * x + (1 - a) * (1 - a)) / v_p;
    // Time spent in the forest:
    double time_f = sqrt((1 - x) * (1 - x) + a * a) / v_f;

    return time_p + time_f;
}

template <typename T>
double ternary_search(const double& a, T v_p, T v_f) {
    double left = 0.0;
    double right = 1.0;

    uint64_t iter_num = log2((right - left) / EPS);

    double mid_left, mid_right;
    for (size_t i = 0; i < iter_num; ++i) {
        mid_left = left + (right - left) / 3.;
        mid_right = left + 2 * (right - left) / 3.;

        if (func(mid_left, a, v_p, v_f) < func(mid_right, a, v_p, v_f))
            right = mid_right;
        else
            left = mid_left;
    }

    return right;
}


int main() {
    uint32_t v_p, v_f;
    scanf("%u %u", &v_p, &v_f);

    double a;
    scanf("%lf", &a);

    printf("%.10lf\n", ternary_search(a, v_p, v_f));

    return 0;
}
