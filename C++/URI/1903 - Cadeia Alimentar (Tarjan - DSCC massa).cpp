#include <bits/stdc++.h>

using namespace std;
#define MAXN 101010

vector<int> g[MAXN], dag[MAXN], topo;
int n, m, d[MAXN], low[MAXN], seen[MAXN], in[MAXN], comp[MAXN], tempo = 1, sccCounter = 1, pos[MAXN], visitados;
map<pair<int, int>, int> mapa;
stack<int> p;

void dfsTarjan(int u){
	seen[u] = 1;
	d[u] = low[u] = tempo++;
	p.push(u);
	
	for(int v : g[u]){
		if(!seen[v]){
			dfsTarjan(v);
			low[u] = min(low[u], low[v]);
		}else low[u] = min(low[u], d[v]);
	}
	
	if(low[u] < d[u]) return;
	
	while(!p.empty()){
		int x = p.top(); p.pop();
		comp[x] = sccCounter;
		d[x] = 1e9;
		if(u == x) break;
	}
	
	sccCounter++;
}

void buildDSCC(){
	for(int u = 1; u <= n; u++)
		for(int v : g[u])
			if(comp[u] != comp[v] && !mapa.count({comp[u], comp[v]})){
				dag[comp[u]].push_back(comp[v]);
				in[comp[v]]++;
				mapa[{comp[u], comp[v]}];
			}
}


void dfsTopo(int u){
	for(int v : dag[u])
		dfsTopo(v);
	topo.push_back(u);
}

void dfsAns(int u){
	visitados++;
	for(int v : dag[u]){
		dfsAns(v);
		break;
	}
}

int main(){
	int u, v;
	scanf("%d %d", &n, &m);
	for (int i = 0; i < m; i++)
	{
		scanf("%d %d", &u, &v);
		g[u].push_back(v);
	}
	
	for(int i = 1; i <= n; i++)
		if(!seen[i])
			dfsTarjan(i);
	
	buildDSCC();
	
	int src = 0;
	for(int i = 1; i < sccCounter; i++)
		if(in[i] == 0){
			src++;
			u = i;
		}
	
	if(src > 1){
		printf("Nao Bolada\n");
		return 0;
	}
	
	dfsTopo(u);
	reverse(topo.begin(), topo.end());
	for (int i = 0; i < (int)topo.size(); i++)
		pos[topo[i]] = i;
	
	for(int i = 1; i <= sccCounter; i++)
		sort(dag[i].begin(), dag[i].end(), [](int a, int b){
															return pos[a] < pos[b];});
	dfsAns(u);
	if(visitados == sccCounter - 1){
		printf("Bolada\n");
	}else printf("Nao Bolada\n");
	
	return 0;
}
