//~ http://codeforces.com/gym/100712

#include <bits/stdc++.h>

using namespace std;
#define MAXN 201010
#define pb push_back
#define mp make_pair
#define F first
#define S second

typedef pair<int, int> pii;
vector<int> g[MAXN];
int n, tot, d[MAXN], low[MAXN], tempo, seen[MAXN], sz[MAXN], longest[MAXN], ans;

void dfs(int u, int pai){
	seen[u] = 1;
	longest[u] = 0;
	int mx = -MAXN;
	int mx2 = -MAXN;
	d[u] = low[u] = tempo++;
	
	int at;
	for(int v : g[u]){
		if(!seen[v]){
			dfs(v, u);
			low[u] = min(low[u], low[v]);
			
			sz[u] += sz[v];
			if(d[u] < low[v]){
				sz[u]++;
				at = 1 + longest[v];
				tot++;
				
				longest[u] = max(longest[u], 1 + longest[v]);
			}else{
				longest[u] = max(longest[u], longest[v]);
				at = longest[v];
			}
			
			if(at >= mx){
				mx2 = mx;
				mx = at;
			}else if(at >= mx2){
				mx2 = at;
			}
			
				
			//~ printf("longest[%d] = %d\n", u, longest[u]);
			//~ printf("mx = %d\n", mx);
			//~ printf("mx2 = %d\n", mx2);
		}else if(v != pai) low[u] = min(low[u], d[v]);
	}
	
	ans = max(ans, mx + mx2);
	ans = max(ans, longest[u]);
}

void reset(){
	for (int i = 0; i <= n; i++)
	{
		g[i].clear();
		seen[i] = 0;
		longest[i] = 0;
		sz[i] = 0;
	}
	tot = 0;
	ans = 0;
	tempo = 1;
}

int main(){
	int tc, m, u, v;
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
		dfs(1, 1);
		//~ printf("tot = %d\n", tot);
		
		printf("%d\n", tot - ans);
	}
	
	
	
	
	return 0;
}
