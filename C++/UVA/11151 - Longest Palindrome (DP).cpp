#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair
#define F first
#define S second
#define oioi printf("oioi\n")
using namespace std;
typedef long long int ll;
typedef unsigned long long int llu;

int dp[1010][1010];
//~ int dp2[1010][1010];
string s;

int solve(int l, int r){
	if(l>r) return dp[l][r] = 0;
	if(l==r) return dp[l][r] = 1;
	if(dp[l][r]!=-1) return dp[l][r];
	
	int ans = 0;
	if(s[l]==s[r]) ans = 2 + solve(l+1, r-1);
	else ans = max(solve(l+1, r), solve(l, r-1));
	
	return dp[l][r] = ans;
}

void path(int l, int r){
	if(l>r) return;
	if(l==r){
		cout << s[l];
		return;
	}
	
	if(s[l]==s[r]){
		cout << s[l];
		path(l+1, r-1);
		cout << s[r];
	}else{
		if(dp[l][r] == dp[l+1][r]) path(l+1, r);
		else path(l, r-1);
	}
}

int main () {
	int t;
	cin >> t;
	getchar();
	while (t--)
	{
		getline(cin, s);
		memset(dp, -1, sizeof dp);
		cout << solve(0, s.size()-1) << "\n";
		//~ path(0, s.size()-1);
		//~ cout << endl;
	}
	
	
	return 0;
}
