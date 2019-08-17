#include <bits/stdc++.h>

using namespace std;
#define INF 1e9
#define MAXN 2020
typedef long long int ll;

int v[MAXN];
ll dp[MAXN][MAXN];
ll sum[MAXN];
int opt[MAXN][MAXN];
int n;
string ans[MAXN];

void path(int l, int r, char c){
	if(l > r) return;
	
	for (int i = l; i <= r; i++)
	{
		ans[i] += c;
	}
	if(l==r) return;
	int k = opt[l][r];
	path(l, k, '0');
	path(k+1, r, '1');
}

int main(){
	
	while (cin >> n)
	{
		for (int i = 1; i <= n; i++)
		{
			cin >> v[i];
			sum[i] = sum[i-1] + v[i];
		}
		
		int r;
		for (int sz = 1; sz <= n; sz++)
		{
			for (int l = 1; l <= n; l++)
			{
				r = l + sz - 1;
				if(r > n) break;
				if(l == r){
					dp[l][r] = 0;
					opt[l][r] = l;
					continue;
				}
				
				int ml = opt[l][r-1];
				int mr = opt[l+1][r];
				
				dp[l][r] = INF;
				for (int k = ml; k <= mr; k++)
				{
					if(dp[l][k] + dp[k+1][r] + sum[r] - sum[l-1] < dp[l][r]){
						dp[l][r] = dp[l][k] + dp[k+1][r] + sum[r] - sum[l-1];
						opt[l][r] = k;
					}
				}
				
			}
			
		}
		
		//~ cout << dp[1][n] << "\n";
		for (int i = 1; i <= n; i++)
		{
			ans[i] = "";
		}
		path(1, opt[1][n], '0');
		path(opt[1][n] + 1, n, '1');
		for (int i = 1; i <= n; i++)
		{
			cout << ans[i] << "\n";
		}
		
		
	}
	
	
	
	
	return 0;
}
