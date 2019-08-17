#include <bits/stdc++.h>

using namespace std;
#define INF 1e9
#define MAXN 1010
int dp[MAXN][MAXN];
int opt[MAXN][MAXN];
int v[MAXN];

int main(){
	int len, n;
	while (cin >> len >> n)
	{
		for (int i = 1; i <= n; i++)
		{
			cin >> v[i];
		}
		
		v[0] = 0;
		v[n+1] = len;
		n++;
		
		int r;
		for (int sz = 1; sz <= n+1; sz++)
		{
			for (int l = 0; l <= n; l++)
			{
				r = l + sz - 1;
				if(r > n) break;
				if(sz <= 2){
					dp[l][r] = 0;
					opt[l][r] = l;
					continue;
				}
				
				dp[l][r] = INF;
				int ml = opt[l][r-1];
				int mr = opt[l+1][r];
				for (int k = ml; k <= mr; k++)
				{
					if(dp[l][k] + dp[k][r] + v[r] - v[l] < dp[l][r]){
						dp[l][r] = dp[l][k] + dp[k][r] + v[r] - v[l];
						opt[l][r] = k;
					}
				}
				
			}
			
		}
		cout << dp[0][n] << "\n";
	}
	
	
	
	return 0;
}
