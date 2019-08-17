#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair
#define F first
#define S second
#define oioi printf("oioi\n")
using namespace std;
typedef long long int ll;
typedef unsigned long long int llu;
#define gc getchar_unlocked // ou usar só getchar
#define MAXN 100100
#define LOG 17

vector<int> g[MAXN];
int lca[MAXN][LOG];
int h[MAXN];
int tam[MAXN];
int pai[MAXN];
int n;

void dfs(int u, int paii){
	h[u] = h[paii] + 1;
	
	int v;
	lca[u][0] = paii;
	for (int i = 1; i < LOG; i++)
	{
		lca[u][i] = lca[lca[u][i-1]][i-1];
	}
	
	tam[u] = 1;
	for (int i = 0; i < g[u].size(); i++)
	{
		v = g[u][i];
		if(v == paii) continue;
		dfs(v, u);
		tam[u] += tam[v];
		pai[v] = u;
	}
	
}

int getLCA(int u, int v){
	if(h[u] < h[v]) swap(u, v);
	int dist = abs(h[u]-h[v]);
	for (int i = LOG-1; i >= 0; i--)
	{
		if(dist & (1<<i)) u = lca[u][i];
	}
	if(u==v) return u;
	for (int i = LOG-1; i >= 0; i--)
	{
		if(lca[u][i]!=lca[v][i]){
			u = lca[u][i];
			v = lca[v][i];
		}
	}
	
	return lca[u][0];
}

int getDist(int a, int b){
	return h[a] + h[b] - 2*h[getLCA(a, b)];
}

int getDist(int a, int b, int LCA){
	return h[a] + h[b] - 2*h[LCA];
}


int sobe(int a, int d){
	for (int i = LOG-1; i >= 0; i--)
	{
		if(d & (1<<i)){
			a = lca[a][i];
		}
	}
	return a;
}

int solve(int a, int b){
	if(a==b) return n;
	int LCA = getLCA(a, b);
	int dist = getDist(a, b, LCA);
	if(dist%2!=0) return 0;
	
	int u, v;
	int k = dist / 2;
	if(getDist(a, LCA) == getDist(b, LCA)){
		u = sobe(a, k-1);
		v = sobe(b, k-1);
		return n - tam[u] - tam[v];
	}
	
	if(h[a] < h[b]){
		u = sobe(b, k);
		v = sobe(b, k-1);
		return tam[u] - tam[v];
	}else{
		u = sobe(a, k);
		v = sobe(a, k-1);
		return tam[u] - tam[v];
	}
	
	
	//~ return ans;
}

int main(){
	//~ ios_base::sync_with_stdio (0);
	//~ cin.tie (0);
	//~ cin >> n;
	scanf("%d", &n);
	int u, v;
	for (int i = 1; i < n; i++)
	{
		//~ cin >> u >> v;
		scanf("%d %d", &u, &v);
		u--; v--;
		g[u].pb(v);
		g[v].pb(u);
	}
	h[0] = -1;
	dfs(0, 0);
	int q;
	//~ cin >> q;
	scanf("%d", &q);
	while (q--)
	{
		//~ cin >> u >> v;
		scanf("%d %d", &u, &v);
		u--; v--;
		printf("%d\n", solve(u, v));
		//~ cout << solve(u, v) << "\n";
	}
	
	
	
	
	
	
	
	return 0;
}
