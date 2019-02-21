//~ http://codeforces.com/problemset/problem/730/I

#include <bits/stdc++.h>

using namespace std;
#define MAXM 10000010
#define MAXN 101010
#define F first
#define S second
#define pb push_back
#define mp make_pair
#define INF 1e9


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
int cur, n;
char inq[MAXN];
int dist[MAXN];
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
	for (int i = 0; i < n+5; i++)
	{
		dist[i] = INF;
	}
	dist[src] = 0;
	q.push(src);
	inq[src] = 1;
	int u, v, idx, cap, cost;
	
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
				if(inq[v]) continue;
				inq[v] = 1;
				q.push(v);
			}
		}
		
	}
	
	return dist[sink]!=INF;
}

pair<int, int> augment(int src, int sink){
	int mn = INF, u = sink;
	int cost = 0;
	int cap;
	
	while (u != src)
	{
		cap = ed[pai[u].S].c - ed[pai[u].S].f;
		mn = min(mn, cap);
		u = pai[u].F;
	}
	
	u = sink;
	while (u != src)
	{
		ed[pai[u].S].f += mn;
		ed[(pai[u].S)^1].f -= mn;
		cost += (mn * ed[pai[u].S].cost);
		u = pai[u].F;
	}
	
	return mp(mn, cost);
}

pair<int, int> mcmf(int src, int sink){
	pair<int, int> ans = mp(0, 0);
	pair<int, int> aux;
	
	int cnt = 0;
	while (spfa(src, sink))
	{
		aux = augment(src, sink);
		ans.F += aux.F;
		ans.S += aux.S;
	}
	
	return ans;
}

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	int qtdProg, qtdSpo;
	vector<int> prog, spo;
	
	cin >> n >> qtdProg >> qtdSpo;
	cur = 0;
	int src = 0, sink = n+3;
	add_edge(n+1, sink, qtdProg, 0, 0);
	add_edge(n+2, sink, qtdSpo, 0, 0);
	//~ printf("SINK - aresta de %d para %d com cap %d e custo %d\n", n+1, sink, qtdProg, 0);
	//~ printf("SINK - aresta de %d para %d com cap %d e custo %d\n", n+2, sink, qtdSpo, 0);
	
	int x;
	for (int i = 1; i <= n; i++)
	{
		cin >> x;
		add_edge(src, i, 1, 0, 0);
		//~ printf("SRC - aresta de %d para %d com cap %d e custo %d\n", src, i, 1, 0);
		//~ printf("aresta de %d para %d com cap %d e custo %d\n", i, n+1, 1, -x);
		add_edge(i, n+1, 1, 0, -x);
	}
	
	for (int i = 1; i <= n; i++)
	{
		cin >> x;
		add_edge(i, n+2, 1, 0, -x);
	}
	
	int idx;
	cout << -mcmf(src, sink).S << "\n";
	for (int at = 1; at <= n; at++)
	{
		for (int i = 0; i < (int)g[at].size(); i++)
		{
			idx = g[at][i];
			if(idx % 2 != 0) continue;
			
			if(ed[idx].f == 1){
				if(ed[idx].to == n+1) prog.pb(at);
				else spo.pb(at);
			}
		}
	}
	
	for (int i = 0; i < (int)prog.size(); i++)
	{
		cout << prog[i] << " ";
	}
	cout << "\n";
	
	for (int i = 0; i < (int)spo.size(); i++)
	{
		cout << spo[i] << " ";
	}
	cout << "\n";
	
	
	
	
	return 0;
}
