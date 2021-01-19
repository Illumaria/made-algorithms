#include <bits/stdc++.h>

class CyclicDynamicArray {
 public:
  CyclicDynamicArray()
      : capacity_(4), begin_(0), end_(0), values_(new int64_t[capacity_]) {}

  ~CyclicDynamicArray() { delete[] values_; }

  // Increase capacity of the CyclicDynamicArray.
  void IncreaseCapacity() {
    end_ = this->size();
    capacity_ *= 2;
    auto new_values = new int64_t[capacity_];
    for (size_t i = 0; i < end_; ++i)
      new_values[i] = values_[(i + begin_) % (capacity_ / 2)];
    delete[] values_;
    values_ = new_values;
    begin_ = 0;
  }

  // Decrease capacity of the CyclicDynamicArray.
  void DecreaseCapacity() {
    end_ = this->size();
    capacity_ /= 2;
    int64_t* new_values = new int64_t[capacity_];
    for (size_t i = 0; i < end_; ++i)
      new_values[i] = values_[(i + begin_) % (capacity_ * 2)];
    delete[] values_;
    values_ = new_values;
    begin_ = 0;
  }

  // Add new element to the CyclicDynamicArray.
  void add(int64_t value) {
    if ((end_ + 1) % capacity_ == begin_) this->IncreaseCapacity();
    values_[end_] = value;
    end_ = (end_ + 1) % capacity_;
  }

  // Get element of the CyclicDynamicArray by index.
  int64_t get(size_t index) {
    if (index < 0 || index >= size()) return 0;
    return values_[(begin_ + index) % capacity_];
  }

  // Remove the last element from the CyclicDynamicArray.
  void remove() {
    begin_ = (begin_ + 1) % capacity_;
    if (size() - 1 < capacity_ / 4) this->DecreaseCapacity();
  }

  // Get size of the CyclicDynamicArray.
  size_t size() {
    return (end_ >= begin_) ? (end_ - begin_) : (capacity_ - begin_ + end_);
  }

 private:
  size_t capacity_, begin_, end_;
  int64_t* values_;
};

class Queue {
 public:
  // Add new element to the end of the Queue.
  void push(int64_t value) { values_.add(value); }

  // Remove the first element from the Queue.
  void pop() { values_.remove(); }

  // Peek at the first element of the Queue.
  int64_t front() { return values_.get(0); }

 private:
  CyclicDynamicArray values_;
};

int main() {
  std::iostream::sync_with_stdio(false);
  std::cin.tie(nullptr);

  uint32_t m;
  std::cin >> m;

  Queue queue;

  char c;
  int64_t num;
  for (; m > 0; --m) {
    std::cin >> c;

    switch (c) {
      case '+':
        std::cin >> num;
        queue.push(num);
        break;
      case '-':
        std::cout << queue.front() << '\n';
        queue.pop();
        break;
      default:
        break;
    }
  }

  return 0;
}
