#include <bits/stdc++.h>

using namespace std;
#define MAXN 4010
#define gc getchar

void scanint(int &x)
{
    register int c = gc();
    x = 0;
    for(;(c<48 || c>57);c = gc());
    for(;c>47 && c<58;c = gc()) {x = (x<<1) + (x<<3) + c - 48;}
}

int grid[MAXN][MAXN];
int sum[MAXN][MAXN];
int dp[2][MAXN];
int n;
int INF = 1e9;


void build(){
	
	for (int i = 1; i <= n; i++)
	{
		for (int j = 1; j <= n; j++)
		{
			sum[i][j] = sum[i-1][j] + sum[i][j-1] - sum[i-1][j-1] + grid[i][j];
		}
	}
}

int getSum(int j, int i){
	return sum[i][i] - sum[j-1][i] - sum[i][j-1] + sum[j-1][j-1];
}

void calc(int k, int l, int r, int optL, int optR){
	if(r < l) return;
	int mid = (l+r)/2;
	int opt = 0;
	dp[k&1][mid] = INF;
	for (int i = optL; i < mid; i++)
	{
		if(i > optR) break;
		if(dp[(k-1)&1][i] + getSum(i+1, mid) < dp[k&1][mid]){
			dp[k&1][mid] = dp[(k-1)&1][i] + getSum(i+1, mid);
			opt = i;
		}
	}
	calc(k, l, mid-1, optL, opt);
	calc(k, mid+1, r, opt, optR);
}

int main(){
	//~ ios_base::sync_with_stdio(0);
	//~ cin.tie(0);
	int k;
	scanint(n);
	scanint(k);
	for (int i = 1; i <= n; i++)
	{
		for (int j = 1; j <= n; j++)
		{
			scanint(grid[i][j]);
		}
	}
	build();
	
	for (int i = 1; i <= n; i++)
	{
		dp[1&1][i] = getSum(1, i);
	}
	
	for (int K = 2; K <= k; K++)
	{
		calc(K, 1, n, 1, n);
	}
	printf("%d\n", dp[k&1][n]/2);
	
	
	return 0;
}
