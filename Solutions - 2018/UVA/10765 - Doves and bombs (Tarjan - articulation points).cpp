#include <bits/stdc++.h>

using namespace std;
#define MAXN 101010
#define pb push_back
#define F first
#define S second

vector<int> g[MAXN];
int d[MAXN], low[MAXN], seen[MAXN], tempo, n, m, root;
vector<pair<int, int> > saida;

void dfs(int u, int pai){
	seen[u] = 1;
	d[u] = low[u] = tempo++;
	int nf = 0;
	int comp = 1;
	bool any = false;
	for(int v : g[u]){
		if(!seen[v]){
			dfs(v, u);
			low[u] = min(low[u], low[v]);
			nf++;
			if(d[u] <= low[v]){
				any = true;
				comp++;
			}
		}else if(v != pai)
			low[u] = min(low[u], d[v]);
	}
	
	if(u == root && nf >= 2){
		saida.pb({u, comp-1});
	}else if(u != root && any){
		saida.pb({u, comp});
	}else{
		saida.pb({u, 1});
	}
}

void reset(){
	saida.clear();
	for (int i = 0; i <= n; i++)
	{
		g[i].clear();
		seen[i] = d[i] = low[i] = 0;
	}
	tempo = 1;
}

int main(){
	int u, v;
	while (scanf("%d %d", &n, &m) != EOF)
	{
		if(n == 0 && m == 0) break;
		reset();
		
		while(scanf("%d %d", &u, &v) != EOF){
			if(u == -1 && v == -1) break;
			g[u].pb(v);
			g[v].pb(u);
		}
		
		for(int i = 0; i < n; i++)
			if(!seen[i]){
				root = i;
				dfs(i, i);
			}
				
		sort(saida.begin(), saida.end(), [](pair<int, int> a, pair<int, int> b){
												if(a.S != b.S) return a.S > b.S;
												return a.F < b.F;
												});
												
		for (int i = 0; i < m; i++)
			printf("%d %d\n", saida[i].F, saida[i].S);
		printf("\n");
	}
	
	
	
	return 0;
}
