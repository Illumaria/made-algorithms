#include <bits/stdc++.h>


void dfs(std::vector<std::vector<uint32_t>>& graph,
         std::set<uint32_t>& articulation_points,
         std::vector<bool>& used,
         std::vector<uint32_t>& time_in,
         std::vector<uint32_t>& time_out,
         uint32_t& time,
         uint32_t from,
         ssize_t parent = -1) {
    used[from] = true;
    time_in[from] = time_out[from] = time++;
    uint32_t children_num = 0;
    for (const auto& to : graph[from]) {
        if (to != parent) {
            if (used[to]) {  // There's an alternative route to the "to" vertex
                time_out[from] = std::min(time_out[from], time_in[to]);
            } else {  // No other routes or first time here
                dfs(graph, articulation_points, used,
                    time_in, time_out, time, to, from);
                ++children_num;
                time_out[from] = std::min(time_out[from], time_out[to]);
                // Check if we can go higher than the "from" vertex:
                if ((time_in[from] <= time_out[to]) && (parent != -1))
                    articulation_points.insert(from);
            }
        }
    }

    // Special case of the initial vertex:
    if ((parent == -1) && (children_num > 1))
        articulation_points.insert(from);
}


int main() {
    std::iostream::sync_with_stdio(false);
    std::cin.tie(nullptr);

    uint32_t n, m;
    std::cin >> n >> m;

    // Read graph:
    std::vector<std::vector<uint32_t>> graph(n);
    uint32_t from, to;
    for (uint32_t i = 0; i < m; ++i) {
        std::cin >> from >> to;
        --from;
        --to;
        graph[from].push_back(to);
        if (from != to)
            graph[to].push_back(from);
    }

    // Find articulation points:
    std::set<uint32_t> articulation_points;
    std::vector<bool> used(n, false);
    std::vector<uint32_t> time_in(n), time_out(n);
    uint32_t time = 0;
    for (uint32_t from = 0; from < n; ++from)
        if (!used[from])
            dfs(graph, articulation_points, used,
                time_in, time_out, time, from);

    // Print the number of articulation points
    // and their corresponding vertices:
    std::cout << articulation_points.size() << "\n";
    for (const auto& x : articulation_points)
        std::cout << x + 1 << " ";

    return 0;
}
