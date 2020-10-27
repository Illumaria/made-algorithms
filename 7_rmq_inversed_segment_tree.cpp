#include <bits/stdc++.h>


#define MAX_VALUE static_cast<int32_t>((1 << 31) - 1)


struct Query {
    uint32_t left;
    uint32_t right;
    int32_t val;
};


class SegmentTree {
 private:
    struct Node {
        uint32_t left;
        uint32_t right;
        int32_t val;
        int32_t set_val;
        bool updated;

        Node(): left(0), right(0),
                val(MAX_VALUE), set_val(MAX_VALUE),
                updated(false) {}
    };
    std::vector<Node> t;
    uint32_t n, m;

 public:
    explicit SegmentTree(const uint32_t& n): n(n), m(1) {
        while (m < n)
            m *= 2;
        t.resize(2 * m - 1);
    }

    void build() {
        for (size_t i = 0; i < m; ++i) {
            t[m - 1 + i].val = MAX_VALUE;
            t[m - 1 + i].set_val = t[m - 1 + i].val;
            t[m - 1 + i].left = i;
            t[m - 1 + i].right = i;
        }

        if (m > 1) {
            for (ssize_t i = m - 2; i > -1; --i) {
                t[i].val = MAX_VALUE;
                t[i].set_val = t[i].val;
                t[i].left = t[2 * i + 1].left;
                t[i].right = t[2 * i + 2].right;
            }
        }
    }

    void push_set(const uint32_t& v) {
        if (t[v].updated) {
            t[v].val = t[v].set_val;
            t[v].updated = false;

            if (t[v].left != t[v].right) {
                t[2 * v + 1].set_val = t[v].set_val;
                t[2 * v + 1].updated = true;

                t[2 * v + 2].set_val = t[v].set_val;
                t[2 * v + 2].updated = true;
            }
        }
    }

    void set(const int32_t& value, const uint32_t& v,
             const uint32_t& left, const uint32_t& right) {
        if (t[v].left <= right && t[v].right >= left) {
            push_set(v);

            if (t[v].left >= left && t[v].right <= right) {
                t[v].set_val = value;
                t[v].updated = true;
            } else {
                set(value, 2 * v + 1, left, right);
                set(value, 2 * v + 2, left, right);

                t[v].val = std::min(t[2 * v + 1].set_val,
                                    t[2 * v + 2].set_val);
                t[v].set_val = t[v].val;
            }
        }
    }

    int32_t get_min(const uint32_t& v,
                    const uint32_t& left, const uint32_t& right) {
        int32_t result = MAX_VALUE;
        if (t[v].left <= right && t[v].right >= left) {
            push_set(v);

            if (t[v].left >= left && t[v].right <= right) {
                result = t[v].val;
            } else {
                result = std::min(get_min(2 * v + 1, left, right),
                                  get_min(2 * v + 2, left, right));
            }
        }

        return result;
    }

    void final_push() {
        for (size_t i = 0; i < m - 1 + n; ++i)
            push_set(i);
    }

    int32_t get_val(uint32_t i) const {
        return t[m - 1 + i].val;
    }
};


int main() {
    std::iostream::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::freopen("rmq.in", "r", stdin);
    std::freopen("rmq.out", "w", stdout);

    uint32_t n, m;
    std::cin >> n >> m;

    std::vector<Query> q(m);
    for (size_t i = 0; i < m; ++i)
        std::cin >> q[i].left >> q[i].right >> q[i].val;

    std::sort(q.begin(), q.end(), [](auto& left, auto& right) {
        return left.val < right.val;
    });

    SegmentTree st(n);
    st.build();

    for (size_t i = 0; i < m; ++i)
        st.set(q[i].val, 0, q[i].left - 1, q[i].right - 1);

    bool consistent = true;
    for (size_t i = 0; i < m; ++i)
        if (st.get_min(0, q[i].left - 1, q[i].right - 1) != q[i].val) {
            consistent = false;
            break;
        }

    if (!consistent) {
        std::cout << "inconsistent\n";
    } else {
        std::cout << "consistent\n";
        st.final_push();
        for (size_t i = 0; i < n; ++i)
            std::cout << st.get_val(i) << " ";
    }

    return 0;
}
