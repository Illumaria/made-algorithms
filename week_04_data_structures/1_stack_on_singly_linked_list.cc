#include <bits/stdc++.h>

// The maximum value of a data structure element.
const int64_t kMaxValue = 1e9 + 1;

class LinkedList {
 public:
  LinkedList() : head_(nullptr), size_(0) {}

  ~LinkedList() {
    auto current = head_;
 
    while (current != nullptr) {
      const auto node_to_delete = current;
      current = current->next;
      delete node_to_delete;
    }
  }

  // Add new element to the start of LinkedList.
  void push(int64_t value) {
    Node* new_node = new Node(value, head_);
    head_ = new_node;
    ++size_;
  }

  // Remove the first element of the LinkedList.
  void pop() {
    if (size_ > 0) {
      const auto current = head_;
      head_ = head_->next;
      delete current;
      --size_;
    }
  }

  // Peek at the first element of the LinkedList.
  int64_t back() {
    if (size_ > 0) return head_->value;
    return kMaxValue;
  }

 private:
  struct Node {
    Node(int64_t value, Node* next) : value(value), next(next) {}
    ~Node() {}

    int64_t value;
    Node* next;
  };

  Node* head_;
  size_t size_;
};

class Stack {
 public:
  Stack() : current_min_(kMaxValue) {}

  // Add new element to the end of the Stack.
  void push(int64_t value) {
    values_.push(value);
    if (value <= current_min_) {
      current_min_ = value;
      min_values_.push(current_min_);
    }
  }

  // Remove the last element from the end of the Stack.
  void pop() {
    if (values_.back() == min_values_.back()) min_values_.pop();
    values_.pop();
    current_min_ = min_values_.back();
  }

  // Get the minimum value in the Stack.
  int64_t get_min() { return min_values_.back(); }

 private:
  LinkedList values_, min_values_;
  int64_t current_min_;
};

int main() {
  std::iostream::sync_with_stdio(false);
  std::cin.tie(nullptr);

  uint32_t n;
  std::cin >> n;

  uint16_t operation;
  int64_t x;
  Stack stack;
  for (; n > 0; --n) {
    std::cin >> operation;

    switch (operation) {
      case 1:
        std::cin >> x;
        stack.push(x);
        break;
      case 2:
        stack.pop();
        break;
      case 3:
        std::cout << stack.get_min() << "\n";
        break;
      default:
        break;
    }
  }

  return 0;
}
