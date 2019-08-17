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

int v[50];
int acc[50];
int n, dp[35][225][225];
char memo[35][225][225];

int solve(int pos, int a, int b){
	if(pos==n+1){
		return max({a, b, acc[pos-1] - a - b}) - min({a, b, acc[pos-1] - a - b});
	}
	if(a > 220 || b > 220 || acc[pos-1]-a-b > 220) return 1e9;
	if(memo[pos][a][b]) return dp[pos][a][b];
	memo[pos][a][b] = 1;
	
	int ans = 1e9;
	ans = min(solve(pos+1, a+v[pos], b), solve(pos+1, a, b+v[pos]));
	ans = min(ans, solve(pos+1, a, b));
	
	return dp[pos][a][b] = ans;
}

int main () {
	
	ios_base::sync_with_stdio (0);
	cin.tie (0);
	int tc, caso=1;
	cin >> tc;
	while (tc--)
	{
		cin >> n;
		acc[0] = 0;
		for (int i = 1; i <= n; i++)
		{
			cin >> v[i];
			acc[i] = acc[i-1] + v[i];
		}
		memset(memo, 0, sizeof memo);
		cout << "Case " << caso++ << ": " << solve(0, 0, 0) << "\n";
		
	}
	
	return 0;
}
