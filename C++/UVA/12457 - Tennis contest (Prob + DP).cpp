#include <bits/stdc++.h>

using namespace std;

int n;
char memo[26][26];
double dp[26][26], ganha, perde;

double solve(int ptA, int ptB){
	if(ptA == n) return 1.0;
	if(ptB == n) return 0.0;
	if(memo[ptA][ptB]) return dp[ptA][ptB];
	memo[ptA][ptB] = 1;
	
	double ans = 0.0;
	ans = ganha * solve(ptA + 1, ptB) + perde * solve(ptA, ptB + 1);
	
	return dp[ptA][ptB] = ans;
}

int main(){
	
	int tc;
	cin >> tc;
	
	while (tc--)
	{
		cin >> n >> ganha;
		perde = 1 - ganha;
		memset(memo, 0, sizeof memo);
		cout << fixed << setprecision(2) << solve(0, 0) << "\n";
	}
	
	
	
	return 0;
}
