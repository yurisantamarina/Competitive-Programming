#include <bits/stdc++.h>

using namespace std;
typedef long long int ll;

#define pb push_back
#define mp make_pair
#define F first
#define S second
#define MAXN 10010
#define INF 100000000000LL
vector<pair<ll, ll> > g[MAXN];
ll tmp[60];
ll dp[MAXN][60];
ll n, k;


void dfs(int u, int pai){
	dp[u][0] = 0;
	dp[u][1] = 0;
	for (int i = 2; i <= k; i++)
	{
		dp[u][i] = INF;
	}
	
	int v, w;
	for (int i = 0; i < (int)g[u].size(); i++)
	{
		v = g[u][i].F;
		w = g[u][i].S;
		if(v == pai) continue;
		
		dfs(v, u);
		
		for (int j = 0; j <= k; j++)
			tmp[j] = INF;
		
		for (int a = 1; a <= k; a++)
		{
			for (int b = 0; b <= k; b++)
			{
				if(a + b > k) break;
				
				tmp[a+b] = min(tmp[a+b], dp[u][a] + dp[v][b] + w);
			}
			
		}
		
		for (int j = 0; j <= k; j++)
			dp[u][j] = min(dp[u][j], tmp[j]);
	}
	
}

int main(){
	int u, v, c;
	cin >> n >> k;
	for (int i = 0; i < n-1; i++)
	{
		cin >> u >> v >> c;
		g[u].pb(mp(v, c));
		g[v].pb(mp(u, c));
	}
	
	dfs(1, 1);
	
	ll ans = INF;
	for (int i = 1; i <= n; i++)
	{
		ans = min(ans, dp[i][k]);
	}
	
	cout << ans << "\n";
	
	
	return 0;
}
