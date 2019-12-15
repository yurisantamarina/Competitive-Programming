#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0); cin.tie(0);
#define MAXN 301010
#define F first
#define S second
typedef long long int ll;

using namespace std;

void Reset(int n, vector<vector<int>>& graph) {
    graph.clear();
    graph.resize(n);
}

bool IsArticulationPoint(int u, int root, const vector<vector<int>>& graph, vector<bool>& seen, vector<int>& discovery_time, vector<int>& low, vector<int>& parent, int& cur_time, vector<int>& subtree_size) {
    discovery_time[u] = low[u] = cur_time;
    ++cur_time;
    seen[u] = true;
    subtree_size[u] = 1;
    int num_children = 0;
    for (int v : graph[u]) {
        if (!seen[v]) {
            ++num_children;
            parent[v] = u;
            IsArticulationPoint(v, root, graph, seen, discovery_time, low, parent, cur_time, subtree_size);
            low[u] = min(low[u], low[v]);
            subtree_size[u] += subtree_size[v];
        } else if (v != parent[u]) {
            low[u] = min(low[u], discovery_time[v]);
        }
    }
    if (u == root) {
        return num_children > 1;
    }
    return false;
}

int GetIsolatedNodes(int cur_fair, int other_fair, const vector<vector<int>>& graph, int n) {
    vector<bool> seen(n, false);
    vector<int> discovery_time(n, 0);
    vector<int> low(n, 0);
    vector<int> parent(n, -1);
    vector<int> substree_size(n, 0);
    int cur_time = 1;
    if (!IsArticulationPoint(cur_fair, cur_fair, graph, seen, discovery_time, low, parent, cur_time, substree_size)) {
        return -1;
    }
    int u = other_fair;
    while(parent[u] != cur_fair) {
        u = parent[u];
    }
    return n - substree_size[u] - 1;
}

int main() {
    fast;
    int num_cases;
    cin >> num_cases;
    vector<vector<int>> graph;
    while (num_cases > 0) {
        --num_cases;
        int n, m, a, b;
        cin >> n >> m >> a >> b;
        --a;
        --b;
        Reset(n, graph);
        for (int i = 0; i < m; ++i) {
            int u, v;
            cin >> u >> v;
            --u;
            --v;
            graph[u].push_back(v);
            graph[v].push_back(u);
        }
        int isolated_a = GetIsolatedNodes(a, b, graph, n);
        int isolated_b = GetIsolatedNodes(b, a, graph, n);
        if (isolated_a == -1 || isolated_b == -1) {
            cout << "0\n";
        } else {
            cout << (ll)isolated_a * isolated_b << "\n";
        }
    }
    return 0;
}