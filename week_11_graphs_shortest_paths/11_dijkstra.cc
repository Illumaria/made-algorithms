#include <bits/stdc++.h>

#define MAX_DISTANCE static_cast<uint64_t>(4e9 + 1)

struct Edge {
  uint32_t to;
  uint32_t weight;
};

void dijkstra(std::vector<std::vector<Edge>>& graph,
              std::vector<uint64_t>& distances) {
  distances[0] = 0;  // distances[start]
  std::set<std::pair<uint64_t, uint32_t>> queue;
  queue.insert({0, 0});  // {distances[start], start}

  uint32_t from;
  while (!queue.empty()) {
    // Extract the first edge from the queue:
    auto top = queue.begin();
    from = top->second;
    queue.erase(top);

    for (const auto& edge : graph[from])
      if (distances[edge.to] > distances[from] + edge.weight) {
        queue.erase({distances[edge.to], edge.to});
        distances[edge.to] = distances[from] + edge.weight;
        queue.insert({distances[edge.to], edge.to});
      }
  }
}

int main() {
  std::iostream::sync_with_stdio(false);
  std::cin.tie(nullptr);

  uint32_t n, m;
  std::cin >> n >> m;

  // Read graph:
  std::vector<std::vector<Edge>> graph(n);
  uint32_t from, to, weight;
  for (size_t i = 0; i < m; ++i) {
    std::cin >> from >> to >> weight;
    --from;
    --to;
    graph[from].push_back({to, weight});
    graph[to].push_back({from, weight});
  }

  // Find distances:
  std::vector<uint64_t> distances(n, MAX_DISTANCE);
  dijkstra(graph, distances);

  // Print distances:
  for (const auto& d : distances) std::cout << d << " ";

  return 0;
}
