#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair
#define F first
#define S second
#define oioi printf("oioi\n")
using namespace std;
#define ll long long int
#define MAXN 20010

int n, m;
vector<pair<int, int> > g[MAXN];
int grau[MAXN];
int root, cnt;

void dfs(int u){
	
	if(grau[u]>2 && u != root) return;
	
	for (int i = 0; i < g[u].size(); i++)
	{
		int v = g[u][i].F;
		if(g[u][i].S){
			//~ cout << "apaga " << u+1 << " " << v+1 << endl;
			g[u][i].S = 0;
			g[v][lower_bound(g[v].begin(), g[v].end(), mp(u, 100)) - g[v].begin() - 1].S = 0;
			//~ cout << lower_bound(g[v].begin(), g[v].end(), mp(u, 100)) - g[v].begin() << endl;
			dfs(v);
		}
	}
	
}

char vis[MAXN];
void dfs2(int u){
	if(vis[u]) return;
	vis[u] = 1;
	cnt++;
	//~ cout << u+1 << " ";
	for (int i = 0; i < g[u].size(); i++)
	{
		int v = g[u][i].F;
		if(g[u][i].S){
			dfs2(v);
		}
	}
	
}

int main () {
	cin >> n >> m;
	int u, v;
	memset(grau, 0, sizeof grau);
	for (int i = 0; i < m; i++)
	{
		cin >> u >> v;
		u--; v--;
		g[u].pb(mp(v, 1));
		g[v].pb(mp(u, 1));
		grau[u]++;
		grau[v]++;
	}
	for (int i = 0; i < n; i++)
	{
		sort(g[i].begin(), g[i].end());
	}
	root = -1;
	for (int i = 0; i < n; i++)
	{
		if(grau[i]>=5){
			root = i;
		}
		if(grau[i]==1){
			//~ cout << i+1 << " ";
			dfs(i);
		}
	}
	//~ cout << endl;
	
	if(root == -1){
		cout << 0 << endl;
		return 0;
	}
	dfs(root);
	int ans = 0;
	memset(vis, 0, sizeof vis);
	for (int i = 0; i < n; i++)
	{
		if(!vis[i]){
			cnt = 0;
			dfs2(i);
			//~ cout << endl;
			ans = max(ans, cnt);
		}
	}
	cout << ans << "\n";
	
	
	
	return 0;
}
