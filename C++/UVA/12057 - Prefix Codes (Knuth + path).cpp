#include <bits/stdc++.h>

using namespace std;
#define MAXN 1010
#define INF 1e9

double dp[MAXN][MAXN];
int opt[MAXN][MAXN];
double sum[MAXN];
double v[MAXN];
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
	bool fst = true;
	while (cin >> n, n)
	{
		if(!fst) cout << "\n";
		fst = false;
		for (int i = 1; i <= n; i++)
		{
			cin >> v[i];
			sum[i] = sum[i-1] + v[i];
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
					dp[l][r] = 0.0;
					opt[l][r] = l;
					continue;
				}
				
				dp[l][r] = INF;
				int ml = opt[l][r-1];
				int mr = opt[l+1][r];
				//~ int ml = l;
				//~ int mr = r;
				
				//se usar ml = l e mr = r só, tem q ser k < mr, pois eu corto entre o k e k+1, mas como uso mr = opt[l+1][r], tem q ser <=, pois o mr é uma posicao valida de corte
				for (int k = ml; k <= mr; k++)
				{
					if(dp[l][k] + dp[k+1][r] + sum[r] - sum[l-1] < dp[l][r]){
						dp[l][r] = dp[l][k] + dp[k+1][r] + sum[r] - sum[l-1];
						opt[l][r] = k;
					}
				}
				
			}
			
		}
		if(n==1){
			cout << "1.0000\n0\n";
			
			continue;
		}
		cout << fixed << setprecision(4) << dp[1][n] << "\n";
		
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
