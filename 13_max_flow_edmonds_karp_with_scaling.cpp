#include <bits/stdc++.h>


#define INF static_cast<int32_t>(1 << 31 - 1)


struct Edge {
    uint16_t from;
    uint16_t to;
    int32_t capacity;
    int32_t flow;
};


int32_t bfs(const uint16_t start,
            const uint16_t finish,
            const std::vector<std::vector<uint16_t>>& graph,
            const std::vector<Edge>& edges,
            std::vector<bool>& used,
            std::stack<uint16_t>& path,
            const uint16_t scale) {
    used[start] = true;

    std::vector<uint16_t> ancestors(used.size());
    ancestors[start] = start;

    std::queue<uint16_t> queue;
    queue.push(start);

    bool finish_reached = false;

    while (!queue.empty() && !finish_reached) {
        auto v = queue.front();
        queue.pop();

        for (const auto& x : graph[v])
            if (!used[edges[x].to] && !finish_reached &&
                edges[x].capacity - edges[x].flow >= scale) {
                used[edges[x].to] = true;
                queue.push(edges[x].to);
                ancestors[edges[x].to] = x;

                if (edges[x].to == finish)
                    finish_reached = true;
            }
    }

    int32_t min_flow = INF;
    if (finish_reached) {
        auto current = finish;
        while (current != start) {
            min_flow = std::min(min_flow,
                                edges[ancestors[current]].capacity -
                                edges[ancestors[current]].flow);
            path.push(ancestors[current]);
            current = edges[ancestors[current]].from;
        }
    }

    return min_flow;
}


uint32_t edmonds_karp_with_scaling(const uint16_t start,
                                   const uint16_t finish,
                                   std::vector<std::vector<uint16_t>>& graph,
                                   std::vector<Edge>& edges,
                                   const uint16_t max_capacity) {
    uint32_t flow = 0;

    uint16_t scale = 1;
    while (scale * 2 <= max_capacity)
        scale *= 2;

    std::vector<bool> used(graph.size());
    std::stack<uint16_t> path;
    while (scale >= 1) {
        while (true) {
            used.assign(used.size(), false);
            auto delta = bfs(start, finish, graph, edges, used, path, scale);

            if (path.empty())
                break;

            while (!path.empty()) {
                auto current = path.top();
                path.pop();
                edges[current].flow += delta;
                edges[current ^ 1].flow -= delta;
            }

            flow += delta;
        }

        scale /= 2;
    }

    return flow;
}


int main() {
    std::iostream::sync_with_stdio(false);
    std::cin.tie(nullptr);

    uint16_t n, m;
    std::cin >> n >> m;

    std::vector<std::vector<uint16_t>> graph(n);
    std::vector<Edge> edges;
    uint16_t from, to, capacity, max_capacity = 0;
    for (size_t i = 0; i < m; ++i) {
        std::cin >> from >> to >> capacity;
        --from;
        --to;

        max_capacity = std::max(max_capacity, capacity);

        graph[from].push_back(edges.size());
        edges.push_back({from, to, capacity, 0});
        graph[to].push_back(edges.size());
        edges.push_back({to, from, capacity, 0});
    }

    std::cout << edmonds_karp_with_scaling(0, n - 1, graph, edges, max_capacity)
              << "\n";

    for (size_t i = 0; i < 2 * m; i += 2)
        std::cout << edges[i].flow << "\n";

    return 0;
}
