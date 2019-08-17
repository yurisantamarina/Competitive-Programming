#include <bits/stdc++.h>

using namespace std;
#define MAXN 510
#define INF 10101010

int n, m, k, grid[MAXN][MAXN], cost[MAXN][MAXN], dp[MAXN][MAXN];

int get(int dia, int l, int r){
	if(l > r) return 0;
	return grid[dia][r] - grid[dia][l - 1];
}

void preprocess(){
	int c;
	
	for (int dia = 1; dia <= n; dia++){
		
		for (c = 0; c <= k; c++)
			cost[dia][c] = c < grid[dia][m] ? INF : 0;
			
		for (int l = 1; l <= m; l++)
			for (int r = l; r <= m; r++)
			{
				c = get(dia, 1, l - 1) + get(dia, r + 1, m);
				cost[dia][c] = min(cost[dia][c], r - l + 1);
			}
			
	}
	
}

int main(){
	scanf("%d %d %d", &n, &m, &k);
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++)
		{
			scanf("%1d", &grid[i][j]);
			grid[i][j] += grid[i][j - 1];
		}

	preprocess();
	
	for (int i = 0; i <= k; i++)
		dp[1][i] = cost[1][i];
	
	for (int dia = 2; dia <= n; dia++)
		for (int faltei = 0; faltei <= k; faltei++)
		{
			dp[dia][faltei] = INF;
			for (int i = 0; i <= faltei; i++)
				dp[dia][faltei] = min(dp[dia][faltei], dp[dia - 1][i] + cost[dia][faltei - i]);
		}
	
	printf("%d\n", dp[n][k]);
	
	
	return 0;
}
