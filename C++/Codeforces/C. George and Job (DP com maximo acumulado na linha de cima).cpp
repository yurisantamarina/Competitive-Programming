#include <bits/stdc++.h>

using namespace std;
typedef long long int ll;

#define MAXN 5010
ll dp[MAXN][2];
ll acc[MAXN];
ll accMx[MAXN];
int n, m, k;

ll get(int l, int r){
	return acc[r] - acc[l-1];
}

void build(int lvl){
	accMx[0] = 0;
	for (int i = 1; i <= n; i++)
	{
		accMx[i] = max(accMx[i-1], dp[i][lvl&1]);
	}
}


int main(){
	scanf("%d %d %d", &n, &m, &k);
	for (int i = 1; i <= n; i++)
	{
		scanf("%lld", &acc[i]);
		acc[i] += acc[i-1];
	}
	
	for (int i = m; i <= n; i++)
	{
		dp[i][1&1] = get(i - m + 1, i);
	}
	
	
	for (int qtd = 2; qtd <= k; qtd++)
	{
		build(qtd-1);
		for (int pos = m*qtd; pos <= n; pos++)
		{
			dp[pos][qtd&1] = accMx[pos - m] + get(pos - m + 1, pos);
		}
	}
	
	ll ans = 0LL;
	for (int i = 1; i <= n; i++)
	{
		ans = max(ans, dp[i][k&1]);
	}
	printf("%lld\n", ans);
	
	
	return 0;
}
