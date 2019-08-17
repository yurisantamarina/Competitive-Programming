#include <bits/stdc++.h>

using namespace std;
#define F first
#define S second
#define mp make_pair
#define pb push_back
#define INF 1e9
#define MAXM 10101010
#define MAXN 101010

struct edge{
	int to, f, c, cost;
	edge(){}
	edge(int _to, int _f, int _c, int _cost){
		to = _to;
		f = _f;
		c = _c;
		cost = _cost;
	}
};

edge ed[MAXM];
vector<int> g[MAXN];
int cur;
int dist[MAXN];
char inq[MAXN];
pair<int, int> pai[MAXN];
int n, m;

int in(int u){
	return u;
}

int out(int u){
	return u+n;
}

void add_edge(int u, int v, int cap, int rcap, int cost){
	ed[cur] = edge(v, 0, cap, cost);
	g[u].pb(cur++);
	
	ed[cur] = edge(u, 0, rcap, -cost);
	g[v].pb(cur++);
}

bool spfa(int src, int sink){
	queue<int> q;
	for (int i = 0; i <= sink; i++)
	{
		dist[i] = INF;
		inq[i] = 0;
	}
	q.push(src);
	inq[src] = 1;
	dist[src] = 0;
	
	int idx, v, cap, u, cost;
	while (!q.empty())
	{
		u = q.front();
		q.pop();
		inq[u] = 0;
		//~ printf("u = %d dist = %d\n", u, dist[u]);
		for (int i = 0; i < (int)g[u].size(); i++)
		{
			idx = g[u][i];
			v = ed[idx].to;
			cap = ed[idx].c - ed[idx].f;
			cost = ed[idx].cost;
			
			if(dist[u] + cost < dist[v] && cap > 0){
				dist[v] = dist[u] + cost;
				pai[v] = mp(u, idx);
				if(!inq[v]){
					q.push(v);
					inq[v] = 1;
				}
			}
		}
		
	}
	
	
	
	return dist[sink]!=INF;
}

pair<int, int> augment(int src, int sink){
	int mn = INF, cost = 0;
	int u, cap, idx;
	
	u = sink;
	while (u!=src)
	{
		idx = pai[u].S;
		cap = ed[idx].c - ed[idx].f;
		mn = min(mn, cap);
		u = pai[u].F;
	}
	
	u = sink;
	while (u!=src)
	{
		idx = pai[u].S;
		ed[idx].f += mn;
		ed[idx^1].f -= mn;
		cost += (ed[idx].cost * mn);
		u = pai[u].F;
	}
	
	
	
	return mp(mn, cost);
}

pair<int, int> mcmf(int src, int sink){
	pair<int, int> ans(0,0), aux;
	
	
	while (spfa(src, sink))
	{
		//~ printf("oi\n");
		aux = augment(src, sink);
		ans.F += aux.F;
		ans.S += aux.S;
	}
	return ans;
}

void reset(){
	for (int i = 0; i <= 2*n + 3; i++)
	{
		g[i].clear();
	}
	cur = 0;
}

int main(){
	int tc;
	cin >> tc;
	int k, u, v, w;
	while (tc--)
	{
		cin >> n >> m >> k;
		
		int src = out(n);
		int sink = src+1;
		
		reset();
		
		for (int i = 0; i < m; i++)
		{
			cin >> u >> v >> w;
			add_edge(out(u), in(v), 1, 0, w);
		}
		
		for (int i = 0; i < n; i++)
		{
			add_edge(src, out(i), k, 0, 0);
			add_edge(in(i), sink, k, 0, 0);
		}
		
		
		pair<int, int> ans = mcmf(src, sink);
		if(ans.F == n*k){
			cout << ans.S << "\n";
		}else{
			cout << "-1\n";
		}
	}
	
	
	
	return 0;
}
