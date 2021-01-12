#include <bits/stdc++.h>

#define INF static_cast<int32_t>(1 << 31 - 1)

struct Point {
  int16_t x;
  int16_t y;

  Point() {}
  Point(const int16_t x, const int16_t y) : x(x), y(y) {}
};

const std::vector<Point> moves = {Point(-1, 0), Point(1, 0), Point(0, 1),
                                  Point(0, -1)};

std::vector<Point> build_moves(const uint16_t map_x, const uint16_t map_y,
                               const Point& v) {
  std::vector<Point> result;

  for (const auto& move : moves)
    if (-1 < v.x + move.x && v.x + move.x < map_x && -1 < v.y + move.y &&
        v.y + move.y < map_y)
      result.emplace_back(v.x + move.x, v.y + move.y);

  return result;
}

struct Edge {
  Point from;
  Point to;
  int32_t capacity;
  int32_t flow;
  uint32_t link;
};

void dfs(const Point& from,
         const std::vector<std::vector<std::vector<uint32_t>>>& graph,
         const std::vector<Edge>& edges, std::vector<std::vector<bool>>& used) {
  used[from.x][from.y] = true;

  for (const auto& x : graph[from.x][from.y])
    if (!used[edges[x].to.x][edges[x].to.y] &&
        edges[x].flow < edges[x].capacity)
      dfs(edges[x].to, graph, edges, used);
}

int32_t bfs(const Point& start, const Point& finish,
            const std::vector<std::vector<std::vector<uint32_t>>>& graph,
            const std::vector<Edge>& edges,
            std::vector<std::vector<bool>>& used, std::stack<uint32_t>& path) {
  used[start.x][start.y] = true;

  std::vector<std::vector<uint32_t>> ancestors(
      used.size(), std::vector<uint32_t>(used[0].size()));
  ancestors[start.x][start.y] = 0;

  std::queue<Point> queue;
  queue.push(start);

  bool finish_reached = false;

  while (!queue.empty() && !finish_reached) {
    auto v = queue.front();
    queue.pop();

    for (const auto& x : graph[v.x][v.y])
      if (!used[edges[x].to.x][edges[x].to.y] && !finish_reached &&
          edges[x].capacity > edges[x].flow) {
        used[edges[x].to.x][edges[x].to.y] = true;
        queue.push(edges[x].to);
        ancestors[edges[x].to.x][edges[x].to.y] = x;

        if (edges[x].to.x == finish.x && edges[x].to.y == finish.y)
          finish_reached = true;
      }
  }

  int32_t min_flow = INF;
  if (finish_reached) {
    auto current = finish;
    while (!(current.x == start.x && current.y == start.y)) {
      min_flow =
          std::min(min_flow, edges[ancestors[current.x][current.y]].capacity -
                                 edges[ancestors[current.x][current.y]].flow);
      path.push(ancestors[current.x][current.y]);
      current = edges[ancestors[current.x][current.y]].from;
    }
  }

  return min_flow;
}

uint64_t edmonds_karp(const Point& start, const Point& finish,
                      std::vector<std::vector<std::vector<uint32_t>>>& graph,
                      std::vector<Edge>& edges, const uint32_t& size_x,
                      const uint32_t& size_y,
                      std::vector<std::vector<char>>& kingdom) {
  uint64_t flow = 0;

  std::vector<std::vector<bool>> used(size_x, std::vector<bool>(size_y));
  std::stack<uint32_t> path;
  while (true) {
    for (size_t i = 0; i < size_x; ++i) used[i].assign(size_y, false);
    auto delta = bfs(start, finish, graph, edges, used, path);

    if (path.empty()) break;

    while (!path.empty()) {
      auto current = path.top();
      path.pop();
      edges[current].flow += delta;
      edges[graph[edges[current].to.x][edges[current].to.y]
                 [edges[current].link]]
          .flow -= delta;
    }

    flow += delta;
  }

  for (size_t i = 0; i < size_x; ++i) used[i].assign(size_y, false);
  dfs(start, graph, edges, used);

  for (size_t i = 0; i < edges.size(); ++i)
    if (used[edges[i].from.x][edges[i].from.y] &&
        !used[edges[i].to.x][edges[i].to.y] && edges[i].flow == 1)
      if (edges[i].to.x >= size_x / 2)
        kingdom[edges[i].to.x - size_x / 2][edges[i].to.y] = '+';
      else
        kingdom[edges[i].to.x][edges[i].to.y] = '+';

  return flow;
}

int main() {
  std::iostream::sync_with_stdio(false);
  std::cin.tie(nullptr);

  uint16_t n, m;
  std::cin >> n >> m;

  /*
   * This problem is about finding vertex disjoint paths.
   * Since for that we need to split each vertex into two parts,
   * here we created an additional kingdom map in graph
   * which results in a sort of a 3D structure:
   * - imagine the two kingdom maps lying one above the other;
   * - the path starts from a cell on the additional map;
   * - the edges of that cell can only lead to the original map
   *   (to the cells on the right/left/top/bottom),
   *   while their reversed versions have zero capacity;
   * - the edges of the cells on the original map
   *   can only lead to their copies on the additional map.
   * Thus, each cell is split, and the pathing looks like this:
   * (starting AMC) -> [(OMC 1) -> (AMC 1 copy)] -> (OMC 2) ->
   * (AMC 2 copy) -> (OMC 3) -> ... -> (AMC k copy) -> (ending OMC),
   * where AMC is additional map cell,
   *       OMC is original map cell,
   *       and [...] illustrates a single cell after split.
   */
  std::vector<std::vector<char>> kingdom(n, std::vector<char>(m));
  std::vector<std::vector<std::vector<uint32_t>>> graph(
      2 * n, std::vector<std::vector<uint32_t>>(m));
  std::vector<Edge> edges;
  Point start, finish;
  std::string row;
  for (uint16_t i = 0; i < n; ++i) {
    std::cin >> row;

    for (uint16_t j = 0; j < m; ++j) {
      kingdom[i][j] = row[j];

      switch (row[j]) {
        case 'A':
          start = {n + i, j};
          break;
        case 'B':
          finish = {i, j};
          break;
        case '#':
          graph[i][j].push_back(edges.size());
          edges.push_back({{i, j}, {n + i, j}, 0, 0});
          break;
        case '.':
          graph[i][j].push_back(edges.size());
          edges.push_back({{i, j}, {n + i, j}, 1, 0});
          break;
        case '-':
          graph[i][j].push_back(edges.size());
          edges.push_back({{i, j}, {n + i, j}, INF, 0});
          break;
        default:
          break;
      }
    }
  }

  for (size_t i = 0; i < n; ++i) {
    for (size_t j = 0; j < m; ++j) {
      auto possible_moves = build_moves(n, m, {i, j});
      for (const auto& move : possible_moves) {
        graph[n + i][j].push_back(edges.size());
        edges.push_back({{n + i, j},
                         {move.x, move.y},
                         INF,
                         0,
                         graph[move.x][move.y].size()});

        graph[move.x][move.y].push_back(edges.size());
        edges.push_back(
            {{move.x, move.y}, {n + i, j}, 0, 0, graph[n + i][j].size() - 1});
      }
    }
  }

  auto max_flow = edmonds_karp(start, finish, graph, edges, 2 * n, m, kingdom);

  if (max_flow >= INF) {
    std::cout << "-1\n";
  } else {
    std::cout << max_flow << "\n";
    for (size_t i = 0; i < n; ++i) {
      for (size_t j = 0; j < m; ++j) std::cout << kingdom[i][j];
      std::cout << "\n";
    }
  }

  return 0;
}
