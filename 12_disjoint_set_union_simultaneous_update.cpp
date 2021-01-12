#include <bits/stdc++.h>

class DisjointSetUnion {
 private:
  struct Subset {
    uint32_t leader;
    int32_t experience;
    uint32_t rank;
  };
  std::vector<Subset> p;

 public:
  void init(const uint32_t& n) {
    p.resize(n);
    for (size_t i = 0; i < n; ++i) {
      p[i].leader = i;
      p[i].experience = p[i].rank = 0;
    }
  }

  uint32_t get(const uint32_t& x) {
    if (p[x].leader != x) {
      auto cur_leader = p[x].leader;
      p[x].leader = get(p[x].leader);
      if (cur_leader != p[x].leader)
        p[x].experience += p[cur_leader].experience;
    }
    return p[x].leader;
  }

  void join(uint32_t x, uint32_t y) {
    x = get(x);
    y = get(y);

    if (x == y) return;

    if (p[x].rank > p[y].rank) std::swap(x, y);

    if (p[x].rank == p[y].rank) ++p[y].rank;

    p[x].leader = y;
    p[x].experience -= p[y].experience;
  }

  void add(uint32_t x, const uint16_t v) {
    x = get(x);
    p[x].experience += v;
  }

  uint32_t getExp(const uint32_t& x) {
    auto y = get(x);
    return p[x].leader == x ? p[x].experience
                            : p[x].experience + p[y].experience;
  }
};

int main() {
  std::iostream::sync_with_stdio(false);
  std::cin.tie(nullptr);

  uint32_t n, m;
  std::cin >> n >> m;

  DisjointSetUnion dsu;
  dsu.init(n);

  std::string command;
  uint32_t x, y;
  uint16_t v;
  for (size_t i = 0; i < m; ++i) {
    std::cin >> command >> x;
    if (command == "add") {
      std::cin >> v;
      dsu.add(x - 1, v);
    } else if (command == "join") {
      std::cin >> y;
      dsu.join(x - 1, y - 1);
    } else if (command == "get") {
      std::cout << dsu.getExp(x - 1) << "\n";
    }
  }

  return 0;
}
