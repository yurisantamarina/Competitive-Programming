#include <bits/stdc++.h>

using namespace std;
#define MAXN 1010
#define INF 1e9
#define F first
#define S second
#define pb push_back
#define mp make_pair
typedef long long int ll;

int dp[MAXN][2];
char memo[MAXN][2];
int preto[MAXN];
int branco[MAXN];
int n, m, mn, mx;
char grid[MAXN][MAXN];

int solve(int pos, int cor){
	if(pos >= m) return 0;
	if(memo[pos][cor]) return dp[pos][cor];
	memo[pos][cor] = 1;
	
	int ans = INF, custo = 0;
	for (int i = pos, cnt = 1; cnt <= mx && i < m; i++, cnt++)
	{
		if(cor == 0) custo += preto[i];
		else custo += branco[i];
		
		if(cnt >= mn && cnt <= mx){
			ans = min(ans, custo + solve(i+1, cor^1));
		}
	}
	
	return dp[pos][cor] = ans;
}

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cin >> n >> m >> mn >> mx;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			cin >> grid[i][j];
			if(grid[i][j] == '#') preto[j]++;
			else branco[j]++;
		}
	}
	cout << min(solve(0, 0), solve(0, 1)) << "\n";
	
	
	return 0;
}


//BOTTOM UP
//~ menor custo para deixar certo o prefixo 'pos' sendo que o bloco está com 'cor' e a partir de pos+1 será com 'cor^1': preciso achar algum indice i para trás com cor^1 para começar a construir meu bloco a partir de i com 'cor' e fechar o bloco que termina em i-1 com 'cor^1';

#include <bits/stdc++.h>

using namespace std;
#define MAXN 1010
#define INF 1e9
#define F first
#define S second
#define pb push_back
#define mp make_pair
typedef long long int ll;

int dp[MAXN][2];
char memo[MAXN][2];
int preto[MAXN];
int branco[MAXN];
int n, m, mn, mx;
char grid[MAXN][MAXN];

int main(){
	//~ ios_base::sync_with_stdio(0);
	//~ cin.tie(0);
	cin >> n >> m >> mn >> mx;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			cin >> grid[i][j];
			if(grid[i][j] == '#') preto[j+1]++;
			else branco[j+1]++;
		}
	}
	
	memset(dp[0], 0, sizeof dp[0]);
	int custo;
	for (int pos = 1; pos <= m; pos++)
	{
		for (int cor = 0; cor < 2; cor++)
		{
			dp[pos][cor] = INF;
			custo = 0;
			for (int i = pos, cnt = 1; cnt <= mx && i >= 1; i--, cnt++)
			{
				if(cor == 0) custo += preto[i];
				else custo += branco[i];
				
				if(cnt >= mn && cnt <= mx){
					dp[pos][cor] = min(dp[pos][cor], custo + dp[i-1][cor^1]);
				}
			}
			
		}
	}
	
	
	cout << min(dp[m][0], dp[m][1]) << "\n";
	
	
	return 0;
}

