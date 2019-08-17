#include <bits/stdc++.h>

using namespace std;
#define INF 1e9

int dp[55][55];
int opt[55][55];
int v[55];

int main(){
	int len, n;
	while (cin >> len, len)
	{
		cin >> n;
		for (int i = 1; i <= n; i++)
		{
			cin >> v[i];
		}
		n++;
		v[0] = 0;
		v[n] = len;
		
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
				
				//sem otimizar ml = l e mr = r;
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
		
		//~ for (int i = 0; i <= n; i++)
		//~ {
			//~ for (int j = 0; j <= n; j++)
			//~ {
				//~ cout << dp[i][j] << " ";
			//~ }
			//~ cout << endl;
		//~ }
		
		cout << "The minimum cutting is " << dp[0][n] << ".\n";
	}
	
	
	return 0;
}
