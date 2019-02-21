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
#define MAXN 5010
#define gc getchar_unlocked // ou usar sÃ³ getchar
 
void scanint(int &x)
{
	register int c = gc();
	x = 0;
	for(;(c<48 || c>57);c = gc());
	for(;c>47 && c<58;c = gc()) {x = (x<<1) + (x<<3) + c - 48;}
}
 
int v[MAXN];
ll dp[2][MAXN];
int cost[MAXN][MAXN];
int n, k;
void build(){
	int oor;
	for (int i = 1; i <= n; i++)
	{
		oor = 0;
		for (int j = i; j <= n; j++)
		{
			oor |= v[j];
			cost[i][j] = oor;
			//~ cout << oor << endl;
			//~ printf("cost[%d][%d] = %d\n", i, j, cost[i][j]);
		}
	}
	//~ oioi;
}
 
void calc(int K, int l, int r, int optL, int optR){
	if(r < l) return;
	int mid = (l+r)/2;
	int best = -1;
	dp[K&1][mid] = -1;
	
	int lim = min(mid-1, optR);
	//~ for (int i = optL; i <= lim; i++)
	//~ {
		//~ if(dp[K&1][mid] < dp[(K-1)&1][i] + cost[i+1][mid]){
			//~ dp[K&1][mid] = dp[(K-1)&1][i] + cost[i+1][mid];
			//~ best = i;
		//~ }
	//~ }
	ll c = 0;
	for (int i = lim+1; i <= mid; i++)
	{
		c|=v[i];
	}
	

	for (int i = lim; i >= optL; i--)
	{
	
		if(dp[K&1][mid] < 0LL + dp[(K-1)&1][i] + c){
			dp[K&1][mid] = 0LL + dp[(K-1)&1][i] + c;
			best = i;
		}
		c|=v[i];
	}
	calc(K, l, mid-1, optL, best);
	calc(K, mid+1, r, best, optR);
}
 
int main () {
	
	ios_base::sync_with_stdio (0);
	cin.tie (0);
	int tc;
	//~ cin >> tc;
	scanint(tc);
	while (tc--)
	{
		scanint(n);
		scanint(k);
		//~ cin >> n >> k;
		for (int i = 1; i <= n; i++)
		{
			//~ cin >> v[i];
			scanint(v[i]);
		}
		//~ oioi;
		//~ build();
		
		dp[1][0] = 0;
		for (int pos = 1; pos <= n; pos++)
		{
			dp[1&1][pos] = dp[1&1][pos-1] | v[pos];
			//~ cout << dp[1][pos] << " ";
		}
		//~ cout << endl;
		
		for (int K = 2; K <= k; K++)
		{
			calc(K, 1, n, 1, n);
			//~ for (int pos = 1; pos <= n; pos++)
			//~ {
				//~ dp[K][pos] = -1e9;
				//~ for (int i = 1; i < pos; i++)
				//~ {
					//~ dp[K][pos] = max(dp[K][pos], dp[K-1][i] + cost[i+1][pos]);
				//~ }
			//~ }
			
		}
		//~ for (int i = 1; i <= k; i++)
		//~ {
			//~ for (int j = 1; j <= n; j++)
			//~ {
				//~ cout << dp[i][j] << " ";
			//~ }
			//~ cout << endl;
		//~ }
		
		//~ cout << dp[k&1][n] << "\n";
		printf("%lld\n", dp[k&1][n]);
	}
	
		
	return 0;
}
 
