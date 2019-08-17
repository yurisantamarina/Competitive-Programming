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
const ll INF = 1000000000000000LL;
const ll LLINF = 1e18 + 10;

ll cost[1010];
ll w[1010];
ll x[1010];
ll sumW[1010];
ll sumXW[1010];
ll dp[1010][1010];
ll n, k;

void build(){
	sumW[0] = 0;
	sumXW[0] = 0;
	for (ll i = 1; i <= n; i++)
	{
		sumW[i] = sumW[i-1] + w[i];
		sumXW[i] = sumXW[i-1] + w[i]*x[i];
	}
}

ll getSumW(int l, int r){
	if(r < l) return 0LL;
	return sumW[r] - sumW[l-1];
}

ll getSumXW(int l, int r){
	if(r < l) return 0LL;
	return sumXW[r] - sumXW[l-1];
}

ll getCost(ll l, ll r){
	
	return x[r] * getSumW(l, r-1) - getSumXW(l, r-1);
}



void calc(int K, int l, int r, int optL, int optR){
	if(l>r) return;
	int mid = (l+r)/2;
	int best = -1;
	int lim = min(mid-1, optR);
	
	dp[K][mid] = INF;
	for (int i = optL; i <= lim; i++)
	{
		if(dp[K][mid] > dp[K-1][i] + getCost(i+1, mid)){
			best = i;
			dp[K][mid] = dp[K-1][i] + getCost(i+1, mid);
		}
	}
	calc(K, l, mid-1, optL, best);
	calc(K, mid+1, r, best, optR);
}

int main () {
	
	ios_base::sync_with_stdio (0);
	cin.tie (0);
	//~ cout << 1000 << " " << 333 << endl;
	//~ for (int i = 0; i < 1000; i++)
	//~ {
		//~ cout << i+1 << " " << rand()%1000000 + 1 << endl;
	//~ }
	
	//~ return 0;
	
	while(cin >> n >> k){
		for (ll i = 1; i <= n; i++)
		{
			cin >> x[i] >> w[i];
		}
		
		build();
		//~ cout << getCost(4, 5) << endl;
		
		for (ll pos = 1; pos <= n; pos++)
		{
			dp[1][pos] = getCost(1, pos);
		}
		
		ll best;
		
		for (ll K = 2; K <= k; K++)
		{
			calc(K, 1, n, 1, n);
			//~ for (ll pos = 1; pos <= n; pos++)
			//~ {
				//~ dp[K][pos] = INF;
				//~ best = -1;
				//~ for (ll i = 1; i < pos; i++)
				//~ {
					//~ if(dp[K-1][i] + getCost(i+1, pos) < dp[K][pos]){
						//~ dp[K][pos] = dp[K-1][i] + getCost(i+1, pos);
						//~ best = i;
					//~ }
				//~ }
			//~ }
		}
		cout << dp[k][n] << "\n";
	}
	
	return 0;
}

