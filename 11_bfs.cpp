#include <bits/stdc++.h>

struct Vertex {
  int16_t x;
  int16_t y;

  Vertex() {}
  Vertex(const int16_t x, const int16_t y) : x(x), y(y) {}
};

using VectorInt16 = std::vector<int16_t>;
using MatrixInt16 = std::vector<VectorInt16>;
using StackVertex = std::stack<Vertex>;
using VectorBool = std::vector<bool>;
using MatrixBool = std::vector<VectorBool>;
using VectorVertex = std::vector<Vertex>;
using MatrixVertex = std::vector<VectorVertex>;

const std::vector<Vertex> moves = {
    Vertex(-2, -1), Vertex(-2, 1), Vertex(-1, -2), Vertex(-1, 2),
    Vertex(1, -2),  Vertex(1, 2),  Vertex(2, -1),  Vertex(2, 1)};

VectorVertex build_edges(const int16_t board_size, const Vertex& v) {
  VectorVertex result;

  for (const auto& move : moves)
    if (-1 < v.x + move.x && v.x + move.x < board_size && -1 < v.y + move.y &&
        v.y + move.y < board_size)
      result.emplace_back(v.x + move.x, v.y + move.y);

  return result;
}

void bfs(const Vertex& start, const Vertex& finish, MatrixBool& used,
         StackVertex& path, MatrixVertex& ancestors) {
  used[start.x][start.y] = true;
  ancestors[start.x][start.y] = {-1, -1};
  bool target_reached = false;
  std::queue<Vertex> queue;
  queue.push(start);

  while (!target_reached) {
    auto v = queue.front();
    queue.pop();
    auto edges = build_edges(used.size(), v);

    for (const auto& to : edges)
      if (!used[to.x][to.y]) {
        used[to.x][to.y] = true;
        queue.push(to);
        ancestors[to.x][to.y] = v;
        if (to.x == finish.x && to.y == finish.y) target_reached = true;
      }
  }

  auto current = finish;
  while (current.x != -1 && current.y != -1) {
    path.push(current);
    current = ancestors[current.x][current.y];
  }
}

int main() {
  std::iostream::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int16_t n, x1, y1, x2, y2;
  std::cin >> n >> x1 >> y1 >> x2 >> y2;

  Vertex start, finish;
  start = {x1 - 1, y1 - 1};
  finish = {x2 - 1, y2 - 1};

  MatrixInt16 distance(n, VectorInt16(n, 0));
  MatrixVertex ancestors(n, VectorVertex(n));
  MatrixBool used(n, VectorBool(n, false));
  StackVertex path;

  bfs(start, finish, used, path, ancestors);

  std::cout << path.size() << "\n";
  while (!path.empty()) {
    auto top = path.top();
    path.pop();
    std::cout << top.x + 1 << " " << top.y + 1 << "\n";
  }

  return 0;
}
