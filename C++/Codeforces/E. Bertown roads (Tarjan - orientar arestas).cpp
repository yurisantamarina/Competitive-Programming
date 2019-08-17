#include <bits/stdc++.h>

using namespace std;
#define MAXN 201010

vector<int> g[MAXN];
int d[MAXN], low[MAXN], seen[MAXN], tempo = 1, pontes;
vector<pair<int, int> > saida;

void dfs(int u, int pai){
	seen[u] = 1;
	d[u] = low[u] = tempo++;
	
	for(int v : g[u]){
		if(!seen[v]){
			
			dfs(v, u);
			low[u] = min(low[u], low[v]);
			
			saida.push_back({u, v});
			if(d[u] < low[v]) pontes++;
			
		}else if(v != pai){
			low[u] = min(low[u], d[v]);
			if(d[v] < d[u])
				saida.push_back({u, v});
		}
	}
}

int main(){
	int n, m, u, v;
	scanf("%d %d", &n, &m);
	for (int i = 0; i < m; i++)
	{
		scanf("%d %d", &u, &v);
		g[u].push_back(v);
		g[v].push_back(u);
	}
	
	for(int i = 1; i <= n; i++)
		if(!seen[i])
			dfs(i, i);
	
	if(pontes) printf("0\n");
	else{
		for(pair<int, int> pp : saida)
			printf("%d %d\n", pp.first, pp.second);
	}
	
	return 0;
}
