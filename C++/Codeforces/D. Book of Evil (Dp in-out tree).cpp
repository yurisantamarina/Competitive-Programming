#include <bits/stdc++.h>

using namespace std;
#define MAXN 100010
#define pb push_back
#define mp make_pair
#define inf 1e9

int in[MAXN];
int out[MAXN];
int c[MAXN];
vector<int> g[MAXN];

void dfs(int u, int pai){
	int v;
	for (int i = 0; i < (int)g[u].size(); i++)
	{
		v = g[u][i];
		if(v == pai) continue;
		dfs(v, u);
		in[u] = max(in[u], in[v] > 0 ? in[v]+1 : 0);
	}
	if(in[u] == 0){
		in[u] = c[u];
	}
}

void dfs2(int u, int pai){
	int mx1=0, mx2=0;
	int mx, v;
	
	for (int i = 0; i < (int)g[u].size(); i++)
	{
		v = g[u][i];
		if(v == pai) continue;
		if(in[v] > mx1){
			mx2 = mx1;
			mx1 = in[v];
		}else if(in[v] > mx2){
			mx2 = in[v];
		}
	}
	
	for (int i = 0; i < (int)g[u].size(); i++)
	{
		v = g[u][i];
		if(v == pai) continue;
		if(in[v] == mx1) mx = mx2;
		else mx = mx1;
		
		if(mx == 0){
			if(c[u] == 1){
				out[v] = max(out[v], 2);
			}
		}else{
			out[v] = max(out[v], 2 + mx);
		}
		
		if(out[u] == 0){
			if(c[u] == 1){
				out[v] = max(out[v], 2);
			}
		}else{
			out[v] = max(out[v], 1 + out[u]);
		}
		
		dfs2(v, u);
	}
	
}

int main(){
	int n, m, d, u, v;
	cin >> n >> m >> d;
	for (int i = 0; i < m; i++)
	{
		cin >> u;
		u--;
		c[u] = 1;
	}
	
	for (int i = 0; i < n-1; i++)
	{
		cin >> u >> v;
		u--; v--;
		g[u].pb(v);
		g[v].pb(u);
	}
	dfs(0, 0);
	
	out[0] = 0;
	dfs2(0, 0);
	
	int ans = 0, at;
	for (int i = 0; i < n; i++)
	{
		at = max(in[i], out[i]) - 1;
		if(at <= d) ans++;
	}
	cout << ans << "\n";
	
	
	return 0;
}
