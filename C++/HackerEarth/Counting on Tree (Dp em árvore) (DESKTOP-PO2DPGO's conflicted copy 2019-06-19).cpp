#include <bits/stdc++.h>

using namespace std;
#define MAXN 50010
#define MAXK 110
#define INF 10000000000000LL
#define MOD 1000000007
#define pb push_back
typedef long long int ll;

vector<int> g[MAXN];
int val[MAXN];
ll dp[MAXN][MAXK];
ll counter[MAXK];
int n, k;

ll add(ll a, ll b){
	a%=MOD;
	b%=MOD;
	
	return (a+b)%MOD;
}

void compute(int u, int pai){//computa de quantas formas distintas consegue soma X com árvore enraizada em u
	memset(counter, 0, sizeof counter);
	//o counter nao é resetado dentro do for pois os eventos sao independentes, eu posso escolher algum filho e foda-se o resto, tem problemas que nao pode e o counter deve ser resetado a cada iteração do for, após ser copiado para a matriz da dp:
	
	/*
	1
	1*2
	1*3
	1*2*3
	1*~2
	1*~3
	1*2*~3
	1*~2*3
	1*~2*~3
	
	Nesse problema eu posso pegar separado cada filhos, tem problemas que preciso pegar todos juntos, que seria tipo:
	1*2*3
	1*2*~3
	1*~2*3
	1*~2*~3
	*/
	
	//~ Pegar todos os filhos seria de quantas formas consigo uma soma X com árvore enraizada em U de tal forma que a soma de TODOS os filhos seja X, enquanto que o problema não pede isso, não é obrigatório vc pegar todos os filhos de um nó para calcular a resposta, pode ser só alguns.
	
	counter[val[u]] = 1LL;
	dp[u][val[u]] = 1LL;
	
	for (auto v : g[u])
	{
		if(v == pai) continue;
		
		//testa todas as combinações. Se tenho x possibildiades de conseguir soma A e y possibilidades de conseguir soma B, tenho x*y possibilidades de conseguir soma A+B
		for (int sumU = 0; sumU <= k; sumU++)
		{
			for (int sumV = 0; sumV <= k; sumV++)
			{
				if(sumU + sumV > k) break;
				counter[sumU + sumV] = add(counter[sumU + sumV], dp[u][sumU] * dp[v][sumV]);
			}
			
		}
		
		for (int sum = 0; sum <= k; sum++)
		{
			dp[u][sum] = add(counter[sum], 0LL);
		}
		
		
	}
	
	
}

void solve(int u, int pai){
	
	int v;
	for (int i = 0; i < (int)g[u].size(); i++)
	{
		v = g[u][i];
		if(v == pai) continue;
		solve(v, u);
	}
	
	compute(u, pai);
}

void reset(){
	for (int i = 0; i < n; i++)
	{
		g[i].clear();
	}
	
}

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	int tc;
	cin >> tc;
	ll ans;
	int u, v;
	while (tc--)
	{
		cin >> n >> k;
		reset();
		for (int i = 0; i < n; i++)
		{
			cin >> val[i];
		}
		
		for (int i = 0; i < n-1; i++)
		{
			cin >> u >> v;
			u--; v--;
			g[u].pb(v);
			g[v].pb(u);
		}
		
		memset(dp, 0, sizeof dp);
		solve(0, 0);
		
		ans = 0LL;
		for (int i = 0; i < n; i++)
		{
			ans = add(ans, dp[i][k]);
		}
		cout << ans << "\n";
	}
	
	
	return 0;
}
