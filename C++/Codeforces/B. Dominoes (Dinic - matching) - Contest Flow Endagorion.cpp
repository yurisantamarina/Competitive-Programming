http://codeforces.com/group/3qadGzUdR4/contest/101712/problem/B

#include <bits/stdc++.h>

using namespace std;
#define MAXN 1700
#define pb push_back
#define mp make_pair
#define F first
#define S second
int dx[]={0, 1, -1, 0};
int dy[]={1, 0, 0, -1};

struct edge{
	int from, to, c, f;
	edge(){}
	edge(int a, int b, int _c, int d){
		from = a;
		to = b;
		c = _c;
		f = d;
	}
};

vector<edge> ed;
vector<int> g[MAXN];
int tempo;
int lvl[MAXN];
int ptr[MAXN];
int src = 0, sink = 1;
int grid[MAXN][MAXN];
map<pair<int, int>, int> mapa;
int n;
vector<int> pares;
map<int, pair<int, int> > rev;
int counter = 2;

void add_edge(int from, int to, int c){
	g[from].pb((int)ed.size());
	ed.pb(edge(from, to, c, 0));
	
	g[to].pb((int)ed.size());
	ed.pb(edge(to, from, 0, 0));
}

bool bfs(){
	queue<int> q;
	for (int i = 0; i < counter; i++)
		lvl[i] = -1;
	
	lvl[src] = 0;
	q.push(src);
	
	int u, v, cap;
	while (!q.empty())
	{
		u = q.front(); q.pop();
		
		for(int idx : g[u]){
			v = ed[idx].to;
			cap = ed[idx].c - ed[idx].f;
			if(cap > 0 && lvl[v] == -1){
				lvl[v] = lvl[u] + 1;
				q.push(v);
			}
		}
	}
	
	return lvl[sink] != -1;
}

int dfs(int at, int mn){
	if(at == sink) return mn;
	
	int idx, v, cap;
	for(int &i = ptr[at]; i < g[at].size(); i++){
		idx = g[at][i];
		v = ed[idx].to;
		cap = ed[idx].c - ed[idx].f;
		
		if(cap > 0 && lvl[v] == lvl[at] + 1){
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
	while(bfs()){
		memset(ptr, 0, sizeof ptr);
		while(int a = dfs(src, INT_MAX)){
			flow += a;
		}
	}
	return flow;
}

bool ok(int x, int y){
	return x>=1 && x <= n && y>=1 && y<=n && grid[x][y] == 0;
}


int get(int i, int j){
	if(mapa.count(mp(i, j))) return mapa[mp(i, j)];
	
	rev[counter] = mp(i, j);
	return mapa[mp(i, j)] = counter++;
}

void build(){
	int u, v;
	for (int i = 1; i <= n; i++)
	{
		for (int j = 1; j <= n; j++)
		{
			if(grid[i][j]) continue;
			if((i+j)%2 != 0){
				add_edge(get(i, j), sink, 1);
				//~ printf("aresta de (%d, %d)[%d] para sink\n", i, j, get(i, j));
				continue;
			}
			add_edge(src, get(i, j), 1);
			
			pares.pb(get(i, j));
			
			//~ printf("aresta de src para (%d, %d)[%d]\n", i, j, get(i, j));
			for (int k = 0; k < 4; k++)
			{
				if(ok(i+dx[k], j+dy[k])){
					u = get(i, j);
					v = get(i+dx[k], j+dy[k]);
					//~ printf("%d+%d, %d+%d = (%d, %d)\n", i, dx[k], j, dy[k], i+dx[k], j+dy[k]);
					//~ printf("aresta de (%d, %d)[%d] para (%d, %d)[%d]\n", i, j, u, i+dx[k], j+dy[k], v);
					add_edge(u, v, 1);
				}
			}
		}
	}
	
	
}

bool horiz(int u, int v){
	pair<int, int> a = rev[u];
	pair<int, int> b = rev[v];
	
	return a.F != b.F;
}

pair<int, int> getF(int u, int v){
	pair<int, int> a = rev[u];
	pair<int, int> b = rev[v];
	if(a.F < b.F) return a;
	if(a.S < b.S) return a;
	return b;
}

int main(){
	int qtd, x, y;
	cin >> n >> qtd;
	
	int tot = n*n;
	for (int i = 0; i < qtd; i++)
	{
		cin >> x >> y;
		grid[x][y] = 1;
		
		tot--;
	}
	
	if(tot % 2){
		cout << "No\n";
		return 0;
	}
	
	build();
	int ans = mf();
	if(ans != tot / 2){
		cout << "No\n";
		return 0;
	}
	cout << "Yes\n";
	
	int u;
	vector<pair<int, int> > hor, ver;
	for (int k = 0; k < pares.size(); k++)
	{
		u = pares[k];
		for (int i = 0; i < g[u].size(); i++)
		{
			if(ed[g[u][i]].to == src) continue;
			if(ed[g[u][i]].f == 1){
				//~ printf("aresta de %d para %d\n", u, ed[g[u][i]].to);
				if(horiz(u, ed[g[u][i]].to)) hor.pb(getF(u, ed[g[u][i]].to));
				else ver.pb(getF(u, ed[g[u][i]].to));
			}
		}
	}
	
	cout << hor.size() << "\n";
	for (int i = 0; i < hor.size(); i++)
	{
		cout << hor[i].F << " " << hor[i].S << "\n";
	}
	
	cout << ver.size() << "\n";
	for (int i = 0; i < ver.size(); i++)
	{
		cout << ver[i].F << " " << ver[i].S << "\n";
	}
	
	return 0;
}
