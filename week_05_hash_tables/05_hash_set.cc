#include <bits/stdc++.h>
 
 
#define A 2
#define P size_t(1e9 + 7)
#define M size_t(2e6)
 
 
size_t mod(const int64_t& a, const size_t& b) {
    int64_t r = a % b;
    if (r < 0) r += b;
    return r;
}
 
 
size_t hash(const int64_t& key) {
    return mod(A * key, P) % M;
}
 
 
class Set {
    struct Item {
        Item(): key(0), deleted(true), empty(true) {}
        int64_t key;
        bool deleted;
        bool empty;
    };
 
 public:
    void _insert(const int64_t& key) {
        size_t i = hash(key);
        while (!set[i].empty && !set[i].deleted) {
            if (set[i].key == key)
                return;
            i = (i + 1) % M;
        }
        set[i].key = key;
        set[i].deleted = false;
        set[i].empty = false;
    }
 
    bool _exists(const int64_t& key) {
        size_t i = hash(key);
        while (!set[i].empty) {
            if (set[i].key == key)
                return !set[i].deleted;
            i = (i + 1) % M;
        }
 
        return false;
    }
 
    void _delete(const int64_t& key) {
        size_t i = hash(key);
        while (!set[i].empty) {
            if (set[i].key == key) {
                set[i].deleted = true;
                return;
            }
            i = (i + 1) % M;
        }
    }
 
 private:
    std::array<Item, M> set;
};
 
 
int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);
 
    Set set;
 
    std::string s;
    int64_t key;
    while (std::cin >> s >> key) {
        if (s == "insert") {
            set._insert(key);
        } else if (s == "exists") {
            set._exists(key) ? std::cout << "true\n" : std::cout << "false\n";
        } else if (s == "delete") {
            set._delete(key);
        }
    }
 
    return 0;
}
