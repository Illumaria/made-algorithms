#include <bits/stdc++.h>


#define RADIX 26
#define OFFSET 97


uint64_t count_substrings(const std::string& s, const std::string& t) {
    int64_t t_chars[RADIX];
    std::fill(t_chars, t_chars + RADIX, -1);

    for (size_t i = 0; i < t.length(); ++i) {
        if (t_chars[t[i] - OFFSET] == -1)
            t_chars[t[i] - OFFSET] += 2;
        else
            ++t_chars[t[i] - OFFSET];
    }

    uint32_t i = 0, j = 0;
    uint64_t result = 0;
    while (j < s.length()) {
        if (t_chars[s[j] - OFFSET] > 0) {
            --t_chars[s[j] - OFFSET];
            result += j - i + 1;
        } else if (t_chars[s[j] - OFFSET] == 0) {
            while (t_chars[s[j] - OFFSET] == 0)
                ++t_chars[s[i++] - OFFSET];
            result += j - i + 1;
            --t_chars[s[j] - OFFSET];
        } else {
            while (i < j)
                ++t_chars[s[i++] - OFFSET];
            ++i;
        }
        ++j;
    }

    return result;
}


int main() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);

    // Read values:
    uint32_t n, m;
    std::cin >> n >> m;

    std::string s, t;
    std::cin >> s >> t;

    // Count substrings and print the result:
    std::cout << count_substrings(s, t) << '\n';

    return 0;
}
