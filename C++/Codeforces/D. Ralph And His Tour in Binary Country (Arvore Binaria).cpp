#include <bits/stdc++.h>

using namespace std;
#define MAXN 1010101
#define pb push_back
#define mp make_pair
#define F first
#define S second
#define all(a) a.begin(), a.end()
typedef pair<int, int> pii;
typedef long long int ll;

vector<ll> subtree[MAXN], acc[MAXN];
vector<pii> g[MAXN];
int pai[MAXN], irmao[MAXN];
int n, q;

void dfs(int u, int p){
	pai[u] = p;
	subtree[u].pb(0);
	acc[u].pb(0);
	
	for(pii v : g[u]){
		if(v.F == p) continue;
		dfs(v.F, u);
	}
	if(g[u].size() == 0) return;
	
	int v1, v2, L1, L2;
	if(g[u].size() == 1){
		L1 = g[u][0].S;
		v1 = g[u][0].F;
		for (int i = 0; i < (int)subtree[v1].size(); i++){
			subtree[u].pb(subtree[v1][i] + L1);
			acc[u].pb(acc[u][i] + subtree[u][i+1]);
		}
		
		return;
	}
	L1 = g[u][0].S;
	L2 = g[u][1].S;
	v1 = g[u][0].F;
	v2 = g[u][1].F;
	int i = 0, j = 0, sz1 = (int)subtree[v1].size(), sz2 = (int)subtree[v2].size();
	
	irmao[v1] = v2;
	irmao[v2] = v1;
	
	while (i < sz1 && j < sz2)
	{
		if(subtree[v1][i] + L1 < subtree[v2][j] + L2){
			subtree[u].pb(subtree[v1][i++] + L1);
		}else{
			subtree[u].pb(subtree[v2][j++] + L2);
		}
		acc[u].pb(acc[u][i+j-1] + subtree[u][i+j]);
	}
	while(i < sz1){
		subtree[u].pb(subtree[v1][i++] + L1);
		acc[u].pb(acc[u][i+j-1] + subtree[u][i+j]);
	}
	while(j < sz2){
		subtree[u].pb(subtree[v2][j++] + L2);
		acc[u].pb(acc[u][i+j-1] + subtree[u][i+j]);
	}
}

int getCost(int V, int lst){
	for(pii u : g[V]){
		if(u.F == lst) return u.S;
	}
}

ll get(int V, ll H){
	if(H < 0) return 0;
	ll qtd = upper_bound(all(subtree[V]), H) - subtree[V].begin() - 1;
	return (qtd+1) * H - acc[V][qtd]; 
}

ll solve(int V, ll H){
	int orig = H, lst;
	ll qtd = upper_bound(all(subtree[V]), H) - subtree[V].begin() - 1;
	ll ans = (qtd+1) * H - acc[V][qtd];
	//~ cout << "V = " << V << "  H = " << H << endl;
	//~ cout << "ansAtual = " << ans << endl;
	lst = V;
	V = pai[V];
	while (V != -1)
	{
		H -= getCost(V, lst);
		//~ printf("V = %d lst = %d H = %d\n", V, lst, H);
		if(H < 0) return ans;
		ans += orig - (orig - H);
		if(g[V].size() == 2){
			ans += get(irmao[lst], H - getCost(V, irmao[lst]));
		}
		lst = V;
		V = pai[V];
	}
	
	return ans;
}

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	int L;
	cin >> n >> q;
	for (int i = 1; i < n; i++){
		cin >> L;
		g[(i+1)/2].pb(mp(i+1, L));
		//~ printf("aresta de %d para %d com custo %d\n", (i+1)/2, i+1, L);
	}
	
	dfs(1, -1);
	
	//~ for(int i = 1; i <= n; i++){
		//~ for(int j : subtree[i]){
			//~ cout << j << " ";
		//~ }
		//~ cout << endl;
		//~ for(int j : acc[i]){
			//~ cout << j << " ";
		//~ }
		//~ cout << endl << endl;
	//~ }
	
	int V, H;
	while (q--)
	{
		cin >> V >> H;
		cout << solve(V, H) << "\n";
	}
	
	
}
