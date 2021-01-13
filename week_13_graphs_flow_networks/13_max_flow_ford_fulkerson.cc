#include <bits/stdc++.h>

#define INF static_cast<int32_t>(1LL << 31 - 1)

struct Edge {
  uint16_t from;
  uint16_t to;
  int32_t capacity;
  int32_t flow;
};

int32_t push_flow(const uint16_t vertex, const uint16_t finish,
                  const int32_t& current_flow,
                  const std::vector<std::vector<uint16_t>>& graph,
                  std::vector<Edge>& edges, std::vector<bool>& used) {
  used[vertex] = true;

  if (vertex == finish) return current_flow;

  for (auto& x : graph[vertex])
    if (!used[edges[x].to] && edges[x].flow < edges[x].capacity) {
      int32_t next_flow =
          std::min(current_flow, edges[x].capacity - edges[x].flow);
      auto delta =
          push_flow(edges[x].to, finish, next_flow, graph, edges, used);

      if (delta > 0) {
        edges[x].flow += delta;
        edges[x ^ 1].flow -= delta;
        return delta;
      }
    }

  return 0;
}

uint32_t ford_fulkerson(const uint16_t start, const uint16_t finish,
                        const std::vector<std::vector<uint16_t>>& graph,
                        std::vector<Edge>& edges) {
  std::vector<bool> used(graph.size());
  uint32_t flow = 0;

  while (true) {
    used.assign(used.size(), false);
    auto delta = push_flow(start, finish, INF, graph, edges, used);

    if (delta > 0)
      flow += delta;
    else
      break;
  }

  return flow;
}

int main() {
  std::iostream::sync_with_stdio(false);
  std::cin.tie(nullptr);

  uint16_t n, m;
  std::cin >> n >> m;

  std::vector<std::vector<uint16_t>> graph(n);
  std::vector<Edge> edges;
  uint16_t from, to, capacity;
  for (size_t i = 0; i < m; ++i) {
    std::cin >> from >> to >> capacity;
    --from;
    --to;

    graph[from].push_back(edges.size());
    edges.push_back({from, to, capacity, 0});
    graph[to].push_back(edges.size());
    edges.push_back({to, from, capacity, 0});
  }

  std::cout << ford_fulkerson(0, n - 1, graph, edges) << "\n";

  return 0;
}
