#include <bits/stdc++.h>


class Treap {
 private:
    struct Node {
        int64_t value;
        size_t priority;
        uint32_t size;
        Node* left;
        Node* right;

        explicit Node(const int64_t& value, const size_t& priority)
            : value(value),
              priority(priority),
              size(1),
              left(nullptr),
              right(nullptr) {}
    };
    Node* root;

 public:
    Treap() : root(nullptr) {}

    Node*& getRoot() {
        return root;
    }

    uint32_t getSize(const Node* t) {
        return t != nullptr ? t->size : 0;
    }

    void add(const uint32_t& pos,
             const uint32_t& value,
             const int64_t& priority) {
        Node *t1, *t2;
        std::tie(t1, t2) = split(root, pos);

        auto newNode = new Node(value, priority);

        t1 = merge(t1, newNode);
        root = merge(t1, t2);
    }

    void remove(const uint64_t& pos) {
        Node *left, *mid, *right;

        std::tie(left, right) = split(root, pos);
        std::tie(mid, right) = split(right, 1);

        root = merge(left, right);
    }

    std::pair<Node*, Node*> split(Node*& t, const int64_t& pos) {
        if (t == nullptr)
            return {nullptr, nullptr};

        Node *t1, *t2;
        if (getSize(t->left) >= pos) {
            std::tie(t1, t2) = split(t->left, pos);
            t->left = t2;
            update(t);
            return {t1, t};
        } else {
            std::tie(t1, t2) = split(t->right, pos - getSize(t->left) - 1);
            t->right = t1;
            update(t);
            return {t, t2};
        }
    }

    void update(Node*& t) {
        t->size = 1 + getSize(t->left) + getSize(t->right);
    }

    Node* merge(Node*& t1, Node*& t2) {
        if (t1 == nullptr)
            return t2;
        if (t2 == nullptr)
            return t1;

        if (t1->priority > t2->priority) {
            t1->right = merge(t1->right, t2);
            update(t1);
            return t1;
        } else {
            t2->left = merge(t1, t2->left);
            update(t2);
            return t2;
        }
    }

    void printArray(Node*& t) {
        if (t != nullptr) {
            printArray(t->left);
            std::cout << t->value << " ";
            printArray(t->right);
        }
    }
};


int main() {
    std::iostream::sync_with_stdio(false);
    std::cin.tie(nullptr);

    uint32_t n0, m;
    std::cin >> n0 >> m;

    Treap trp;
    int64_t x;
    for (size_t i = 0; i < n0; ++i) {
        std::cin >> x;
        trp.add(i, x, std::rand());
    }

    std::string command;
    uint32_t i;
    for (size_t j = 0; j < m; ++j) {
        std::cin >> command >> i;
        if (command == "add") {
            std::cin >> x;
            trp.add(i, x, std::rand());
        } else if (command == "del") {
            trp.remove(i - 1);
        }
    }

    std::cout << trp.getSize(trp.getRoot()) << "\n";
    trp.printArray(trp.getRoot());

    return 0;
}
