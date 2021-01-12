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

  bool segmentsIntersect(const Segment& other) const {
    Vector ab(_begin, _end);
    Vector ac(_begin, other._begin);
    Vector ad(_begin, other._end);

    Vector cd(other._begin, other._end);
    Vector ca(other._begin, _begin);
    Vector cb(other._begin, _end);

    const auto ab_x_ac = ab % ac;
    const auto ab_x_ad = ab % ad;
    const auto cd_x_ca = cd % ca;
    const auto cd_x_cb = cd % cb;

    if (ab_x_ac == 0 && ab_x_ad == 0 && cd_x_ca == 0 && cd_x_cb == 0) {
      return this->pointOnSegment(other._begin) ||
             this->pointOnSegment(other._end) || other.pointOnSegment(_begin) ||
             other.pointOnSegment(_end);
    } else {
      return ab_x_ac * ab_x_ad <= 0 && cd_x_ca * cd_x_cb <= 0;
    }
  }
};

int main() {
  std::iostream::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int64_t a_x, a_y, b_x, b_y, c_x, c_y, d_x, d_y;
  std::cin >> a_x >> a_y >> b_x >> b_y >> c_x >> c_y >> d_x >> d_y;

  Segment ab({a_x, a_y}, {b_x, b_y});
  Segment cd({c_x, c_y}, {d_x, d_y});

  std::cout << (ab.segmentsIntersect(cd) ? "YES\n" : "NO\n");

  return 0;
}
