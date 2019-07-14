#include <bits/stdc++.h>

using namespace std;

int n, m, q, dp[1<<13][1400], cnt[1<<13], val[12], sum[1<<13];
char s[13];

int getSum(int i, int j){
	return sum[i ^ j];
}

void build(){
	int len = 1 << n;
	
	for (int i = 0; i < len; i++)
		for (int j = 0; j < n; j++)
			if((i & (1 << j)) == 0)
				sum[i] += val[j];
	
	for (int i = 0; i < len; i++){
		for (int j = 0; j < len; j++)
			dp[i][getSum(i, j)] += cnt[j];
		
		for(int j = 1; j <= 100; j++)
			dp[i][j] += dp[i][j-1];
	}
}

int get(){
	int at = 0;
	for (int i = 0; i < n; i++)
		at += (s[i] - '0') * (1 << (n - i - 1));
	
	return at;
}

int main(){
	scanf("%d %d %d", &n, &m, &q);
	for (int i = n - 1; i >= 0; i--)
		scanf("%d", &val[i]);
	
	for (int i = 0; i < m; i++)
	{
		scanf(" %s", s);
		int x = get();
		cnt[x]++;
	}
	
	build();
	int k;
	for (int i = 0; i < q; i++)
	{
		scanf(" %s %d", s, &k);
		printf("%d\n", dp[get()][k]);
	}
	
	
	
	return 0;
}
