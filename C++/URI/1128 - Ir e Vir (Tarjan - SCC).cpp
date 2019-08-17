#include <bits/stdc++.h>

using namespace std;
#define MAXN 3010
#define pb push_back

vector<int> g[MAXN];
int d[MAXN], seen[MAXN], low[MAXN], tempo, n, comp[MAXN], scc;
stack<int> p;

void dfs(int u){
	seen[u] = 1;
	d[u] = low[u] = tempo++;
	p.push(u);
	
	for(int v : g[u]){
		if(!seen[v]){
			dfs(v);
			low[u] = min(low[u], low[v]);
		}else
			low[u] = min(low[u], d[v]);
	}
	
	if(low[u] < d[u]) return;
	
	scc++;
	while(!p.empty()){
		int x = p.top();
		p.pop();
		comp[x] = u;
		d[x] = 1e9;
		if(x == u) break;
	}
}

void reset(){
	for(int i = 1; i <= n; i++){
		g[i].clear();
		d[i] = seen[i] = low[i] = 0;
	}
	tempo = 1;
	scc = 0;
	while(!p.empty()) p.pop();
}

int main(){
	int m, u, v, op;
	while (scanf("%d %d", &n, &m) != EOF)
	{
		if(n == 0 && m == 0) break;
		reset();
		for (int i = 0; i < m; i++)
		{
			scanf("%d %d %d", &u, &v, &op);
			g[u].pb(v);
			if(op == 2)
				g[v].pb(u);
		}
		for(int i = 1; i <= n; i++)
			if(!seen[i])
				dfs(i);
		
		printf("%d\n", scc == 1);
	}
	
	
	return 0;
}
