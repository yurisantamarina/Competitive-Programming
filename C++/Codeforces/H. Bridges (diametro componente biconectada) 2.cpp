#include <bits/stdc++.h>

using namespace std;
#define MAXN 201010
#define mp make_pair
#define pb push_back
#define F first
#define S second

vector<int> g[MAXN], tr[MAXN];
int d[MAXN], seen[MAXN], low[MAXN], comp[MAXN], tempo, n, dist[MAXN], bridges;
stack<int> pilha;

void dfs(int u, int pai, bool flag){//true constroi componentes, false constroi a arvore
	seen[u] = 1;
	d[u] = low[u] = tempo++;
	
	if(flag)
		pilha.push(u);
	
	for(int v : g[u]){
		
		if(!seen[v]){
			dfs(v, u, flag);
			low[u] = min(low[u], low[v]);
			
			if(d[u] < low[v]){//essa aresta u-v é uma ponte
				if(flag){
					while(!pilha.empty()){
						int x = pilha.top();
						comp[x] = v;
						pilha.pop();
						if(x == v) break;
					}
					bridges++;
				}else{
					tr[comp[u]].pb(comp[v]);
					tr[comp[v]].pb(comp[u]);
					//~ printf("aresta entre %d e %d\n", comp[u], comp[v]);
				}
			}
			
		}else if(v != pai)
			low[u] = min(low[u], d[v]);
			
	} 
}

void reset(){
	for (int i = 0; i <= n; i++)
	{
		g[i].clear();
		tr[i].clear();
		seen[i] = 0;
	}
	while(!pilha.empty()) pilha.pop();
	bridges = 0;
}

void diameter(int u, int pai){
	for(int v : tr[u])
		if(v != pai){
			dist[v] = dist[u] + 1;
			diameter(v, u);
		}
}

int main(){
	int m, tc, u, v;
	scanf("%d", &tc);
	while (tc--)
	{
		scanf("%d %d", &n, &m);
		reset();
		for (int i = 0; i < m; i++)
		{
			scanf("%d %d", &u, &v);
			g[u].pb(v);
			g[v].pb(u);
		}
		
		memset(seen, 0, sizeof seen);
		tempo = 1;
		dfs(1, 1, true);
		while(!pilha.empty()){
			comp[pilha.top()] = 1;
			pilha.pop();
		}
		
		memset(seen, 0, sizeof seen);
		tempo = 1;
		dfs(1, 1, false);
		
		//~ for (int i = 1; i <= n; i++)
		//~ {
			//~ printf("comp[%d] = %d\n", i, comp[i]);
		//~ }
		int ponta1 = 0, ponta2 = 0;
		
		memset(dist, 0, sizeof dist);
		diameter(1, 1);
		for(int i = 1; i <= n; i++)
			if(dist[i] > dist[ponta1])
				ponta1 = i;
		
		memset(dist, 0, sizeof dist);
		diameter(ponta1, ponta1);
		for(int i = 1; i <= n; i++)
			if(dist[i] > dist[ponta2])
				ponta2 = i;
		
		printf("%d\n", bridges - dist[ponta2]);
	}
	
	
	return 0;
}
