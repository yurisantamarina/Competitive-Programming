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
const int MOD = 1000000007;
const int INF = 1e9 + 10;
const ll LLINF = 1e18 + 10;

int n, len;
int dp[101][2][10][1<<10];
char memo[101][2][10][1<<10];

int solve(int pos, char comecou, int lst, int mask){
	if(pos==len) return (mask == (1<<n)-1) ? 1 : 0;
	if(memo[pos][comecou][lst][mask]) return dp[pos][comecou][lst][mask];
	memo[pos][comecou][lst][mask] = 1;
	
	int ans = 0;
	if(comecou){
		if(lst-1>=0) ans = (ans + solve(pos+1, true, lst-1, mask | (1<<(lst-1))))%MOD;
		if(lst+1<n) ans = (ans + solve(pos+1, true, lst+1, mask | (1<<(lst+1))))%MOD;
		//~ ans = (ans + solve(pos+1, true, lst, mask | (1<<lst)))%MOD;
	}else{
		ans = solve(pos+1, false, lst, mask);
		for (int i = 1; i < n; i++)
		{
			ans = (ans + solve(pos+1, true, i, mask | (1<<i)))%MOD;
		}
		
	}
	
	return dp[pos][comecou][lst][mask] = ans;
}

int main () {
	
	ios_base::sync_with_stdio (0);
	cin.tie (0);
	int tc;
	cin >> tc;
	while (tc--)
	{
		cin >> n >> len;
		memset(memo, 0, sizeof memo);
		cout << solve(0, false, 0, 0) << "\n";
	}
	
		
	return 0;
}
