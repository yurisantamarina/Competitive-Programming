#include <bits/stdc++.h>
 
using namespace std;

const long long int kInf = 1000000000000000LL;

class Edge {
public:
	int from, to, cost;
	Edge(int from, int to, int cost) : from(from), to(to), cost(cost) {}
	bool operator < (const Edge& other) const {
		return cost < other.cost;
	}
};

long long int FloydWarshall(vector<vector<long long int> >& dist, int kth_path, int n) {
	
	for (int k = 0; k < n; k++) {
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
			}
		}
	}
	
	
	vector<long long int> smallest_paths;
	for (int i = 0; i < n; i++) {
		for (int j = i + 1; j < n; j++) {
			smallest_paths.push_back(dist[i][j]);
		}
	}
	
	sort(smallest_paths.begin(), smallest_paths.end());
	return smallest_paths[kth_path - 1];
}

int main() {
	int n, m, k;
	cin >> n >> m >> k;
	
	vector<Edge> edges;
	for (int i = 0; i < m; i++) {
		int u, v, w;
		cin >> u >> v >> w;
		u--;
		v--;
		edges.push_back({u, v, w});
	}
	
	vector<vector<long long int> > dist(1000, vector<long long int>(1000, kInf));
	
	if (int{edges.size()} >= k) {
		sort(edges.begin(), edges.end());
		vector<int> used_v;
		for (int i = 0; i < k; i++) {
			used_v.push_back(edges[i].from);
			used_v.push_back(edges[i].to);
		}
		sort(used_v.begin(), used_v.end());
		used_v.resize(distance(used_v.begin(), unique(used_v.begin(), used_v.end())));
		map<int, int> new_id;
		for (int i = 0; i < int{used_v.size()}; i++) {
			new_id[used_v[i]] = i;
			dist[i][i] = 0LL;
		}
		for (int i = 0; i < k; i++) {
			const Edge& edge = edges[i];
			int u = new_id[edge.from];
			int v = new_id[edge.to];
			dist[u][v] = edge.cost;
			dist[v][u] = edge.cost;
		}
	} else {
		for (const Edge& edge : edges) {
			int u = edge.from;
			int v = edge.to;
			dist[u][v] = edge.cost;
			dist[v][u] = edge.cost;
		}
		for (int i = 0; i < n; i++) {
			dist[i][i] = 0LL;
		}
		
	}
	
	cout << FloydWarshall(dist, k, 802) << "\n";
	
}
