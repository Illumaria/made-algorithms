#include <bits/stdc++.h>

class BinaryHeap {
 public:
  struct Element {
    int64_t value;
    ssize_t id;
  };

  BinaryHeap() { operations_.emplace_back(-1); }

  ~BinaryHeap() {}

  // Insert new element to the BinaryHeap.
  void Insert(int64_t value, ssize_t ops_num) {
    values_.push_back({value, ops_num});
    operations_.emplace_back(values_.size() - 1);
    this->SiftUp(values_.size() - 1);
  }

  // Sift the BinaryHeap up.
  void SiftUp(size_t i) {
    while (i > 0 && values_[i].value < values_[(i - 1) / 2].value) {
      std::swap(operations_[values_[i].id],
                operations_[values_[(i - 1) / 2].id]);
      std::swap(values_[i], values_[(i - 1) / 2]);
      i = (i - 1) / 2;
    }
  }

  // Sift the BinaryHeap down.
  void SiftDown(size_t i) {
    size_t left, right, j;
    while (2 * i + 1 < values_.size()) {
      left = 2 * i + 1;
      right = 2 * i + 2;
      j = left;

      if (right < values_.size() && values_[right].value < values_[left].value)
        j = right;
      if (values_[i].value <= values_[j].value) break;
      std::swap(operations_[values_[i].id], operations_[values_[j].id]);
      std::swap(values_[i], values_[j]);
      i = j;
    }
  }

  // Extract the first (minimum) element from the BinaryHeap.
  Element ExtractMin() {
    operations_.emplace_back(-1);

    if (values_.empty()) return {-1, -1};

    auto min_value = values_[0].value;
    auto min_id = values_[0].id;
    std::swap(operations_[min_id],
              operations_[values_[values_.size() - 1].id]);
    operations_[min_id] = -1;
    std::swap(values_[0], values_[values_.size() - 1]);
    values_.pop_back();
    this->SiftDown(0);

    return {min_value, min_id};
  }

  // Set the element added by operation with number "id" to "value".
  void DecreaseKey(size_t id, int64_t value) {
    operations_.emplace_back(-1);

    if (operations_[id] != -1) {
      values_[operations_[id]].value = value;
      this->SiftUp(operations_[id]);
    }
  }

 private:
  std::vector<Element> values_;
  std::vector<ssize_t> operations_;
};

int main() {
  std::iostream::sync_with_stdio(false);
  std::cin.tie(nullptr);

  BinaryHeap heap;

  std::string s, token_1, token_2;
  int64_t result;
  size_t ops_count = 1, result_num;
  while (std::getline(std::cin, s)) {
    if (s.empty()) break;

    std::stringstream iss(s);
    iss >> token_1;
    if (token_1 == "push") {
      iss >> token_1;
      heap.Insert(std::stoll(token_1), ops_count);
    } else if (token_1 == "extract-min") {
      auto result = heap.ExtractMin();
      if (result.id == -1)
        std::cout << "*\n";
      else
        std::cout << result.value << " " << result.id << "\n";
    } else if (token_1 == "decrease-key") {
      iss >> token_1 >> token_2;
      heap.DecreaseKey(std::stoll(token_1), std::stoll(token_2));
    }
    ++ops_count;
  }

  return 0;
}
