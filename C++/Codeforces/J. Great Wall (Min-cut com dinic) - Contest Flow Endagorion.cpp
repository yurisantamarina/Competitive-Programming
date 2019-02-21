http://codeforces.com/group/3qadGzUdR4/contest/101712/problem/J

#include <bits/stdc++.h>

using namespace std;
#define mp make_pair
#define pb push_back
#define F first
#define S second
#define INF 1e9
#define MAXN 6000

int dx[]={1, 0, -1, 0};
int dy[]={0, 1, 0, -1};

struct edge{
	int from, to, f, c;
	edge(){}
	edge(int a, int b, int cc, int d){
		from = a;
		to = b;
		f = cc;
		c = d;
	}
};

int n = 5, m = 5;
int ptr[MAXN], lvl[MAXN];
char vis[MAXN];
vector<int> g[MAXN];
vector<edge> ed;
char mount[55][55], forb[55][55];

void add_edge(int from, int to, int cap){
	g[from].pb((int)ed.size());
	ed.pb(edge(from, to, 0, cap));
	
	g[to].pb((int)ed.size());
	ed.pb(edge(to, from, 0, 0));
}

int getIn(int i, int j){
	return (i-1)*m + j;
}

int getOut(int i, int j){
	return getIn(i, j) + n*m;
}

pair<int, int> getRev(int u){
	if(u > n*m) u -= n*m;
	
	if(u % m == 0) return mp(u / m, m);
	return mp(u / m + 1, u % m);
}

bool bfs(int src, int sink){
	queue<int> q;
	int lim = getOut(n, m);
	for(int i = 0; i <= lim+1; i++)
		lvl[i] = -1;
	
	q.push(src);
	lvl[src] = 0;
	
	int u, v, cap;
	while(!q.empty()){
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

int dfs(int at, int sink, int mn){
	if(at == sink) return mn;
	int idx, v, cap;
	
	for(int &i = ptr[at]; i < g[at].size(); i++){
		idx = g[at][i];
		v = ed[idx].to;
		cap = ed[idx].c - ed[idx].f;
		
		if(cap > 0 && lvl[v] == lvl[at] + 1){
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
	while(bfs(src, sink)){
		memset(ptr, 0, sizeof ptr);
		
		while(int a = dfs(src, sink, INT_MAX)){
			flow += a;
		}
	}
	return flow;
}

void dfs2(int u){
	if(vis[u]) return;
	vis[u] = 1;
	
	int v, cap;
	for(int idx : g[u]){
		v = ed[idx].to;
		cap = ed[idx].c - ed[idx].f;
		if(cap > 0) dfs2(v);
	}
}

void recover(vector<pair<int, int> >& saida, int x, int y){
	saida.clear();
	dfs2(getIn(x, y));
	
	int v, u;
	for (int i = 0; i < ed.size(); i++)
	{
		u = ed[i].from;
		v = ed[i].to;
		
		if(vis[u] && !vis[v]){
			if(v - u == n*m) saida.pb(getRev(u));
		}
	}
	
}

bool ok(int x, int y){
	return x >= 1 && x <= n && y >= 1 && y <= m && !mount[x][y];
}

void build_graph(){
	
	for (int i = 1; i <= n; i++)
	{
		for (int j = 1; j <= m; j++)
		{
			if(mount[i][j]) continue;
			
			if(forb[i][j]){
				add_edge(getIn(i, j), getOut(i, j), INF);
			}else{
				add_edge(getIn(i, j), getOut(i, j), 1);
			}
			
			for(int k = 0; k < 4; k++){
				if(ok(i + dx[k], j + dy[k])){
					add_edge(getOut(i, j), getIn(i + dx[k], j + dy[k]), INF);
				}
			}
		}
	}
}

int main(){
	int mountains, ok, x, y, xini, yini, xfim, yfim;
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cin >> n >> m;
	cin >> mountains >> ok;
	
	for (int i = 0; i < mountains; i++)
	{
		cin >> x >> y;
		mount[x][y] = 1;
	}
	
	for(int i = 0; i <= n; i++)
		for (int j = 0; j <= m; j++)
			forb[i][j] = 1;
			
	for (int i = 0; i < ok; i++)
	{
		cin >> x >> y;
		forb[x][y] = 0;
	}
	
	cin >> xini >> yini >> xfim >> yfim;
	
	build_graph();
	
	int ans = mf(getIn(xini, yini), getOut(xfim, yfim));
	vector<pair<int, int> > saida;
	if(ans <= ok){
		cout << ans << "\n";
		recover(saida, xini, yini);
		sort(saida.begin(), saida.end());
		for (int i = 0; i < saida.size(); i++)
		{
			cout << saida[i].F << " " << saida[i].S << "\n";
		}
		
	}else{
		cout << "-1\n";
	}
	
	
	return 0;
}
