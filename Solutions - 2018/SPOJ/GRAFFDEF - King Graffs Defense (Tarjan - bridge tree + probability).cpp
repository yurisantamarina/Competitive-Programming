#include <bits/stdc++.h>

using namespace std;
#define MAXN 101010
#define F first
#define S second
#define mp make_pair
#define pb push_back
typedef long long int ll;

int n, d[MAXN], low[MAXN], seen[MAXN], tempo = 1;
ll possible = 0;
stack<int> p;
vector<int> g[MAXN];

void dfs(int u, int pai){
	seen[u] = 1;
	d[u] = low[u] = tempo++;
	p.push(u);
	
	for(int v : g[u]){
		if(!seen[v]){
			dfs(v, u);
			low[u] = min(low[u], low[v]);
			
			if(d[u] < low[v]){
				int cnt = 0;
				while(!p.empty()){
					int x = p.top(); p.pop();
					cnt++;
					if(x == v) break;
				}
				possible += (ll)cnt * (n - cnt);
			}
		}else if(v != pai)
			low[u] = min(low[u], d[v]);
	}
}

double solve(){
	dfs(1, 1);
	int cnt = 0;
	while(!p.empty()){
		int x = p.top(); p.pop();
		cnt++;
	}
	possible += (ll)cnt * (n - cnt);
	possible /= 2;
	ll tot = ((ll)n * (n - 1)) / 2;
	return (possible * 1.0) / tot;
}

int main(){
	int m, u, v;
	scanf("%d %d", &n, &m);
	for (int i = 0; i < m; i++)
	{
		scanf("%d %d", &u, &v);
		g[u].pb(v);
		g[v].pb(u);
	}
	
	printf("%.5lf\n", solve());
	
	
	return 0;
}
