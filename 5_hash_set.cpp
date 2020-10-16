#include <bits/stdc++.h>


#define CONST_A 31
#define PRIME_P size_t(1e9 + 7)
#define INIT_SIZE 2


size_t hash(const std::string& key, const size_t& m) {
    size_t result = 0;
    for (const auto& ch : key)
        result = (CONST_A * result + ch) % PRIME_P;
    return result % m;
}


class Set {
    struct Item {
        Item(): key(""), empty(true) {}
        std::string key;
        bool empty;
    };

 public:
    Set(): m(INIT_SIZE), size(0), set(new Item[INIT_SIZE]) {}

    void _insert(const std::string& key) {
        if (size + 1 > m / 2)
            rehash();

        size_t i = hash(key, m);

        while (!set[i].empty) {
            if (!set[i].empty && set[i].key == key)
                return;
            i = (i + 1) % m;
        }
        ++size;
        set[i].key = key;
        set[i].empty = false;
    }

    bool _exists(const std::string& key) {
        size_t i = hash(key, m);
        while (!set[i].empty) {
            if (set[i].key == key)
                return true;
            i = (i + 1) % m;
        }

        return false;
    }

    void _delete(const std::string& key) {
        size_t i = hash(key, m);
        bool deleted = false;
        while (!set[i].empty) {
            if (set[i].key == key) {
                set[i].empty = true;
                deleted = true;
                size_t j = (i + 1) % m;
                while (!set[j].empty) {
                    if (hash(set[j].key, m) <= i) {
                        std::swap(set[i], set[j]);
                        i = j;
                        break;
                    }
                    j = (j + 1) & m;
                }
            }
            i = (i + 1) % m;
        }
        if (deleted)
            --size;
    }

    void rehash() {
        m *= 2;
        Item* newSet = new Item[m];
        size_t j;
        for (size_t i = 0; i < m / 2; ++i)
            if (!set[i].empty) {
                j = hash(set[i].key, m);
                while (!newSet[j].empty)
                    j = (j + 1) % m;
                newSet[j].key = set[i].key;
                newSet[j].empty = false;
            }
        delete[] set;
        set = newSet;
    }

 private:
    Item* set;
    size_t size, m;
};


int main() {
    // std::ios::sync_with_stdio(false);
    // std::cin.tie(0);
 
    Set set;
 
    std::string s;
    int64_t key;
    while (std::cin >> s >> key) {
        if (s == "insert") {
            set._insert(std::to_string(key));
        } else if (s == "exists") {
            (set._exists(std::to_string(key))) ? std::cout << "true\n" : std::cout << "false\n";
        } else if (s == "delete") {
            set._delete(std::to_string(key));
        }
    }

    return 0;
}
