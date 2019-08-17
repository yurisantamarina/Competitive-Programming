#include <bits/stdc++.h>

using namespace std;
#define MAXM 510
#define MAXN 53
#define F first
#define S second
#define pb push_back
#define mp make_pair
#define INF 1e9

struct edge{
	int to, f, c;
	edge(){}
	edge(int _to, int _f, int _c){
		to = _to;
		f = _f;
		c = _c;
	}
};

edge ed[4*MAXM];
vector<int> g[MAXN];
int tempo, cur;
int seen[MAXN];
int src = 0, sink = 1;
int n, m;
pair<int, int> pai[MAXN];

void add_edge(int u, int v, int cap, int rcap){
	ed[cur] = edge(v, 0, cap);
	g[u].pb(cur++);
	
	ed[cur] = edge(u, 0, rcap);
	g[v].pb(cur++);
}

int dfs(int at, int mn){
	if(at == sink) return mn;
	
	int idx, v, cap;
	
	for (int i = 0; i < (int)g[at].size(); i++)
	{
		idx = g[at][i];
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

bool bfs(){
	queue<int> q;
	q.push(src);
	
	int u, v, cap, idx;
	
	while (!q.empty())
	{
		u = q.front();
		q.pop();
		if(u == sink) return true;
		
		for (int i = 0; i < (int)g[u].size(); i++)
		{
			idx = g[u][i];
			v = ed[idx].to;
			cap = ed[idx].c - ed[idx].f;
			
			if(seen[v] < tempo && cap > 0){
				seen[v] = tempo;
				pai[v] = mp(u, idx);
				q.push(v);
			}
		}
	}
	
	return false;
}

int mf(){
	int flow = 0;
	tempo = 1;
	memset(seen, 0, sizeof seen);
	
	int u, v, w, mn = INF, idx, cap;
	while (bfs())
	{
		u = sink;
		mn = INF;
		while(u!=src){
			v = pai[u].F;
			idx = pai[u].S;
			cap = ed[idx].c - ed[idx].f;
			mn = min(mn, cap);
			
			u = v;
		}
		
		u = sink;
		while(u!=src){
			v = pai[u].F;
			idx = pai[u].S;
			ed[idx].f += mn;
			ed[idx^1].f -= mn;
			
			u = v;
		}
		
		flow += mn;
		tempo++;
	}
	
	
	return flow;
}

void reset(){
	cur = 0;
	
	for (int i = 0; i < n; i++)
	{
		g[i].clear();
	}
}

void dfs2(int u){
	if(seen[u] == tempo) return;
	seen[u] = tempo;
	
	int idx, v, cap;
	for (int i = 0; i < (int)g[u].size(); i++)
	{
		idx = g[u][i];
		v = ed[idx].to;
		cap = ed[idx].c - ed[idx].f;
		
		if(seen[v] < tempo && cap > 0){
			dfs2(v);
		}
	}
	
}

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	int u, v, w;
	while (cin >> n >> m, n && m)
	{
		reset();
		for (int i = 0; i < m; i++)
		{
			cin >> u >> v >> w;
			u--; v--;
			add_edge(u, v, w, 0);
			add_edge(v, u, w, 0);
		}
		
		mf();
		
		tempo++;
		dfs2(0);
		
		int idx, v;
		for (u = 0; u < n; u++)
		{
			if(seen[u] < tempo) continue;//ta no set do sink
			
			for(int j = 0; j < (int)g[u].size(); j++){
				idx = g[u][j];
				if(idx%2!=0) continue;//é aresta da volta
				
				v = ed[idx].to;
				
				if(seen[v] < tempo){//visitou u mas nao visitou v
					cout << u+1 << " " << v+1 << "\n";
				}
			}
		}
		cout << "\n";
		
	}
	
	
	return 0;
}
