#include <bits/stdc++.h>

using namespace std;
#define MAXN 10101
#define pb push_back

vector<int> g[MAXN], saida;
int n, m, d[MAXN], low[MAXN], seen[MAXN], comp[MAXN], tempo, counterScc, out[MAXN];
stack<int> p;
map<pair<int, int>, int> mapa;

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
	
	
	while(!p.empty()){
		int x = p.top();
		p.pop();
		comp[x] = counterScc;
		d[x] = 1e9;
		if(x == u) break;
	}
	
	counterScc++;
}

void reset(){
	mapa.clear();
	saida.clear();
	counterScc = tempo = 1;
	for (int i = 0; i <= n; i++)
	{
		g[i].clear();
		seen[i] = d[i] = low[i] = 0;
		out[i] = 0;
	}
	while(!p.empty()) p.pop();
}

int main(){
	int u, v;
	while (scanf("%d", &n) != EOF)
	{
		if(!n) break;
		scanf("%d", &m);
		reset();
		for (int i = 0; i < m; i++)
		{
			scanf("%d %d", &u, &v);
			g[u].pb(v);
		}
		
		
		for(int i = 1; i <= n; i++)
			if(!seen[i])
				dfs(i);
		
		for(u = 1; u <= n; u++){
			for(int x : g[u]){
				if(comp[u] != comp[x] && !mapa.count({comp[u], comp[x]})){
					out[comp[u]]++;
					mapa[{comp[u], comp[x]}];
				}
			}
		}
		
		for(int i = 1; i <= n; i++)
			if(out[comp[i]] == 0)
				saida.pb(i);
		sort(saida.begin(), saida.end());
		
		for(int i = 0; i < (int)saida.size(); i++){
			if(i) printf(" ");
			printf("%d", saida[i]);
		}
		printf("\n");
	}
	
	
	
	return 0;
}
