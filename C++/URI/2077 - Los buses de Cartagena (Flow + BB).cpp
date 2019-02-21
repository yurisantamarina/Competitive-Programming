#include <bits/stdc++.h>

using namespace std;
#define MAXN 300
#define INF 10101010
#define pb push_back

struct edge{
	int from, to, c, f;
	edge(){}
	edge(int a, int b, int cc, int d){
		from = a;
		to = b;
		c = cc;
		f = d;
	}
};

vector<edge> ed;
vector<int> g[MAXN];
int seen[MAXN], tempo, src, sink, n, m;
map<string, vector<int> > mapa;

void add_edge(int from, int to, int cap){
	g[from].pb(ed.size());
	ed.pb(edge(from, to, cap, 0));
	g[to].pb(ed.size());
	ed.pb(edge(to, from, 0, 0));
}

int dfs(int u, int mn){
	if(u == sink) return mn;
	
	int idx, v, cap;
	for (int i = 0; i < g[u].size(); i++)
	{
		idx = g[u][i];
		v = ed[idx].to;
		cap = ed[idx].c - ed[idx].f;
		if(seen[v] < tempo && cap > 0){
			seen[v] = tempo;
			if(int a = dfs(v, min(mn, cap))){
				ed[idx].f += a;
				ed[idx^1].f -= a;
				return a;
			}
		}
	}
	return 0;
}

bool ok(int cap){
	for (int i = 0; i < ed.size(); i++)
	{
		ed[i].f = 0;
		if(i % 2 == 0 && ed[i].to == sink)
			ed[i].c = cap;
	}
	
	int f = 0;
	tempo = 1;
	memset(seen, 0, sizeof seen);
	while(int a = dfs(src, INT_MAX)){
		f += a;
		tempo++;
	}
	//~ printf("chute %d   f = %d\n", cap, f);
	return f == n;
}

int solve(){
	int lo = 0, hi = 100000, mid, ans = INF;
	while (lo <= hi)
	{
		mid = (lo + hi)/2;
		if(ok(mid)){
			hi = mid-1;
			ans = mid;
		}else lo = mid+1;
	}
	return ans;
}

void resetCases(){
	for (int i = 0; i <= sink; i++)
		g[i].clear();
	ed.clear();
	mapa.clear();
}

int main(){
	int tc, qtd;
	scanf("%d", &tc);
	char h[15];
	
	while (tc--)
	{
		scanf("%d %d", &n, &m);
		src = 0;
		sink = n+m+1;
		resetCases();
		//~ printf("%d %d\n", n, m);
		
		for (int i = 1; i <= m; i++){
			scanf(" %s", h);
			//~ printf("%s\n", h);
			mapa[h].pb(i + n);
			add_edge(i + n, sink, 1);
		}
		for (int i = 1; i <= n; i++)
		{
			scanf("%d", &qtd);
			add_edge(src, i, 1);
			//~ printf("%d ", qtd);
			while (qtd--)
			{
				scanf(" %s", h);
				//~ printf("%s ", h);
				if(mapa.count(h)){
					for(auto it : mapa[h])
						add_edge(i, it, INF);
					//~ printf("aresta de %d para %s\n", i, h);
				}
			}
			//~ printf("\n");
		}
		printf("%d\n", solve());
	}
	
	
	
	return 0;
}
