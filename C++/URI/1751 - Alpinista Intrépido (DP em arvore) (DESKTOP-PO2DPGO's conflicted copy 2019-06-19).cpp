#include <bits/stdc++.h>

using namespace std;
#define F first
#define S second
#define MAXN 101010
#define gc getchar_unlocked // ou usar só getchar

void scanint(int &x)
{
    register int c = gc();
    x = 0;
    for(;(c<48 || c>57);c = gc());
    for(;c>47 && c<58;c = gc()) {x = (x<<1) + (x<<3) + c - 48;}
}

vector<pair<int, int> > g[MAXN];
int cost[MAXN], ida[MAXN], volta[MAXN];
bool has[MAXN];

void dfspre(int u, int p){
	for(pair<int, int> &pp : g[u]){
		int v = pp.F;
		int w = pp.S;
		
		if(v == p) continue;
		cost[v] = w;
		dfspre(v, u);
		has[u] |= has[v];
	}
}

void dfsdp(int u, int p){
	ida[u] = volta[u] = 0;
	
	for(pair<int, int> &pp : g[u]){
		int v = pp.F;
		int w = pp.S;
		
		if(!has[v] || v == p) continue;
		dfsdp(v, u);
		volta[u] += volta[v];
	}
	ida[u] = volta[u];
	if(has[u]) volta[u] += cost[u];
	
	int tot = ida[u];
	for(pair<int, int> &pp : g[u]){
		int v = pp.F;
		int w = pp.S;
		
		if(!has[v] || v == p) continue;
		ida[u] = min(ida[u], tot - volta[v] + ida[v]);
	}
}

int main(){
	//~ ios_base::sync_with_stdio(0);
	//~ cin.tie(0);
	int u, v, q, n, w, x;
	//~ cin >> n >> q;
	scanint(n);
	scanint(q);
	for (int i = 1; i < n; i++)
	{
		//~ cin >> u >> v >> w;
		scanint(u);
		scanint(v);
		scanint(w);
		g[u].push_back({v, w});
		g[v].push_back({u, w});
	}
	
	for (int i = 0; i < q; i++)
	{
		//~ cin >> x;
		scanint(x);
		has[x] = true;
	}
	
	dfspre(1, 1);
	
	dfsdp(1, 1);
	//~ cout << ida[1] << "\n";
	printf("%d\n", ida[1]);
	
	return 0;
}
