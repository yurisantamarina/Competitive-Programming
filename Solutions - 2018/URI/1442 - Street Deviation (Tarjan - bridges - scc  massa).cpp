#include <bits/stdc++.h>

using namespace std;
#define MAXN 101010
#define F first
#define S second
#define pb push_back

vector<int> g[MAXN], bid[MAXN];
int d[MAXN], low[MAXN], seen[MAXN], n, m, tempo, sccCounter;
stack<int> p;
map<pair<int, int>, int> mapa;
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
		if(x == u) break;
 	}
	
	sccCounter++;
}

void dfsNormal(int u){
	seen[u] = 1;
	for(int v : bid[u])
		if(!seen[v])
			dfsNormal(v);
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

		}else if(v != pai)
			low[u] = min(low[u], d[v]);
	}
}

bool stronglyConnected(){
	memset(seen, 0, sizeof seen);
	tempo = 1;
	sccCounter = 0;
	for(int i = 1; i <= n; i++)
		if(!seen[i])
			dfsSCC(i);
	return sccCounter == 1;
}

bool connected(){
	memset(seen, 0, sizeof seen);
	tempo = 1;
	int cnt = 0;
	for(int i = 1; cnt <= 1 && i <= n; i++)
		if(!seen[i]){
			cnt++;
			dfsNormal(i);
		}
	return cnt == 1;
}

bool pontesBidirecionais(){
	memset(seen, 0, sizeof seen);
	tempo = 1;
	for(int i = 1; i <= n; i++)
		if(!seen[i])
			dfsBridges(i, i);
	
	for(pair<int, int> pp : bridges){
		int u = pp.F;
		int v = pp.S;
		
		if(mapa.count({u, v}) && mapa.count({v, u})) continue;
		return false;
	}
	
	return true;
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
	mapa.clear();
	bridges.clear();
	while(!p.empty()) p.pop();
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
				mapa[{u, v}] = 1;
			}else{
				g[u].pb(v);
				g[v].pb(u);
				mapa[{u, v}] = 2;
				mapa[{v, u}] = 2;
			}
			
			bid[u].pb(v);
			bid[v].pb(u);
		}
		
		if(stronglyConnected())
			printf("-\n");
		else if(!connected())
			printf("*\n");
		else if(pontesBidirecionais())
			printf("1\n");
		else
			printf("2\n");
	}
	
	
	
	return 0;
}
