#include <bits/stdc++.h>


void dfs(std::map<std::string, std::vector<std::string>>& graph,
         const std::string& from,
         std::map<std::string, bool>& used,
         uint16_t& max_depth,
         uint16_t cur_depth = 1) {
    used[from] = true;

    max_depth = std::max(max_depth, cur_depth);
    ++cur_depth;

    for (const auto& to : graph[from])
        if (!used[to])
            dfs(graph, to, used, max_depth, cur_depth);
}


int main() {
    std::iostream::sync_with_stdio(false);
    std::cin.tie(nullptr);

    uint16_t n;
    std::cin >> n;

    // Read graph:
    std::map<std::string, std::vector<std::string>> graph;
    std::string name1, reposted, name2;
    for (size_t i = 0; i < n; ++i) {
        std::cin >> name1 >> reposted >> name2;
        std::transform(name1.begin(), name1.end(), name1.begin(), ::tolower);
        std::transform(name2.begin(), name2.end(), name2.begin(), ::tolower);
        graph[name2].push_back(name1);
    }

    // Calculate max graph depth:
    uint16_t max_depth = 0;
    std::map<std::string, bool> used;
    dfs(graph, "polycarp", used, max_depth);

    // Print max graph depth:
    std::cout << max_depth << "\n";

    return 0;
}
