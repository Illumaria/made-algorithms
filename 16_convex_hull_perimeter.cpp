#include <bits/stdc++.h>


struct Point {
    int64_t x, y;

    bool operator==(const Point& other) const {
        return x == other.x && y == other.y;
    }

    bool operator<(const Point& other) const {
        return x < other.x || (x == other.x && y < other.y);
    }
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


class Segment {
 private:
    Point _begin, _end;

 public:
    Segment(const Point& a, const Point& b) : _begin(a), _end(b) {}

    double length() const {
        return std::sqrt(std::pow(_end.x - _begin.x, 2) +
                         std::pow(_end.y - _begin.y, 2));
    }
};


class ConvexHull {
 private:
    std::vector<Point> _hull;

 public:
    explicit ConvexHull(std::vector<Point>& points) {
        // Sort the points lexicographically:
        std::sort(points.begin(), points.end());

        // Remove duplicates to detect the case we have just one unique point:
        points.erase(std::unique(points.begin(), points.end()), points.end());

        // No points or a single point, possibly repeated multiple times:
        if (points.size() <= 1) {
            _hull = points;
            return;
        }

        // Build the lower hull:
        std::vector<Point> lower;
        build_hull(points, lower);

        // Build the upper hull:
        std::vector<Point> upper;
        std::reverse(points.begin(), points.end());
        build_hull(points, upper);

        // Concatenate the lower and the upper parts
        // to get the full convex hull.
        // Last point of each part is omitted because it is repeated
        // at the beginning of the other part:
        _hull.insert(_hull.end(),
                     std::make_move_iterator(lower.begin()),
                     std::make_move_iterator(lower.end() - 1));
        _hull.insert(_hull.end(),
                     std::make_move_iterator(upper.begin()),
                     std::make_move_iterator(upper.end() - 1));
    }

    void build_hull(const std::vector<Point>& points,
                    std::vector<Point>& hull) {
        for (const auto& p : points) {
            while (hull.size() >= 2 &&
                   Vector(hull[hull.size() - 2], hull[hull.size() - 1]) %
                   Vector(hull[hull.size() - 2], p) <= 0)
                hull.pop_back();
            hull.push_back(p);
        }
        hull.shrink_to_fit();
    }

    double perimeter() const {
        double perimeter = 0.0;
        for (size_t i = 0; i < _hull.size(); i++) {
            perimeter +=
                Segment(_hull[i], _hull[(i + 1) % _hull.size()]).length();
        }

        return perimeter;
    }
};


int main() {
    std::iostream::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int64_t n;
    std::cin >> n;

    std::vector<Point> points(n);
    int64_t x, y;
    for (size_t i = 0; i < n; ++i) {
        std::cin >> x >> y;
        points[i] = {x, y};
    }

    ConvexHull convex_hull(points);

    std::cout << convex_hull.perimeter() << "\n";

    return 0;
}
