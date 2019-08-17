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
const int INF = 1e9 + 10;
const ll LLINF = 1e18 + 10;
#define MAXN 200010

int n;
int cost[MAXN];
ll dp[MAXN][3];
vector<int> v;
ll valSub[MAXN];
vector<int> g[MAXN];
int tamSub[MAXN];
ll inf = 10000000000000000LL;

void dfs(int u, int pai){
	tamSub[u] = 1;
	valSub[u] = cost[u];	
	v.pb(u);
	
	for (int i = 0; i < g[u].size(); i++)
	{
		if(g[u][i]==pai) continue;
		dfs(g[u][i], u);
		tamSub[u] += tamSub[g[u][i]];
		valSub[u] += valSub[g[u][i]];
	}
	
}

ll solve(int pos, int falta){
	if(falta < 0) return -inf;
	if(pos==v.size()) return falta ? -inf : 0;
	if(dp[pos][falta]!=-1) return dp[pos][falta];
	int u = v[pos];
	ll ans = 0LL;
	ans = max(solve(pos+1, falta), valSub[u] + solve(pos + tamSub[u], falta-1));
	
	return dp[pos][falta] = ans;
}

int main () {
	
	ios_base::sync_with_stdio (0);
	cin.tie (0);
	cin >> n;
	for (int i = 0; i < n; i++)
	{
		cin >> cost[i];
	}
	int u, vv;
	for (int i = 0; i < n-1; i++)
	{
		cin >> u >> vv;
		u--; vv--;
		g[u].pb(vv);
		g[vv].pb(u);
	}
	dfs(0, 0);
	memset(dp, -1, sizeof dp);
	ll ans = solve(0, 2);
	if(ans < -10000000000000LL) cout << "Impossible\n";
	else cout << ans << "\n";
	
	
	return 0;
}
