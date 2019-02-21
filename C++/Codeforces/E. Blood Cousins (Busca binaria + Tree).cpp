#include <bits/stdc++.h>

using namespace std;
#define mp make_pair
#define pb push_back
#define F first
#define S second
#define MAXN 201010
#define LOG 20
typedef long long int ll;

int ini[MAXN], fim[MAXN], h[MAXN], pai[MAXN], lca[MAXN][LOG], t = 0;
vector<int> g[MAXN], vet[MAXN];

void dfs(int u, int pai, int prof){
	h[u] = prof;
	lca[u][0] = pai;
	
	ini[u] = t++;
	vet[prof].pb(ini[u]);
	
	for (int i = 1; i < LOG; i++)
		lca[u][i] = lca[lca[u][i-1]][i-1];
	
	for (int i = 0; i < (int)g[u].size(); i++)
		if(g[u][i] != pai) dfs(g[u][i], u, prof+1);
	
	fim[u] = t-1;
}

int get(int alt, int l, int r){
	int L = lower_bound(vet[alt].begin(), vet[alt].end(), l) - vet[alt].begin();
	int R = upper_bound(vet[alt].begin(), vet[alt].end(), r) - vet[alt].begin();
	return max(0, R-L);
}

int sobe(int u, int p){
	for (int i = 0; i < LOG; i++)
		if(p & (1<<i)) u = lca[u][i];

	return u;
}

int query(int u, int p){
	int v = sobe(u, p);
	return get(h[u], ini[v], fim[v]);
}

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	int n, u, p, q;
	cin >> n;
	for (int i = 1; i <= n; i++)
	{
		cin >> pai[i];
		if(pai[i] == 0) continue;
		g[pai[i]].pb(i);
	}
	for (int i = 1; i <= n; i++)
	{
		if(pai[i] == 0) dfs(i, i, 0);
	}
	
	cin >> q;
	for (int i = 0; i < q; i++)
	{
		cin >> u >> p;
		if(h[u] < p){
			cout << "0 ";
			continue;
		}
		cout << query(u, p)-1 << endl;
		//~ query(u, p);
	}
	cout << "\n";
	
	return 0;
}
