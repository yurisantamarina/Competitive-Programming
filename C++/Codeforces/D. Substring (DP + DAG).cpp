#include <bits/stdc++.h>

using namespace std;
#define MAXN 301010
#define pb push_back

int dp[MAXN][26];
int n, m;
int vis[MAXN];
string s;
bool cycle;
vector<int> g[MAXN];

void dfs(int u){
	if(cycle) return;
	if(vis[u] == 2) return;
	dp[u][s[u]-'a'] = 1;
	
	vis[u] = 1;
	for (int v : g[u])
	{
		if(vis[v] == 1){
			cycle = true;
			return;
		}
		if(vis[v] == 0) dfs(v);
		
		for (int i = 0; i < 26; i++)
			dp[u][i] = max(dp[u][i], (s[u]-'a' == i) + dp[v][i]);
		
	}
	vis[u] = 2;
}

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	int u, v;
	cin >> n >> m;
	cin >> s;
	for (int i = 0; i < m; i++)
	{
		cin >> u >> v;
		u--; v--;
		g[u].pb(v);
	}
	
	cycle = false;
	int ans = 0;
	
	for (int i = 0; i < n; i++)
	{
		if(vis[i] == 0) dfs(i);
		for(int j = 0; j < 26; j++) ans = max(ans, dp[i][j]);
	}
	if(!cycle) cout << ans << "\n";
	else cout << "-1\n";
	
	
	return 0;
}
