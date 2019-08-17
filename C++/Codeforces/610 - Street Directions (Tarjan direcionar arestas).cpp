#include <bits/stdc++.h>

using namespace std;
#define MAXN 101010
#define F first
#define S second
#define pb push_back
#define mp make_pair

vector<int> g[MAXN];
vector<pair<int, int> > saida;
int d[MAXN], low[MAXN], tempo, seen[MAXN], n;

void dfs(int u, int pai){
	seen[u] = 1;
	d[u] = low[u] = tempo++;
	
	for(int v : g[u]){
		if(!seen[v]){
			dfs(v, u);
			low[u] = min(low[u], low[v]);
			if(d[u] < low[v]){
				saida.pb(mp(u, v));
				saida.pb(mp(v, u));
			}else
				saida.pb(mp(u, v));
		}else if(v != pai){
			low[u] = min(low[u], d[v]);
			if(d[v] < d[u]) saida.pb(mp(u, v));
		}
	}
}

void reset(){
	tempo = 1;
	saida.clear();
	for (int i = 0; i <= n; i++)
	{
		g[i].clear();
		d[i] = seen[i] = low[i] = 0;
	}
	
}

int main(){
	int caso = 1, m, u, v;
	while(scanf("%d %d", &n, &m) != EOF){
		if(n == 0 && m == 0) break;
		reset();
		for (int i = 0; i < m; i++)
		{
			scanf("%d %d", &u, &v);
			g[u].pb(v);
			g[v].pb(u);
		}
		dfs(1, 1);
		printf("%d\n\n", caso++);
		for (int i = 0; i < (int)saida.size(); i++)
			printf("%d %d\n", saida[i].F, saida[i].S);
		printf("#\n");
	}
	
	
	return 0;
}
