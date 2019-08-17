#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair
#define F first
#define S second
using namespace std;
typedef long long int ll;
typedef unsigned long long int llu;
#define MAXN 2010

vector<int> g[MAXN];
int n, x;
int dp[MAXN];

int solve(int u){
	if(dp[u] != -1) return dp[u];
	int ans = 0;
	for(int v : g[u]){
		ans = max(ans, solve(v));
	}
	
	return dp[u] = 1 + ans;
}

int main () {
	cin >> n;
	for (int i = 0; i < n; i++)
	{
		cin >> x;
		if(x == -1) continue;
		x--;
		g[x].pb(i);
	}
	
	memset(dp, -1, sizeof dp);
	int ans = 0;
	for (int i = 0; i < n; i++)
	{
		ans = max(ans, solve(i));
	}
	cout << ans << "\n";
	
	return 0;
}
