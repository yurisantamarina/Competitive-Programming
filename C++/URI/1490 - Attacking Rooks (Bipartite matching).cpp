#include <bits/stdc++.h>

using namespace std;
#define MAXM 101010
#define MAXN 7500
#define F first
#define S second
#define pb push_back
#define mp make_pair

struct edge{
	int to, f, c;
	edge(){}
	edge(int _to, int _f, int _c){
		to = _to;
		f = _f;
		c = _c;
	}
};

int at[110][110];
char grid[110][110];
int n;
int cur;
vector<int> g[MAXN];
edge ed[MAXM];
int src = 0;
int sink = 1;
int seen[MAXN];
int tempo;
int cnt;


void add_edge(int u, int v, int cap, int rcap){
	ed[cur] = edge(v, 0, cap);
	g[u].pb(cur++);
	
	ed[cur] = edge(u, 0, rcap);
	g[v].pb(cur++);
}

int dfs(int at, int mn){
	if(at == sink) return mn;
	
	int idx, v, cap;
	for (int i = 0; i < (int)g[at].size(); i++)
	{
		idx = g[at][i];
		v = ed[idx].to;
		cap = ed[idx].c - ed[idx].f;
		
		if(seen[v] < tempo && cap > 0){
			seen[v] = tempo;
			if(int a = dfs(v, min(mn, cap))){
				ed[idx].f += a;
				ed[idx^1].f -= a;
				return a;
			}
		}
	}
	return 0;
}

int mf(){
	int flow = 0;
	tempo = 1;
	memset(seen, 0, sizeof seen);
	
	while (int a = dfs(src, INT_MAX))
	{
		flow += a;
		tempo++;
	}
	
	return flow;
}

void build(){
	
	cnt = 2;
	
	add_edge(src, cnt, 1, 0);
	//~ printf("aresta de src pra %d\n", cnt);
	
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			if(grid[i][j] == 'X'){
				if(j == 0 || grid[i][j-1]=='X') continue;
				cnt++;
				add_edge(src, cnt, 1, 0);
				//~ printf("aresta de src pra %d\n", cnt);
				continue;
			}
			//~ printf("posicao [%d][%d] tem linha %d\n", i, j, cnt);
			at[i][j] = cnt;
		}
		cnt++;
		add_edge(src, cnt, 1, 0);
		//~ printf("aresta de src pra %d\n", cnt);
	}
	
	cnt++;
	add_edge(cnt, sink, 1, 0);
	//~ printf("aresta de %d pra sink\n", cnt);
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			if(grid[j][i] == 'X'){
				if(j==0 || grid[j-1][i] == 'X') continue;
				cnt++;
				add_edge(cnt, sink, 1, 0);
				//~ printf("aresta de %d pra sink\n", cnt);
				continue;
			}
			add_edge(at[j][i], cnt, 1, 0);
			//~ printf("posicao [%d][%d] tem coluna %d\n", j, i, cnt);
		}
		cnt++;
		add_edge(cnt, sink, 1, 0);
		//~ printf("aresta de %d pra sink\n", cnt);
	}
	
	
}

void reset(){
	cur = 0;
	for (int i = 0; i <= cnt; i++)
	{
		g[i].clear();
	}
}


int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	while(cin >> n){
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < n; j++)
			{
				cin >> grid[i][j];
			}
		}

		build();
		cout << mf() << "\n";
		reset();
	}

	return 0;
}
