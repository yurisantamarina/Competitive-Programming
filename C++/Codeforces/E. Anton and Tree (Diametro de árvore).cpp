#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair
#define F first
#define S second
#define oioi printf("oioi\n")
#define eoq cout << "eoq" << '\n'
using namespace std;
typedef long long int ll;
typedef unsigned long long int llu;
typedef pair<ll, ll> ii;
typedef pair<double, double> dd;
typedef vector<ll> vi;
typedef vector<ii> vii;
const int dx[] = { 0, 1, -1, 0, 1, -1, -1,  1};
const int dy[] = {-1, 0,  0, 1, 1,  1, -1, -1};
const ll MOD = 0;
const ll N = 0;
#define MAXN 200010
vector<int> g[MAXN];
int dist[MAXN];
int cor[MAXN];
int n;

void dfs(int u, int ult, int cost){
	
	dist[u] = cost;
	for (int i = 0; i < g[u].size(); i++)
	{
		int v = g[u][i];
		if(v == ult) continue;
		dfs(v, u, cost + (cor[u]!=cor[v]));
	}
	
}

int main () {

	ios_base::sync_with_stdio (0);
	cin.tie (0);
	int u, v;
	cin >> n;
	for (int i = 0; i < n; i++) cin >> cor[i];
	
	for (int i = 0; i < n-1; i++)
	{
		cin >> u >> v;
		u--; v--;
		g[u].pb(v);
		g[v].pb(u);
	}
	
	memset(dist, 0, sizeof dist);
	dfs(0, 0, 1);
	int ans = 0, mn = 0;
	for (int i = 0; i < n; i++)
	{
		//~ cout << dist[i] << ' ';
		if(dist[i] > dist[ans]) ans = i;
	}
	//~ cout << endl;
	//~ cout << ans+1 << '\n';
	
	memset(dist, 0, sizeof dist);
	dfs(ans, ans, 1);
	ans = 0;
	for (int i = 0; i < n; i++)
	{
		if(dist[i] > dist[ans]) ans = i;
	}
	
	ans = dist[ans];
	cout << ans/2 << '\n';
	
	
	
	
	
	
	return 0;
}
