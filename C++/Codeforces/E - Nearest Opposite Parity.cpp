#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0); cin.tie(0);
#define MAXN 301010
#define F first
#define S second
typedef long long int ll;
 
using namespace std;
 
void Bfs(int parity, vector<int>& min_dist, const vector<vector<int>>& g, int n, const vector<int>& a) {
    queue<int> q;
    vector<int> dist(n, INT_MAX);
    for (int i = 0; i < n; ++i) {
        if ((a[i] & 1) == parity) {
            q.push(i);
            dist[i] = 0;
        }
    }
    while(!q.empty()) {
        int u = q.front();
        q.pop();
        for (int v : g[u]) {
            if (dist[u] + 1 < dist[v]) {
                dist[v] = dist[u] + 1;
                q.push(v);
            }
        }
    }
    for (int i = 0; i < n; ++i) {
        if ((a[i] & 1) != parity) {
            if (dist[i] != INT_MAX) {
                min_dist[i] = dist[i];
            }
        }
    }
}
 
int main() {
    int n;
    cin >> n;
    vector<vector<int>> g(n);
    vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
        if (i + a[i] < n) {
            g[i + a[i]].push_back(i);
        }
        if (i - a[i] >= 0) {
            g[i - a[i]].push_back(i);
        }
    }
    vector<int> min_dist(n, -1);
    Bfs(0, min_dist, g, n, a);
    Bfs(1, min_dist, g, n, a);
    for (int d : min_dist) {
        cout << d << " ";
    }
    cout << "\n";
 
    
 
    return 0;
}