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
const int MOD = 0;
const int INF = 1e9 + 10;
const ll LLINF = 1e18 + 10;

int dp[160][110][60];
int n;
int total;

int solve(int pos, int n5, int n10){
	int n1 = total - 8*pos - 5*n5 - 10*n10;
	if(n5 < 0 || n10 < 0 || n1 < 0) return 1e9;
	if(pos==n) return 0;
	if(dp[pos][n5][n10]!=-1) return dp[pos][n5][n10];
	
	int ans = 1e9;
	ans = min(ans, 1 + solve(pos+1, n5, n10-1));
	ans = min(ans, 2 + solve(pos+1, n5-2, n10));
	ans = min(ans, 8 + solve(pos+1, n5, n10));
	ans = min(ans, 4 + solve(pos+1, n5-1, n10));
	ans = min(ans, 4 + solve(pos+1, n5+1, n10-1));
	
	return dp[pos][n5][n10] = ans;
}

int main () {
	
	ios_base::sync_with_stdio (0);
	cin.tie (0);
	int tc;
	cin >> tc;
	int n1, n5, n10;
	while (tc--)
	{
		cin >> n >> n1 >> n5 >> n10;
		total = n1 + 5*n5 + 10*n10;
		memset(dp, -1, sizeof dp);
		cout << solve(0, n5, n10) << "\n";
	}
	
		
	return 0;
}
