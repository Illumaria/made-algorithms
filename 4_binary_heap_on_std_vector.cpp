#include <bits/stdc++.h>


class BinaryHeap {
 public:
    BinaryHeap() {
        operations.push_back(-1);
    }

    ~BinaryHeap() {}

    // Insert new element to the BinaryHeap:
    void insert(int64_t value, size_t ops_num) {
        values.push_back(std::make_pair(value, ops_num));
        operations.push_back(values.size() - 1);
        siftUp(values.size() - 1);
    }

    // Sift the BinaryHeap up:
    void siftUp(size_t i) {
        while (i > 0 && values[i].first < values[(i - 1) / 2].first) {
            std::swap(operations[values[i].second],
                      operations[values[(i - 1) / 2].second]);
            std::swap(values[i], values[(i - 1) / 2]);
            i = (i - 1) / 2;
        }
    }

    // Sift the BinaryHeap down:
    void siftDown(size_t i) {
        size_t left, right, j;
        while (2 * i + 1 < values.size()) {
            left = 2 * i + 1;
            right = 2 * i + 2;
            j = left;

            if (right < values.size()
                && values[right].first < values[left].first)
                j = right;
            if (values[i].first <= values[j].first)
                break;
            std::swap(operations[values[i].second],
                      operations[values[j].second]);
            std::swap(values[i], values[j]);
            i = j;
        }
    }

    // Extract the first (minimum) element from the BinaryHeap:
    std::pair<int64_t, ssize_t> extractMin() {
        operations.push_back(-1);

        if (values.size() == 0)
            return std::make_pair(-1, -1);

        int64_t min = values[0].first;
        size_t min_num = values[0].second;
        std::swap(operations[min_num],
                  operations[values[values.size() - 1].second]);
        operations[min_num] = -1;
        std::swap(values[0], values[values.size() - 1]);
        values.pop_back();
        siftDown(0);

        return std::make_pair(min, min_num);
    }

    // Set the element added by operation with number "id" to "value":
    void decreaseKey(size_t id, int64_t value) {
        operations.push_back(-1);

        if (operations[id] != -1) {
            values[operations[id]].first = value;
            siftUp(operations[id]);
        }
    }

 private:
    std::vector<std::pair<int64_t, size_t>> values;
    std::vector<ssize_t> operations;
};


int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);

    BinaryHeap heap;

    std::string s, token_1, token_2;
    int64_t result;
    size_t ops_count = 1, result_num;
    while (std::getline(std::cin, s)) {
        if (s.empty())
            break;

        std::stringstream iss(s);
        std::getline(iss, token_1, ' ');
        if (token_1 == "push") {
            std::getline(iss, token_1);
            heap.insert(std::stoll(token_1), ops_count);
        } else if (token_1 == "extract-min") {
            std::tie(result, result_num) = heap.extractMin();
            if (result_num == -1)
                std::cout << "*\n";
            else
                std::cout << result << " " << result_num << "\n";
        } else if (token_1 == "decrease-key") {
            std::getline(iss, token_1, ' ');
            std::getline(iss, token_2);
            heap.decreaseKey(std::stoll(token_1), std::stoll(token_2));
        }
        ++ops_count;
    }

    return 0;
}
