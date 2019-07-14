#include <bits/stdc++.h>

using namespace std;

int get(char a, char b){
	int i = a - 'a';
	int j = b - 'a';
	if(i > j) swap(i, j);
	return min(j - i, 26 - j + i);
}

int cost[420][420];
int dp[420][420];
string s;
int n, k;

void build(){
	for (int len = 1; len <= (int)s.size(); len++)
	{
		for (int i = 1; i <= n; i++)
		{
			int j = i + len - 1;
			if(j > n) continue;
			if(len == 1) cost[i][i] = 0;
			else if(len == 2) cost[i][j] = get(s[i], s[j]);
			else cost[i][j] = cost[i + 1][j - 1] + get(s[i], s[j]);
		}
	}
}

int main(){
	scanf("%d %d", &n, &k);
	char c;
	s = "0";
	getchar();
	for (int i = 0; i < n; i++)
	{
		scanf("%c", &c);
		s += c;
	}
	
	build();
	
	memset(dp, 1, sizeof dp);
	dp[0][0] = 0;
	for (int i = 1; i <= n; i++)
		dp[i][1] = cost[1][i];
	
	for(int K = 2; K <= k; K++)
		for (int i = 1; i <= n; i++)
			for (int j = 0; j < i; j++)
				dp[i][K] = min(dp[i][K], dp[j][K - 1] + cost[j + 1][i]);
			
	int ans = 10101010;
	for (int i = 1; i <= k; i++)
		ans = min(ans, dp[n][i]);
	printf("%d\n", ans);
	
	return 0;
}
