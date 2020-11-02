#include <bits/stdc++.h>


class AVLTree {
 private:
    struct Node {
        int64_t key;
        uint8_t height;
        Node* left;
        Node* right;

        explicit Node(const int64_t& x)
            : key(x), left(nullptr), right(nullptr), height(1) {}
    };
    Node* root;

 public:
    AVLTree() : root(nullptr) {}

    Node*& getRoot() {
        return root;
    }

    uint8_t getHeight(const Node* v) const {
        return v != nullptr ? v->height : 0;
    }

    int8_t diffHeight(const Node* v) const {
        return getHeight(v->right) - getHeight(v->left);
    }

    void fixHeight(Node*& v) {
        v->height = std::max(getHeight(v->left), getHeight(v->right)) + 1;
    }

    Node* search(Node*& v, const int64_t& x) {
        if (v == nullptr)
            return nullptr;

        if (v->key == x)
            return v;
        else if (x < v->key)
            return search(v->left, x);
        else
            return search(v->right, x);
    }

    Node* insert(Node*& v, const int64_t& x) {
        if (v == nullptr) {
            v = new Node(x);
            return v;
        }

        if (x < v->key)
            v->left = insert(v->left, x);
        else if (x > v->key)
            v->right = insert(v->right, x);

        return balance(v);
    }

    Node* balance(Node*& p) {
        fixHeight(p);

        if (diffHeight(p) == 2) {
            if (diffHeight(p->right) < 0)
                p->right = rotateRight(p->right);
            p = rotateLeft(p);
        }

        if (diffHeight(p) == -2) {
            if (diffHeight(p->left) > 0)
                p->left = rotateLeft(p->left);
            p = rotateRight(p);
        }

        return p;
    }

    Node* remove(Node*& v, const int64_t& x) {
        if (v == nullptr)
            return nullptr;

        if (x < v->key) {
            v->left = remove(v->left, x);
        } else if (x > v->key) {
            v->right = remove(v->right, x);
        } else {
            Node* left = v->left;
            Node* right = v->right;
            if (right == nullptr) {
                v = left;
                return v;
            }
            v = findMin(right);
            v->right = removeMin(right);
            v->left = left;
        }

        return balance(v);
    }

    Node* findMin(Node* v) {
        while (v->left != nullptr)
            v = v->left;
        return v;
    }

    Node* removeMin(Node* v) {
        if (v->left == nullptr)
            return v->right;
        v->left = removeMin(v->left);

        return balance(v);
    }

    Node* next(const int64_t& x) const {
        Node* v = root;
        Node* result = nullptr;

        while (v != nullptr) {
            if (v->key > x) {
                result = v;
                v = v->left;
            } else {
                v = v->right;
            }
        }

        return result;
    }

    Node* prev(const int64_t& x) const {
        Node* v = root;
        Node* result = nullptr;

        while (v != nullptr) {
            if (v->key < x) {
                result = v;
                v = v->right;
            } else {
                v = v->left;
            }
        }

        return result;
    }

    Node* rotateRight(Node*& p) {
        Node* q = p->left;
        p->left = q->right;
        q->right = p;

        fixHeight(p);

        fixHeight(q);

        return q;
    }

    Node* rotateLeft(Node*& q) {
        Node* p = q->right;
        q->right = p->left;
        p->left = q;

        fixHeight(q);

        fixHeight(p);

        return p;
    }

    void printTree(Node*& v, std::string indent) {
        if (v != nullptr) {
            printTree(v->left, indent + "  ");
            std::cout << indent << v->key << "\n";
            printTree(v->right, indent + "  ");
        }
    }
};


int main() {
    std::iostream::sync_with_stdio(false);
    std::cin.tie(nullptr);

    AVLTree avlt;

    std::string command;
    int64_t x;
    while (std::cin >> command >> x) {
        if (command == "insert") {
            avlt.insert(avlt.getRoot(), x);
            // avlt.printTree(avlt.getRoot(), "");
        } else if (command == "delete") {
            avlt.remove(avlt.getRoot(), x);
            // avlt.printTree(avlt.getRoot(), "");
        } else if (command == "exists") {
            avlt.search(avlt.getRoot(), x) != nullptr ? std::cout << "true\n"
                                                      : std::cout << "false\n";
        } else if (command == "next") {
            auto next = avlt.next(x);
            next == nullptr ? std::cout << "none\n"
                            : std::cout << next->key << "\n";
        } else if (command == "prev") {
            auto prev = avlt.prev(x);
            prev == nullptr ? std::cout << "none\n"
                            : std::cout << prev->key << "\n";
        }
    }

    return 0;
}
