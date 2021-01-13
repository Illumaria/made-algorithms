#include <bits/stdc++.h>

#define MAX_VALUE static_cast<int64_t>(1e18)

class SegmentTree {
 private:
  struct Node {
    uint32_t left;
    uint32_t right;
    int64_t val;
    int64_t add_val;
    int64_t set_val;
    bool updated;

    Node()
        : left(0),
          right(0),
          val(MAX_VALUE),
          add_val(0),
          set_val(MAX_VALUE),
          updated(false) {}
  };
  std::vector<Node> t;
  uint32_t n, m;

 public:
  explicit SegmentTree(uint32_t n) : n(n), m(1) {
    while (m < n) m *= 2;
    t.resize(2 * m - 1);
  }

  void build(const std::vector<int64_t>& a) {
    for (size_t i = 0; i < m; ++i) {
      t[m - 1 + i].val = i < n ? a[i] : MAX_VALUE;
      t[m - 1 + i].set_val = t[m - 1 + i].val;
      t[m - 1 + i].left = i;
      t[m - 1 + i].right = i;
    }

    if (m > 1) {
      for (ssize_t i = m - 2; i > -1; --i) {
        t[i].val = std::min(t[2 * i + 1].val, t[2 * i + 2].val);
        t[i].set_val = t[i].val;
        t[i].left = t[2 * i + 1].left;
        t[i].right = t[2 * i + 2].right;
      }
    }
  }

  void push_set(const uint32_t& v) {
    if (t[v].updated) {
      t[v].val = t[v].set_val;
      t[v].updated = false;

      if (t[v].left != t[v].right) {
        t[2 * v + 1].set_val = t[v].set_val;
        t[2 * v + 1].add_val = 0;
        t[2 * v + 1].updated = true;

        t[2 * v + 2].set_val = t[v].set_val;
        t[2 * v + 2].add_val = 0;
        t[2 * v + 2].updated = true;
      }
    }
  }

  void push(const uint32_t& v) {
    push_set(v);

    if (t[v].add_val != 0) {
      t[v].val += t[v].add_val;
      t[v].set_val = t[v].val;

      if (t[v].left < t[v].right) {
        t[2 * v + 1].add_val += t[v].add_val;
        t[2 * v + 2].add_val += t[v].add_val;
      }

      t[v].add_val = 0;
    }
  }

  void set(const int64_t& value, const uint32_t& v, const uint32_t& left,
           const uint32_t& right) {
    if (t[v].left <= right && t[v].right >= left) {
      if (t[v].left >= left && t[v].right <= right) {
        t[v].add_val = 0;
        push_set(v);

        t[v].set_val = value;
        t[v].updated = true;
      } else {
        push(v);

        set(value, 2 * v + 1, left, right);
        set(value, 2 * v + 2, left, right);

        t[v].val = std::min(t[2 * v + 1].set_val + t[2 * v + 1].add_val,
                            t[2 * v + 2].set_val + t[2 * v + 2].add_val);
        t[v].set_val = t[v].val;
      }
    }
  }

  void add(const int64_t& value, const uint32_t& v, const uint32_t& left,
           const uint32_t& right) {
    if (t[v].left <= right && t[v].right >= left) {
      push(v);

      if (t[v].left >= left && t[v].right <= right) {
        t[v].add_val = value;
      } else {
        add(value, 2 * v + 1, left, right);
        add(value, 2 * v + 2, left, right);

        t[v].val = std::min(t[2 * v + 1].set_val + t[2 * v + 1].add_val,
                            t[2 * v + 2].set_val + t[2 * v + 2].add_val);
        t[v].set_val = t[v].val;
      }
    }
  }

  int64_t get_min(const uint32_t& v, const uint32_t& left,
                  const uint32_t& right) {
    int64_t result = MAX_VALUE;
    if (t[v].left <= right && t[v].right >= left) {
      push(v);

      if (t[v].right <= right && t[v].left >= left) {
        result = t[v].val;
      } else {
        result = std::min(get_min(2 * v + 1, left, right),
                          get_min(2 * v + 2, left, right));
      }
    }

    return result;
  }
};

int main() {
  std::iostream::sync_with_stdio(false);
  std::cin.tie(nullptr);

  uint32_t n;
  std::cin >> n;

  std::vector<int64_t> a(n);
  for (size_t i = 0; i < n; ++i) std::cin >> a[i];

  SegmentTree st(n);
  st.build(a);

  uint32_t i, j;
  int64_t x;
  std::string command;
  while (std::cin >> command) {
    if (command == "set") {
      std::cin >> i >> j >> x;
      st.set(x, 0, i - 1, j - 1);
    } else if (command == "add") {
      std::cin >> i >> j >> x;
      st.add(x, 0, i - 1, j - 1);
    } else if (command == "min") {
      std::cin >> i >> j;
      std::cout << st.get_min(0, i - 1, j - 1) << "\n";
    }
  }

  return 0;
}
