#include <bits/stdc++.h>


class Treap {
 private:
    struct Node {
        uint32_t value;
        size_t priority;
        uint32_t size;
        Node* left;
        Node* right;

        explicit Node(const uint32_t& value, const size_t& priority)
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
             const uint32_t& priority) {
        Node *t1, *t2;
        std::tie(t1, t2) = split(root, pos);

        auto newNode = new Node(value, priority);

        t1 = merge(t1, newNode);
        root = merge(t1, t2);
    }

    void remove(const uint32_t& pos) {
        Node *left, *mid, *right;

        std::tie(left, right) = split(root, pos);
        std::tie(mid, right) = split(right, 1);

        root = merge(left, right);
    }

    void update(Node*& t) {
        t->size = 1 + getSize(t->left) + getSize(t->right);
    }

    std::pair<Node*, Node*> split(Node*& t, const uint32_t& pos) {
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

    void moveToStart(const uint32_t& left_pos, const uint32_t& right_pos) {
        Node *left, *mid, *right;
        std::tie(left, mid) = split(root, left_pos);
        std::tie(mid, right) = split(mid, right_pos - left_pos);

        left = merge(mid, left);
        root = merge(left, right);
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

    uint32_t n, m;
    std::cin >> n >> m;

    Treap trp;
    for (uint32_t i = 0; i < n; ++i)
        trp.add(i, i + 1, std::rand());

    uint32_t left_pos, right_pos;
    for (size_t i = 0; i < m; ++i) {
        std::cin >> left_pos >> right_pos;
        trp.moveToStart(left_pos - 1, right_pos);
    }

    trp.printArray(trp.getRoot());

    return 0;
}
