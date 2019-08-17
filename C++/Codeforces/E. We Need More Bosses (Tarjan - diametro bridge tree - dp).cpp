#include <bits/stdc++.h>

using namespace std;
#define MAXN 301010
#define pb push_back

vector<int> g[MAXN];
int dp[MAXN], low[MAXN], d[MAXN], tempo, n, seen[MAXN], ans;

void dfs(int u, int pai){
	seen[u] = 1;
	
	d[u] = low[u] = tempo++;
	int mx1 = -INT_MAX/2 - 1;
	int mx2 = -INT_MAX/2 - 1;
	dp[u] = 0;
	for(int v : g[u]){
		if(!seen[v]){
			dfs(v, u);
			low[u] = min(low[u], low[v]);
			
			int at = dp[v];
			if(d[u] < low[v])
				at++;
			
			if(at >= mx1){
				mx2 = mx1;
				mx1 = at;
			}else if(at > mx2){
				mx2 = at;
			}
			dp[u] = max(dp[u], at);
		}else if(v != pai){
			low[u] = min(low[u], d[v]);
		}
	}
	
	ans = max(ans, dp[u]);
	if(mx1 >= 0 && mx2 >= 0)
		ans = max(ans, mx1+mx2);
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
	dfs(1, 1);
	
	printf("%d\n", ans);
	
	return 0;
}
