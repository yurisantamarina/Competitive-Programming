//~ http://codeforces.com/group/kZPk3ZTzR5/contest/101447/attachments

#include <bits/stdc++.h>

using namespace std;
#define MAXN 101010
#define pb push_back

vector<int> g[MAXN], dag[MAXN];
int d[MAXN], low[MAXN], comp[MAXN], val[MAXN], seen[MAXN], dp[MAXN], sccCounter = 1, tempo = 1, n, m;
stack<int> p;
map<pair<int, int>, int> mapa;

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
		val[sccCounter]++;
		if(x == u) break;
	}
	
	sccCounter++;
}

int dfs(int u){
	if(seen[u]) return dp[u];
	seen[u] = 1;
	
	dp[u] = val[u];
	
	for(int v : dag[u])
		dp[u] += dfs(v);
	
	return dp[u];
}

void buildDSCC(){
	for(int u = 1 ; u <= n; u++){
		for(int v : g[u]){
			if(comp[u] != comp[v] && !mapa.count({comp[u], comp[v]})){
				dag[comp[u]].pb(comp[v]);
				mapa[{comp[u], comp[v]}];
			}
		}
	}
}

int main(){
	int u, v, op;
	scanf("%d %d", &n, &m);
	for (int i = 0; i < m; i++)
	{
		scanf("%d %d %d", &u, &v, &op);
		if(u == v) continue;
		g[u].pb(v);
		if(op == 2)
			g[v].pb(u);
	}
	
	for(int i = 1; i <= n; i++)
		if(!seen[i])
			dfsTarjan(i);
	
	buildDSCC();
	
	int ans = 0;
	memset(seen, 0, sizeof seen);
	for(int i = 1; i < sccCounter; i++){
		dp[i] = dfs(i);
		if(dp[i] > dp[ans])
			ans = i;
	}
	
	for(int i = 1; i < sccCounter; i++)
		if(comp[i] == ans){
			ans = i;
			break;
		}
	printf("%d\n", ans);
	
	return 0;
}
