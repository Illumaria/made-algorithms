#include <bits/stdc++.h>

class DynamicArray {
 public:
  DynamicArray() : capacity(1), size(0), values(new int64_t[capacity]) {}

  ~DynamicArray() { delete[] values; }

  // Increase capacity of the DynamicArray:
  void increaseCapacity() {
    capacity *= 2;
    int64_t* newValues = new int64_t[capacity];
    for (size_t i = 0; i < size; ++i) newValues[i] = values[i];
    delete[] values;
    values = newValues;
  }

  // Decrease capacity of the DynamicArray:
  void decreaseCapacity() {
    capacity /= 2;
    int64_t* newValues = new int64_t[capacity];
    for (size_t i = 0; i < size; ++i) newValues[i] = values[i];
    delete[] values;
    values = newValues;
  }

  // Add new element to the DynamicArray:
  void add(int64_t value) {
    if (size + 1 > capacity) this->increaseCapacity();
    values[size] = value;
    ++size;
  }

  // Get element of the DynamicArray by index:
  int64_t get(size_t index) {
    if (index < 0 || index >= size) return NULL;
    return values[index];
  }

  // Remove the last element from the DynamicArray:
  void remove() {
    if (size - 1 < capacity / 4) this->decreaseCapacity();
    --size;
  }

  // Get size of the DynamicArray:
  size_t getSize() { return size; }

 private:
  size_t capacity, size;
  int64_t* values;
};

class Stack {
 public:
  // Add new element to the end of the Stack:
  void push(int64_t value) { values.add(value); }

  // Remove the last element from the Stack:
  void pop() { values.remove(); }

  // Peek at the last element in the Stack:
  int64_t back() { return values.get(values.getSize() - 1); }

 private:
  DynamicArray values;
};

int main() {
  std::string s;
  std::getline(std::cin, s);
  std::stringstream iss(s);

  Stack stack;

  char c;
  while (iss >> c) {
    if (isdigit(c)) {
      stack.push(c - '0');
    } else {
      int64_t val2 = stack.back();
      stack.pop();
      int64_t val1 = stack.back();
      stack.pop();

      switch (c) {
        case '+':
          stack.push(val1 + val2);
          break;
        case '-':
          stack.push(val1 - val2);
          break;
        case '*':
          stack.push(val1 * val2);
          break;
        default:
          break;
      }
    }
  }
  std::cout << stack.back() << '\n';

  return 0;
}
