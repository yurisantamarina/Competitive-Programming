#include <bits/stdc++.h>

using namespace std;
#define MAXN 101010
#define F first
#define S second
int n;
pair<int, int> v[MAXN];
int dp[MAXN][3];

int main(){
	scanf("%d", &n);
	for (int i = 0; i < n; i++)
		scanf("%d %d", &v[i].F, &v[i].S);
	
	v[n].F = 2e9 + 3;
	dp[0][0] = dp[0][1] = dp[0][2] = 1;
	for (int tree = 1; tree < n; tree++)
	{
		dp[tree][0] = dp[tree][1] = dp[tree][2] = INT_MIN;
		
		dp[tree][0] = max(dp[tree-1][0], dp[tree-1][1]);
		if(v[tree-1].F + v[tree-1].S < v[tree].F)
			dp[tree][0] = max(dp[tree][0], dp[tree-1][2]);
		
			
		if(v[tree].F - v[tree].S > v[tree-1].F)
			dp[tree][1] = 1 + max(dp[tree-1][0], dp[tree-1][1]);
		if(v[tree-1].F + v[tree-1].S < v[tree].F - v[tree].S)
			dp[tree][1] = max(dp[tree][1], 1 + dp[tree-1][2]);
		
		if(tree == n-1 || v[tree].F + v[tree].S < v[tree+1].F){
			dp[tree][2] = 1 + max(dp[tree-1][0], dp[tree-1][1]);
			if(v[tree-1].F + v[tree-1].S < v[tree].F)
				dp[tree][2] = max(dp[tree][2], 1 + dp[tree-1][2]);
		}
		
	}
	
	printf("%d\n", max({dp[n-1][0], dp[n-1][1], dp[n-1][2]}));
	
	return 0;
}
