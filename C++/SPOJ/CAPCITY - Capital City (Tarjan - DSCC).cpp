#include <bits/stdc++.h>

using namespace std;
#define MAXN 201010
#define pb push_back

vector<int> g[MAXN];
int n, m, d[MAXN], low[MAXN], seen[MAXN], comp[MAXN], out[MAXN], tempo = 1, sccCounter = 1;
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
		int x = p.top(); p.pop();
		comp[x] = sccCounter;
		d[x] = 1e9;
		if(x == u) break;
	}
	
	sccCounter++;
}

int main(){
	scanf("%d %d", &n, &m);
	int u, v;
	for (int i = 0; i < m; i++)
	{
		scanf("%d %d", &u, &v);
		g[u].pb(v);
	}
	
	for (int i = 1; i <= n; i++)
		if(!seen[i])
			dfs(i);
	
	for(u = 1; u <= n; u++)
		for(int x : g[u])
			if(comp[u] != comp[x] && !mapa.count({comp[u], comp[x]})){
				out[comp[u]]++;
				mapa[{comp[u], comp[v]}];
			}
	
	int cnt = 0;
	for(int i = 1; i < sccCounter; i++)
		cnt += (out[i] == 0);
	
	if(cnt > 1) printf("0\n\n");
	else{
		
		vector<int> saida;
		for(int i = 1; i <= n; i++)
			if(out[comp[i]] == 0)
				saida.pb(i);
		
		printf("%d\n", (int)saida.size());
		for(int x : saida)
			printf("%d ", x);
		printf("\n");
	}
	
	return 0;
}
