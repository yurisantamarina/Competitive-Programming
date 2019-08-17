#include <bits/stdc++.h>

using namespace std;

#define MAXM 101010
#define MAXN 110
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

edge ed[MAXM];
vector<int> g[MAXN];
vector<pair<int, int> > votos;
int grau[MAXN];
int n;
int cur;
int tempo;
int seen[MAXN];

int in(int u){
	return u;
}

int out(int u){
	return n+u;
}

void add_edge(int u, int v, int cap, int rcap){
	ed[cur] = edge(v, 0, cap);
	g[u].pb(cur++);
	
	ed[cur] = edge(u, 0, rcap);
	g[v].pb(cur++);
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
			if(int a = dfs(v, sink, min(mn, cap))){//achei caminho
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
	
	//~ printf("flow = %d\n", flow);
	return flow;
}

void reset(){
	cur = 0;
	for (int i = 0; i < MAXN; i++)
	{
		g[i].clear();
	}
	
}

bool sobrevive(int wf){
	int recebe = grau[wf];
	int faltaVotar = n - 1 - recebe;
	int src = MAXN-1;
	int sink = MAXN-2;
	reset();
	
	//~ printf("wf = %d  recebe %d votos\n", wf+1, recebe);
	for (int i = 0; i < n; i++)
	{
		//src -> in
		if(i == wf || votos[i].F == wf || votos[i].S == wf){
			add_edge(src, in(i), 0, 0);
			//~ printf("aresta do src para %d com cap %d\n", i+1, 0);
		}else{
			add_edge(src, in(i), 1, 0);
			//~ printf("aresta do src para %d com cap %d\n", i+1, 1);
		}
		
		//in -> out
		add_edge(in(i), out(votos[i].F), INF, 0);
		add_edge(in(i), out(votos[i].S), INF, 0);
		
		//out -> sink
		if(votos[wf].F == i || votos[wf].S == i){
			add_edge(out(i), sink, max(recebe-2, 0), 0);
			//~ printf("aresta de %d para sink com cap %d\n", i+1, max(recebe-2, 0));
		}else{
			if(i!=wf){
				add_edge(out(i), sink, max(recebe-1, 0), 0);
				//~ printf("aresta de %d para sink com cap %d\n", i+1, max(recebe-1, 0));
			}
		}
	}
	
	//~ printf("faltaVotar = %d\n", faltaVotar);
	return mf(src, sink) != faltaVotar;
}


int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	int u, v;
	cin >> n;
	for (int i = 0; i < n; i++)
	{
		cin >> u >> v;
		votos.pb(mp(u-1, v-1));
		grau[u-1]++;
		grau[v-1]++;
	}
	
	int ans = 0;
	for (int i = 0; i < n; i++)
	{
		if(sobrevive(i)){
			ans++;
			//~ printf("%d sobrevive\n", i+1);
		}
	}
	cout << ans << "\n";
	
	
	return 0;
}
