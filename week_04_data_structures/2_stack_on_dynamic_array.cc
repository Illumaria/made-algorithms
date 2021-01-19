#include <bits/stdc++.h>

class DynamicArray {
 public:
  DynamicArray() : capacity_(1), size_(0), values_(new int64_t[capacity_]) {}

  ~DynamicArray() { delete[] values_; }

  // Increase capacity of the DynamicArray.
  void IncreaseCapacity() {
    capacity_ *= 2;
    int64_t* new_values = new int64_t[capacity_];
    for (size_t i = 0; i < size_; ++i) new_values[i] = values_[i];
    delete[] values_;
    values_ = new_values;
  }

  // Decrease capacity of the DynamicArray.
  void DecreaseCapacity() {
    capacity_ /= 2;
    int64_t* new_values = new int64_t[capacity_];
    for (size_t i = 0; i < size_; ++i) new_values[i] = values_[i];
    delete[] values_;
    values_ = new_values;
  }

  // Add new element to the DynamicArray.
  void add(int64_t value) {
    if (size_ + 1 > capacity_) this->IncreaseCapacity();
    values_[size_] = value;
    ++size_;
  }

  // Get element of the DynamicArray by index.
  int64_t get(size_t index) {
    if (index < 0 || index >= size_) return 0;
    return values_[index];
  }

  // Remove the last element from the DynamicArray.
  void remove() {
    if (size_ - 1 < capacity_ / 4) this->DecreaseCapacity();
    --size_;
  }

  // Get size of the DynamicArray.
  size_t size() { return size_; }

 private:
  size_t capacity_, size_;
  int64_t* values_;
};

class Stack {
 public:
  // Add new element to the end of the Stack.
  void push(int64_t value) { values_.add(value); }

  // Remove the last element from the Stack.
  void pop() { values_.remove(); }

  // Peek at the last element in the Stack.
  int64_t back() { return values_.get(values_.size() - 1); }

 private:
  DynamicArray values_;
};

int main() {
  std::iostream::sync_with_stdio(false);
  std::cin.tie(nullptr);

  std::string s;
  std::getline(std::cin, s);
  std::stringstream iss(s);

  Stack stack;

  char c;
  while (iss >> c) {
    if (isdigit(c)) {
      stack.push(c - '0');
    } else {
      auto val_2 = stack.back();
      stack.pop();
      auto val_1 = stack.back();
      stack.pop();

      switch (c) {
        case '+':
          stack.push(val_1 + val_2);
          break;
        case '-':
          stack.push(val_1 - val_2);
          break;
        case '*':
          stack.push(val_1 * val_2);
          break;
        default:
          break;
      }
    }
  }
  std::cout << stack.back() << "\n";

  return 0;
}
