#include <bits/stdc++.h>

using namespace std;
#define MAXN 10001
typedef long long int ll;
int v[MAXN];
ll dp[MAXN][3];

int main()
{
	int n;
	while(scanf("%d", &n)!=EOF) {
		for(int i = 0; i < n; i++)
			scanf("%d", &v[i]);

		int j;
		for (int len = 1; len <= n; len++)
		{
			for (int i = 0; i + len - 1 < n; i++)
			{
				j = i + len - 1;
				
				if(i == j){
					dp[i][len%3] = v[i];
				}else if(i == j-1){
					dp[i][len%3] = max(v[i], v[j]);
				}else{
					dp[i][len%3] = max(v[i] + min(dp[i+2][(len-2)%3], dp[i+1][(len-2)%3]), v[j] + min(dp[i][(len-2)%3], dp[i+1][(len-2)%3]));
				}
			}
		}
		printf("%lld\n", dp[0][n%3]);
	}

	return 0;
}
