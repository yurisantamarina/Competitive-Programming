#include <bits/stdc++.h>

using namespace std;
typedef long long int ll;
#define MAXN 100
#define pb push_back
#define mp make_pair
#define F first
#define S second

struct edge{
	ll to, f, c;
	edge(){}
	edge(ll _to, ll _f, ll _c){
		to = _to;
		f = _f;
		c = _c;
	}
};

vector<edge> ed;
vector<ll> g[MAXN];
ll n, m, bears;
vector<edge> aresta;
int lvl[MAXN];
int ptr[MAXN];

void add_edge(ll u, ll v, ll cap, ll rcap){
	ed.pb(edge(v, 0, cap));
	g[u].pb((ll)ed.size() - 1);
	
	ed.pb(edge(u, 0, rcap));
	g[v].pb((ll)ed.size() - 1);
}

void build(double mx){
	for (ll i = 0; i <= n; i++)
	{
		g[i].clear();
	}
	ed.clear();
	
	for (ll i = 0; i < m; i++)
	{
		add_edge(aresta[i].to, aresta[i].f, ll(aresta[i].c*1.0 / mx), 0);
		//~ printf("aresta de %lld para %lld com cap %lld\n", aresta[i].to+1, aresta[i].f+1, ll(aresta[i].c*1.0 / mx));
	}
	
}

bool bfs(){
	queue<int> q;
	memset(lvl, -1, sizeof lvl);
	lvl[0] = 0;
	q.push(0);
	
	int u, v, idx;
	ll cap;
	
	while (!q.empty())
	{
		u = q.front();
		q.pop();
		
		for (int i = 0; i < (int)g[u].size(); i++)
		{
			idx = g[u][i];
			v = ed[idx].to;
			cap = ed[idx].c - ed[idx].f;
			
			if(lvl[v]==-1 && cap > 0){
				lvl[v] = lvl[u] + 1;
				q.push(v);
			}
		}
		
	}
	
	
	return lvl[n-1]!=-1;
}

ll dfs(int at, int sink, ll mn){
	if(at == sink) return mn;
	
	int idx, v;
	ll cap;
	
	for (int &i = ptr[at]; i < (int)g[at].size(); i++)
	{
		idx = g[at][i];
		v = ed[idx].to;
		cap = ed[idx].c - ed[idx].f;
		
		if(lvl[v] == lvl[at] + 1 && cap > 0){
			
			if(ll a = dfs(v, sink, min(mn, cap))){
				ed[idx].f += a;
				ed[idx^1].f -= a;
				return a;
			}
			
		}
		
	}
	
	
	return 0;
}

int mf(){
	ll flow = 0;
	
	while (bfs())
	{
		memset(ptr, 0, sizeof ptr);
		while (ll a = dfs(0, n-1, LLONG_MAX))
		{
			flow += a;
		}
	}
	
	
	return flow;
}

double solve(){
	double lo = 0.0;
	double hi = 10000000000000000000000000.0;
	double mid;
	
	double ans = 0.0;
	for (ll i = 0; i < 150; i++)
	{
		mid = (lo+hi)/2.0;
		build(mid);
		
		if(mf() >= bears){
			lo = mid;
			ans = max(ans, mid);
		}else{
			hi = mid;
		}
	}
	
	
	return ans * bears;
}

int main(){
	ll u, v, w;
	cin >> n >> m >> bears;
	for (ll i = 0; i < m; i++)
	{
		cin >> u >> v >> w;
		u--; v--;
		aresta.pb(edge(u, v, w));
	}
	
	cout << fixed << setprecision(15) << solve() << "\n";
	
	return 0;
}
