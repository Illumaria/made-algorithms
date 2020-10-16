#include <bits/stdc++.h>


#define CONST_A 31
#define PRIME_P size_t(1e9 + 7)
#define INIT_SIZE 8


typedef std::vector<std::pair<std::string, std::string>> Item;


size_t hash(const std::string& key, const size_t& m) {
    size_t result = 0;
    for (const auto& ch : key)
        result = (CONST_A * result + ch) % PRIME_P;
    return result % m;
}

class Map {
 public:
    Map(): m(INIT_SIZE), size(0),
           map(new Item[INIT_SIZE]) {}

    void _put(const std::string& key, const std::string& value) {
        if (size + 1 > m / 2)
            rehash();

        size_t i = hash(key, m);
        for (auto& x : map[i])
            if (x.first == key) {
                x.second = value;
                return;
            }
        map[i].push_back(std::make_pair(key, value));
        ++size;
    }

    std::string _get(const std::string& key) {
        size_t i = hash(key, m);
        for (const auto& x : map[i])
            if (x.first == key)
                return x.second;

        return "none";
    }

    void _delete(const std::string& key) {
        size_t i = hash(key, m);
        for (auto& x : map[i])
            if (x.first == key) {
                std::swap(x, map[i].back());
                map[i].pop_back();
                break;
            }
    }

    void rehash() {
        m *= 2;
        Item* newMap = new Item[m];
        size_t j;
        for (size_t i = 0; i < m / 2; ++i)
            if (!map[i].empty()) {
                for (const auto& x : map[i]) {
                    j = hash(x.first, m);
                    newMap[j].push_back(std::make_pair(x.first, x.second));
                }
            }
        delete[] map;
        map = newMap;
    }

 private:
    Item* map;
    size_t m, size;
};


int main() {
    // std::ios::sync_with_stdio(false);
    // std::cin.tie(0);

    Map map;

    std::string command, key, value;
    while (std::cin >> command >> key) {
        if (command == "put") {
            std::cin >> value;
            map._put(key, value);
        } else if (command == "get") {
            std::cout << map._get(key) << "\n";
        } else if (command == "delete") {
            map._delete(key);
        }
    }

    return 0;
}
