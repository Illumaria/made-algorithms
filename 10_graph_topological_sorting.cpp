#include <bits/stdc++.h>


void dfs(const std::vector<std::vector<uint32_t>>& graph,
         const uint32_t& from,
         std::vector<uint16_t>& color,
         std::stack<uint32_t>& top_sort,
         bool& has_cycle) {
    color[from] = 1;
    if (!has_cycle) {
        for (const auto& to : graph[from]) {
            if (color[to] == 0)
                dfs(graph, to, color, top_sort, has_cycle);
            if (color[to] == 1) {
                has_cycle = true;
                break;
            }
        }
        color[from] = 2;
        top_sort.push(from);
    }
}


int main() {
    std::iostream::sync_with_stdio(false);
    std::cin.tie(nullptr);

    uint32_t n, m;
    std::cin >> n >> m;

    // Read graph:
    std::vector<std::vector<uint32_t>> graph(n);
    uint32_t from, to;
    for (size_t i = 0; i < m; ++i) {
        std::cin >> from >> to;
        --from;
        --to;
        graph[from].push_back(to);
    }

    // Perform topological sorting:
    std::vector<bool> used(n, false);
    // 0: unvisited, 1: current recursion, 2: visited
    std::vector<uint16_t> color(n, 0);
    std::stack<uint32_t> top_sort;
    bool has_cycle = false;
    for (uint32_t from = 0; from < n; ++from)
        if (color[from] == 0)
            dfs(graph, from, color, top_sort, has_cycle);

    // Print sorted graph if there're no cycles:
    if (!has_cycle) {
        while (!top_sort.empty()) {
            std::cout << top_sort.top() + 1 << " ";
            top_sort.pop();
        }
    } else {
        std::cout << -1;
    }

    return 0;
}
