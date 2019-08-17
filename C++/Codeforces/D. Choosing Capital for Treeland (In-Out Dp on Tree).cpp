#include <bits/stdc++.h>

using namespace std;

#define MAXN 200010
#define F first
#define S second
#define pb push_back
#define mp make_pair
#define INF 100000000000000000LL
typedef long long int ll;

vector<pair<int, int> > g[MAXN];
int n;
int in[MAXN];
int out[MAXN];

void dfs1(int u, int pai){
	
	in[u] = 0;
	for(pair<int, int> p : g[u]){
		if(p.F == pai) continue;
		dfs1(p.F, u);
		in[u] += p.S + in[p.F];
	}
	
}

void dfs2(int u, int pai){
	
	for(pair<int, int> p : g[u]){
		if(p.F == pai) continue;
		out[p.F] = out[u] + in[u] - (p.S + in[p.F]) + (1 - p.S);
		dfs2(p.F, u);
	}
	
}

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cin >> n;
	
	int u, v;
	for (int i = 0; i < n-1; i++)
	{
		cin >> u >> v;
		g[u].pb(mp(v, 0));
		g[v].pb(mp(u, 1));
	}
	
	dfs1(1, 1);
	dfs2(1, 1);
	
	ll ans = INF;
	for (int i = 1; i <= n; i++)
	{
		ans = min(ans, ll(in[i]) + ll(out[i]));
	}
	cout << ans << "\n";
	for (int i = 1; i <= n; i++)
	{
		if(ll(in[i]) + ll(out[i]) == ans){
			cout << i << " ";
		}
	}
	cout << "\n";
	
	return 0;
}
