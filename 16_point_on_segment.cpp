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
    int64_t operator*(const Vector& other) {
        return _x * other._x + _y * other._y;
    }

    // Cross product:
    int64_t operator%(const Vector& other) {
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


int main() {
    std::iostream::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int64_t m_x, m_y, a_x, a_y, b_x, b_y;
    std::cin >> m_x >> m_y >> a_x >> a_y >> b_x >> b_y;

    Segment ab({a_x, a_y}, {b_x, b_y});

    std::cout << (ab.pointOnSegment({m_x, m_y})
                  ? "YES\n"
                  : "NO\n");

    return 0;
}
