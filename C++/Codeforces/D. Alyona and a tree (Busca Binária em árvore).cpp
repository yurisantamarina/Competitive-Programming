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

vector<pair<ll, int> > path;
int n;
ll cost[200010];
int parent[200010];
vector<pair<int, int> > g[200010];
int ans[200010];

void dfs(int u, int pai, ll len){
	path.pb(mp(len, u));
	if(u!=0){
		pair<int, int> p = *lower_bound(path.begin(), path.end(), mp(len - cost[u], -1));
		ans[parent[u]]++;
		if(p.S!=0) ans[parent[p.S]]--;
	}
	
	for (int i = 0; i < g[u].size(); i++)
	{
		if(g[u][i].F == pai) continue;
		dfs(g[u][i].F, u, len + g[u][i].S);
	}
	path.pop_back();
}

void solve(int u, int pai){
	
	for (int i = 0; i < g[u].size(); i++)
	{
		if(g[u][i].F == pai) continue;
		solve(g[u][i].F, u);
		ans[u] += ans[g[u][i].F];
	}
	
	
}

int main () {
	
	ios_base::sync_with_stdio (0);
	cin.tie (0);
	cin >> n;
	for (int i = 0; i < n; i++)
	{
		cin >> cost[i];
	}
	
	int w;
	for (int i = 1; i < n; i++)
	{
		cin >> parent[i] >> w;
		parent[i]--;
		g[i].pb(mp(parent[i], w));
		g[parent[i]].pb(mp(i, w));
	}
	dfs(0, 0, 0);
	solve(0, 0);
	for (int i = 0; i < n; i++)
	{
		cout << ans[i] << ' ';
	}
	cout << "\n";
	
	
	
		
	return 0;
}
