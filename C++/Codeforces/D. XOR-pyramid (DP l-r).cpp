#include <bits/stdc++.h>

using namespace std;

#define MAXN 5010

int v[MAXN];
int val[MAXN][MAXN];
int dp[MAXN][MAXN];
int n;

int main(){
	scanf("%d", &n);
	for (int i = 1; i <= n; i++)
	{
		scanf("%d", &v[i]);
		val[i][i] = v[i];
		dp[i][i] = v[i];
	}
	
	for (int len = 2; len <= n; len++)
	{
		for (int i = 1; i <= n; i++)
		{
			val[i][i + len - 1] = val[i][i + len - 2] ^ val[i + 1][i + len - 1];
			dp[i][i + len - 1] = max({val[i][i + len - 1], dp[i][i + len - 2], dp[i + 1][i + len - 1]});
		}
	}
	
	int q, l, r;
	scanf("%d", &q);
	while (q--)
	{
		scanf("%d %d", &l, &r);
		printf("%d\n", dp[l][r]);
	}
	
	
	
	
	return 0;
}
