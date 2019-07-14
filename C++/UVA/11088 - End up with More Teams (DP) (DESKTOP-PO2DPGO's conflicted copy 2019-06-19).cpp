#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair
#define F first
#define S second
#define oioi printf("oioi\n")
#define eoq cout << "eoq" << '\n'
#define CLS while (getchar () != '\n')
using namespace std;
typedef long long int ll;
typedef unsigned long long int llu;
typedef pair<ll, ll> ii;
typedef pair<double, double> dd;
typedef vector<ll> vi;
typedef vector<ii> vii;
const int dx[] = { 0, 1, -1, 0, 1, -1, -1,  1};
const int dy[] = {-1, 0,  0, 1, 1,  1, -1, -1};
const int N = 0;
const ll MOD = 1000000007LL;
const int INF = 1e9 + 10;
const ll LLINF = 1e18 + 10;
#define MAXN 1000000

int dp[1<<16];
int v[16];
int n;

int solve(int mask){
	if(n - __builtin_popcount(mask) < 3) return 0;
	if(dp[mask]!=-1) return dp[mask];
	
	int ans = 0;
	
	for (int i = 0; i < n; i++)
	{
		if(mask & (1<<i)) continue;
		for (int j = i+1; j < n; j++)
		{
			if(mask & (1<<j)) continue;
			for (int k = j+1; k < n; k++)
			{
				if(mask & (1<<k)) continue;
				ans = max(ans, ((v[i]+v[j]+v[k]) >= 20) + solve(mask | (1<<i) | (1<<j) | (1<<k)));
			}
		}
	}
	
	return dp[mask] = ans;
}

void path(int mask){
	if(n - __builtin_popcount(mask) < 3) return;
	
	int ans = 0;
	
	for (int i = 0; i < n; i++)
	{
		if(mask & (1<<i)) continue;
		for (int j = i+1; j < n; j++)
		{
			if(mask & (1<<j)) continue;
			for (int k = j+1; k < n; k++)
			{
				if(mask & (1<<k)) continue;
				if(dp[mask] == ((v[i]+v[j]+v[k]) >= 20) + solve(mask | (1<<i) | (1<<j) | (1<<k))){
					printf("group = %d %d %d\n", v[i], v[j], v[k]);
					path(mask | (1<<i) | (1<<j) | (1<<k));
					return;
				}
			}
			
		}
		
	}
	
}

int main () {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	int caso = 1;
	while (cin >> n, n)
	{
		for (int i = 0; i < n; i++)
		{
			cin >> v[i];
		}
		memset(dp, -1, sizeof dp);
		cout << "Case " << caso++ << ": " << solve(0) << "\n";
		//~ path(0);
	}
	
	return 0;
}
