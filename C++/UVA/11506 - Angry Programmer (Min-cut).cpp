#include <bits/stdc++.h>

using namespace std;
#define MAXM 1010101
#define MAXN 120
#define F first
#define S second
#define pb push_back
#define mp make_pair

struct edge{
	long long to, f, c;
	edge(){}
	edge(long long _to, long long _f, long long _c){
		to = _to;
		f = _f;
		c = _c;
	}
};

edge ed[MAXM];
vector<long long> g[MAXN];
long long tempo, cur;
long long seen[MAXN];
long long src, sink;
long long n, m;

long long in(long long u){
	return u;
}

long long out(long long u){
	return u+n;
}

void add_edge(long long u, long long v, long long cap, long long rcap){
	ed[cur] = edge(v, 0, cap);
	g[u].pb(cur++);
	
	ed[cur] = edge(u, 0, rcap);
	g[v].pb(cur++);
}

long long dfs(long long at, long long mn){
	if(at == sink){
		//~ prlong longf("%d - ", at);
		return mn;
	}
	
	long long idx, v, cap;
	
	for (long long i = 0; i < (long long)g[at].size(); i++)
	{
		idx = g[at][i];
		v = ed[idx].to;
		cap = ed[idx].c - ed[idx].f;
		
		if(seen[v] < tempo && cap > 0){
			seen[v] = tempo;
			
			if(long long a = dfs(v, min(mn, cap))){
				ed[idx].f += a;
				ed[idx^1].f -= a;
				//~ prlong longf("%d - ", at);
				return a;
			}
		}
	}
	
	
	return 0;
}

long long mf(){
	memset(seen, 0, sizeof seen);
	tempo = 1;
	long long flow = 0;
	while (long long a = dfs(src, INT_MAX))
	{
		flow += a;
		
		//~ prlong longf("  flow += %d\n", a);
		tempo++;
	}
	
	return flow;
}

void reset(){
	cur = 0;
	
	for (long long i = 0; i < MAXN; i++)
	{
		g[i].clear();
	}
}

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	long long u, v, w;
	while (cin >> n >> m)
	{
		if(n == 0 && m == 0) break;
		reset();
		for (long long i = 0; i < n-2; i++)
		{
			cin >> u >> w;
			u--;
			
			add_edge(in(u), out(u), w, 0);
			add_edge(out(u), in(u), w, 0);
		}
		
		for (long long i = 0; i < m; i++)
		{
			cin >> u >> v >> w;
			u--; v--;
			add_edge(out(u), in(v), w, 0);
			add_edge(out(v), in(u), w, 0);
		}
		
		src = out(0);
		sink = in(n-1);
		cout << mf() << "\n";
	}
	
	
}
