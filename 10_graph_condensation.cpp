#include <bits/stdc++.h>


void dfs(std::vector<std::vector<uint32_t>>& graph,
         const uint32_t& from,
         std::vector<bool>& used,
         std::stack<uint32_t>& top_sort) {
    used[from] = true;
    for (const auto& to : graph[from])
        if (!used[to])
            dfs(graph, to, used, top_sort);
    top_sort.push(from);
}

void dfs_inv(std::vector<std::vector<uint32_t>>& graph_inv,
             uint32_t from,
             std::vector<uint32_t>& scc,
             uint32_t current_scc) {
    scc[from] = current_scc;
    for (const auto& to : graph_inv[from])
        if (scc[to] == 0)
            dfs_inv(graph_inv, to, scc, current_scc);
}

int main() {
    std::iostream::sync_with_stdio(false);
    std::cin.tie(nullptr);

    uint32_t n, m;
    std::cin >> n >> m;

    // Read graph and build its inversed graph:
    std::vector<std::vector<uint32_t>> graph(n), graph_inv(n);
    uint32_t from, to;
    for (uint32_t i = 0; i < m; ++i) {
        std::cin >> from >> to;
        --from;
        --to;
        graph[from].push_back(to);
        graph_inv[to].push_back(from);
    }

    // Perform topological sorting of the graph.
    // We don't care about cycles here:
    std::vector<bool> used(n, false);
    std::stack<uint32_t> top_sort;
    for (uint32_t from = 0; from < n; ++from)
        if (!used[from])
            dfs(graph, from, used, top_sort);

    // Find strongly connected components (scc)
    // for the inversed graph, picking vertices
    // in the order of top_sort:
    uint32_t scc_num = 0;
    std::vector<uint32_t> scc(n, 0);
    while (!top_sort.empty()) {
        auto from = top_sort.top();
        top_sort.pop();
        if (scc[from] == 0) {
            ++scc_num;
            dfs_inv(graph_inv, from, scc, scc_num);
        }
    }

    // Count edges in the condensation of the graph:
    std::set<std::pair<uint32_t, uint32_t>> edges_num;
    for (uint32_t from = 0; from < n; ++from)
        for (const auto& to : graph[from])
            if (scc[from] != scc[to])
                edges_num.insert({scc[from], scc[to]});

    std::cout << edges_num.size();

    return 0;
}
