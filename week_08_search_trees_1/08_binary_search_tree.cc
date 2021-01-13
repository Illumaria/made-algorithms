#include <bits/stdc++.h>

class BinarySearchTree {
 private:
  struct Node {
    int64_t key;
    Node* left;
    Node* right;

    explicit Node(const int64_t& x) : key(x), left(nullptr), right(nullptr) {}
  };
  Node* root;

 public:
  BinarySearchTree() : root(nullptr) {}

  Node*& getRoot() { return root; }

  Node* search(Node*& v, const int64_t& x) {
    if (v == nullptr) return nullptr;

    if (v->key == x)
      return v;
    else if (x < v->key)
      return search(v->left, x);
    else
      return search(v->right, x);
  }

  Node* insert(Node*& v, const int64_t& x) {
    if (v == nullptr)
      v = new Node(x);
    else if (x < v->key)
      v->left = insert(v->left, x);
    else if (x > v->key)
      v->right = insert(v->right, x);

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

    return v;
  }

  Node* findMin(Node* v) {
    while (v->left != nullptr) v = v->left;
    return v;
  }

  Node* removeMin(Node* v) {
    if (v->left == nullptr) return v->right;
    v->left = removeMin(v->left);

    return v;
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

  BinarySearchTree bst;

  std::string command;
  int64_t x;
  while (std::cin >> command >> x) {
    if (command == "insert") {
      bst.insert(bst.getRoot(), x);
      // bst.printTree(bst.getRoot(), "");
    } else if (command == "delete") {
      bst.remove(bst.getRoot(), x);
      // bst.printTree(bst.getRoot(), "");
    } else if (command == "exists") {
      bst.search(bst.getRoot(), x) != nullptr ? std::cout << "true\n"
                                              : std::cout << "false\n";
    } else if (command == "next") {
      auto next = bst.next(x);
      next == nullptr ? std::cout << "none\n" : std::cout << next->key << "\n";
    } else if (command == "prev") {
      auto prev = bst.prev(x);
      prev == nullptr ? std::cout << "none\n" : std::cout << prev->key << "\n";
    }
  }

  return 0;
}
