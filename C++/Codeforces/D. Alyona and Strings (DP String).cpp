#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair
#define F first
#define S second

using namespace std;


int dp[1010][1010][12][2];
string s, t;

int solve(int i, int j, int k, int fecha){
	if(i==s.size() || j==t.size()) return dp[i][j][k][fecha] = (k==0 || (k==1 && fecha) ? 0 : -1e9);
	if(k==0) return dp[i][j][k][fecha] = 0;
	if(dp[i][j][k][fecha]!=-1) return dp[i][j][k][fecha];
	
	int ans=0;
	if(s[i] == t[j]){
		ans = max(solve(i+1, j, fecha ? k-1 : k, fecha), solve(i, j+1, fecha ? k-1 : k, fecha));
		ans = max(ans, 1 + solve(i+1, j+1, k-1, false));
		ans = max(ans, 1 + solve(i+1, j+1, k, true));
	}else{
		if(fecha){
			ans = max(solve(i+1, j, k-1, false), solve(i, j+1, k-1, false));
		}else{
			ans = max(solve(i+1, j, k, false), solve(i, j+1, k, false));
		}
		
	}
	
	return dp[i][j][k][fecha] = ans;
}

int main () {
	int a, b, k;
	cin >> a >> b >> k;
	cin >> s;
	cin >> t;
	
	memset(dp, -1, sizeof dp);
	cout << solve(0, 0, k, false) << "\n";
	
	
	return 0;
}
