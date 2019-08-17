#include <bits/stdc++.h>

using namespace std;
#define MAXN 201010
#define pb push_back
#define mp make_pair
#define F first
#define S second

typedef pair<int, int> pii;

vector<int> g[MAXN];
char seen[MAXN];
int pai[MAXN], d[MAXN], low[MAXN], n, tempo, root;

int find(int u){
	if(u == pai[u]) return u;
	return pai[u] = find(pai[u]);
}

bool same(int u, int v){
	return find(u) == find(v);
}

void join(int u, int v){
	if(same(u, v)) return;
	u = find(u);
	v = find(v);
	pai[u] = v;
}

void dfs(int u, int p){
	seen[u] = 1;
	d[u] = low[u] = tempo++;
	for(int v : g[u]){
		if(!seen[v]){
			dfs(v, u);
			low[u] = min(low[u], low[v]);
			if(d[u] < low[v])
				join(u, v);
		}else if(v != p)
			low[u] = min(low[u], d[v]);
	}
}

void reset(){
	for (int i = 0; i <= n; i++)
	{
		g[i].clear();
		seen[i] = 0;
		pai[i] = i;
	}
	tempo = 1;
}

int main(){
	int m, q, u, v;
	while (scanf("%d %d %d", &n, &m, &q) != EOF)
	{
		
		reset();
		for (int i = 0; i < m; i++)
		{
			scanf("%d %d", &u, &v);
			g[u].pb(v);
			g[v].pb(u);
		}
		
		for(int i = 1; i <= n; i++)
			if(!seen[i]){
				root = i;
				dfs(i, i);
			}
		
		
		
		
		
		while (q--)
		{
			scanf("%d %d", &u, &v);
			printf("%c\n", same(u, v) ? '1' : '0');
		}
	}
	
	
	
	return 0;
}
