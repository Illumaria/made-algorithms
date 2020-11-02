#include <bits/stdc++.h>


#define MOD static_cast<int64_t>(1e9)
#define MAX_VALUE ((1LL << 63) - 1)
#define MIN_VALUE (1LL << 63)


class AVLTree {
 private:
    struct Node {
        int64_t key;
        int64_t min, max;
        int64_t sum;
        uint8_t height;
        Node* left;
        Node* right;

        explicit Node(const int64_t& x)
            : key(x),
              min(x),
              max(x),
              sum(0),
              height(1),
              left(nullptr),
              right(nullptr) {}
    };
    Node* root;

 public:
    AVLTree() : root(nullptr) {}

    Node*& getRoot() {
        return root;
    }

    int64_t getMin(const Node* v) const {
        return v != nullptr ? v->min : MAX_VALUE;
    }

    int64_t getMax(const Node* v) const {
        return v != nullptr ? v->max : MIN_VALUE;
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

    void fixMinMax(Node*& v) {
        v->min = std::min(std::min(getMin(v->left), getMin(v->right)), v->key);
        v->max = std::max(std::max(getMax(v->left), getMax(v->right)), v->key);
    }

    void fixSum(Node*& v) {
        v->sum = 0;
        if (v->left != nullptr)
            v->sum += v->left->sum + v->left->key;
        if (v->right != nullptr)
            v->sum += v->right->sum + v->right->key;
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

    Node* balance(Node*& v) {
        fixHeight(v);
        fixSum(v);
        fixMinMax(v);

        if (diffHeight(v) == 2) {
            if (diffHeight(v->right) < 0)
                v->right = rotateRight(v->right);
            v = rotateLeft(v);
        }

        if (diffHeight(v) == -2) {
            if (diffHeight(v->left) > 0)
                v->left = rotateLeft(v->left);
            v = rotateRight(v);
        }

        return v;
    }

    Node* rotateRight(Node*& p) {
        Node* q = p->left;
        p->left = q->right;
        q->right = p;

        fixHeight(p);
        fixSum(p);
        fixMinMax(p);

        fixHeight(q);
        fixSum(q);
        fixMinMax(q);

        return q;
    }

    Node* rotateLeft(Node*& q) {
        Node* p = q->right;
        q->right = p->left;
        p->left = q;

        fixHeight(q);
        fixSum(q);
        fixMinMax(q);

        fixHeight(p);
        fixSum(p);
        fixMinMax(p);

        return p;
    }

    int64_t sum(const Node* v,
                const int64_t& left,
                const int64_t& right) const {
        if (v == nullptr)
            return 0;

        if (v->key > right)
            return sum(v->left, left, right);

        if (v->key < left)
            return sum(v->right, left, right);

        if (v->left == nullptr && v->right == nullptr)
            return v->key;

        if (v->min >= left && v->max <= right)
            return v->sum + v->key;

        return sum(v->left, left, right) + sum(v->right, left, right) + v->key;
    }

    void printTree(const Node* v, std::string indent) {
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

    uint32_t n;
    std::cin >> n;

    AVLTree avlt;

    char command, last_command = '+';
    int64_t x, left, right, result = 0;
    for (size_t i = 0; i < n; ++i) {
        std::cin >> command;
        if (command == '+') {
            std::cin >> x;
            if (last_command == '?')
                avlt.insert(avlt.getRoot(), (x + result) % MOD);
            else
                avlt.insert(avlt.getRoot(), x);
            // avlt.printTree(avlt.getRoot(), "");
        } else if (command == '?') {
            std::cin >> left >> right;
            result = avlt.sum(avlt.getRoot(), left, right);
            std::cout << result << "\n";
        }
        last_command = command;
    }

    return 0;
}
