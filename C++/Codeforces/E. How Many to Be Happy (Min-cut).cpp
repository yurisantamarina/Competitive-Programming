#include <bits/stdc++.h>

using namespace std;
#define pb push_back
#define mp make_pair
#define F first
#define S second
#define MAXN 202

struct edge{
	int from, to, f, c;
	edge(){}
	edge(int a, int b, int cc, int d){
		from = a;
		to = b;
		f = cc;
		c = d;
	}
};

vector<edge> ed;
vector<int> g[MAXN];
int seen[MAXN], tempo;
vector<pair<int, pair<int, int> > > e;

void add_edge(int from, int to, int cap){
	g[from].pb(ed.size());
	ed.pb(edge(from, to, 0, cap));
	
	g[to].pb(ed.size());
	ed.pb(edge(to, from, 0, 0));
}

int dfs(int u, int mn, int sink){
	if(u == sink) return mn;
	int v, cap;
	
	//~ cout << "oi\n";
	for(int idx : g[u]){
		v = ed[idx].to;
		cap = ed[idx].c - ed[idx].f;
		
		if(seen[v] < tempo && cap > 0){
			seen[v] = tempo;
			if(int a = dfs(v, min(mn, cap), sink)){
				ed[idx].f += a;
				ed[idx^1].f -= a;
				return a;
			}
		}
	}
	
	return 0;
}

int cut(int src, int sink){
	for (int i = 0; i < ed.size(); i++)
		ed[i].f = 0;
	
	int flow = 0;
	tempo++;
	
	while (int a = dfs(src, INT_MAX, sink))
	{
		tempo++;
		//~ cout << "oi\n";
		flow += a;
	}
	return flow;
}

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	int n, m, u, v, w, src, sink;
	cin >> n >> m;
	for (int i = 0; i < m; i++)
	{
		cin >> u >> v >> w;
		e.pb(mp(w, mp(u, v)));
	}
	sort(e.begin(), e.end());
	
	tempo = 1;
	int j = 0, ans = 0;
	for (int i = 0; i < m; i++)
	{
		src = e[i].S.F;
		sink = e[i].S.S;
		
		while(e[j].F < e[i].F){
			add_edge(e[j].S.F, e[j].S.S, 1);
			add_edge(e[j].S.S, e[j].S.F, 1);
			j++;
		}
		
		//~ printf("i = %d j = %d  src = %d  sink = %d\n", i, j, src, sink);
		ans += cut(src, sink);
		//~ printf("ans = %d\n", ans);
	}
	cout << ans << "\n";
	
	
	return 0;
}
