#include <bits/stdc++.h>

using namespace std;
#define F first
#define S second
#define MAXM 10000000
#define MAXN 51000
#define mp make_pair
#define pb push_back

struct edge{
	int to, f, c;
	edge(){}
	edge(int _to, int _f, int _c){
		to = _to;
		f = _f;
		c = _c;
	}
};

edge ed[MAXM];
vector<int> g[MAXN];
int cur;
int ptr[MAXN];
int lvl[MAXN];
int n, m, mx;

void add_edge(int u, int v, int cap, int rcap){
	ed[cur] = edge(v, 0, cap);
	g[u].pb(cur++);
	
	ed[cur] = edge(u, 0, rcap);
	g[v].pb(cur++);
}

bool bfs(int src, int sink){
	memset(lvl, -1, sizeof lvl);
	queue<int> q;
	q.push(src);
	lvl[src] = 0;
	
	int u, v, cap, idx;
	while (!q.empty())
	{
		u = q.front();
		q.pop();
		
		for (int i = 0; i < (int)g[u].size(); i++)
		{
			idx = g[u][i];
			v = ed[idx].to;
			cap = ed[idx].c - ed[idx].f;
			
			if(lvl[v] == -1 && cap > 0){
				lvl[v] = lvl[u] + 1;
				q.push(v);
			}
		}
		
	}
	
	return lvl[sink] != -1;
}

int dfs(int at, int sink, int mn){
	if(at == sink) return mn;
	
	int idx, v, cap;
	for (int &i = ptr[at]; i < (int)g[at].size(); i++)
	{
		idx = g[at][i];
		v = ed[idx].to;
		cap = ed[idx].c - ed[idx].f;
		
		if(lvl[v] == lvl[at] + 1 && cap > 0){
			
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
	int flow = 0;
	
	while (bfs(src, sink))
	{
		memset(ptr, 0, sizeof ptr);
		while (int a = dfs(src, sink, INT_MAX))
		{
			flow += a;
		}
	}
	
	return flow;
}

void printa(int u){
	
	int idx;
	vector<pair<int, int> > intervalo;
	vector<pair<int, int> > saida;
	
	int ini = -1, fim = -1;
	for (int i = 0; i < (int)g[u].size(); i++)
	{
		idx = g[u][i];
		if(idx % 2 != 0) continue;
		
		//~ printf("aresta de %d para %d\n", u, ed[idx].to);
		if(ed[idx].f == 1){
			if(ini == fim && ini == -1){
				ini = ed[idx].to - n;
				fim = ed[idx].to - n + 1;
				//~ printf("ini = %d  fim = %d\n", ini, fim);
			}else{
				if(ed[idx].to - n == fim){
					fim++;
				}else{
					intervalo.pb(mp(ini, fim));
					ini = ed[idx].to - n;
					fim = ed[idx].to - n + 1;
				}
			}
		}
	}
	intervalo.pb(mp(ini, fim));
	
	cout << (int)intervalo.size();
	for (int i = 0; i < (int)intervalo.size(); i++)
	{
		cout << " " << "(" << intervalo[i].F << "," << intervalo[i].S << ")";
	}
	cout << "\n";
	
}

void reset(){
	cur = 0;
	for (int i = 0; i < n+mx+3; i++)
	{
		g[i].clear();
	}
	
}

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	int src, sink, need, tot, a, b, caso = 1;
	while(cin >> n, n){
		cin >> m;
	
		tot = 0;
		src = 0;
		
		reset();
		mx = 0;
		for (int i = 0; i < n; i++)
		{
			cin >> need >> a >> b;
			mx = max(mx, b);
			
			tot += need;
			add_edge(src, i+1, need, 0);
			for(int j = a; j < b; j++){
				add_edge(i+1, j+n, 1, 0);
				//~ printf("aresta de %d para %d\n", i+1, j+n);
			}
		}
		
		sink = mx + n;
		for (int i = 1; i <= mx; i++)
		{
			add_edge(i+n, sink, m, 0);
		}
		
		int aux = mf(src, sink);
		//~ printf("mf = %d\n", aux);
		cout << "Case " << caso++ << ": ";
		if(aux != tot){
			cout << "No\n";
			
		}else{
			cout << "Yes\n";
			for (int i = 1; i <= n; i++)
			{
				printa(i);
			}
			
		}
	}
		
	return 0;
}
