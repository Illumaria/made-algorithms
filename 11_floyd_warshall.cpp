#include <bits/stdc++.h>


#define MAX_DISTANCE static_cast<int32_t>(1e8)
#define NO_EDGE static_cast<int32_t>(1e5)


void floyd_warshall(std::vector<std::vector<int32_t>>& weights,
                    std::vector<std::vector<int16_t>>& next,
                    int16_t& neg_cycle_start) {
    for (size_t k = 0; k < weights.size(); ++k)
        for (size_t from = 0; from < weights.size(); ++from)
            for (size_t to = 0; to < weights.size(); ++to) {
                if (weights[from][to] > weights[from][k] + weights[k][to]
                    // May result in wrong path
                    // if weights[from][k] == MAX_DISTANCE
                    // and weights[k][to] < 0
                    && weights[from][k] < MAX_DISTANCE
                    && weights[k][to] < MAX_DISTANCE) {
                    weights[from][to] =
                        std::max(-MAX_DISTANCE,
                                 weights[from][k] + weights[k][to]);
                    next[from][to] = next[from][k];
                }
                if (from == to && weights[from][to] < 0) {
                    neg_cycle_start = from;
                    return;
                }
            }
}

int main() {
    std::iostream::sync_with_stdio(false);
    std::cin.tie(nullptr);

    uint16_t n;
    std::cin >> n;

    std::vector<std::vector<int32_t>> weights(n, std::vector<int32_t>(n));
    int32_t weight;
    for (uint16_t from = 0; from < n; ++from)
        for (uint16_t to = 0; to < n; ++to) {
            std::cin >> weight;
            if (weight == NO_EDGE)
                weights[from][to] = MAX_DISTANCE;
            else
                weights[from][to] = weight;
        }

    std::vector<std::vector<int16_t>> next(n, std::vector<int16_t>(n));
    for (size_t from = 0; from < n; ++from)
            for (size_t to = 0; to < n; ++to)
                next[from][to] = to;

    int16_t neg_cycle_start = -1;
    floyd_warshall(weights, next, neg_cycle_start);

    if (neg_cycle_start == -1) {
        std::cout << "NO" << "\n";
    } else {
        std::cout << "YES" << "\n";
        std::queue<int16_t> cycle;
        cycle.push(neg_cycle_start);
        auto current = next[neg_cycle_start][neg_cycle_start];
        while (current != neg_cycle_start) {
            cycle.push(current);
            current = next[current][neg_cycle_start];
        }
        std::cout << cycle.size() << "\n";
        while (!cycle.empty()) {
            std::cout << cycle.front() + 1 << " ";
            cycle.pop();
        }
        std::cout << "\n";
    }

    return 0;
}
