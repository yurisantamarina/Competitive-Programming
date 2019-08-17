#include <bits/stdc++.h>

using namespace std;
#define MAXM 10101010
#define MAXN 101010
#define pb push_back
#define mp make_pair
#define F first
#define S second
#define INF 1e9

struct pv{
	int x, y;
	pv(){}
	pv(int _x, int _y){
		x = _x;
		y = _y;
	}
};

struct edge{
	int to, f, c;
	double cost;
	edge(){}
	edge(int _to, int _f, int _c, double _cost){
		to = _to;
		f = _f;
		c = _c;
		cost = _cost;
	}
};

edge ed[MAXM];
char inq[MAXN];
vector<int> g[MAXN];
double dist[MAXN];
int n;
int cur;
pair<int, int> pai[MAXN];

int in(int u){
	return u;
}

int out(int u){
	return u + n;
}

double distPt(pv a, pv b){
	return hypot(a.x - b.x, a.y - b.y);
}

void add_edge(int u, int v, int cap, int rcap, double cost){
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
	inq[src] = 1;
	dist[src] = 0;
	
	int u, v, idx, cap;
	double cost;
	while (!q.empty())
	{
		u = q.front();
		q.pop();
		inq[u] = 0;
		
		for (int i = 0; i < (int)g[u].size(); i++)
		{
			idx = g[u][i];
			v = ed[idx].to;
			cap = ed[idx].c - ed[idx].f;
			cost = ed[idx].cost;
			
			if(dist[u] + cost < dist[v] && cap){
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

pair<int, double> augment(int src, int sink){
	int u, mn = INF;
	double cost = 0.0;
	int cap, idx;
	
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

pair<int, double> mcmf(int src, int sink){
	pair<int, double> ans, aux;
	ans = mp(0, 0.0);
	
	while (spfa(src, sink))
	{
		aux = augment(src, sink);
		ans.F += aux.F;
		ans.S += aux.S;
	}
	
	//~ printf("flow = %d  cost = %.2lf\n", ans.F, ans.S);
	return ans;
}

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	int cur;
	vector<pv> vet;
	
	int x, y;
	cin >> n;
	for (int i = 0; i < n; i++)
	{
		cin >> x >> y;
		vet.pb(pv(x, y));
	}
	
	int src = 2*n + 2;
	int sink = 2*n + 3;
	for (int i = 0; i < n; i++)
	{
		add_edge(src, out(i), 2, 0, 0);
		//~ printf("aresta de %d para %d com cap %d e custo %.2lf\n", src, out(i))
		for (int j = 0; j < n; j++)
		{
			if(i==0) add_edge(in(j), sink, 1, 0, 0);
			if(i == j) continue;
			if(vet[i].y > vet[j].y){
				add_edge(out(i), in(j), 1, 0, distPt(vet[i], vet[j]));
			}
		}
	}
	
	pair<int, double> ans = mcmf(src, sink);
	if(ans.F == n-1){
		cout << fixed << setprecision(20) << ans.S << "\n";
	}else cout << "-1\n";
	
	
	return 0;
}
