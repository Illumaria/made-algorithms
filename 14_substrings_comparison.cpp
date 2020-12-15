#include <bits/stdc++.h>


#define PRIME_P static_cast<uint64_t>(31)
#define CONST_M static_cast<uint64_t>(1e9 + 7)


void init(const std::string& s,
          std::vector<uint64_t>& hash,
          std::vector<uint64_t>& powp) {
    hash[0] = s[0];
    powp[0] = 1;
    for (size_t i = 1; i < s.size(); ++i) {
        hash[i] = (hash[i - 1] * PRIME_P + s[i]) % CONST_M;
        powp[i] = (powp[i - 1] * PRIME_P) % CONST_M;
    }
}


uint64_t get_hash(const std::vector<uint64_t>& hash,
                  const std::vector<uint64_t>& powp,
                  const uint32_t& left,
                  const uint32_t& right) {
    if (left == 0)
        return hash[right];
    return (hash[right] - (hash[left - 1] * powp[right - left + 1]) % CONST_M +
            CONST_M) %
           CONST_M;
}


int main() {
    std::iostream::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::string s;
    uint32_t m, a, b, c, d;
    std::cin >> s >> m;

    std::vector<uint64_t> hash(s.size()), powp(s.size());
    init(s, hash, powp);

    for (size_t i = 0; i < m; ++i) {
        std::cin >> a >> b >> c >> d;
        std::cout << (get_hash(hash, powp, a - 1, b - 1) ==
                      get_hash(hash, powp, c - 1, d - 1)
                      ? "Yes\n"
                      : "No\n");
    }

    return 0;
}
