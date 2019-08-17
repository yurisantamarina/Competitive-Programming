#include <bits/stdc++.h>

using namespace std;
#define MAXN 201010
#define pb push_back
#define mp make_pair
#define F first
#define S second

typedef pair<int, int> pii;
int componente[MAXN], valorComp[MAXN], seen[MAXN], valor[MAXN];
int sz[MAXN], low[MAXN], d[MAXN], tempo, root, tot = 0, ans[MAXN];
vector<int> g[MAXN];

void dfsCalc(int u, int counter){
	valorComp[counter] += valor[u];
	componente[u] = counter;
	seen[u] = 1;
	for(int v : g[u])
		if(!seen[v])
			dfsCalc(v, counter);
}

void dfs(int u, int pai){
	seen[u] = 1;
	int valorComponenteAtual = valorComp[componente[u]];
	
	int cp = tot;
	if(valorComponenteAtual > 0) cp -= valorComponenteAtual;
	
	bool any = false;
	int nf = 0, junto = 0, isolado = 0;
	d[u] = low[u] = tempo++;
	sz[u] = valor[u];
	for(int v : g[u]){
		
		if(!seen[v]){
			dfs(v, u);
			sz[u] += sz[v];
			low[u] = min(low[u], low[v]);
			nf++;
			if(d[u] <= low[v]){
				any = true;
				if(sz[v] > 0)
					isolado += sz[v];
			}else{
				junto += sz[v];
			}
			
			
		}else{
			if(v != pai){
				low[u] = min(low[u], d[v]);
			}
		}
		
	}
	
	junto += (valorComponenteAtual - sz[u]);
	
	if(root == u && nf >= 2){
		ans[u] = cp;
		ans[u] += isolado;
		
	}else if(root != u && any){
		ans[u] = cp;
		ans[u] += isolado;
		if(junto > 0)
			ans[u] += junto;
		
	}else{
		if(valorComponenteAtual - valor[u] > 0)
			ans[u] = cp + valorComponenteAtual - valor[u];
		else
			ans[u] = cp;
	}
	
	
	
}

int main(){
	int n, m, u, v;
	scanf("%d %d", &n, &m);
	for (int i = 1; i <= n; i++)
		scanf("%d", &valor[i]);
	
	for (int i = 0; i < m; i++)
	{
		scanf("%d %d", &u, &v);
		g[u].pb(v);
		g[v].pb(u);
	}
	
	int cnt = 0;
	for (int i = 1; i <= n; i++)
		if(!seen[i]){
			dfsCalc(i, cnt);
			if(valorComp[cnt] > 0)
				tot += valorComp[cnt];
			cnt++;
		}
	
	memset(seen, 0, sizeof seen);
	tempo = 1;
	
	for(int i = 1; i <= n; i++)
		if(!seen[i]){
			root = i;
			dfs(i, i);
		}
		
	for(int i = 1; i <= n; i++){
		if(i > 1) printf(" ");
		printf("%d", ans[i]);
	}
	printf("\n");
	
	return 0;
}
