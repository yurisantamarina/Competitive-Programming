#include <bits/stdc++.h>

using namespace std;
#define MAXN 301010
#define F first
#define S second
#define pb push_back
typedef pair<int, int> pii;

int d[MAXN], low[MAXN], seen[MAXN], tempo = 1, comp[MAXN], n, m, src, target;
vector<pii> g[MAXN], tr[MAXN];
bool has[MAXN];
stack<int> p;

void dfs(int u, int pai){
	seen[u] = 1;
	d[u] = low[u] = tempo++;
	
	p.push(u);
	
	for(pii pp : g[u]){
		int v = pp.F;
		if(!seen[v]){
			dfs(v, u);
			low[u] = min(low[u], low[v]);
			
			if(d[u] < low[v]){
				while(!p.empty()){
					int x = p.top(); p.pop();
					comp[x] = v;
					if(x == v) break;
				}
			}
			
		}else if(v != pai)
			low[u] = min(low[u], d[v]);
	}
}

bool dfs2(int u, int pai, bool flag){
	if(u == target) return flag;
	
	bool ans = false;
	for(pii pp : tr[u]){
		int v = pp.F;
		if(v != pai)
			ans |= dfs2(v, u, flag || pp.S || has[v]);
	}
	
	return ans;
}

void build(){
	for (int u = 1; u <= n; u++)
	{
		for(pii pp : g[u]){
			int v = pp.F;
			int op = pp.S;
			if(comp[u] != comp[v]){
				tr[comp[u]].pb({comp[v], op});
			}else{
				has[comp[u]] |= op;
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
		g[u].pb({v, op});
		g[v].pb({u, op});
	}
	
	dfs(1, 1);
	
	while(!p.empty()){
		int x = p.top(); p.pop();
		comp[x] = 1;
	}
	
	build();
	
	scanf("%d %d", &src, &target);
	src = comp[src];
	target = comp[target];
	bool ans = dfs2(src, src, has[src]);
	
	if(ans) printf("YES\n");
	else printf("NO\n");
	
	
	return 0;
}
