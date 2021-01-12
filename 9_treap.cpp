#include <bits/stdc++.h>

class Treap {
 private:
  struct Node {
    int64_t key;
    size_t priority;
    Node* left;
    Node* right;

    explicit Node(const int64_t& key, const size_t& priority)
        : key(key), priority(priority), left(nullptr), right(nullptr) {}
  };
  Node* root;

 public:
  Treap() : root(nullptr) {}

  Node*& getRoot() { return root; }

  Node* search(Node*& t, const int64_t& key) {
    if (t == nullptr) return nullptr;

    if (t->key > key)
      return search(t->left, key);
    else if (t->key < key)
      return search(t->right, key);
    else
      return t;
  }

  void insert(Node*& t, const int64_t& key, const int64_t& priority) {
    if (search(t, key) != nullptr) return;

    if (t == nullptr) {
      t = new Node(key, priority);
      return;
    }

    if (t->priority > priority) {
      if (t->key > key)
        insert(t->left, key, priority);
      else if (t->key < key)
        insert(t->right, key, priority);
      return;
    }

    Node *t1, *t2;
    std::tie(t1, t2) = split(t, key);

    auto newNode = new Node(key, priority);
    newNode->left = t1;
    newNode->right = t2;
    t = newNode;
  }

  void remove(Node*& t, const int64_t& x) {
    if (t != nullptr) {
      if (t->key > x)
        remove(t->left, x);
      else if (t->key < x)
        remove(t->right, x);
      else
        t = merge(t->left, t->right);
    }
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

  std::pair<Node*, Node*> split(Node*& t, const int64_t& x) {
    if (t == nullptr) return {nullptr, nullptr};

    Node *t1, *t2;
    if (t->key > x) {
      std::tie(t1, t2) = split(t->left, x);
      t->left = t2;
      return {t1, t};
    } else {
      std::tie(t1, t2) = split(t->right, x);
      t->right = t1;
      return {t, t2};
    }
  }

  Node* merge(Node*& t1, Node*& t2) {
    if (t1 == nullptr) return t2;
    if (t2 == nullptr) return t1;

    if (t1->priority > t2->priority) {
      t1->right = merge(t1->right, t2);
      return t1;
    } else {
      t2->left = merge(t1, t2->left);
      return t2;
    }
  }
};

int main() {
  std::iostream::sync_with_stdio(false);
  std::cin.tie(nullptr);

  Treap trp;

  std::string command;
  int64_t x;
  while (std::cin >> command >> x) {
    if (command == "insert") {
      trp.insert(trp.getRoot(), x, std::rand());
    } else if (command == "delete") {
      trp.remove(trp.getRoot(), x);
    } else if (command == "exists") {
      trp.search(trp.getRoot(), x) != nullptr ? std::cout << "true\n"
                                              : std::cout << "false\n";
    } else if (command == "next") {
      auto next = trp.next(x);
      next == nullptr ? std::cout << "none\n" : std::cout << next->key << "\n";
    } else if (command == "prev") {
      auto prev = trp.prev(x);
      prev == nullptr ? std::cout << "none\n" : std::cout << prev->key << "\n";
    }
  }

  return 0;
}
