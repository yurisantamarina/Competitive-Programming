#include <bits/stdc++.h>

using namespace std;
#define MAXN 401010
#define pb push_back
#define F first
#define S second

typedef pair<int, int> pii;

int seen[MAXN], d[MAXN], low[MAXN], bridge[MAXN], root, tempo = 1, ans = 0;
stack<int> p;
vector<pii> g[MAXN];
pii saida[MAXN];

void dfsTarjan(int u, int pai){
	seen[u] = 1;
	d[u] = low[u] = tempo++;
	p.push(u);
	
	for(pii pp : g[u]){
		int v = pp.F;
		if(!seen[v]){
			dfsTarjan(v, u);
			low[u] = min(low[u], low[v]);
			if(d[u] < low[v]){
				int cnt = 0;
				bridge[pp.S] = 1;
				while(!p.empty()){
					int x = p.top();
					cnt++;
					p.pop();
					if(x == v) break;
				}
				if(cnt > ans){
					ans = cnt;
					root = v;
				}
			}
		}else if(v != pai)
			low[u] = min(low[u], d[v]);
	}
}

void dfs(int u){
	seen[u] = 1;
	d[u] = tempo++;
	for(pii pp : g[u]){
		int v = pp.F;
		int id = pp.S;
		if(!seen[v]){
			dfs(v);
			if(bridge[id])
				saida[id] = {v, u};
			else
				saida[id] = {u, v};
		}else if(d[u] < d[v])
			saida[id] = {v, u};
	}
}

int main(){
	int n, m, u, v;
	scanf("%d %d", &n, &m);
	for (int i = 0; i < m; i++)
	{
		scanf("%d %d", &u, &v);
		g[u].pb({v, i});
		g[v].pb({u, i});
	}
	
	dfsTarjan(1, 1);
	int cnt = 0;
	while(!p.empty()){
		int x = p.top();
		cnt++;
		p.pop();
	}
	if(cnt > ans){
		ans = cnt;
		root = 1;
	}
	
	memset(seen, 0, sizeof seen);
	dfs(root);
	
	printf("%d\n", ans);
	for (int i = 0; i < m; i++)
		printf("%d %d\n", saida[i].F, saida[i].S);
	
	
	
	return 0;
}
