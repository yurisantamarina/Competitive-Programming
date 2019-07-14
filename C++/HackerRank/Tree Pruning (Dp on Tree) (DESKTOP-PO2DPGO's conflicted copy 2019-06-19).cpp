#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair
#define F first
#define S second
#define oioi printf("oioi\n")
#define eoq cout << "eoq" << '\n'
#define CLS while (getchar () != '\n')
using namespace std;
typedef long long int ll;
typedef unsigned long long int llu;
typedef pair<ll, ll> ii;
typedef pair<double, double> dd;
typedef vector<ll> vi;
typedef vector<ii> vii;
const int dx[] = { 0, 1, -1, 0, 1, -1, -1,  1};
const int dy[] = {-1, 0,  0, 1, 1,  1, -1, -1};
const int N = 0;
const int MOD = 0;
const ll LLINF = 1e18 + 10;
#define MAXN 100010

vector<int> g[MAXN];
vector<int> v;
int valSub[MAXN];
int tamSub[MAXN];
int cost[MAXN];
int n;
ll INF = 1000000000000000LL;
ll dp[MAXN][210];

void dfs(int u, int pai){
	
	v.pb(u);
	valSub[u] = cost[u];
	tamSub[u] = 1;
	for (int i = 0; i < g[u].size(); i++)
	{
		if(g[u][i] == pai) continue;
		dfs(g[u][i], u);
		valSub[u] += valSub[g[u][i]];
		tamSub[u] += tamSub[g[u][i]];
	}
	
}

ll solve(int pos, int k){
	if(k<0) return -INF;
	if(pos >= n) return 0;
	if(dp[pos][k]!=-1) return dp[pos][k];
	
	ll ans = 0;
	ans = max(cost[v[pos]] + solve(pos+1, k),  solve(pos + tamSub[v[pos]], k-1));
	
	return dp[pos][k] = ans;
	
}

int main () {
	
	ios_base::sync_with_stdio (0);
	cin.tie (0);
	int u, vv, k;
	cin >> n >> k;
	for (int i = 0; i < n; i++)
	{
		cin >> cost[i];
	}
	for (int i = 0; i < n-1; i++)
	{
		cin >> u >> vv;
		u--;
		vv--;
		g[u].pb(vv);
		g[vv].pb(u);
	}
	
	dfs(0, 0);
	memset(dp, -1, sizeof dp);
	cout << solve(0, k) << "\n";
	
		
	return 0;
}
