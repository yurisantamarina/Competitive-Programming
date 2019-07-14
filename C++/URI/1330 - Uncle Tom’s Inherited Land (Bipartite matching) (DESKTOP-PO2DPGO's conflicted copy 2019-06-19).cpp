#include <bits/stdc++.h>

using namespace std;
#define F first
#define S second
#define mp make_pair
#define pb push_back
#define MAXM 101010
#define MAXN 10100


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
int dx[]={1,0,-1,0};
int dy[]={0,1,0,-1};
int src;
int sink;
int grid[110][110];
int n, m;
int seen[MAXN];
int cur;
vector<int> g[MAXN];
int tempo;

bool pode(int x, int y){
	return x >= 0 && x < n && y>=0 && y<m && grid[x][y] == 0;
}

bool par(int i, int j){
	return (i+j)%2 == 0;
}

void add_edge(int u, int v, int cap, int rcap){
	ed[cur] = edge(v, 0, cap);
	g[u].pb(cur++);
	
	ed[cur] = edge(u, 0, rcap);
	g[v].pb(cur++);
}

void build(){
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			if(grid[i][j] == 0){
				if(par(i, j)){
					add_edge(src, i*m + j, 1, 0);
					
					for(int k = 0; k<4; k++){
						if(pode(i+dx[k], j+dy[k])){
							add_edge(i*m + j, (i+dx[k])*m + (j+dy[k]), 1, 0);
						}
					}
					
				}else add_edge(i*m + j, sink, 1, 0);
				
				
				
			}
		}
	}
}

void reset(){
	cur = 0;
	memset(grid, 0, sizeof grid);
	for (int i = 0; i < n*m+5; i++)
	{
		g[i].clear();
	}
	
}

int dfs(int at, int mn){
	if(at==sink) return mn;
	
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
	memset(seen, 0, sizeof seen);
	tempo = 1;
	while (int a = dfs(src, INT_MAX))
	{
		flow += a;
		tempo++;
	}
	
	return flow;
}

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	int x, y, qtd;
	while (cin >> n >> m, n && m)
	{
		reset();
		src = n*m + 2;
		sink = n*m + 3;
		cin >> qtd;
		while (qtd--)
		{
			cin >> x >> y;
			x--; y--;
			grid[x][y] = 1;
		}
		
		build();
		cout << mf() << "\n";
		
		
	}
	
	
	return 0;
}
