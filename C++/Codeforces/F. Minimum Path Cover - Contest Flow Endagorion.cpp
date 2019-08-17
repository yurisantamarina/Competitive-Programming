#include <bits/stdc++.h>

using namespace std;
#define pb push_back
#define mp make_pair
#define MAXN 300

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
int nxt[MAXN];
char comeco[MAXN];

void add_edge(int from, int to, int c){
	g[from].pb((int)ed.size());
	ed.pb(edge(from, to, 0, c));
	
	g[to].pb((int)ed.size());
	ed.pb(edge(to, from, 0, 0));
}

int in(int u){
	return u + n;
}

int out(int u){
	return u;
}

int dfs(int at, int sink, int mn){
	if(at == sink) return mn;
	
	int v, cap;
	for(int idx : g[at]){
		v = ed[idx].to;
		cap = ed[idx].c - ed[idx].f;
		if(cap > 0 && seen[v] < tempo){
			seen[v] = tempo;
			if(int a = dfs(v, sink, min(mn, cap))){
				ed[idx].f += a;
				ed[idx^1].f -= a;
				return a;
			}
		}
	}
	
	return 0;
}

int mf(int src, int sink){
	tempo = 1;
	int flow = 0;
	memset(seen, 0, sizeof seen);
	while(int a = dfs(src, sink, INT_MAX)){
		flow += a;
		tempo++;
	}
	return flow;
}

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	int u, v;
	cin >> n >> m;
	for (int i = 0; i < m; i++)
	{
		cin >> u >> v;
		add_edge(out(u), in(v), 1);
	}
	
	int src = 0, sink = 2*n + 1;
	for (int i = 1; i <= n; i++)
	{
		add_edge(src, out(i), 1);
		add_edge(in(i), sink, 1);
	}
	
	int ans = n - mf(src, sink);
	
	for (int i = 1; i <= n; i++){
		comeco[i] = 1;
		nxt[i] = -1;
	}
	
	int cap;
	for (u = 1; u <= n; u++)
	{
		for (int idx : g[u])
		{
			v = ed[idx].to;
			cap = ed[idx].c - ed[idx].f;
			if(cap == 0 && v != src){
				nxt[u] = v - n;
				comeco[v - n] = 0;
			}
		}
		
	}
	
	cout << ans << "\n";
	for (int i = 1; i <= n; i++)
	{
		if(comeco[i]){
			u = i;
			while(u != -1){
				if(u != i) cout << " ";
				cout << u;
				u = nxt[u];
			}
			cout << "\n";
		}
		
	}
	
	
	
	return 0;
}
