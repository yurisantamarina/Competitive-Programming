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

struct pv{
	double x, y;
	pv(){}
	pv(double a, double b){
		x = a;
		y = b;
	}
};

double dist(pv a, pv b){
	return hypot(a.x-b.x, a.y-b.y);
}

double dp[1<<17];
int n;
vector<pv> v;

double solve(int mask){
	if(mask == (1<<n) - 1) return 0;
	if(dp[mask] > -0.5) return dp[mask];
	double ans = 10000000000.0;
	
	for (int i = 0; i < n; i++)
	{
		if(mask & (1<<i)) continue;
		for (int j = i+1; j < n; j++)
		{
			if(mask & (1<<j)) continue;
			if(i==j) continue;
			ans = min(ans, dist(v[i], v[j]) + solve(mask | (1 << i) | (1 << j)));
		}
		break;
	}
	
	
	return dp[mask] = ans;
}

int main () {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	string nome;
	double x, y;
	int caso=1;
	while (cin >> n, n)
	{
		n*=2;
		v.clear();
		for (int i = 0; i < n; i++)
		{
			cin >> nome >> x >> y;
			v.pb(pv(x, y));
		}
		memset(dp, -1, sizeof dp);
		cout << fixed << setprecision(2) << "Case " << caso++ << ": " << solve(0) << "\n";
	}
	
	
	return 0;
}
