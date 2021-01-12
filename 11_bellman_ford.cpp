#include <bits/stdc++.h>

#define MAX_DISTANCE static_cast<int64_t>(6e18)

struct Edge {
  uint16_t to;
  int64_t weight;
};

void bellman_ford(const std::vector<std::vector<Edge>>& graph,
                  std::vector<int64_t>& distances, uint16_t start) {
  distances[start] = 0;
  for (size_t k = 0; k < graph.size(); ++k)
    for (size_t from = 0; from < graph.size(); ++from)
      if (distances[from] < MAX_DISTANCE)  // "start->from" edge exists
        for (const auto& edge : graph[from])
          distances[edge.to] =
              std::min(distances[edge.to], distances[from] + edge.weight);
}

void dfs(std::vector<std::vector<Edge>>& graph,
         std::vector<bool>& no_shortest_path, uint16_t from) {
  no_shortest_path[from] = true;
  // Propagate to every vertex that
  // is reachable from the current one:
  for (const auto& edge : graph[from])
    if (!no_shortest_path[edge.to]) dfs(graph, no_shortest_path, edge.to);
}

int main() {
  std::iostream::sync_with_stdio(false);
  std::cin.tie(nullptr);

  uint16_t n, m, start;
  std::cin >> n >> m >> start;
  --start;

  std::vector<std::vector<Edge>> graph(n);
  std::vector<bool> no_shortest_path(n, false);
  std::vector<int64_t> distances(n, MAX_DISTANCE);

  // Read graph:
  uint16_t from, to;
  int64_t weight;
  for (size_t i = 0; i < m; ++i) {
    std::cin >> from >> to >> weight;
    --from;
    --to;
    graph[from].push_back({to, weight});
  }

  // Find the shortest path from start to every other vertex:
  bellman_ford(graph, distances, start);

  // Mark vertices that lie on or are reachable
  // only from a negative cycle:
  for (size_t from = 0; from < n; ++from) {
    if (distances[from] < MAX_DISTANCE)  // "start->from" edge exists
      for (const auto& edge : graph[from]) {
        if (distances[edge.to] > distances[from] + edge.weight &&
            !no_shortest_path[edge.to]) {
          dfs(graph, no_shortest_path, edge.to);
        }
      }
  }

  for (size_t i = 0; i < n; ++i) {
    // Vertex is unreachable:
    if (distances[i] == MAX_DISTANCE) std::cout << "*\n";
    // Vertex lies on or is reachable
    // from a negative cycle:
    else if (no_shortest_path[i])
      std::cout << "-\n";
    // Vertex is reachable:
    else
      std::cout << distances[i] << "\n";
  }

  return 0;
}
