#include <bits/stdc++.h>

using namespace std;
#define MAXN 301010
#define LOG 20
#define pb push_back
typedef long long int ll;
int d[MAXN], low[MAXN], seen[MAXN], tempo = 1, n, q, m, h[MAXN], lca[MAXN][LOG];
stack<int> p;
unordered_map<ll, int> mapaBridge;
vector<int> tmp, g[MAXN], adj[MAXN];

ll f(pair<int, int> a){
	return (((ll)a.first) << 20LL) + a.second;
}

void dfsTarjan(int u, int pai){
	p.push(u);
	seen[u] = 1;
	d[u] = low[u] = tempo++;
	
	for(int &v : adj[u]){
		if(!seen[v]){
			dfsTarjan(v, u);
			low[u] = min(low[u], low[v]);
			
			if(d[u] <= low[v]){
				int dummy = ++n;
				if(d[u] < low[v])
					mapaBridge[f({min(u, v), max(u, v)})] = dummy;
				
				tmp.clear();
				tmp.pb(u);
				while (!p.empty())
				{
					int x = p.top(); p.pop();
					tmp.pb(x);
					if(x == v) break;
				}
				
				for(int &x : tmp){
					g[x].pb(dummy);
					g[dummy].pb(x);
				}
			}
		}else if(v != pai)
			low[u] = min(low[u], d[v]);
	}
}

void dfs(int u, int pai){
	h[u] = h[pai] + 1;
	lca[u][0] = pai;
	for (int i = 1; i < LOG; i++)
		lca[u][i] = lca[lca[u][i - 1]][i - 1];
	for(int &v : g[u])
		if(v != pai)
			dfs(v, u);
}

int getLca(int u, int v){
	if(h[u] < h[v]) swap(u, v);
	int d = abs(h[u] - h[v]);
	for (int i = 0; i < LOG; i++)
		if(d & (1 << i))
			u = lca[u][i];
	if(u == v) return u;
	
	for(int i = LOG - 1; i >= 0; i--)
		if(lca[u][i] != lca[v][i]){
			u = lca[u][i];
			v = lca[v][i];
		}
	
	return lca[u][0];
}

int getDist(int u, int v){
	return h[u] + h[v] - 2 * h[getLca(u, v)];
}

bool inPath(int a, int u, int v){
	return getDist(u, a) + getDist(v, a) == getDist(u, v);
}

void solve1(int u, int v, int a, int b){
	if(a > b) swap(a, b);
	
	if(mapaBridge.count(f({a, b})) && inPath(mapaBridge[f({a, b})], u, v))
		printf("ne\n");
	else
		printf("da\n");
}

void solve2(int u, int v, int c){
	if(inPath(c, u, v))
		printf("ne\n");
	else
		printf("da\n");
}

int main(){
	scanf("%d %d", &n, &m);
	int u, v, a, b, c, op;
	for (int i = 0; i < m; i++)
	{
		scanf("%d %d", &u, &v);
		adj[u].pb(v);
		adj[v].pb(u);
	}
	
	dfsTarjan(1, 1);
	
	dfs(1, 1);
	
	scanf("%d", &q);
	while (q--)
	{
		scanf("%d", &op);
		if(op == 1){
			scanf("%d %d %d %d", &u, &v, &a, &b);
			solve1(u, v, a, b);
		}else{
			scanf("%d %d %d", &u, &v, &c);
			solve2(u, v, c);
		}
	}
	
	return 0;
}
