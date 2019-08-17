#include <bits/stdc++.h>

using namespace std;
typedef long long int ll;
#define pb push_back
#define mp make_pair
#define F first
#define S second
#define MAXN 120
#define inf 1e9

vector<pair<int, int> > g[MAXN];
int n, q;
int cost[MAXN];
int tam[MAXN];
int dp[MAXN][MAXN];
vector<int> aux;

int dfs(int u, int pai){
	int ans = 1;
	aux.pb(u);
	int v;
	for (int i = 0; i < (int)g[u].size(); i++)
	{
		v = g[u][i].F;
		if(v == pai) continue;
		cost[v] = g[u][i].S;
		ans += dfs(v, u);
	}
	
	return tam[u] = ans;
}

int solve(int pos, int falta){
	if(falta == 0) return 0;
	if(falta < 0) return -inf;
	if(pos==n) return -inf;
	if(dp[pos][falta]!=-1) return dp[pos][falta];
	
	int ans = 0;
	ans = max(solve(pos+tam[aux[pos]], falta), cost[aux[pos]] + solve(pos+1, falta-1));
	
	return dp[pos][falta] = ans;
}

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	int u, v, w;
	cin >> n >> q;
	for (int i = 0; i < n-1; i++)
	{
		cin >> u >> v >> w;
		u--; v--;
		g[u].pb(mp(v, w));
		g[v].pb(mp(u, w));
	}
	
	dfs(0, 0);
	memset(dp, -1, sizeof dp);
	cout << solve(0, q+1) << "\n";
	
	
	
	return 0;
}

