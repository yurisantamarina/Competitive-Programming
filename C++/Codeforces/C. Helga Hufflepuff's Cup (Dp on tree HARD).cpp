#include <bits/stdc++.h>

using namespace std;
typedef long long int ll;
#define pb push_back
#define mp make_pair
#define F first
#define S second
#define MAXN 100020
#define inf 1e9
#define MOD 1000000007

/*
dp[u][op][usou]:
De quantas formas eu consigo colorir a subárvore do U, tendo usado "usou" cores do tipo k e o vértice atual está com o estado op:
op = 0: colorido com valor menor que k
op = 1: colorido com valor igual k
op = 2: colorido com valor maior que k

Se eu tenho qtd formas de colorir a subárvore do u com cor do u > k e tendo usado i cores do tipo k, e ele tem dois vizinhos v1 e v2, a expressao que calcula isso é a seguinte:

qtd * (v1<)*(v2<) + qtd*(v1<)*(v2>) + qtd*(v1>)*(v2<) + qtd*(v1>)*(v2<)
Reescrevendo..
[qtd * (v1<) + qtd * (v1>)] * ((v2<) + (v2>))
[qtd * ((v1<) + (v1>))] * ((v2<) + (v2>))
Com isso eu posso calcular separado para cada vértice em uma matriz temporária e depois copiar para a matriz dp para que os outros irmaos do v possam usar.
*/

vector<int> g[MAXN];
ll dp[MAXN][3][12];
int n, k, x, m;

ll add(ll a, ll b){
	a%=MOD;
	b%=MOD;
	return (a+b)%MOD;
}

int solve(int u, int pai){
	dp[u][0][0] = k-1;//tenho k-1 possibilidades de colorir o vertice u com cor < k
	dp[u][1][1] = 1;//apenas 1 possibilidade de colorir o vertice u com cor = k
	dp[u][2][0] = m-k;//tenho m-k possibilidades de colorir o vertice u com cor > k
	
	ll tmp[3][12];
	memset(tmp, 0, sizeof tmp);
	
	for(int v : g[u]){
		if(v == pai) continue;
		
		solve(v, u);
		
		//aqui eu testo todas as combinações (usando i na dp do u e j na dp do v)
		for (int i = 0; i <= x; i++)
		{
			for (int j = 0; j <= x; j++)
			{
				if(i+j > x) break;
				
				//botando cor < k no vertice u: v pode ser menor, igual ou maior
				tmp[0][i+j] += dp[u][0][i] * (dp[v][0][j] + dp[v][1][j] + dp[v][2][j]);
				
				//botando cor = k no vertice u: v só pode ser menor
				tmp[1][i+j] += dp[u][1][i] * (dp[v][0][j]);
				
				//botando cor > k no vertice u: v só pode ser menor ou maior
				tmp[2][i+j] += dp[u][2][i] * (dp[v][0][j] + dp[v][2][j]);
				
				tmp[0][i+j]%=MOD;
				tmp[1][i+j]%=MOD;
				tmp[2][i+j]%=MOD;
			}
		}
		
		
		for (int i = 0; i <= x; i++)
		{
			dp[u][0][i] = tmp[0][i];
			dp[u][1][i] = tmp[1][i];
			dp[u][2][i] = tmp[2][i];
			tmp[0][i] = 0;
			tmp[1][i] = 0;
			tmp[2][i] = 0;
		}
		
	}
	
}
	

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cin >> n >> m;
	int u, v;
	for (int i = 0; i < n-1; i++)
	{
		cin >> u >> v;
		u--; v--;
		g[u].pb(v);
		g[v].pb(u);
	}
	
	cin >> k >> x;
	solve(0, 0);
	
	ll ans = 0LL;
	for (int i = 0; i <= x; i++)
	{
		ans = add(ans, dp[0][0][i]);
		ans = add(ans, dp[0][1][i]);
		ans = add(ans, dp[0][2][i]);
	}
	cout << ans << "\n";
	
	
	return 0;
}

