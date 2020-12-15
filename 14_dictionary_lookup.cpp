#include <bits/stdc++.h>


#define ALPHABET_SIZE 26


class Trie {
 private:
    size_t vertices_num;
    size_t words_num;
    std::vector<std::vector<int32_t>> next;
    std::vector<int32_t> isTerminal;

 public:
    Trie() : vertices_num(1),
             words_num(0),
             next(1, std::vector<int32_t>(ALPHABET_SIZE, -1)),
             isTerminal(1, -1) {}

    void insert(const std::string& s) {
        int32_t v = 0;
        for (size_t i = 0; i < s.size(); ++i) {
            if (next[v][s[i] - 'a'] == -1) {
                next[v][s[i] - 'a'] = vertices_num;
                next.emplace_back(std::vector<int32_t>(ALPHABET_SIZE, -1));
                isTerminal.emplace_back(-1);
                ++vertices_num;
            }
            v = next[v][s[i] - 'a'];
        }
        isTerminal[v] = words_num++;
    }

    void contains(const std::string& s, std::vector<bool>& used) {
        for (size_t start = 0; start < s.size(); ++start) {
            int32_t v = 0;
            for (size_t i = start; i < s.size(); ++i) {
                if (isTerminal[v] != -1)
                    used[isTerminal[v]] = true;
                if (next[v][s[i] - 'a'] == -1)
                    break;
                v = next[v][s[i] - 'a'];
            }

            if (isTerminal[v] != -1)
                used[isTerminal[v]] = true;
        }
    }

    size_t getWordsNum() const {
        return words_num;
    }
};


int main() {
    std::iostream::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::string text;
    uint32_t m;
    std::cin >> text >> m;

    Trie trie;
    std::string word;
    for (size_t i = 0; i < m; ++i) {
        std::cin >> word;
        trie.insert(word);
    }

    std::vector<bool> used(trie.getWordsNum(), false);
    trie.contains(text, used);

    for (size_t i = 0; i < used.size(); ++i)
        std::cout << (used[i] ? "Yes\n" : "No\n");

    return 0;
}
