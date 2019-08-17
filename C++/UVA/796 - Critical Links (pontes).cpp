#include <bits/stdc++.h>

using namespace std;
#define MAXN 201010
#define pb push_back
#define mp make_pair
#define F first
#define S second

typedef pair<int, int> pii;
vector<int> g[MAXN];
char seen[MAXN];
int root, tempo, d[MAXN], low[MAXN], n;
vector<pii> ponte;

void dfs(int u, int p){
	seen[u] = 1;
	d[u] = low[u] = tempo++;
	for(int v : g[u]){
		if(!seen[v]){
			dfs(v, u);
			low[u] = min(low[u], low[v]);
			
			if(d[u] < low[v])
				ponte.pb(mp(min(u, v), max(u, v)));
		}else{
			if(v != p)
				low[u] = min(low[u], d[v]);
		}
	}
}

void reset(){
	for (int i = 0; i <= n; i++)
	{
		g[i].clear();
		seen[i] = 0;
	}
	tempo = 1;
	ponte.clear();
}

int main(){
	int u, v, qtd;
	while (scanf("%d", &n) != EOF)
	{
		reset();
		for (int i = 0; i < n; i++)
		{
			scanf("%d (%d)", &u, &qtd);
			while (qtd--)
			{
				scanf("%d", &v);
				//~ printf("%d-%d\n", u, v);
				g[u].pb(v);
			}
		}
		
		for(int i = 0; i < n; i++){
			if(seen[i]) continue;
			//~ printf("comecando em %d\n", i);
			root = i;
			dfs(i, i);
		}
		
		sort(ponte.begin(), ponte.end());
		printf("%d critical links\n", (int)ponte.size());
		for(pii p : ponte)
			printf("%d - %d\n", p.F, p.S);
		printf("\n");
	}
	
	
	
	return 0;
}
