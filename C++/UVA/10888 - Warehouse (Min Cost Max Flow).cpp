#include <bits/stdc++.h>

using namespace std;
#define INF 1e9
#define mp make_pair
#define pb push_back
#define F first
#define S second
#define MAXM 10101001
#define MAXN 10101
int dx[]={1, 0, -1, 0};
int dy[]={0, 1, 0, -1};

struct edge{
	int to, f, c, cost;
	edge(){}
	edge(int _to, int _f, int _c, int _cost){
		to = _to;
		f = _f;
		c = _c;
		cost = _cost;
	}
};

edge ed[MAXM];
vector<int> g[MAXN];
int cur;
char inq[MAXN];
int dist2[45][45];
int n, m;
int dist[MAXN];
vector<pair<int, int> > ini, fim;
char grid[45][45];
pair<int, int> pai[MAXN];

void add_edge(int u, int v, int cap, int rcap, int cost){
	ed[cur] = edge(v, 0, cap, cost);
	g[u].pb(cur++);
	
	ed[cur] = edge(u, 0, rcap, -cost);
	g[v].pb(cur++);
}

bool pode(int x, int y){
	return x>=0 && x<n && y>=0 && y<m && grid[x][y] != '#';
}

void bfs(int x, int y){
	int xx, yy;
	xx = x;
	yy = y;
	queue<pair<int, int> > q;
	q.push(mp(x, y));
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			dist2[i][j] = INF;
		}
	}
	dist2[x][y] = 0;
	
	while (!q.empty())
	{
		x = q.front().F;
		y = q.front().S;
		q.pop();
		
		for (int i = 0; i < 4; i++)
		{
			if(pode(x+dx[i], y+dy[i]) && dist2[x][y] + 1 < dist2[x+dx[i]][y+dy[i]]){
				dist2[x+dx[i]][y+dy[i]] = dist2[x][y] + 1;
				q.push(mp(x+dx[i], y+dy[i]));
			}
		}
	}
	
	for (int i = 0; i < (int)fim.size(); i++)
	{
		add_edge(xx * m + yy, fim[i].F * m + fim[i].S, 1, 0, dist2[fim[i].F][fim[i].S]);
		
		//~ printf("ligando (%d, %d) a (%d, %d) com custo %d\n", xx, yy, fim[i].F, fim[i].S, dist2[fim[i].F][fim[i].S]);
	}
	
}

bool spfa(int src, int sink){
	memset(inq, 0, sizeof inq);
	for (int i = 0; i < n*m+5; i++)
	{
		dist[i] = INF;
	}
	
	
	queue<int> q;
	q.push(src);
	dist[src] = 0;
	inq[src] = 1;
	
	int cost, v, u, idx, cap;
	while (!q.empty())
	{
		u = q.front();
		q.pop();
		
		inq[u] = 0;
		
		for (int i = 0; i < (int)g[u].size(); i++)
		{
			idx = g[u][i];
			v = ed[idx].to;
			cap = ed[idx].c - ed[idx].f;
			cost = ed[idx].cost;
			
			if(dist[u] + cost < dist[v] && cap > 0){
				dist[v] = dist[u] + cost;
				pai[v] = mp(u, idx);
				if(!inq[v]){
					q.push(v);
					inq[v] = 1;
				}
			}
		}
		
	}
	
	
	return dist[sink]!=INF;
	
}

int augment(int src, int sink){
	int u, mn = INF;
	int cap, cost = 0;
	int idx;
	
	
	u = sink;
	while (u!=src)
	{
		
		idx = pai[u].S;
		cap = ed[idx].c - ed[idx].f;
		mn = min(mn, cap);
		u = pai[u].F;
	}
	
	u = sink;
	while (u!=src)
	{
		idx = pai[u].S;
		ed[idx].f += mn;
		ed[idx^1].f -= mn;
		cost += (ed[idx].cost * mn);
		u = pai[u].F;
	}
	
	
	return cost;
}

int mcmf(int src, int sink){
	int cost = 0;
	
	while (spfa(src, sink))
	{
		
		cost += augment(src, sink);
	}
	return cost;
}

void reset(){
	
	cur = 0;
	ini.clear();
	fim.clear();
	for (int i = 0; i <= n*m+5; i++)
	{
		g[i].clear();
	}
}

int main(){
	int tc, src, sink;
	cin >> tc;
	while (tc--)
	{
		cin >> n >> m;
		reset();
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < m; j++)
			{
				cin >> grid[i][j];
				if(grid[i][j] == 'B'){
					ini.pb(mp(i, j));
				}else if(grid[i][j] == 'X'){
					fim.pb(mp(i, j));
				}
			}
		}
		
		src = n*m + 2, sink = n*m + 3;
		
		for (int i = 0; i < (int)ini.size(); i++)
		{
			bfs(ini[i].F, ini[i].S);
			
			add_edge(src, ini[i].F * m + ini[i].S, 1, 0, 0);
		}
		for (int i = 0; i < (int)fim.size(); i++)
		{
			add_edge(fim[i].F * m + fim[i].S, sink, 1, 0, 0);
		}
		
		cout << mcmf(src, sink) << "\n";
	}
	
	
	return 0;
}
