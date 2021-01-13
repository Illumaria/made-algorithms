#include <bits/stdc++.h>

class CyclicDynamicArray {
 public:
  CyclicDynamicArray()
      : capacity(4), begin(0), end(0), values(new int64_t[capacity]) {}

  ~CyclicDynamicArray() { delete[] values; }

  // Increase capacity of the CyclicDynamicArray:
  void increaseCapacity() {
    end = getSize();
    capacity *= 2;
    int64_t* newValues = new int64_t[capacity];
    for (size_t i = 0; i < end; ++i)
      newValues[i] = values[(i + begin) % (capacity / 2)];
    delete[] values;
    values = newValues;
    begin = 0;
  }

  // Decrease capacity of the CyclicDynamicArray:
  void decreaseCapacity() {
    end = getSize();
    capacity /= 2;
    int64_t* newValues = new int64_t[capacity];
    for (size_t i = 0; i < end; ++i)
      newValues[i] = values[(i + begin) % (capacity * 2)];
    delete[] values;
    values = newValues;
    begin = 0;
  }

  // Add new element to the CyclicDynamicArray:
  void add(int64_t value) {
    if ((end + 1) % capacity == begin) increaseCapacity();
    values[end] = value;
    end = (end + 1) % capacity;
  }

  // Get element of the CyclicDynamicArray by index:
  int64_t get(size_t index) {
    if (index < 0 || index >= getSize()) return NULL;
    return values[(begin + index) % capacity];
  }

  // Remove the last element from the CyclicDynamicArray:
  void remove() {
    begin = (begin + 1) % capacity;
    if (getSize() - 1 < capacity / 4) decreaseCapacity();
  }

  // Get size of the CyclicDynamicArray:
  size_t getSize() {
    return (end >= begin) ? (end - begin) : (capacity - begin + end);
  }

 private:
  size_t capacity, begin, end;
  int64_t* values;
};

class Queue {
 public:
  // Add new element to the end of the Queue:
  void push(int64_t value) { values.add(value); }

  // Remove the first element from the Queue:
  void pop() { values.remove(); }

  // Peek at the first element of the Queue:
  int64_t front() { return values.get(0); }

 private:
  CyclicDynamicArray values;
};

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(0);

  uint32_t m;
  std::cin >> m;

  Queue queue;

  char ch;
  int64_t num;
  for (; m > 0; --m) {
    std::cin >> ch;

    switch (ch) {
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
