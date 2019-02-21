#include <bits/stdc++.h>

using namespace std;
#define MAXM 101010
#define MAXN 1010
#define F first
#define S second
#define mp make_pair
#define pb push_back
#define INF 1e9

struct edge{
	int to, f, c;
	int cost;
	edge(){}
	edge(int _to, int _f, int _c, int _cost){
		to = _to;
		f = _f;
		c = _c;
		cost = _cost;
	}
};

int dist[MAXN];
char inq[MAXN];
vector<int> g[MAXN];
edge ed[MAXM];
int cur;
int n, m;
pair<int, int> pai[MAXN];

void add_edge(int u, int v, int cap, int rcap, int cost){
	ed[cur] = edge(v, 0, cap, cost);
	g[u].pb(cur++);
	
	ed[cur] = edge(u, 0, rcap, -cost);
	g[v].pb(cur++);
}

bool spfa(int src, int sink){
	queue<int> q;
	memset(inq, 0, sizeof inq);
	for (int i = 0; i <= sink; i++)
	{
		dist[i] = INF;
	}
	q.push(src);
	dist[src] = 0;
	inq[src] = 1;
	
	int idx, u, v, cap;
	int cost;
	while (!q.empty())
	{
		u = q.front(); q.pop();
		inq[u] = 0;
		
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

int augment(int src, int sink){
	int cost = 0.0;
	int mn = INF;
	int u, idx, cap;
	
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
	//~ printf("passando %d  %.5lf\n", mn, cost);
	
	
	return cost;
}


int mcmf(int src, int sink){
	int cost = 0;
	
	while (spfa(src, sink))
	{
		cost += augment(src, sink);
	}
	return cost;
}

void reset(){
	for (int i = 0; i < n+m+3; i++)
	{
		g[i].clear();
	}
	cur = 0;
	
}

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	int x, xx;
	char ch;
	
	while (cin >> n >> m)
	{
		if(n==0 && m==0) continue;
		
		reset();
		
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < m; j++)
			{
				cin >> x >> ch >> xx;
				//~ printf("%d.%d = %d\n", x, xx, x*10 + xx);
				add_edge(j, i+m, 1, 0, x*10 + xx);
			}
		}
		
		int src = n+m;
		int sink = src+1;
		
		for (int i = 0; i < m; i++)
		{
			add_edge(src, i, 1, 0, 0);
		}
		
		for (int i = m; i < n+m; i++)
		{
			add_edge(i, sink, 1, 0, 0);
		}
		printf("%.2lf\n", mcmf(src, sink)/(10.0*n)+1e-9);
	}
	
	
	return 0;
}
