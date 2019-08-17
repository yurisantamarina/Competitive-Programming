#include <bits/stdc++.h>

using namespace std;
#define F first
#define S second
#define mp make_pair
#define MAXN 501010
#define pb push_back

map<pair<int, int>, int> mapa;
vector<int> g[MAXN];
int cor[MAXN], cntA, cntB, n;
pair<int, int> vet[MAXN];


void dfs(int u, int c){
	cor[u] = c;
	if(c) cntA++;
	else cntB++;
	
	for(int v : g[u])
		if(cor[v] == -1)
			dfs(v, c^1);
}

int main(){
	scanf("%d", &n);
	int x, y;
	for (int i = 1; i <= n; i++)
	{
		scanf("%d %d", &x, &y);
		mapa[mp(x, y)] = i;
		vet[i] = mp(x, y);
	}
	
	for (int i = 1; i <= n; i++)
	{
		x = vet[i].F;
		y = vet[i].S;
		
		for(int j = x - 5; j <= x + 5; j++){
			for(int k = y - 5; k <= y + 5; k++){
				if(j == x && k == y) continue;
				if((x-j)*(x-j) + (k-y)*(k-y) <= 25 && mapa.count(mp(j, k))){
					g[i].pb(mapa[mp(j, k)]);
					g[mapa[mp(j, k)]].pb(i);
				}
			}
		}
	}
	
	memset(cor, -1, sizeof cor);
	int a = 0, b = 0;
	for (int i = 1; i <= n; i++)
	{
		if(cor[i] != -1) continue;
		cntA = 0; cntB = 0;
		dfs(i, 0);
		a += max(cntA, cntB);
		b += min(cntA, cntB);
	}
	printf("%d\n", b);
	
	
	
	return 0;
}
