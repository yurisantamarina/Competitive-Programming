#include <bits/stdc++.h>

using namespace std;
#define F first
#define S second
#define mp make_pair
#define pb push_back
#define MAXM 101010
#define MAXN 5000
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

struct gelo{
	int x, y, tem, pode, id;
	gelo(){}
	gelo(int a, int b, int c, int d, int e){
		x = a;
		y = b;
		tem = c;
		pode = d;
		id = e;
	}
};

edge ed[MAXM];
vector<int> g[MAXN];
vector<int> adj[MAXN];
int cur, tempo;
int seen[MAXN];
vector<gelo> vet;
int n;
double maxDist;



void add_edge(int u, int v, int cap, int rcap){
	ed[cur] = edge(v, 0, cap);
	g[u].pb(cur++);
	
	ed[cur] = edge(u, 0, rcap);
	g[v].pb(cur++);
}

double dist(gelo a, gelo b){
	return hypot(a.x - b.x, a.y - b.y);
}

int need;
int in(int u){return u;}
int out(int u){return u+n;}

void build(int fim){
	for (int i = 0; i < 2*n + 10; i++)
	{
		g[i].clear();
	}
	cur = 0;
	
	need = 0;
	int src = 2*n+1;
	for (int i = 0; i < n; i++)
	{
		if(i==fim){
			add_edge(in(i), out(i), INF, 0);
		}else{
			add_edge(in(i), out(i), vet[i].pode, 0);
		}
		if(vet[i].tem && i!=fim){
			add_edge(src, in(i), vet[i].tem, 0);
			need += vet[i].tem;
		}
		
		for(int j = 0; j < (int)adj[i].size(); j++){
			add_edge(out(i), in(adj[i][j]), INF, 0);
		}
	}
}

int dfs(int at, int sink, int mn){
	if(at == sink){
		return mn;
	}
	
	int idx, v, cap;
	
	for (int i = 0; i < (int)g[at].size(); i++)
	{
		idx = g[at][i];
		v = ed[idx].to;
		cap = ed[idx].c - ed[idx].f;
		
		if(seen[v] < tempo && cap > 0){
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
	int flow = 0;
	tempo = 1;
	memset(seen, 0, sizeof seen);
	while (int a = dfs(src, sink, INT_MAX))
	{
		flow += a;
		tempo++;
	}
	
	return flow;
}

bool ok(int fim){
	
	return mf(2*n+1, out(fim)) == need;
	
}

void reset(){
	cur = 0;
	for (int i = 0; i < 2*n+10; i++)
	{
		g[i].clear();
		adj[i].clear();
	}
	vet.clear();
}

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	int x, y, pode, tem, tc;
	cin >> tc;
	while (tc--)
	{
		reset();
		cin >> n >> maxDist;
		for (int i = 0; i < n; i++)
		{
			cin >> x >> y >> tem >> pode;
			vet.pb(gelo(x, y, tem, pode, i));
		}
		
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < n; j++)
			{
				if(i==j) continue;
				if(dist(vet[i], vet[j]) <= maxDist){
					adj[i].pb(j);
				}
			}
		}
		
		int ans = 0;
		vector<int> aux;
		for (int i = 0; i < n; i++)
		{
			build(i);
			if(ok(i)) aux.pb(i);
		}
		if((int)aux.size() == 0) cout << "-1\n";
		else{
			for (int i = 0; i < (int)aux.size(); i++)
			{
				if(i) cout << " ";
				cout << aux[i];
			}
			cout << "\n";
		}
	}
	
	
	
	return 0;
}
