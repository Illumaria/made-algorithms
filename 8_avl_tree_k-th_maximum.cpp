#include <bits/stdc++.h>

class AVLTree {
 private:
  struct Node {
    int64_t key;
    uint8_t height;
    uint32_t size;
    Node* left;
    Node* right;

    explicit Node(const int64_t& x)
        : key(x), height(1), size(1), left(nullptr), right(nullptr) {}
  };
  Node* root;

 public:
  AVLTree() : root(nullptr) {}

  Node*& getRoot() { return root; }

  uint8_t getHeight(const Node* v) const {
    return v != nullptr ? v->height : 0;
  }

  uint32_t getSize(const Node* v) const { return v != nullptr ? v->size : 0; }

  int8_t diffHeight(const Node* v) const {
    return getHeight(v->right) - getHeight(v->left);
  }

  void fixHeight(Node*& v) {
    v->height = std::max(getHeight(v->left), getHeight(v->right)) + 1;
  }

  void fixSize(Node*& v) {
    if (v != nullptr) v->size = 1 + getSize(v->left) + getSize(v->right);
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
    fixSize(v);

    if (diffHeight(v) == 2) {
      if (diffHeight(v->right) < 0) v->right = rotateRight(v->right);
      v = rotateLeft(v);
    }

    if (diffHeight(v) == -2) {
      if (diffHeight(v->left) > 0) v->left = rotateLeft(v->left);
      v = rotateRight(v);
    }

    return v;
  }

  Node* remove(Node*& v, const int64_t& x) {
    if (v == nullptr) return nullptr;

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
    while (v->left != nullptr) v = v->left;
    return v;
  }

  Node* removeMin(Node* v) {
    if (v->left == nullptr) return v->right;
    v->left = removeMin(v->left);

    return balance(v);
  }

  Node* rotateRight(Node*& p) {
    Node* q = p->left;
    p->left = q->right;
    q->right = p;

    fixHeight(p);
    fixSize(p);

    fixHeight(q);
    fixSize(q);

    return q;
  }

  Node* rotateLeft(Node*& q) {
    Node* p = q->right;
    q->right = p->left;
    p->left = q;

    fixHeight(q);
    fixSize(q);

    fixHeight(p);
    fixSize(p);

    return p;
  }

  int64_t findKthMax(Node*& v, uint32_t k) {
    uint32_t left_size = getSize(v->left);
    if (left_size == k) {
      return v->key;
    } else if (left_size > k) {
      return findKthMax(v->left, k);
    } else {
      k -= left_size + 1;
      return findKthMax(v->right, k);
    }
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

  uint32_t n;
  std::cin >> n;

  AVLTree avlt;

  int16_t command;
  int64_t x;
  uint32_t k;
  for (size_t i = 0; i < n; ++i) {
    std::cin >> command;
    if (command == 1) {
      std::cin >> x;
      avlt.insert(avlt.getRoot(), x);
      // avlt.printTree(avlt.getRoot(), "");
    } else if (command == 0) {
      std::cin >> k;
      std::cout << avlt.findKthMax(avlt.getRoot(),
                                   avlt.getSize(avlt.getRoot()) - k)
                << "\n";
    } else if (command == -1) {
      std::cin >> x;
      avlt.remove(avlt.getRoot(), x);
      // avlt.printTree(avlt.getRoot(), "");
    }
  }

  return 0;
}
