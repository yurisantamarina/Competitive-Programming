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

ll dp[1010][1010];
ll t;

ll solve(int b, int g){
	if(b==0 && g==0) return 1;
	if(b<0) return 0;
	if(g<0) return 0;	
	if(dp[b][g]!=-1) return dp[b][g];
	
	return dp[b][g] = (g * solve(b-1, g-1) + (t - g) * solve(b-1, g))%MOD;
}

int main () {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	int b, g;
	while (cin >> b >> g, b+g)
	{
		memset(dp, -1, sizeof dp);
		t = g;
		cout << solve(b, g) << "\n";
	}
	
	
	
	
	
	return 0;
}
