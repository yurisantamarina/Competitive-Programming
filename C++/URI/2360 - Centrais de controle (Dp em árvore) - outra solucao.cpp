#include <bits/stdc++.h>

using namespace std;
typedef long long int ll;
#define pb push_back
#define mp make_pair
#define F first
#define S second
#define MAXN 1010
#define inf 1e9
#define MOD 1000000007
#define gc getchar_unlocked // ou usar só getchar

void scanint(int &x)
{
    register int c = gc();
    x = 0;
    for(;(c<48 || c>57);c = gc());
    for(;c>47 && c<58;c = gc()) {x = (x<<1) + (x<<3) + c - 48;}
}


vector<int> g[MAXN];
ll dp[MAXN][3];
int n, k;

//~ dp[u][i]: de quantas formas eu consigo colorir a subárvore do vértice u, tal que o vértice u está com o estado i:
//~ i = 0: não está colorido e pelo menos um dos filhos está colorido.
//~ i = 1: não está colorido e nenhum dos filhos está colorido.
//~ i = 2: está colorido

//~ - Para calcular a dp[u][0] (não colorindo vértice u e deixando a subárvore ok), eu preciso ter pelos menos um filho colorido, então preciso considerar a dp[v][0] e dp[v][2], mas tem a possibilidade de todos os vértices não estarem coloridos, e isso nao pode, entao tenho de descontar isso, que é a variável "mult", representando a quantidade de formas dada por dp[u][0] (no inicio = 1) * dp[v1][0] * dp[v2][0] * ... * (dp[vn][0])
//~ Suponha a árvore 1-2, 1-3 e que eu esteja calculando a dp[1][0], eu tenho as possibilidades:
//~ Não colore 1 * colore 2 * colore 3         (N1 * C2 * C3)
//~ Não colore 1 * colore 2 * nao colore 3     (N1 * C2 * N3)
//~ Não colore 1 * nao colore 2 * colore 3     (N1 * N2 * C3) 
//~ Não colore 1 * nao colore 2 * nao colore 3 (N1 * N2 * N3)

//~ Reescrevendo a fórumula:
//~ [N1 * (C2 + N2)] * (C3 + N3)

//~ Só que a última possibilidade (N1 * N2 * N3) não é valida para dp[u][0], pois eu estaria não colorindo o u, e não colorindo nenhum filho, logo o u não estaria ok. Sabendo disso, preciso usar a fórmula: [N1 * (C2 + N2)] * (C3 + N3) - (N1 * N2 * N3). Como N1 (dp[u][0]) é sempre 1 no início (para vértices não folha), a fórmula fica: [N1 * (C2 + N2)] * (C3 + N3) - (N2 * N3)

//~ Para calcular a dp[u][1] (não colorindo vértice u e deixando a subárvore não ok), eu preciso que nenhum dos filhos seja colorido, mas eu não posso considerar aqueles que nao estao coloridos e nao ok (opcao 1), pois já não estao coloridos e nem ok, e o pai também nao vai ser colorido, o que resultaria em respostas inválidas, por isso, só posso considerar a dp[v][0].

//~ Para calcular a dp[u][2] (colorindo vértice u), eu posso considerar todas as possibilidades, pois a árvore estará ok.


void reset(){
	for (int i = 0; i < n; i++)
	{
		g[i].clear();
	}
}

bool folha(int u){
	return (int)g[u].size() == 1 && u!=0;
}

void dfs(int u, int pai){
	ll tmp[3];
	memset(tmp, 0, sizeof tmp);
	if(folha(u)){
		dp[u][0] = 0;
		dp[u][1] = 1;
		dp[u][2] = 1;
		return;
	}else{
		dp[u][0] = 1;//apenas para não zerar a conta
		dp[u][1] = 1;
		dp[u][2] = 1;
	}
	
	ll mult = 1;
	for(int v : g[u]){
		if(v==pai) continue;
		dfs(v, u);
		
		mult *= dp[v][0];
		mult %= MOD;
		
		//nao colorido e ok
		tmp[0] += dp[u][0] * (dp[v][0] + dp[v][2]);
		
		//nao colorido e nao ok
		tmp[1] += dp[u][1] * (dp[v][0]);
		
		//colorido
		tmp[2] += dp[u][2] * (dp[v][0] + dp[v][1] + dp[v][2]);
		
		tmp[0] %= MOD;
		tmp[1] %= MOD;
		tmp[2] %= MOD;
		
		for (int i = 0; i < 3; i++)
		{
			dp[u][i] = tmp[i];
			tmp[i] = 0;
		}
		
	}
	dp[u][0] = dp[u][0] + MOD + MOD - mult;//aqui eu tiro a possibilidade de todos os filhos nao estarem coloridos
	dp[u][0] %= MOD;
	
}

int main(){
	
	int tc, u, v;
	while (scanf("%d", &n)!=EOF)
	{
		reset();
		for (int i = 0; i < n-1; i++)
		{
			scanint(u);
			scanint(v);
			u--; v--;
			g[u].pb(v);
			g[v].pb(u);
		}
		if(n==1){
			puts("1");
			continue;
		}
		memset(dp, 0, sizeof dp);
		dfs(0, 0);
		printf("%lld\n", (dp[0][0] + dp[0][2])%MOD);
	}
	
	
	return 0;
}

