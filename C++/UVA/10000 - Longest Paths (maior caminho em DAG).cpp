#include <bits/stdc++.h>

using namespace std;

#define MAXN 101010
#define pb push_back

vector<int> g[MAXN], topo;
int d[MAXN], seen[MAXN];

void dfs(int u){
	seen[u] = 1;
	for(int v : g[u])
		if(!seen[v])
			dfs(v);
	topo.pb(u);
}

void reset(int n){
	for(int i = 1; i <= n; i++){
		g[i].clear();
		seen[i] = 0;
	}
	topo.clear();
}

int main(){
	int n, u, v, src, caso = 1;
	
	while(scanf("%d", &n), n){
		reset(n);
		scanf("%d", &src);
		
		while (scanf("%d %d", &u, &v), u && v)
			g[u].pb(v);
		
		dfs(src);
		reverse(topo.begin(), topo.end());
		
		for(int i = 1; i <= n; i++)
			d[i] = 0;
			
		d[src] = 0;
		for(int x : topo){
			for(int y : g[x]){
				d[y] = max(d[y], d[x] + 1);
			}
		}
		
		int ans = 0;
		for(int i = 1; i <= n; i++)
			if(d[i] > d[ans])
				ans = i;
		
		printf("Case %d: The longest path from %d has length %d, finishing at %d.\n\n", caso++, src, d[ans], ans);
	}
	
	return 0;
}
