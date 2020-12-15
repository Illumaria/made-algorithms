#include <bits/stdc++.h>


void pfunction(const std::string& s,
               std::vector<int32_t>& p) {
    p[0] = 0;

    for (int32_t i = 1; i < s.size(); ++i) {
        auto k = p[i - 1];

        while (k > 0 && s[i] != s[k])
            k = p[k - 1];

        if (s[i] == s[k])
            ++k;

        p[i] = k;
    }
}


int main() {
    std::iostream::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::string p, t;
    std::cin >> p >> t;

    std::string s = p + '#' + t;
    std::vector<int32_t> pf(s.size());
    pfunction(s, pf);

    std::vector<int32_t> indices;
    for (size_t i = 0; i < pf.size(); ++i)
        if (pf[i] == p.size())
            indices.push_back(i - 2 * p.size() + 1);

    std::cout << indices.size() << "\n";
    for (const auto& index : indices)
        std::cout << index << " ";
    std::cout << "\n";

    return 0;
}
