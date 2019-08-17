#include <bits/stdc++.h>

using namespace std;
#define MAXN 101010
#define F first
#define S second
#define pb push_back

vector<int> g[MAXN], bid[MAXN];
int d[MAXN], low[MAXN], seen[MAXN], n, m, tempo, sccCounter, comp[MAXN];
stack<int> p;
map<pair<int, int>, int> edges;
vector<pair<int, int> > bridges; 

void dfsSCC(int u){
	seen[u] = 1;
	d[u] = low[u] = tempo++;
	p.push(u);
	
	for(int v : g[u]){
		if(!seen[v]){
			dfsSCC(v);
			low[u] = min(low[u], low[v]);
		}else low[u] = min(low[u], d[v]);
	}
	
	if(low[u] < d[u]) return;
	
	while(!p.empty()){
		int x = p.top(); p.pop();
		d[x] = 1e9;
		comp[x] = sccCounter;
		if(x == u) break;
 	}
	
	sccCounter++;
}

void dfsBridges(int u, int pai){
	seen[u] = 1;
	d[u] = low[u] = tempo++;
	p.push(u);
	
	for(int v : bid[u]){
		if(!seen[v]){
			dfsBridges(v, u);
			low[u] = min(low[u], low[v]);
			
			if(d[u] < low[v])
				bridges.pb({u, v});

		}else if(v != pai || edges[{min(u, v), max(u, v)}] > 1)
			low[u] = min(low[u], d[v]);
	}
}

void buildDSCC(){
	memset(seen, 0, sizeof seen);
	for(int i = 1; i <= n; i++)
		if(!seen[i])
			dfsSCC(i);
	
	if(sccCounter == 1) return;
	
	for(int u = 1; u <= n; u++){
		for(int v : g[u]){
			if(comp[u] != comp[v]){
				bid[comp[u]].pb(comp[v]);
				bid[comp[v]].pb(comp[u]);
				edges[{min(comp[u], comp[v]), max(comp[u], comp[v])}]++;
			}
		}
	}
}

void dfsNormal(int u){
	seen[u] = 1;
	for(int v : bid[u])
		if(!seen[v])
			dfsNormal(v);
}

bool conexo(){
	memset(seen, 0, sizeof seen);
	int cnt = 0;
	for(int i = 0; i < sccCounter; i++)
		if(!seen[i]){
			cnt++;
			dfsNormal(i);
		}
	
	return cnt == 1;
}

void reset(){
	for (int i = 0; i <= n; i++)
	{
		g[i].clear();
		bid[i].clear();
		seen[i] = d[i] = low[i] = 0;
	}
	tempo = 1;
	sccCounter = 0;
	edges.clear();
	bridges.clear();
	while(!p.empty()) p.pop();
}

bool temPonte(){
	memset(seen, 0, sizeof seen);
	tempo = 1;
	for(int i = 0; i < sccCounter; i++)
		if(!seen[i])
			dfsBridges(i, i);
	
	return (int)bridges.size() > 0;
}

int main(){
	int u, v, op;
	while (scanf("%d %d", &n, &m) != EOF)
	{
		reset();
		for (int i = 0; i < m; i++)
		{
			scanf("%d %d %d", &u, &v, &op);
			
			if(i == 0) continue;
			
			if(op == 1){
				g[u].pb(v);
			}else{
				g[u].pb(v);
				g[v].pb(u);
			}
		}
		
		buildDSCC();
		if(sccCounter == 1) printf("-\n");
		else if(!conexo()) printf("*\n");
		else if(temPonte()) printf("2\n");
		else printf("1\n");
	}
	
	
	
	return 0;
}
