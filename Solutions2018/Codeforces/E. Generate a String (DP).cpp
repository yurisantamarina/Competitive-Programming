#include <bits/stdc++.h>

using namespace std;
#define MAXN 10101010
typedef long long int ll;
ll dp[MAXN];

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	ll n, x, y;
	cin >> n >> x >> y;
	dp[1] = x;
	for (int i = 2; i <= n; i++)
	{
		if(i % 2 == 0)
			dp[i] = min(dp[i-1] + x, dp[i/2] + y);
		else
			dp[i] = min(dp[i-1] + x, dp[(i/2) + 1] + y + x);
	}
	cout << dp[n] << "\n";
	
	
	
	return 0;
}
