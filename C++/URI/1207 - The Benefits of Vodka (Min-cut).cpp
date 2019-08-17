#include <bits/stdc++.h>

using namespace std;
#define pb push_back
#define mp make_pair
#define MAXN 2000

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

int n, m;
vector<edge> ed;
vector<int> g[MAXN];
int tempo;
int seen[MAXN];
int bonus[MAXN], qtd[MAXN], cost[MAXN];
int lvl[MAXN];
int ptr[MAXN], counter;

void add_edge(int from, int to, int c){
	g[from].pb((int)ed.size());
	ed.pb(edge(from, to, 0, c));
	
	g[to].pb((int)ed.size());
	ed.pb(edge(to, from, 0, 0));
}

bool bfs(int src, int sink){
	queue<int> q;
	for (int i = 0; i < counter; i++)
		lvl[i] = -1;
	
	lvl[src] = 0;
	q.push(src);
	
	int u, v, cap;
	while (!q.empty())
	{
		u = q.front(); q.pop();
		
		for(int idx : g[u]){
			v = ed[idx].to;
			cap = ed[idx].c - ed[idx].f;
			if(cap > 0 && lvl[v] == -1){
				lvl[v] = lvl[u] + 1;
				q.push(v);
			}
		}
	}
	
	return lvl[sink] != -1;
}

int dfs(int at, int mn, int sink){
	if(at == sink) return mn;
	
	int idx, v, cap;
	for(int &i = ptr[at]; i < g[at].size(); i++){
		idx = g[at][i];
		v = ed[idx].to;
		cap = ed[idx].c - ed[idx].f;
		
		if(cap > 0 && lvl[v] == lvl[at] + 1){
			if(int a = dfs(v, min(mn, cap), sink)){
				ed[idx].f += a;
				ed[idx^1].f -= a;
				return a;
			}
		}
	}
	return 0;
}

int mf(int src, int sink){
	int flow = 0;
	while(bfs(src, sink)){
		memset(ptr, 0, sizeof ptr);
		while(int a = dfs(src, INT_MAX, sink)){
			flow += a;
		}
	}
	return flow;
}
void clear(int x){
	for (int i = 0; i < x; i++)
	{
		g[i].clear();
	}
	ed.clear();
}

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	int src, sink;
	int n, m, x;
	while (cin >> n >> m)
	{
		clear(n+m+10);
		src = 0;
		sink = n+m+1;
		counter = sink+1;
		for (int i = 1; i <= n; i++)
		{
			cin >> cost[i];
			add_edge(i + m, sink, cost[i]);
		}
		
		for (int i = 1; i <= m; i++)
		{
			cin >> qtd[i];
		}
		
		int ans = 0;
		for (int i = 1; i <= m; i++)
		{
			cin >> bonus[i];
			add_edge(src, i, bonus[i]);
			ans += bonus[i];
			while (qtd[i]--)
			{
				cin >> x;
				add_edge(i, x + m, 1e9);
			}
			
		}
		cout << ans - mf(src, sink) << "\n";
	}
	
	
	return 0;
}
