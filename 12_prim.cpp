#include <bits/stdc++.h>


#define MAX_DISTANCE static_cast<double>(8e8 + 1)


struct Point {
    int16_t x;
    int16_t y;
};


double distance(const Point& a, const Point& b) {
    return std::sqrt((b.x - a.x) * (b.x - a.x) + (b.y - a.y) * (b.y - a.y));
}


void prim(const std::vector<Point>& graph,
          std::vector<bool>& used,
          std::vector<double>& weights) {
    size_t from = 0, next = 0;
    weights[from] = 0;

    double cur_min;
    for (size_t i = 0; i < graph.size(); ++i) {
        used[from] = true;
        cur_min = MAX_DISTANCE;
        for (size_t to = 0; to < graph.size(); ++to)
            if (!used[to]) {
                weights[to] = std::min(weights[to],
                                       distance(graph[from], graph[to]));

                // The next vertex to visit will be
                // the closest one to the "from" vertex:
                if (cur_min > weights[to]) {
                    cur_min = weights[to];
                    next = to;
                }
            }
        from = next;
    }
}

int main() {
    std::iostream::sync_with_stdio(false);
    std::cin.tie(nullptr);

    uint16_t n;
    std::cin >> n;

    // Read graph:
    std::vector<Point> graph(n);
    int16_t x, y;
    for (size_t i = 0; i < n; ++i) {
        std::cin >> x >> y;
        graph[i] = {x, y};
    }

    // Find edges:
    std::vector<double> weights(n, MAX_DISTANCE);
    std::vector<bool> used(n, false);
    prim(graph, used, weights);

    // Find total weight:
    double result = 0.0;
    for (const auto& w : weights) {
        result += w;
    }
    std::cout << result << "\n";

    return 0;
}
