#include <bits/stdc++.h>

#define MAX_DISTANCE static_cast<int64_t>((1ll << 63) - 1)

struct Edge {
  uint16_t from;
  uint16_t to;
  int64_t weight;
};

void dfs(const std::vector<std::vector<Edge>>& graph, std::vector<bool>& used,
         const uint32_t from) {
  used[from] = true;

  for (const auto& edge : graph[from])
    if (!used[edge.to]) dfs(graph, used, edge.to);
}

bool all_vertices_reachable(const std::vector<std::vector<Edge>>& graph,
                            const uint16_t root) {
  std::vector<bool> used(graph.size(), false);

  dfs(graph, used, root);

  for (const auto& x : used)
    if (!x) return false;
  return true;
}

void condensation_dfs(const std::vector<std::vector<Edge>>& graph,
                      const uint16_t& from, std::vector<bool>& used,
                      std::stack<uint16_t>& top_sort) {
  used[from] = true;
  for (const auto& edge : graph[from])
    if (!used[edge.to]) condensation_dfs(graph, edge.to, used, top_sort);
  top_sort.push(from);
}

void condensation_dfs_inv(const std::vector<std::vector<Edge>>& graph_inv,
                          uint16_t from, std::vector<uint16_t>& scc,
                          uint16_t current_scc) {
  scc[from] = current_scc;
  for (const auto& edge : graph_inv[from])
    if (scc[edge.to] == 0)
      condensation_dfs_inv(graph_inv, edge.to, scc, current_scc);
}

std::pair<std::vector<uint16_t>, uint16_t> condensation(
    const std::vector<std::vector<Edge>>& graph,
    const std::vector<std::vector<Edge>>& graph_inv) {
  // Perform topological sorting of the graph.
  // We don't care about cycles here:
  std::vector<bool> used(graph.size(), false);
  std::stack<uint16_t> top_sort;
  for (uint16_t from = 0; from < graph.size(); ++from)
    if (!used[from]) condensation_dfs(graph, from, used, top_sort);

  // Find strongly connected components (scc)
  // for the inversed graph, picking vertices
  // in the order of top_sort:
  uint16_t scc_num = 0;
  std::vector<uint16_t> scc(graph.size(), 0);
  while (!top_sort.empty()) {
    auto from = top_sort.top();
    top_sort.pop();
    if (scc[from] == 0) {
      ++scc_num;
      condensation_dfs_inv(graph_inv, from, scc, scc_num);
    }
  }

  return {scc, scc_num};
}

int64_t findMST(const std::vector<std::vector<Edge>>& graph, const uint16_t n,
                const uint16_t root) {
  int64_t res = 0;
  // Create array of minimum incoming edges:
  std::vector<int64_t> minEdge(n, MAX_DISTANCE);

  // Find the minimum incoming edge for each vertex:
  for (size_t i = 0; i < n; ++i) {
    for (const auto& edge : graph[i])
      minEdge[edge.to] = std::min(minEdge[edge.to], edge.weight);
  }
  // Minimum edges weights will count towards the resulting total weight:
  for (size_t v = 0; v < graph.size(); ++v)
    if (v != root) res += minEdge[v];
  // Create array of zero edges and its reversed version
  // which is needed to find condensation:
  std::vector<std::vector<Edge>> zeroEdges(n), invZeroEdges(n);
  for (size_t i = 0; i < graph.size(); ++i)
    for (const auto& edge : graph[i])
      if (edge.weight == minEdge[edge.to]) {
        zeroEdges[edge.from].push_back({edge.from, edge.to, 0});
        invZeroEdges[edge.to].push_back({edge.to, edge.from, 0});
      }
  // Check if we can visit all other vertices
  // from the root vertex via zero edges:
  if (all_vertices_reachable(zeroEdges, root)) return res;
  // Find strongly connected components:
  std::vector<uint16_t> newComponents;
  uint16_t componentsCount;
  std::tie(newComponents, componentsCount) =
      condensation(zeroEdges, invZeroEdges);
  // Create array of edges in the newComponents graph:
  std::vector<std::vector<Edge>> newEdges(componentsCount);
  for (uint16_t from = 0; from < graph.size(); ++from)
    for (const auto& edge : graph[from])
      if (newComponents[edge.from] != newComponents[edge.to])
        newEdges[newComponents[edge.from] - 1].push_back(
            {newComponents[edge.from] - 1, newComponents[edge.to] - 1,
             edge.weight - minEdge[edge.to]});
  // We won't need all of the arrays created above.
  // Let's free some memory before going deeper in recursion:
  std::vector<int64_t>().swap(minEdge);
  std::vector<std::vector<Edge>>().swap(zeroEdges);
  std::vector<std::vector<Edge>>().swap(invZeroEdges);
  // Repeat the sequence for the newComponents graph:
  res += findMST(newEdges, componentsCount, newComponents[root] - 1);
  return res;
}

int main() {
  std::iostream::sync_with_stdio(false);
  std::cin.tie(nullptr);

  uint16_t n, m;
  std::cin >> n >> m;

  std::vector<std::vector<Edge>> graph(n), reversed_graph(n);
  uint16_t from, to;
  int64_t weight;
  for (size_t i = 0; i < m; ++i) {
    std::cin >> from >> to >> weight;
    graph[from - 1].push_back({from - 1, to - 1, weight});
    reversed_graph[to - 1].push_back({to - 1, from - 1, weight});
  }

  // Check if we can visit all other vertices
  // from the root vertex (given root = 0):
  if (!all_vertices_reachable(graph, 0)) {
    std::cout << "NO\n";
  } else {
    // Find the minimum spanning tree
    // and print its total weight:
    std::cout << "YES\n" << findMST(graph, n, 0) << "\n";
  }

  return 0;
}
