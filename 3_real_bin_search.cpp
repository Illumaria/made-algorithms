#include <bits/stdc++.h>


#define EPS 1e-12


double func(const double& x) {
    return (x * x) + sqrt(x);
}


double real_bin_search(const double& c) {
    double left = 1e0;
    double right = 1e10;

    uint64_t iter_num = log2((right - left) / EPS);

    double mid;
    for (size_t i = 0; i < iter_num; ++i) {
        mid = left + (right - left) / 2.;

        if (func(mid) < c)
            left = mid;
        else
            right = mid;
    }

    return right;
}


int main() {
    double c;
    scanf("%lf", &c);

    printf("%.10lf\n", real_bin_search(c));

    return 0;
}
