#include <bits/stdc++.h>

using namespace std;
#define MAXN 200010
#define BLACK 1
#define WHITE 0

vector<int> g[MAXN];
vector<pair<int, int> > edge;
int color[MAXN];

bool bipartite(int u) {
	
	bool ans = true;
	for (int v : g[u]) {
		if (color[v] == -1) {
			color[v] = color[u] == BLACK ? WHITE : BLACK;
			ans &= bipartite(v);
		} else if(color[u] == color[v]) {
			return false;
		}
	}

	return ans;
}

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	int a, b, n, m;
	cin >> n >> m;

	for (int i = 0; i < m; i++) {
		cin >> a >> b;
		g[a].push_back(b);
		g[b].push_back(a);
		edge.push_back({a, b});
	}
	
	memset(color, -1, sizeof color);

	color[1] = BLACK;
	if (bipartite(1)) {
		cout << "YES\n";
		for (auto i : edge) {
			if (color[i.first] == BLACK && color[i.second] == WHITE) {
				cout << "1";
			} else {
				cout << "0";			}
		}
		cout << "\n";
	} else {
		cout << "NO\n";
	}
	
	
	
	return 0;
}