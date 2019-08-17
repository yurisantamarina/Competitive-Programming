#include <bits/stdc++.h>

using namespace std;
#define inf 1e9
#define pb push_back
#define mp make_pair
#define MAXN 100010

vector<int> g[MAXN];
int in[MAXN];
int out[MAXN];
int diameter;

void dfs(int u, int pai){
	int v;
	in[u] = 0;
	
	for (int i = 0; i < (int)g[u].size(); i++)
	{
		v = g[u][i];
		if(v == pai) continue;
		dfs(v, u);
		in[u] = max(in[u], 1 + in[v]);
	}
}

void dfs2(int u, int pai){
	int mx1 = -1;
	int mx2 = -1;
	int v;
	
	diameter = max(diameter, max(in[u], out[u]));
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
		if(in[v] == mx1){
			out[v] = max(out[v], 2 + mx2);
		}else{
			out[v] = max(out[v], 2 + mx1);
		}
		out[v] = max(out[v], 1 + out[u]);
		dfs2(v, u);
	}
	
	
}

int main(){
	int n, u, v;
	cin >> n;
	for (int i = 0; i < n-1; i++)
	{
		cin >> u >> v;
		g[u].pb(v);
		g[v].pb(u);
	}
	
	diameter = 0;
	dfs(1, 1);
	out[1] = -inf;
	dfs2(1, 1);
	
	//~ cout << "   in  out\n";
	//~ for (int i = 0; i < n; i++)
	//~ {
		//~ cout << i+1 << ": " << in[i+1] << "   " << out[i+1] << endl;
	//~ }
	
	cout << diameter << "\n";
	
	
	return 0;
}
