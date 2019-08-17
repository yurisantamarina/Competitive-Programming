//~ http://codeforces.com/contest/1046/problem/B

#include <bits/stdc++.h>

using namespace std;
#define MAXN 301010
#define LOG 20

int d[MAXN], low[MAXN], tempo = 1, seen[MAXN], n, m, q, lca[MAXN][LOG], h[MAXN];
stack<int> p;
vector<int> g[MAXN], adj[MAXN], tmp;

void dfsTarjan(int u, int pai){
	p.push(u);
	seen[u] = 1;
	d[u] = low[u] = tempo++;
	for(int &v : adj[u]){
		if(!seen[v]){
			dfsTarjan(v, u);
			low[u] = min(low[u], low[v]);
			
			if(d[u] <= low[v]){
				tmp.clear();
				tmp.push_back(u);
				while (!p.empty())
				{
					int x = p.top(); p.pop();
					tmp.push_back(x);
					if(x == v) break;
				}
				
				int dummy = ++n;
				for (int &x : tmp)
				{
					g[dummy].push_back(x);
					g[x].push_back(dummy);
				}
				
			}
		}else if(v != pai)
			low[u] = min(low[u], d[v]);
	}
}

void dfs(int u, int pai){
	lca[u][0] = pai;
	h[u] = h[pai] + 1;
	for (int i = 1; i < LOG; i++)
		lca[u][i] = lca[lca[u][i - 1]][i - 1];
	
	for(int &v : g[u])
		if(v != pai)
			dfs(v, u);
}

int getLca(int u, int v){
	if(h[u] < h[v]) swap(u, v);
	int d = abs(h[u] - h[v]);
	for (int i = 0; i < LOG; i++)
		if(d & (1 << i))
			u = lca[u][i];
	if(u == v) return u;
	for(int i = LOG - 1; i >= 0; i--)
		if(lca[u][i] != lca[v][i]){
			u = lca[u][i];
			v = lca[v][i];
		}
	
	return lca[u][0];
}

int getDist(int u, int v){
	return h[u] + h[v] - 2 * h[getLca(u, v)];
}

int main(){
	scanf("%d %d %d", &n, &m, &q);
	int u, v;
	for (int i = 1; i <= m; i++)
	{
		scanf("%d %d", &u, &v);
		adj[u].push_back(v);
		adj[v].push_back(u);
	}
	
	dfsTarjan(1, 1);
	
	dfs(1, 1);
	
	while (q--)
	{
		scanf("%d %d", &u, &v);
		printf("%d\n", getDist(u, v) / 2);
	}
	
	return 0;
}
