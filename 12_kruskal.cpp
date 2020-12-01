#include <bits/stdc++.h>

class DisjointSetUnion {
    private:
        struct Subset {
            uint32_t parent;
            uint32_t rank;
        };
        std::vector<Subset> p;

    public:
        void init(const uint32_t& n) {
            p.resize(n);
            for (size_t i = 0; i < n; ++i) {
                p[i].parent = i;
                p[i].rank = 0;
            }
        }

        uint32_t get(const uint32_t& x) {
            if (p[x].parent != x)
                p[x].parent = get(p[x].parent);
            return p[x].parent;
        }

        void join(uint32_t x, uint32_t y) {
            x = get(x);
            y = get(y);

            if (x == y)
                return;

            if (p[x].rank > p[y].rank)
                std::swap(x, y);

            if (p[x].rank == p[y].rank)
                ++p[y].rank;

            p[x].parent = y;
        }
};


struct Edge {
    uint32_t from;
    uint32_t to;
    uint32_t weight;
};


uint64_t kruskal(const std::vector<Edge>& graph, DisjointSetUnion& dsu) {
    uint64_t result = 0;
    for (const auto& edge : graph) {
        if (dsu.get(edge.from) != dsu.get(edge.to)) {
            result += edge.weight;
            dsu.join(edge.from, edge.to);
        }
    }
    return result;
}


int main() {
    std::iostream::sync_with_stdio(false);
    std::cin.tie(nullptr);

    uint32_t n, m;
    std::cin >> n >> m;

    DisjointSetUnion dsu;
    dsu.init(n);

    std::vector<Edge> graph(m);
    uint32_t from, to, weight;
    for (size_t i = 0; i < m; ++i) {
        std::cin >> from >> to >> weight;
        graph[i] = {from - 1, to - 1, weight};
    }

    std::sort(graph.begin(), graph.end(),
              [](const auto& lhs, const auto& rhs) {
        return lhs.weight < rhs.weight;
    });

    std::cout << kruskal(graph, dsu) << "\n";

    return 0;
}
