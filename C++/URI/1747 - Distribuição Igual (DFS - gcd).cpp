#include <bits/stdc++.h>

using namespace std;
#define MAXN 10101

set<int> memo[MAXN];
vector<int> g[MAXN];
int f[MAXN * 20], ans = 0, val[MAXN];

void dfs(int u, int gc){
	f[gc]++;
	if(f[gc] == 1) ans++;// se a frequencia do cara é 1 eu achei um novo gcd
	if(gc == 1 || memo[u].count(gc)) return;// se a passei por esse cara com esse gcd, nao tem motivo pra continuar
	memo[u].insert(gc);
	
	for(int v : g[u])
		dfs(v, __gcd(gc, val[v]));//chama dfs botando esse cara
}

int main(){
	int n, m, u, v;
	scanf("%d %d", &n, &m);
	for (int i = 1; i <= n; i++)
		scanf("%d", &val[i]);
	for (int i = 0; i < m; i++)
	{
		scanf("%d %d", &u, &v);
		g[u].push_back(v);
		g[v].push_back(u);
	}
	
	for (int i = 1; i <= n; i++)
	{
		dfs(i, val[i]);//comeca pegando o cara
		dfs(i, 0);//comeca nao pegando o cara
	}
	
	printf("%d\n", ans-1);// ans - 1 pq eu conto o 0
	
	return 0;
}
