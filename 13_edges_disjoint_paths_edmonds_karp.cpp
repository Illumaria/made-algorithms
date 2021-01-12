#include <bits/stdc++.h>

#define INF static_cast<int32_t>(1 << 31 - 1)

struct Edge {
  uint32_t from;
  uint32_t to;
  int32_t capacity;
  int32_t flow;
};

void dfs(const uint32_t& from, const uint32_t& finish,
         const std::vector<std::vector<uint32_t>>& graph,
         const std::vector<Edge>& edges, std::vector<bool>& used,
         std::vector<uint32_t>& path) {
  path.push_back(from);

  if (from == finish) return;

  for (const auto& x : graph[from])
    if (!used[x] && edges[x].flow > 0) {
      used[x] = true;
      dfs(edges[x].to, finish, graph, edges, used, path);
      break;
    }
}

int32_t bfs(const uint32_t& start, const uint32_t& finish,
            const std::vector<std::vector<uint32_t>>& graph,
            const std::vector<Edge>& edges, std::vector<bool>& used,
            std::stack<uint32_t>& path) {
  used[start] = true;

  std::vector<uint32_t> ancestors(graph.size());
  ancestors[start] = start;

  std::queue<uint32_t> queue;
  queue.push(start);

  bool finish_reached = false;

  while (!queue.empty() && !finish_reached) {
    auto v = queue.front();
    queue.pop();

    for (const auto& x : graph[v])
      if (!used[edges[x].to] && !finish_reached &&
          edges[x].capacity > edges[x].flow) {
        used[edges[x].to] = true;
        queue.push(edges[x].to);
        ancestors[edges[x].to] = x;
        if (edges[x].to == finish) finish_reached = true;
      }
  }

  int32_t min_flow = INF;
  if (finish_reached) {
    auto current = finish;
    while (current != start) {
      min_flow = std::min(min_flow, edges[ancestors[current]].capacity -
                                        edges[ancestors[current]].flow);
      path.push(ancestors[current]);
      current = edges[ancestors[current]].from;
    }
  }

  return min_flow;
}

uint32_t edmonds_karp(const uint32_t& start, const uint32_t& finish,
                      std::vector<std::vector<uint32_t>>& graph,
                      std::vector<Edge>& edges) {
  uint32_t flow = 0;

  std::vector<bool> used(graph.size());
  std::stack<uint32_t> path;
  while (true) {
    used.assign(used.size(), false);
    auto delta = bfs(start, finish, graph, edges, used, path);

    if (path.empty()) break;

    while (!path.empty()) {
      auto current = path.top();
      path.pop();
      edges[current].flow += delta;
      edges[current ^ 1].flow -= delta;
    }

    flow += delta;
  }

  return flow;
}

int main() {
  std::iostream::sync_with_stdio(false);
  std::cin.tie(nullptr);

  uint32_t n, m, start, finish;
  std::cin >> n >> m >> start >> finish;
  --start;
  --finish;

  std::vector<std::vector<uint32_t>> graph(n);
  std::vector<Edge> edges;
  uint32_t from, to;
  for (size_t i = 0; i < m; ++i) {
    std::cin >> from >> to;
    --from;
    --to;

    graph[from].push_back(edges.size());
    edges.push_back({from, to, 1, 0});
    graph[to].push_back(edges.size());
    edges.push_back({to, from, 0, 0});
  }

  uint32_t max_flow = edmonds_karp(start, finish, graph, edges);

  if (max_flow < 2) {
    std::cout << "NO\n";
  } else {
    std::cout << "YES\n";

    std::vector<bool> used(2 * m, false);
    std::vector<uint32_t> path_1, path_2;
    dfs(start, finish, graph, edges, used, path_1);
    dfs(start, finish, graph, edges, used, path_2);

    for (const auto& x : path_1) std::cout << x + 1 << " ";
    std::cout << "\n";

    for (const auto& x : path_2) std::cout << x + 1 << " ";
    std::cout << "\n";
  }

  return 0;
}
