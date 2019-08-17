#include <bits/stdc++.h>

using namespace std;
#define MAXN 101010
#define pb push_back
typedef long long int ll;
vector<int> g[MAXN];
int d[MAXN], low[MAXN], seen[MAXN], val[MAXN], tempo = 1, n, m;
ll valor, ways, MOD = 1000000007;
stack<int> p;

void dfs(int u){
	seen[u] = 1;
	d[u] = low[u] = tempo++;
	p.push(u);
	
	for(int v : g[u]){
		if(!seen[v]){
			dfs(v);
			low[u] = min(low[u], low[v]);
		}else low[u] = min(low[u], d[v]);
	}
	
	if(low[u] < d[u]) return;
	
	int cnt = 0, mn = 1e9 + 10;
	while(!p.empty()){
		int x = p.top(); p.pop();
		
		if(val[x] < mn){
			mn = val[x];
			cnt = 1;
		}else if(val[x] == mn)
			cnt++;
		
		d[x] = 1e9;
		if(u == x) break;
	}
	
	valor += mn;
	ways = (ways * cnt) % MOD;
}

int main(){
	scanf("%d", &n);
	for(int i = 1; i <= n; i++)
		scanf("%d", &val[i]);
	
	scanf("%d", &m);
	
	int u, v;
	for (int i = 0; i < m; i++)
	{
		scanf("%d %d", &u, &v);
		g[u].pb(v);
	}
	
	
	valor = 0;
	ways = 1;
	for(int i = 1; i <= n; i++)
		if(!seen[i])
			dfs(i);
	
	printf("%lld %lld\n", valor, ways);
	return 0;
}
