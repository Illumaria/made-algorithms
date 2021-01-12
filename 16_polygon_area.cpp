#include <bits/stdc++.h>

struct Point {
  int64_t x, y;
};

class Vector {
 private:
  int64_t _x, _y;

 public:
  Vector(const Point& a, const Point& b) : _x(b.x - a.x), _y(b.y - a.y) {}

  // Cross product:
  int64_t operator%(const Vector& other) const {
    return _x * other._y - _y * other._x;
  }
};

class Polygon {
 private:
  size_t _vertices_num;
  std::vector<Point> _vertices;

 public:
  explicit Polygon(const size_t& n) : _vertices_num(n) {
    _vertices.resize(_vertices_num);
  }

  float area() const {
    int64_t area = 0;
    for (size_t i = 0; i < _vertices_num; i++) {
      area += Vector({0, 0}, _vertices[i]) %
              Vector({0, 0}, _vertices[(i + 1) % _vertices_num]);
    }
    return std::abs(area) / 2.0;
  }

  friend std::istream& operator>>(std::istream& input, Polygon& polygon);
};

std::istream& operator>>(std::istream& input, Polygon& polygon) {
  int64_t x, y;
  for (size_t i = 0; i < polygon._vertices_num; ++i) {
    input >> x >> y;
    polygon._vertices[i] = {x, y};
  }

  return input;
}

int main() {
  std::iostream::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int64_t n;
  std::cin >> n;

  Polygon polygon(n);
  std::cin >> polygon;

  std::cout << polygon.area() << "\n";

  return 0;
}
