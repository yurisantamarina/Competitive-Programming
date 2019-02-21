#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair
#define F first
#define S second
#define oioi printf("oioi\n")
#define eoq cout << "eoq" << '\n'
#define CLS while (getchar () != '\n')
using namespace std;
typedef unsigned long long int ll;
//~ typedef long long int ll;
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
const ll LLINF = 1e18 + 10LL;

ll acc[10010];
ll v[10010];
ll dp[2][10010];
int n, k;

ll cost(ll l, ll r){
	return (acc[r] - acc[l-1])*(r-l+1);
}

void calc(int K, int l, int r, int optL, int optR){
	if(r < l) return;
	int mid = (l+r)/2;
	int best = -1;
	int lim = min(mid-1, optR);
	
	dp[K&1][mid] = dp[(K-1)&1][mid];
	for (int pos = optL; pos <= lim; pos++)
	{
		if(dp[(K-1)&1][pos] + cost(pos+1, mid) < dp[K&1][mid]){
			best = pos;
			dp[K&1][mid] = dp[(K-1)&1][pos] + cost(pos+1, mid);
		}
	}
	//~ if(best == -1) dp[K&1][mid] = 0;
	calc(K, l, mid-1, optL, best);
	calc(K, mid+1, r, best, optR);
}

int main () {
	
	ios_base::sync_with_stdio (0);
	cin.tie (0);
	cin >> n >> k;
	for (int i = 1; i <= n; i++)
	{
		cin >> v[i];
		acc[i] = acc[i-1] + v[i];
	}
	
	for (int pos = 1; pos <= n; pos++)
	{
		dp[1&1][pos] = acc[pos] * pos;
	}
	
	for (int K = 2; K <= k; K++)
	{
		calc(K, 1, n, 1, n);
	}
	cout << dp[k&1][n] << "\n";
	
	return 0;
}
