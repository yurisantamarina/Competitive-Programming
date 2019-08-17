#include <bits/stdc++.h>

using namespace std;
#define MAXN 10101
#define INF 10101010
#define F first
#define S second
#define pb push_back
typedef pair<int, int> pii;

vector<pii> g[MAXN];
int d[MAXN], low[MAXN], seen[MAXN], tempo = 1, comp[MAXN], sz[MAXN], dist[MAXN], n;
stack<int> p;

void dfs(int u, int pai){
	seen[u] = 1;
	d[u] = low[u] = tempo++;
	
	p.push(u);
	
	for(pii e : g[u]){
		int v = e.F;
		if(!seen[v]){
			dfs(v, u);
			low[u] = min(low[u], low[v]);
			
			if(d[u] < low[v]){
				while(!p.empty()){
					int x = p.top(); p.pop();
					comp[x] = v;
					if(v == x) break;
				}
			}
		}else if(v != pai)
			low[u] = min(low[u], d[v]);
	}
}

void buildCycles(){
	for(int u = 1; u <= n; u++)
		for(pii e : g[u]){
			int v = e.F;
			int w = e.S;
			if(comp[u] == comp[v])
				sz[comp[u]] += w;
		}
	
	for(int i = 1; i <= n; i++)
		sz[i] /= 2;
}

int solve(int start, int len){
	priority_queue<pii, vector<pii>, greater<pii> > pq;
	for (int i = 1; i <= n; i++)
		dist[i] = INF;
	dist[start] = 0;
	pq.push({dist[start], start});
	int ans = INF;
	
	while(!pq.empty()){
		int u = pq.top().S;
		int d = pq.top().F;
		pq.pop();
		
		if(d > dist[u]) continue;
		if(sz[comp[u]] >= len) ans = min(ans, d + sz[comp[u]]);
		
		for(pii e : g[u]){
			int v = e.F;
			int w = e.S;
			if(dist[u] + 2 * w < dist[v]){
				dist[v] = dist[u] + 2 * w;
				pq.push({dist[v], v});
			}
		}
	}
	
	return ans == INF ? -1 : ans;
}

void reset(){
	for (int i = 1; i <= n; i++)
	{
		d[i] = low[i] = seen[i] = sz[i] = comp[i] = 0;
		g[i].clear();
	}
	tempo = 1;
	while(!p.empty()) p.pop();
}

int main(){
	int m, u, v, w, q, start, len;
	
	while(scanf("%d %d", &n, &m) != EOF){
		reset();
		for (int i = 0; i < m; i++)
		{
			scanf("%d %d %d", &u, &v, &w);
			g[u].pb({v, w});
			g[v].pb({u, w});
		}
		
		for(int i = 1; i <= n; i++)
			if(!seen[i])
				dfs(i, i);
		
		int a = p.top();
		while(!p.empty()){
			int x = p.top(); p.pop();
			comp[x] = a;
		}
		buildCycles();
		
		scanf("%d", &q);
		while (q--)
		{
			scanf("%d %d", &start, &len);
			printf("%d\n", solve(start, len));
		}
	}
	
	return 0;
}
