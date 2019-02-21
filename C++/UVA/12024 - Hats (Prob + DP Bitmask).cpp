#include <bits/stdc++.h>

using namespace std;

int n;
char memo[1<<13];
int dp[1<<13];
int fat[1<<13];

int solve(int mask){
	if(mask == (1 << n) - 1) return 1;
	if(memo[mask]) return dp[mask];
	memo[mask] = 1;
	
	int ans = 0;
	int pos = __builtin_popcount(mask);
	for (int i = 0; i < n; i++)
	{
		if(i == pos || (mask & (1<<i))) continue;
		ans += solve(mask | (1<<i));
	}
	
	return dp[mask] = ans;
}

int main(){
	fat[0] = 1;
	for (int i = 1; i < 13; i++)
		fat[i] = fat[i-1] * i;
	
	int tc;
	cin >> tc;
	while (tc--)
	{
		cin >> n;
		memset(memo, 0, sizeof memo);
		cout << solve(0) << "/" << fat[n] << "\n";
	}
	
	
	return 0;
}
