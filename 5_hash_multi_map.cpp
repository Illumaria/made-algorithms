#include <bits/stdc++.h>


#define A 31
#define P size_t(1e9 + 7)
#define MAP_M size_t(2e5)
#define INIT_SET_M 4


size_t hash(const std::string& key, const size_t& m) {
    size_t result = 0;
    for (const auto& ch : key)
        result = (A * result + ch) % P;
    return result % m;
}


class Set {
    struct Item {
        Item(): key(""), empty(true), deleted(false) {}
        std::string key;
        bool empty;
        bool deleted;
    };

 private:
    size_t capacity, alive_size, total_size;
    Item* set;

 public:
    Set(): capacity(INIT_SET_M), alive_size(0), total_size(0),
           set(new Item[INIT_SET_M]) {}

    void changeCapacity(bool increase) {
        size_t cur_capacity = capacity;
        increase ? capacity *= 2 : capacity /= 2;
        Item* newSet = new Item[capacity];
        for (size_t i = 0; i < cur_capacity; ++i)
            if (!set[i].empty && !set[i].deleted) {
                size_t j = hash(set[i].key, capacity);
                while (!newSet[j].empty)
                    j = (j + 1) % capacity;
                newSet[j].key = set[i].key;
                newSet[j].empty = false;
            }
        total_size = alive_size;
        delete[] set;
        set = newSet;
    }

    void _insert(const std::string& key) {
        size_t i = hash(key, capacity);
        while (!set[i].empty) {
            if (set[i].key == key && !set[i].deleted)
                return;
            i = (i + 1) % capacity;
        }
        set[i].key = key;
        set[i].empty = false;
        ++alive_size;
        ++total_size;

        if (total_size >= capacity / 2)
            changeCapacity(true);
    }

    void _delete(const std::string& key) {
        size_t i = hash(key, capacity);
        while (!set[i].empty) {
            if (set[i].key == key && !set[i].deleted) {
                set[i].deleted = true;
                --alive_size;
                break;
            }
            i = (i + 1) % capacity;
        }
        if (alive_size < capacity / 4 && capacity > INIT_SET_M)
            changeCapacity(false);
    }

    std::string getAll() const {
        std::string result;
        for (size_t i = 0; i < capacity; ++i)
            if (!set[i].empty && !set[i].deleted)
                result += set[i].key + " ";

        return result;
    }

    std::string getSize() const {
        return std::to_string(alive_size);
    }
};


class MultiMap {
 private:
    std::array<std::list<std::pair<std::string, Set>>, MAP_M> map;

 public:
    void _put(const std::string& key, const std::string& value) {
        size_t i = hash(key, MAP_M);
        for (auto& x : map[i])
            if (x.first == key) {
                x.second._insert(value);
                return;
            }
        map[i].push_back(std::make_pair(key, Set()));
        map[i].back().second._insert(value);
    }

    std::string _get(const std::string& key) {
        size_t i = hash(key, MAP_M);
        for (const auto& x : map[i])
            if (x.first == key)
                return x.second.getSize() + " " + x.second.getAll();
        return "0";
    }

    void _delete(const std::string& key, const std::string& value) {
        size_t i = hash(key, MAP_M);
        for (auto& x : map[i])
            if (x.first == key) {
                x.second._delete(value);
                return;
            }
    }

    void _deleteAll(const std::string& key) {
        size_t i = hash(key, MAP_M);
        for (auto& x : map[i])
            if (x.first == key) {
                std::swap(x, map[i].back());
                map[i].pop_back();
                return;
            }
    }
};


int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);

    MultiMap map;

    std::string command, key, value;
    while (std::cin >> command >> key) {
        if (command == "put") {
            std::cin >> value;
            map._put(key, value);
        } else if (command == "get") {
            std::cout << map._get(key) << "\n";
        } else if (command == "delete") {
            std::cin >> value;
            map._delete(key, value);
        } else if (command == "deleteall") {
            map._deleteAll(key);
        }
    }

    return 0;
}
