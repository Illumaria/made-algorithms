#include <bits/stdc++.h>

struct Point {
  int64_t x, y;
};

class Vector {
 private:
  int64_t _x, _y;

 public:
  Vector(const Point& a, const Point& b) : _x(b.x - a.x), _y(b.y - a.y) {}

  // Dot product:
  int64_t operator*(const Vector& other) const {
    return _x * other._x + _y * other._y;
  }

  // Cross product:
  int64_t operator%(const Vector& other) const {
    return _x * other._y - _y * other._x;
  }
};

class Segment {
 private:
  Point _begin, _end;

 public:
  Segment(const Point& a, const Point& b) : _begin(a), _end(b) {}

  bool pointOnSegment(const Point& m) const {
    return Vector(_begin, _end) % Vector(_begin, m) == 0 &&
           Vector(m, _begin) * Vector(m, _end) <= 0;
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

  bool pointInside(const Point& m) const {
    bool is_inside = false;
    ;

    for (size_t i = 0; i != _vertices_num; i++) {
      // Define the highest and the lowest points
      // of the current edge:
      Point min_point = _vertices[i];
      Point max_point = _vertices[(i + 1) % _vertices_num];
      if (min_point.y > max_point.y) std::swap(min_point, max_point);

      // Return "true" if the point lies on the current edge:
      Segment edge(min_point, max_point);
      if (edge.pointOnSegment(m)) return true;

      // Skip the edge if it is parallel to the X axis (and to the ray)
      // since if won't contribute to the resulting value:
      if (min_point.y == max_point.y) continue;
      // The ray goes through the highest edge point:
      if (m.y == max_point.y && m.x < std::min(min_point.x, max_point.x))
        is_inside ^= true;
      // The ray goes through the lowest edge point:
      if (m.y == min_point.y) continue;
      // The ray intersects the edge:
      if (m.y < max_point.y && m.y > min_point.y &&
          Vector(m, min_point) % Vector(m, max_point) > 0)
        is_inside ^= true;
    }

    return is_inside;
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

  int64_t n, m_x, m_y;
  std::cin >> n >> m_x >> m_y;

  Polygon polygon(n);
  std::cin >> polygon;

  std::cout << (polygon.pointInside({m_x, m_y}) ? "YES\n" : "NO\n");

  return 0;
}
