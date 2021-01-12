#include <bits/stdc++.h>

void dfs(const std::vector<std::vector<uint32_t>>& graph, const uint32_t& from,
         std::vector<uint32_t>& scc, uint32_t current_scc) {
  scc[from] = current_scc;
  for (const auto& to : graph[from])
    if (scc[to] == 0) dfs(graph, to, scc, current_scc);
}

int main() {
  std::iostream::sync_with_stdio(false);
  std::cin.tie(nullptr);

  uint32_t n, m;
  std::cin >> n >> m;

  // Read graph:
  std::vector<std::vector<uint32_t>> graph(n);
  uint32_t from, to;
  for (size_t i = 0; i < m; ++i) {
    std::cin >> from >> to;
    --from;
    --to;
    graph[from].push_back(to);
    if (from != to) graph[to].push_back(from);
  }

  // Сount strongly connected components (scc):
  uint32_t scc_num = 0;
  std::vector<uint32_t> scc(n, 0);
  for (uint32_t from = 0; from < n; ++from) {
    if (scc[from] == 0) {
      ++scc_num;
      dfs(graph, from, scc, scc_num);
    }
  }

  // Print the number of strongly connected components
  // and component number that each vertex belongs to:
  std::cout << scc_num << "\n";
  for (const auto& x : scc) std::cout << x << " ";
  std::cout << "\n";

  return 0;
}
