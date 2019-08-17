#include <bits/stdc++.h>

//~ tempo sem otimizar: 0.460
//~ tempo com otimização: 0.090

using namespace std;
#define INF 1e9
#define MAXN 260

int dp[MAXN][MAXN];
int opt[MAXN][MAXN];
int f[MAXN];
int sum[MAXN];

int main(){
	int n;
	while (cin >> n)
	{
		for (int i = 1; i <= n; i++)
		{
			cin >> f[i];
			sum[i] = sum[i-1] + f[i];
		}
		memset(dp, 0, sizeof dp);
		
		int r;
		for (int sz = 1; sz <= n; sz++)
		{
			for (int l = 1; l <= n; l++)
			{
				r = l + sz - 1;
				if(r > n) break;
				if(sz == 1){
					dp[l][r] = 0;
					opt[l][r] = l;
					continue;
				}
				
				int ml = opt[l][r-1];
				int mr = opt[l+1][r];
				dp[l][r] = INF;
				for (int k = ml; k <= mr; k++)
				{
					if(dp[l][k-1] + dp[k+1][r] + sum[r] - sum[l-1] - f[k] < dp[l][r]){
						dp[l][r] = dp[l][k-1] + dp[k+1][r] + sum[r] - sum[l-1] - f[k];
						opt[l][r] = k;
					}
					
				}
				
			}
		}
		
		cout << dp[1][n] << "\n";
	}
	
	
	return 0;
}
