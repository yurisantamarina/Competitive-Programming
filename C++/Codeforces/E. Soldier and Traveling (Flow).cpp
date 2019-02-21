#include <bits/stdc++.h>

using namespace std;
#define F first
#define S second
#define pb push_back
#define mp make_pair
#define MAXM 101010
#define MAXN 250
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

edge ed[MAXM];
vector<int> g[MAXN];
vector<int> adj[MAXN];
int seen[MAXN];
int cur;
int tempo;
int A[MAXN];
int B[MAXN];
int sumA, sumB;
int n, m;

int in(int u){
	return u;
}

int out(int u){
	return n+u;
}

void add_edge(int u, int v, int cap, int rcap){
	ed[cur] = edge(v, 0, cap);
	g[u].pb(cur++);
	//~ printf("adicionando %d na lista de adjacencia do %d\n", v, u);
	
	ed[cur] = edge(u, 0, rcap);
	g[v].pb(cur++);
	//~ printf("adicionando %d na lista de adjacencia do %d\n", u, v);
}

int dfs(int at, int sink, int mn){
	if(at == sink) return mn;
	
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

bool ok(){
	int src = MAXN-1;
	int sink = MAXN-2;
	
	for (int i = 0; i < n; i++)
	{
		add_edge(src, in(i), A[i], 0);
		add_edge(out(i), sink, B[i], 0);
		//~ printf("aresta do src para in(%d) = %d   com cap %d\n", i, in(i), A[i]);
		//~ printf("aresta do out(%d) = %d para sink  com cap %d\n", i, out(i), B[i]);
		for (int j = 0; j < (int)adj[i].size(); j++)
		{
			add_edge(in(i), out(adj[i][j]), INF, 0);
			//~ printf("aresta do in(%d) = %d para out(%d) = %d  com cap INF\n", i, in(i), adj[i][j], out(adj[i][j]));
		}
		add_edge(in(i), out(i), INF, 0);
		//~ printf("aresta do in(%d) = %d para out(%d) = %d  com cap INF\n", i, in(i), i, out(i));
	}
	
	return mf(src, sink) == sumA;
}

void printa(){
	int ans[102][102];
	memset(ans, 0, sizeof ans);
	
	int idx, v;
	for (int i = 0; i < n; i++)
	{
		for(int j = 0; j < (int)g[i].size(); j++){
			idx = g[i][j];
			v = ed[idx].to;
			if(ed[idx].f > 0 && idx%2==0){
				//~ printf("oi i = %d v = %d  f = %d\n", i, v, ed[idx].f);
				ans[i][v-n] = ed[idx].f;
			}
		}
		for (int j = 0; j < n; j++)
		{
			cout << ans[i][j] << " ";
		}
		cout << "\n";
	}
	
	
}

int main(){
	sumA = 0;
	sumB = 0;
	int u, v;
	cin >> n >> m;
	for (int i = 0; i < n; i++)
	{
		cin >> A[i];
		sumA += A[i];
	}
	for (int i = 0; i < n; i++)
	{
		cin >> B[i];
		sumB += B[i];
	}
	
	for (int i = 0; i < m; i++)
	{
		cin >> u >> v;
		u--; v--;
		adj[u].pb(v);
		adj[v].pb(u);
	}
	
	
	if(sumA != sumB){
		cout << "NO\n";
		return 0;
	}
	
	if(ok()){
		cout << "YES\n";
		printa();
	}else{
		cout << "NO\n";
	}
	
	return 0;
}
