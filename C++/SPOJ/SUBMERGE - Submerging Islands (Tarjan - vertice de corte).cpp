#include <bits/stdc++.h>

using namespace std;
#define MAXN 101010
#define pb push_back

vector<int> g[MAXN];
int d[MAXN], low[MAXN], seen[MAXN], vcorte, tempo, root, n;

void dfs(int u, int pai){
	
	seen[u] = 1;
	d[u] = low[u] = tempo++;
	
	bool any = false;
	int nf = 0;
	for(int v : g[u]){
		if(!seen[v]){
			dfs(v, u);
			low[u] = min(low[u], low[v]);
			nf++;
			if(d[u] <= low[v]) any = true;
		}else if(v != pai)
			low[u] = min(low[u], d[v]);
	}
	
	if(root == u && nf >= 2) vcorte++;
	else if(root != u && any) vcorte++;
	
}

void reset(){
	for (int i = 0; i <= n; i++)
	{
		g[i].clear();
		low[i] = d[i] = seen[i] = 0;
	}
	vcorte = 0;
	tempo = 1;
}

int main(){
	int m, u, v;
	while (scanf("%d %d", &n, &m) != EOF)
	{
		if(!n && !m) break;
		reset();
		for (int i = 0; i < m; i++)
		{
			scanf("%d %d", &u, &v);
			g[u].pb(v);
			g[v].pb(u);
		}
		
		for (int i = 1; i <= n; i++)
		{
			if(!seen[i]){
				root = i;
				dfs(i, i);
			}
		}
		
		printf("%d\n", vcorte);
	}
	
	
	
	return 0;
}
