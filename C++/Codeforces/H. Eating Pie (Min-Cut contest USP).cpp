//~ http://codeforces.com/gym/101484/problem/H

#include <bits/stdc++.h>

using namespace std;
#define MAXN 1010
#define INF 1010101010

struct edge{
	int from, to, f, c;
	edge(){}
	edge(int a, int b, int cc, int d){
		from = a;
		to = b;
		f = cc;
		c = d;
	}
};

int dist[MAXN], ptr[MAXN], tmp[MAXN][MAXN], p[MAXN], gg[MAXN];
bool joao[MAXN], nicoleta[MAXN];
vector<edge> ed;
int K, N, A, B;
vector<int> g[MAXN];

void add_edge(int from, int to, int c){
	g[from].push_back(ed.size());
	ed.push_back(edge(from, to, 0, c));
	
	g[to].push_back(ed.size());
	ed.push_back(edge(to, from, 0, 0));
}

bool bfs(int src, int sink){
	
	for (int i = 0; i <= sink; i++)
		dist[i] = -1;
	
	dist[src] = 0;
	
	queue<int> q;
	q.push(src);
	
	int v, u, cap, idx;
	while (!q.empty())
	{
		u = q.front();
		q.pop();
		//~ if(u == sink) return;
		
		for(int i = 0; i < g[u].size(); i++){
			idx = g[u][i];
			v = ed[idx].to;
			cap = ed[idx].c - ed[idx].f;
			
			if(dist[v] == -1 && cap > 0){
				dist[v] = dist[u] + 1;
				q.push(v);
			}
		}
		
	}
	
	
	return dist[sink] != -1;
}

int dfs(int u, int mn, int sink){
	if(u == sink) return mn;
	
	int idx, v, cap;
	for(int &i = ptr[u]; i < g[u].size(); i++){
		idx = g[u][i];
		v = ed[idx].to;
		cap = ed[idx].c - ed[idx].f;
		
		if(dist[v] == dist[u] + 1 && cap > 0){
			if(int a = dfs(v, min(mn, cap), sink)){
				ed[idx].f += a;
				ed[idx^1].f -= a;
				
				return a;
			}
		}
	}
	
	return 0;
}

int penalty(int src, int sink){
	int flow = 0;
	
	while (bfs(src, sink))
	{
		memset(ptr, 0, sizeof ptr);
		//~ cout << "oi\n";
		while(int a = dfs(src, INF, sink))
			flow += a;
	}
	return flow;
}

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cin >> K >> N >> A >> B;
	
	int src = 0, sink = K + 1, type;
	
	for (int i = 0; i < A; i++)
	{
		cin >> type;
		joao[type] = true;
	}
	for (int i = 0; i < B; i++)
	{
		cin >> type;
		nicoleta[type] = true;
	}
	
	for (int i = 1; i <= K; i++)
	{
		if(joao[i] && !nicoleta[i]){
			add_edge(src, i, INF);
		}
		if(!joao[i] && nicoleta[i]){
			add_edge(i, sink, INF);
		}
	}
	
	for (int i = 0; i < N; i++)
		cin >> p[i];
	
	int ans = 0;
	for (int i = 0; i < N-1; i++)
	{
		cin >> gg[i];
		ans += gg[i];
		tmp[min(p[i], p[i+1])][max(p[i], p[i+1])] += gg[i];
	}
	
	for (int i = 1; i <= K; i++)
	{
		for (int j = i+1; j <= K; j++)
		{
			if(!tmp[i][j]) continue;
			add_edge(i, j, tmp[i][j]);
			add_edge(j, i, tmp[i][j]);
		}
	}
	
	cout << ans - penalty(src, sink) << "\n";
	
	
	return 0;
}
