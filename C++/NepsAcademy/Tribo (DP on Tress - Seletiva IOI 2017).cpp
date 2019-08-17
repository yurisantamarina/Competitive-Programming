#include <bits/stdc++.h>

using namespace std;
typedef long long int ll;
typedef long double ld;
typedef pair<int, int> pii;
#define fast ios_base::sync_with_stdio(0); cin.tie(0)
#define F first
#define S second
#define mp make_pair
#define pb push_back
#define MAXN 10101
#define MAXK 55

ll INF = (ll)1e12;
ll dp[MAXN][MAXK];
vector<pii> g[MAXN];
int n, k;

void dfs(int u, int pai){
	dp[u][1] = 0;
	
	//~ printf("n = %d  k = %d\n", n, k);
	//~ printf("u = %d  pai = %d   1\n", u, pai);
	int v, w;
	for(pii p : g[u]){
		v = p.F;
		w = p.S;
		if(v == pai) continue;
		dfs(v, u);
	}
	
	//~ return;
	//~ printf("u = %d  pai = %d   2\n", u, pai);
	ll tmp[MAXK];
	for(pii p : g[u]){
		v = p.F;
		w = p.S;
		if(v == pai) continue;
		
		for(int i = 1; i <= k; i++)
			tmp[i] = INF;
		
		for(int i = 1; i <= k; i++){
			for(int j = 1; j <= k; j++){
				if(i + j > k) break;
				tmp[i + j] = min(tmp[i + j], dp[u][i] + dp[v][j] + w);
			}
		}
		
		for(int i = 1; i <= k; i++)
			dp[u][i] = min(dp[u][i], tmp[i]);
	}
}

int main(){
	scanf("%d %d", &n, &k);
	int u, v, w;
	for (int i = 0; i < n - 1; i++)
	{
		scanf("%d %d %d", &u, &v, &w);
		g[u].push_back({v, w});
		g[v].push_back({u, w});
	}
	
	
	for(int i = 1; i <= n; i++)
		for(int j = 1; j <= k; j++)
			dp[i][j] = INF;
	
	//~ return 0;
	dfs(1, 1);
	ll ans = INF;
	for(int i = 1; i <= n; i++)
		ans = min(ans, dp[i][k]);
	printf("%lld\n", ans);
	
	return 0;
}
