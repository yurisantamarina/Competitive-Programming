#include <bits/stdc++.h>

using namespace std;
int n, k;
int cost[1200];
double p[1200];
char memo[1200][1200];
double dp[1200][1200];

double solve(int pos, int falta){
	if(falta < 0) return -1000000;
	if(pos == n) return 0;
	if(memo[pos][falta]) return dp[pos][falta];
	memo[pos][falta] = 1;
	return dp[pos][falta] = max(cost[pos] + solve(pos+1, falta-1), cost[pos] * p[pos] + p[pos] * solve(pos+1, falta));
}

int main(){
	
	
	while(cin >> n >> k){
		for (int i = 0; i < n; i++)
			cin >> cost[i];
		
		for (int i = 0; i < n; i++){
			cin >> p[i];
			p[i] /= 100;
		}
		
		memset(memo, 0, sizeof memo);
		cout << fixed << setprecision(2) << solve(0, k) << "\n";
	}
	
	
	return 0;
}
