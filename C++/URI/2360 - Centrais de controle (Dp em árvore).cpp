//~ chama somando para os irmaos pois isso testa todas as possibilidades, igual a um knapsack (pega ou nao pega).
//~ multiplica a chamada do filho direto com o irmao pois são independentes as formas de colorir, com isso, para cada forma de colorir a sub-arvore do filho direto, eu posso colorir de todas as formas possíveis o irmao

#include <bits/stdc++.h>

using namespace std;
typedef long long int ll;
const ll MOD = 1000000007LL;
#define MAXN 100100
#define pb push_back

ll dp[MAXN][5][2];
vector<int> g[MAXN];
int down[MAXN];
int nxt[MAXN];
int n;

bool folha(int u){
	return down[u] == -1;
}

bool lst(int u){
	return nxt[u] == -1;
}

void dfs(int u, int pai){
	
	int v;
	int aux = -1;
	for (int i = 0; i < (int)g[u].size(); i++)
	{
		v = g[u][i];
		if(v == pai) continue;
		dfs(v, u);
		if(aux != -1){
			nxt[aux] = v;
		}
		aux = v;
		
		if(down[u] == -1) down[u] = v;
	}
}

ll solve(int u, int pai, int ok){
	if(u == -1) return 1LL;
	if(dp[u][pai][ok]!=-1) return dp[u][pai][ok];
	ll ans = 0LL;
	
	if(folha(u)){
		if(pai == 0){//não colorido e não OK
			ans = solve(nxt[u], pai, true);
		}else if(pai == 1){//colorido
			ans = (solve(nxt[u], pai, ok) + solve(nxt[u], pai, true))%MOD;
		}else{//não colorido mas OK
			ans = solve(nxt[u], pai, true);
		}
	}else{
		if(pai == 0){//não colorido e não OK
			if(lst(u)){//se o vértice for o ultimo da lista do pai
				if(ok){
					ans = (solve(down[u], 1, false) + solve(down[u], 0, false))%MOD;
				}else{
					ans = solve(down[u], 1, false);
				}
			}else{
				ans = (solve(down[u], 1, false) * solve(nxt[u], pai, true))%MOD;
				ans = ans + (solve(down[u], 0, false) * solve(nxt[u], pai, ok))%MOD;
			}
		}else if(pai == 1){//colorido
			ans = (solve(down[u], 1, false) * solve(nxt[u], pai, true))%MOD;
			ans = ans + (solve(down[u], 2, false) * solve(nxt[u], pai, ok))%MOD;
		}else{//não colorido mas OK
			ans = (solve(down[u], 1, false) * solve(nxt[u], pai, true))%MOD;
			ans = ans + (solve(down[u], 0, false) * solve(nxt[u], pai, ok))%MOD;
		}
	}
	
	return dp[u][pai][ok] = ans%MOD;
}

void reset(){
	for (int i = 0; i < n; i++)
	{
		g[i].clear();
	}
	
}

int main(){
	
	int u, v;
	
	while (cin >> n)
	{
		reset();
		for (int i = 0; i < n-1; i++)
		{
			cin >> u >> v;
			u--;
			v--;
			g[u].pb(v);
			g[v].pb(u);
		}
		if(n==1){
			cout << "1\n";
			continue;
		}
		memset(down, -1, sizeof down);
		memset(nxt, -1, sizeof nxt);
		dfs(0, 0);
		memset(dp, -1, sizeof dp);
		cout << (solve(down[0], 1, false) + solve(down[0], 0, false))%MOD << "\n";
	}
	
	
	return 0;
}
