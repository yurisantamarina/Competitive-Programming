#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair
#define F first
#define S second
#define oioi printf("oioi\n")
#define eoq cout << "eoq" << '\n'
using namespace std;
typedef long long int ll;
typedef unsigned long long int llu;
typedef pair<ll, ll> ii;
typedef pair<double, double> dd;
typedef vector<ll> vi;
typedef vector<ii> vii;
const int dx[] = {0 ,1,-1,0,1,-1,-1, 1};
const int dy[] = {-1,0,0, 1,1, 1,-1,-1};
const ll MOD = 0;
const ll N = 0;
#define INF 1e9

vector<pair<int, int> > v[6000];
int n, m;
int cost[6000];
int dp[30][30][1010][2];

int solve(int batch, int idx, int resta, bool abriu){
	if(resta < 0) return -INF;
	if(batch==n){
		//~ cout << resta << "\n";
		return dp[batch][idx][resta][abriu] = 0;
	}
	if(dp[batch][idx][resta][abriu]!=-1) return dp[batch][idx][resta][abriu];
	
	int ans;
	if(idx+1==m){
		ans = max(solve(batch+1, 0, resta, false),
				  v[batch][idx].S + solve(batch, idx, resta - v[batch][idx].F - (abriu ? 0 : cost[batch]), true));
	}else{
		ans = max(solve(batch, idx+1, resta, abriu),
				  v[batch][idx].S + solve(batch, idx, resta - v[batch][idx].F - (abriu ? 0 : cost[batch]), true));
	}
	
	return dp[batch][idx][resta][abriu] = ans;
}

void path(int batch, int idx, int resta, bool abriu){
	if(resta < 0) return;
	if(batch==n){
		//~ if(ans == )
		return;
	}
	
	int ans = dp[batch][idx][resta][abriu];
	if(idx+1==m){
		
		if(ans == solve(batch+1, 0, resta, false)){
			path(batch+1, 0, resta, false);
		}else{
			printf("Batch = %d  idx = %d\n", batch, idx);
			path(batch, idx, resta - v[batch][idx].F - (abriu ? 0 : cost[batch]), true);
		}
	}else{
		
		if(ans == solve(batch, idx+1, resta, abriu)){
			path(batch, idx+1, resta, abriu);
		}else{
			printf("Batch = %d  idx = %d\n", batch, idx);
			path(batch, idx, resta - v[batch][idx].F - (abriu ? 0 : cost[batch]), true);
		}
	}
	
}

int main () {
	int k;
	int t;
	cin >> t;
	
	while (t--)
	{
		cin >> n >> m >> k;
		for (int i = 0; i < n; i++)
		{
			cin >> cost[i];
		}
		
		int c;
		for (int i = 0; i < n; i++)
		{
			v[i].clear();
			for (int j = 0; j < m; j++)
			{
				cin >> c;
				v[i].pb(mp(c, 0));
			}
		}
		
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < m; j++)
			{
				cin >> v[i][j].S;
			}
		}
		memset(dp, -1, sizeof dp);
		cout << solve(0, 0, k, false) << "\n";
		//~ path(0, 0, k, false);
	
	}
	
	
	return 0;
}
