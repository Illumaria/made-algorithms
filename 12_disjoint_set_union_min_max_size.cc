#include <bits/stdc++.h>

class DisjointSetUnion {
 private:
  struct Subset {
    uint32_t parent;
    uint32_t min;
    uint32_t max;
    uint32_t rank;
    uint32_t size;
  };
  std::vector<Subset> p;

 public:
  void init(const uint32_t& n) {
    p.resize(n);
    for (size_t i = 0; i < n; ++i) {
      p[i].parent = p[i].min = p[i].max = i;
      p[i].size = 1;
      p[i].rank = 0;
    }
  }

  uint32_t get(const uint32_t& x) {
    if (p[x].parent != x) p[x].parent = get(p[x].parent);
    return p[x].parent;
  }

  void join(uint32_t x, uint32_t y) {
    x = get(x);
    y = get(y);

    if (x == y) return;

    if (p[x].rank > p[y].rank) std::swap(x, y);

    if (p[x].rank == p[y].rank) ++p[y].rank;

    p[x].parent = y;
    p[y].min = std::min(p[x].min, p[y].min);
    p[y].max = std::max(p[x].max, p[y].max);
    p[y].size += p[x].size;
  }

  uint32_t getMin(const uint32_t& x) { return p[x].min + 1; }

  uint32_t getMax(const uint32_t& x) { return p[x].max + 1; }

  uint32_t getSize(const uint32_t& x) { return p[x].size; }
};

int main() {
  std::iostream::sync_with_stdio(false);
  std::cin.tie(nullptr);

  uint32_t n;
  std::cin >> n;

  DisjointSetUnion dsu;
  dsu.init(n);

  std::string command;
  uint32_t x, y;
  while (std::cin >> command >> x) {
    if (command == "get") {
      auto z = dsu.get(x - 1);
      std::cout << dsu.getMin(z) << " " << dsu.getMax(z) << " "
                << dsu.getSize(z) << "\n";
    } else if (command == "union") {
      std::cin >> y;
      dsu.join(x - 1, y - 1);
    }
  }

  return 0;
}
