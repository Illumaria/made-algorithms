#include <bits/stdc++.h>


#define PRIME_M size_t(200000)
#define MAX_SIZE PRIME_M
#define PRIME_P size_t(1e9 + 7)
#define CONST_A 31


size_t hash(const std::string& key) {
    size_t result = 0;
    for (size_t i = 0; i < key.length(); ++i)
        result = (CONST_A * result + size_t(key[i] - 'A')) % PRIME_P;
    return result % PRIME_M;
}


struct Item {
    Item(): prev(nullptr), next(nullptr), key(""), value("") {}
    Item(const std::string& key, const std::string& value,
         Item* prev, Item* next): key(key), value(value),
                                  prev(prev), next(next) {}

    std::string key;
    std::string value;
    Item* prev;
    Item* next;
};


class LinkedMap {
 public:
    LinkedMap(): last(nullptr) {}
 
    void _put(const std::string& key, const std::string& value) {
        size_t i = hash(key);
        for (auto& x : map[i])
            if (x->key == key) {
                x->value = value;
                return;
            }
        Item* item = new Item(key, value, last, nullptr);
        map[i].push_back(item);
        if (last) last->next = map[i].back();
        last = map[i].back();
    }

    std::string _get(const std::string& key) {
        size_t i = hash(key);
        for (const auto& x : map[i])
            if (x->key == key)
                return x->value;

        return "none";
    }

    std::string _prev(const std::string& key) {
        size_t i = hash(key);
        for (const auto& x : map[i])
            if ((x->key == key) && x->prev)
                return x->prev->value;

        return "none";
    }

    std::string _next(const std::string& key) {
        size_t i = hash(key);
        for (const auto& x : map[i])
            if ((x->key == key) && x->next)
                return x->next->value;

        return "none";
    }


    void _delete(const std::string& key) {
        size_t i = hash(key);
        for (auto& x : map[i])
            if (x->key == key) {
                if (x->prev) x->prev->next = x->next;
                if (x->next) x->next->prev = x->prev;
                if (x == last) last = x->prev;
                std::swap(x, map[i].back());
                map[i].pop_back();
                delete x;
                return;
            }
    }

 private:
    std::array<std::vector<Item*>, MAX_SIZE> map;
    Item* last;
};

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);

    LinkedMap map;

    std::string command, key, value;
    while (std::cin >> command >> key) {
        if (command == "put") {
            std::cin >> value;
            map._put(key, value);
        } else if (command == "get") {
            std::cout << map._get(key) << "\n";
        } else if (command == "delete") {
            map._delete(key);
        } else if (command == "prev") {
            std::cout << map._prev(key) << "\n";
        } else if (command == "next") {
            std::cout << map._next(key) << "\n";
        }
    }

    return 0;
}
