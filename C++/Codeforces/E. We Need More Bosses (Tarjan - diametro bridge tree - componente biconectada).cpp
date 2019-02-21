#include <bits/stdc++.h>

using namespace std;
#define MAXN 301010
#define pb push_back

vector<int> g[MAXN], tr[MAXN];
int dp[MAXN], low[MAXN], d[MAXN], tempo, n, seen[MAXN], ans, comp[MAXN];
stack<int> p;

void dfs(int u, int pai, bool flag){
	seen[u] = 1;
	if(flag)
		p.push(u);
		
	d[u] = low[u] = tempo++;
	
	for(int v : g[u]){
		if(!seen[v]){
			dfs(v, u, flag);
			low[u] = min(low[u], low[v]);
			if(d[u] < low[v]){
				if(flag){
					while(!p.empty()){
						int x = p.top();
						comp[x] = v;
						p.pop();
						if(v == x) break;
					}
				}else{
					tr[comp[u]].pb(comp[v]);
					tr[comp[v]].pb(comp[u]);
				}
			}
		}else if(v!=pai)
			low[u] = min(low[u], d[v]);
	}
}

void diameter(int u, int pai){
	int mx1 = -INT_MAX, mx2 = -INT_MAX;
	for(int v : tr[u]){
		if(v == pai) continue;
		diameter(v, u);
		dp[u] = max(dp[u], 1 + dp[v]);
		
		if(1 + dp[v] >= mx1){
			mx2 = mx1;
			mx1 = 1 + dp[v];
		}else if(1 + dp[v] > mx2){
			mx2 = 1 + dp[v];
		}
	}
	
	ans = max(ans, dp[u]);
	if(mx1 >= 0 && mx2 >= 0)
		ans = max(ans, mx1 + mx2);
}

int main(){
	int m, u, v;
	scanf("%d %d", &n, &m);
	for (int i = 0; i < m; i++)
	{
		scanf("%d %d", &u, &v);
		g[u].pb(v);
		g[v].pb(u);
	}
	
	memset(seen, 0, sizeof seen);
	dfs(1, 1, true);
	while(!p.empty()){
		comp[p.top()] = 1;
		p.pop();
	}
	memset(seen, 0, sizeof seen);
	dfs(1, 1, false);

	diameter(1, 1);
	
	printf("%d\n", ans);
	
	return 0;
}
