#include <bits/stdc++.h>

using namespace std;
#define MAXN 101010
#define pb push_back
typedef long long int ll;
vector<int> g[MAXN];
int d[MAXN], low[MAXN], seen[MAXN], tempo = 1, n, m;
bool hasBridge;

void dfs(int u, int pai){
	if(hasBridge) return;
	seen[u] = 1;
	d[u] = low[u] = tempo++;
	
	for(int v : g[u]){
		if(!seen[v]){
			dfs(v, u);
			low[u] = min(low[u], low[v]);
			
			if(d[u] < low[v])
				hasBridge = true;
		}else if(v != pai)
			low[u] = min(low[u], d[v]);
	}
}

void reset(){
	for(int i = 1; i <= n; i++){
		g[i].clear();
		seen[i] = d[i] = low[i] = 0;
	}
	hasBridge = false;
	tempo = 1;
}

int main(){
	
	int u, v;
	while(scanf("%d %d", &n, &m), n && m){
		reset();
		for (int i = 0; i < m; i++)
		{
			scanf("%d %d", &u, &v);
			g[u].pb(v);
			g[v].pb(u);
		}
		
		dfs(1, 1);
		printf("%c\n", hasBridge ? 'N' : 'S');
	}
	
	return 0;
}
