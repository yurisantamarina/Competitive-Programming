#include <bits/stdc++.h>

using namespace std;
#define MAXN 10101
#define INF 1000000000000000LL
typedef long long int ll;

ll n, W, B, X;
ll qtd[MAXN];
ll cost[MAXN];
ll dp[1010][MAXN];
ll sum = 0;

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cin >> n >> W >> B >> X;
	for (ll i = 1; i <= n; i++){
		cin >> qtd[i];
		sum += qtd[i];
	}
	
	for (ll i = 1; i <= n; i++)
		cin >> cost[i];
	
	for (ll i = 0; i < 1010; i++)
	{
		for (ll j = 0; j < MAXN; j++)
		{
			dp[i][j] = -INF;
		}
	}
	
	ll cap, ans = 0;
	for (ll i = 0; i <= qtd[1]; i++)
	{
		dp[1][i] = W - i*cost[1];
		if(dp[1][i] < 0) dp[1][i] = -INF;
		if(n == 1 && dp[1][i] >= 0) ans = max(ans, i);
	}
	
	for (ll i = 2; i <= n; i++)
	{
		for (ll j = 0; j <= sum; j++)
		{
			dp[i][j] = -INF;
			
			for(ll k = 0; k <= min(qtd[i], j); k++){
				cap = (j-k)*B + W;
				dp[i][j] = max(dp[i][j], min(cap, dp[i-1][j-k] + X) - k * cost[i]);
				
			}
			if(dp[i][j] < 0) dp[i][j] = -INF;
			
			if(i == n){
				if(dp[i][j] >= 0) ans = max(ans, j);
			}
		}
	}
	cout << ans << "\n";
	
	return 0;
}
