#include <bits/stdc++.h>


#define MAX_VALUE 1e9 + 1


class LinkedList {
    struct Node {
        Node(const int64_t& x, Node *head): value(x), next(head) {}

        ~Node() {}

        int64_t value;
        Node *next;
    };

 public:
    LinkedList(): head(nullptr), size(0) {}

    ~LinkedList() {
        Node *current = head;

        while (current != nullptr) {
            Node *nodeToDelete = current;
            current = current->next;
            delete nodeToDelete;
        }
    }

    // Add new element to the start of LinkedList:
    void push(int64_t value) {
        Node *new_node = new Node(value, head);
        head = new_node;
        ++size;
    }

    // Remove the first element of the LinkedList:
    void pop() {
        if (size > 0) {
            Node *current = head;
            head = head->next;
            delete current;
            --size;
        }
    }

    // Peek at the first element of the LinkedList:
    int64_t back() {
        if (size > 0)
            return head->value;
        return MAX_VALUE;
    }

 private:
    Node *head;
    size_t size;
};


class Stack {
 public:
    Stack(): current_min(MAX_VALUE) {}

    // Add new element to the end of the Stack:
    void push(int64_t value) {
        values.push(value);
        if (value <= current_min) {
            current_min = value;
            min_values.push(current_min);
        }
    }

    // Remove the last element from the end of the Stack:
    void pop() {
        if (values.back() == min_values.back())
            min_values.pop();
        values.pop();
        current_min = min_values.back();
    }

    // Get the minimum value in the Stack:
    int64_t getMin() {
        return min_values.back();
    }

 private:
    LinkedList values, min_values;
    int64_t current_min;
};


int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);

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
                std::cout << stack.getMin() << '\n';
                break;
            default:
                break;
        }
    }

    return 0;
}
